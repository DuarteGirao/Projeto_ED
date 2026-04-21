#ifndef CLIENTE_H
#define CLIENTE_H

#include "produto.h"
#include <time.h>

#define MAX_NOME 50

typedef struct Cliente {
    char nome[MAX_NOME];

    ListaProdutos *produtos;
    time_t tempo_entrada;

} Cliente;



// Funções
Cliente* criarCliente(const char *nome);
void adicionarProdutoCliente(Cliente *c, Produto *p, int quantidade);
void imprimirCliente(Cliente *c);
void apagarCliente(Cliente *c);

#endif
