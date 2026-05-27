#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cliente.h"


Cliente* criarCliente(int id, const char *nome) {
    if (!strcmp(nome,""))
    {
        //TODO: Procurar no hashing se já não existe um cliente com o mesmo ID
        return NULL;
    }
    
    Cliente *c = (Cliente*) malloc(sizeof(Cliente));
    if (!c) return NULL;

    c->pessoa = criarPessoa(id, nome);

    c->produtos = criarListaProdutos();

    c->tempo_entrada = time(NULL);

    return c;
}

void adicionarProdutoCliente(Cliente *c, Produto *p, int quantidade) {
    if (!c || !p || quantidade <= 0) return;

    if (!c->produtos)
        c->produtos = criarListaProdutos();
    

    adicionarListaProduto(c->produtos, p, quantidade);
}

void imprimirCliente(Cliente *c, int mostrarProdutos) {
    if (!c) 
    {
        printf("Cliente inválido\n");
        return;
    }

    printf("Cliente:");
    imprimirPessoa(c->pessoa);
    
    if (mostrarProdutos)
    {
        printf("\n");
        imprimirListaProdutos(c->produtos);
    }
    
}


void apagarCliente(Cliente *c)
{
    if (!c) return;

    esvaziarListaProdutos(c->produtos);
    free(c->produtos);
    c->produtos = NULL;

    apagarPessoa(c->pessoa);
    c->pessoa = NULL;

    free(c);
    c = NULL;
}

//-----------------------Listas
ListaClientes *criarListaClientes()
{
    ListaClientes *lista = (ListaClientes*) malloc(sizeof(ListaClientes));

    if (!lista)
        return NULL;

    lista->inicio= NULL;
    lista->n_clientes = 0;

    return lista;
}

void adicionarListaCliente(ListaClientes *l, Cliente *c)
{
    if (!l || !c) return;

    ItemCliente *aux = l->inicio;

    // lista vazia
    if (aux == NULL)
    {
        ItemCliente *novo = malloc(sizeof(ItemCliente));
        if (!novo) return;

        novo->cliente = c;
        novo->prox = NULL;

        l->inicio = novo;
        l->n_clientes++;
        return;
    }

    ItemCliente *anterior = NULL;

    while (aux != NULL)
    {
        if (aux->cliente->pessoa->id == c->pessoa->id)
        {
            throwError("2 CLIENTES DIFERENTES COM O MESMO ID NA FUNCAO [adicionarListaCliente]");
        }

        anterior = aux;
        aux = aux->prox;
    }

    ItemCliente *novo = malloc(sizeof(ItemCliente));
    if (!novo) return;

    novo->cliente = c;
    novo->prox = NULL;

    anterior->prox = novo;
    l->n_clientes++;
}

void imprimirListaClientes(ListaClientes *l)
{
    if (!l) 
    {
        printf("Lista inválida\n");
        return;
    }

    printf("Nº clientes: %d\n", l->n_clientes);

    ItemCliente *aux = l->inicio;

    while (aux != NULL) {
        imprimirCliente(aux->cliente, 0);

        aux = aux->prox;
    }
}



/**
 * @brief Remove todos os clientes dentro de uma lista de clientes
 * 
 * @param l -> Lista a esvaziar
 * 
 * @note Não apaga os clientes nem a lista, só remove as referências dos clientes na lista
 * @note Na prática ficamos com uma lista nova
 */
void esvaziarListaClientes(ListaClientes *l)
{
    if (!l) return;

    ItemCliente *aux = l->inicio;

    while (aux != NULL)
    {
        ItemCliente *prox = aux->prox;
        free(aux);

        aux = prox;
    }

    l->inicio = NULL;
    l->n_clientes = 0;
}


