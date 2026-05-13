#ifndef CAIXA_H
#define CAIXA_H

#include "../clientes/cliente.h"

typedef struct 
{
    Pessoa funcionario;
    ListaClientes clientes;
} Caixa;

void inicializarCaixa(Caixa *caixa);
void imprimirCaixa(Caixa *c);
void adicionarClienteCaixa(Cliente *cliente, Caixa *caixa);
void removerClienteCaixa(Cliente *cliente, Caixa *caixa);


#endif