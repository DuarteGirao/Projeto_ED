#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cliente.h"


Cliente* criarCliente(const char *nome) {
    Cliente *c = (Cliente*) malloc(sizeof(Cliente));
    if (!c) return NULL;

    strncpy(c->nome, nome, MAX_NOME);
    c->nome[MAX_NOME - 1] = '\0';

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

void imprimirCliente(Cliente *c) {
    if (!c) 
    {
        printf("Cliente inválido\n");
        return;
    }

    printf("Cliente: %s\n", c->nome);
    imprimirListaProdutos(c->produtos);
}


void apagarCliente(Cliente *c)
{
    if (!c) return;

    esvaziarListaProdutos(c->produtos);
    free(c->produtos);
    c->produtos = NULL;

    free(c);
    c = NULL;
}