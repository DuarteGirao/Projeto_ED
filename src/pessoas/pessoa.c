#include <stdlib.h>
#include <string.h>

#include "pessoa.h"


Pessoa* criarPessoa(int id, const char *nome) {
    Pessoa *p = (Pessoa*) malloc(sizeof(Pessoa));
    if (!p || id<=0) return NULL;

    strncpy(p->nome, nome, MAX_NOME);
    p->nome[MAX_NOME - 1] = '\0';

    p->id=id;
    
    return p;
}


void apagarPessoa(Pessoa *p)
{
    if (!p) return;

    free(p);
}

void imprimirPessoa(Pessoa *p)
{
    if (!p) 
    {
        printf("Pessoa inválida\n");
        return;
    }

    printf("[%d] %s",p->id, p->nome);
}

//-----------------------Listas
ListaPessoas *criarListaPessoas()
{
    ListaPessoas *lista = (ListaPessoas*) malloc(sizeof(ListaPessoas));

    if (!lista)
        return NULL;

    lista->inicio= NULL;
    lista->n_pessoas = 0;

    return lista;
}

void adicionarListaPessoa(ListaPessoas *l, Pessoa *p)
{
    if (!l || !p) return;

    ItemPessoa *aux = l->inicio;

    // lista vazia
    if (aux == NULL)
    {
        ItemPessoa *novo = malloc(sizeof(ItemPessoa));
        if (!novo) return;

        novo->pessoa = p;
        novo->prox = NULL;

        l->inicio = novo;
        l->n_pessoas++;
        return;
    }

    ItemPessoa *anterior = NULL;

    while (aux != NULL)
    {
        if (aux->pessoa->id == p->id)
        {
            throwError("2 PESSOAS DIFERENTES COM O MESMO ID NA FUNCAO [adicionarListaPessoa]");
        }

        anterior = aux;
        aux = aux->prox;
    }

    ItemPessoa *novo = malloc(sizeof(ItemPessoa));
    if (!novo) return;

    novo->pessoa = p;
    novo->prox = NULL;

    anterior->prox = novo;
    l->n_pessoas++;
}

void imprimirListaPessoas(ListaPessoas *l)
{
    if (!l) 
    {
        printf("Lista inválida\n");
        return;
    }

    printf("Nº pessoas: %d\n", l->n_pessoas);

    ItemPessoa *aux = l->inicio;

    while (aux != NULL) {
        imprimirPessoa(aux->pessoa);
        
        aux = aux->prox;
    }
    printf("\n");
}



void esvaziarListaPessoas(ListaPessoas *l)
{
    if (!l) return;

    ItemPessoa *aux = l->inicio;

    while (aux != NULL)
    {
        ItemPessoa *prox = aux->prox;
        free(aux);

        aux = prox;
    }

    l->inicio = NULL;
    l->n_pessoas = 0;
}


void removerListaPessoa(ListaPessoas *l, Pessoa *p)
{
    if (!l || !l->inicio || !p) return;

    ItemPessoa *atual = l->inicio;
    ItemPessoa *anterior = NULL;

    while (atual != NULL) 
    {
        if (atual->pessoa == p) 
        {

            if (anterior == NULL) 
            {
                l->inicio = atual->prox;
            } 
            else 
            {
                anterior->prox = atual->prox;
            }

            ItemPessoa *temp = atual;
            atual = atual->prox;
            free(temp);

            l->n_pessoas--;
            continue;
        }

        anterior = atual;
        atual = atual->prox;
    }
}

ItemPessoa *ProcurarListaPessoa(ListaPessoas *l, int id)
{
    if (!l->inicio || id < 0 || !l->inicio->pessoa) 
        return NULL; 

    ItemPessoa *temp = l->inicio;

    while (temp != NULL) 
    {
        if (temp->pessoa->id == id) 
        {
            return temp;
        }
        temp = temp->prox;
    }

    return NULL;
}

void destruirListaPessoas(ListaPessoas *l)
{
    if (!l) return;

    ItemPessoa *atual = l->inicio;

    while (atual)
    {
        ItemPessoa *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    free(l);
}