void removerListaCliente(ListaClientes *l, Cliente *c) 
{
    if (!l || !l->inicio || !c) return;

    ItemCliente *atual = l->inicio;
    ItemCliente *anterior = NULL;

    while (atual != NULL) 
    {
        if (atual->cliente == c) 
        {

            if (anterior == NULL) 
            {
                l->inicio = atual->prox;
            } 
            else 
            {
                anterior->prox = atual->prox;
            }

            ItemCliente *temp = atual;
            atual = atual->prox;
            free(temp);

            l->n_clientes--;
            continue;
            }
    }

    anterior = atual;
    atual = atual->prox;
}

//TODO: Usar árvores
ItemCliente *ProcurarListaCliente(ListaClientes *l, int id)
{
    if (!l->inicio || id < 0 || !l->inicio->cliente) 
        return NULL; 

    ItemCliente *temp = l->inicio;

    while (temp != NULL) 
    {
        if (temp->cliente->pessoa->id == id) 
        {
            return temp;
        }
        temp = temp->prox;
    }

    return NULL;
}

/**
 * @brief Destroi todos os dados dentro de uma lista, e depois destroi a lista em sí
 * 
 * @param l - lista a destruir
 * 
 * @note Em principio esta função só será chamada para destruir o hashing clientes quando o programa acabar
 */
void destruirListaClientes(ListaClientes *l)
{
    if (!l) return;

    ItemCliente *atual = l->inicio;

    while (atual)
    {
        ItemCliente *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    free(l);
}


//------------------------------Hashing


int getHashClientes(int id) 
{
    return id % TAMANHO_HASHING;
}


void inserirHashClientes(HashingClientes *h, Cliente *c)
{
    if (!h || !c)
    {
        return;
    }
    
    int indice = getHashClientes(c->pessoa->id);

    adicionarListaCliente(h->tabela[indice], c);
}

ItemCliente* procurarHashClientes(HashingClientes *h, int id)
{
    int indice = getHashClientes(id);

    if (!h || !h->tabela[indice])
    {
        return NULL;
    }

    //TODO: usar àrvores
    return ProcurarListaCliente(h->tabela[indice], id);

}

HashingClientes *inicializarHashClientes()
{
    HashingClientes *h = (HashingClientes*) malloc(sizeof(HashingClientes));

    if (!h)
    {
        return NULL;
    }

    for (int i = 0; i < TAMANHO_HASHING; i++) 
    {
        h->tabela[i] = criarListaClientes();
        if (!h->tabela[i])
        {
            printf("ERRO ao criar lista do hashing nº [%d]\n", i);
            return NULL;
        }
        
    }

    return h;
}

void destruirHashClientes(HashingClientes *h)
{
    if (!h) return;

    for (int i = 0; i < TAMANHO_HASHING; i++)
    {
        if (h->tabela[i])
            destruirListaClientes(h->tabela[i]);
    }

    free(h);
}

void listarHashClientes(HashingClientes *h)
{
    if (!h) return;
    for (int i = 0; i < TAMANHO_HASHING; i++)
    {
        printf("\n\nHash nº[%d]\n",i);
        imprimirListaClientes(h->tabela[i]);
    }

}

static void _showCliente_paginacao(void *d) {
    Cliente *c = (Cliente*)d;
    imprimirCliente(c, 0);
}

void listarHashClientes_paginado(HashingClientes *h, int itemsPerPage) {
    if (!h || itemsPerPage <= 0) return;

    int count = 0;
    for (int i = 0; i < TAMANHO_HASHING; i++) {
        ListaClientes *l = h->tabela[i];
        if (!l) continue;
        ItemCliente *it = l->inicio;
        while (it) { count++; it = it->prox; }
    }

    if (count == 0) { printf("Nenhum cliente registado.\n"); return; }

    void **arr = malloc(sizeof(void*) * count);
    if (!arr) { printf("Erro de memoria.\n"); return; }

    int idx = 0;
    for (int i = 0; i < TAMANHO_HASHING; i++) {
        ListaClientes *l = h->tabela[i];
        if (!l) continue;
        ItemCliente *it = l->inicio;
        while (it) { arr[idx++] = it->cliente; it = it->prox; }
    }

    paginacao(arr, count, itemsPerPage, _showCliente_paginacao);

    free(arr);
}