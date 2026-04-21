/**
 * @file produto.c
 * @brief Código com as funções dos produtos
 * @version 0.1
 * @date 2026-04-13
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/produto.h"
#include "../headers/uteis.h"

Produto *criarProduto(int id, const char *nome, float preco) {

    Produto *p = (Produto*) malloc(sizeof(Produto));
    strncpy(p->nome, nome, MAX_NOME);
    p->id = id;
    p->nome[MAX_NOME - 1] = '\0';
    p->preco = preco;
    return p;
}

void imprimirProduto(Produto *p) {
    printf("[%d] Produto: %s | Preco: %.2f", p->id, p->nome, p->preco);
}

ListaProdutos *criarListaProdutos()
{
    ListaProdutos *lista = (ListaProdutos*) malloc(sizeof(ListaProdutos));

    if (!lista)
        return NULL;

    lista->inicio= NULL;
    lista->n_itens = 0;

    return lista;
}

void adicionarListaProduto(ListaProdutos *l, Produto *p, int quantidade)
{
    if (!l || !p) return;

    ItemProduto *aux = l->inicio;

    // lista vazia
    if (aux == NULL)
    {
        ItemProduto *novo = malloc(sizeof(ItemProduto));
        if (!novo) return;

        novo->produto = p;
        novo->quantidade = quantidade;
        novo->prox = NULL;

        l->inicio = novo;
        l->n_itens++;
        return;
    }

    ItemProduto *anterior = NULL;

    while (aux != NULL)
    {
        if (aux->produto == p)
        {
            aux->quantidade += quantidade;
            return;
        }
        else if (aux->produto->id == p->id)
        {
            throwError(("2 PRODUTOS DIFERENTES COM O MESMO ID NA FUNCAO [%s]", __FUNCTION__));
        }

        anterior = aux;
        aux = aux->prox;
    }

    ItemProduto *novo = malloc(sizeof(ItemProduto));
    if (!novo) return;

    novo->produto = p;
    novo->quantidade = quantidade;
    novo->prox = NULL;

    anterior->prox = novo;
    l->n_itens++;
}

void imprimirListaProdutos(ListaProdutos *l)
{
    if (!l) 
    {
        printf("Lista inválida\n");
        return;
    }

    printf("Itens: %d\n", l->n_itens);

    ItemProduto *aux = l->inicio;

    while (aux != NULL) {
        imprimirProduto(aux->produto);
        printf(" | Quantidade: %.d\n", aux->quantidade);

        aux = aux->prox;
    }
}

/**
 * @brief Limpa a memoria associada ao produto
 * 
 * @param p Produto a apagar
 * 
 * @warning Nunca usar isto por sí só
 * @warning Nunca apagar um produto que ainda está em listas
 * @warning Em caso de dúvida, não usar
 */
void apagarProduto(Produto *p)
{
    free(p);
}



/**
 * @brief Remove todos os items dentro de uma lista de produtos
 * 
 * @param l -> Lista a esvaziar
 * 
 * @note Não apaga os produtos nem a lista, só remove as referências dos produtos na lista
 * @note Na prática ficamos com uma lista nova
 */
void esvaziarListaProdutos(ListaProdutos *l)
{
    if (!l) return;

    ItemProduto *aux = l->inicio;

    while (aux != NULL)
    {
        ItemProduto *prox = aux->prox;
        free(aux);

        aux = prox;
    }

    l->inicio = NULL;
    l->n_itens = 0;
}


void removerListaProduto(ListaProdutos *l, Produto *p, int quantidade) {
    if (!l || !l->inicio || !p || quantidade <= 0) return;

    ItemProduto *atual = l->inicio;
    ItemProduto *anterior = NULL;

    while (atual != NULL) {
        if (atual->produto == p) {

            atual->quantidade -= quantidade;

            if (atual->quantidade <= 0) {

                if (anterior == NULL) {
                    l->inicio = atual->prox;
                } else {
                    anterior->prox = atual->prox;
                }

                ItemProduto *temp = atual;
                atual = atual->prox;
                free(temp);

                l->n_itens--;
                continue;
            }
        }

        anterior = atual;
        atual = atual->prox;
    }
}


// int encherListaProdutos(ListaProdutos *L)
// {
//     if (!L)
//     {
//         return 0;
//     }
//
//     char *produtos[] = {"leite","agua","pao","arroz","massa","ovos","acucar","sal","azeite","manteiga","queijo","iogurte","frango","carne","atum","cereais","cafe","cha","bolachas","sumo"};
//
//     for (int i = 0; i < 20; i++)
//     {
//         Produto *p = criarProduto(i, produtos[i], (float)numAleatorio(100,1000)/100);
//         adicionarListaProduto(L, p, numAleatorio(5,20));
//     }
//
//     return 1;
// }

ItemProduto *ProcurarProduto(ListaProdutos *l, int id)
{
    if (!l->inicio || id < 0 || !l->inicio->produto) 
        return NULL; 

    ItemProduto *temp = l->inicio;

    while (temp != NULL) 
    {
        if (temp->produto->id == id) 
        {
            return temp;
        }
        temp = temp->prox;
    }

    return NULL;
}


void destruirListaProdutos(ListaProdutos *l)
{
    if (!l) return;

    ItemProduto *atual = l->inicio;

    while (atual)
    {
        ItemProduto *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    free(l);
}

//------------------------------Hashing


int gethash(int id) 
{
    return id % TAMANHO_HASHING;
}


void inserirHash(HashingProdutos *h, Produto *p, int quantidade) 
{
    if (!h || !p || quantidade <=0)
    {
        return;
    }
    
    int indice = gethash(p->id);

    adicionarListaProduto(h->tabela[indice], p, quantidade);
}

ItemProduto* procurarHash(HashingProdutos *h, int id) 
{
    int indice = gethash(id);

    if (!h || !h->tabela[indice])
    {
        return NULL;
    }

    //TODO: usar àrvores
    return ProcurarProduto(h->tabela[indice], id);

}

HashingProdutos *inicializarHash() 
{
    HashingProdutos *h = (HashingProdutos*) malloc(sizeof(HashingProdutos));

    if (!h)
    {
        return NULL;
    }

    for (int i = 0; i < TAMANHO_HASHING; i++) 
    {
        h->tabela[i] = criarListaProdutos();
        if (!h->tabela[i])
        {
            printf("ERRO ao criar lista do hashing nº [%d]\n", i);
            return NULL;
        }
        
    }

    return h;
}

void destruirHash(HashingProdutos *h)
{
    if (!h) return;

    for (int i = 0; i < TAMANHO_HASHING; i++)
    {
        if (h->tabela[i])
            destruirListaProdutos(h->tabela[i]);
    }

    free(h);
}

void listarHash(HashingProdutos *h)
{
    if (!h) return;
    for (int i = 0; i < TAMANHO_HASHING; i++)
    {
        printf("\n\nHash nº[%d]",i);
        imprimirListaProdutos(h->tabela[i]);
    }

}