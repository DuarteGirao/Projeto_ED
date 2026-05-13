#ifndef CLIENTE_H
#define CLIENTE_H

#include "../produtos/produto.h"
#include "../pessoas/pessoa.h"
#include <time.h>
#include "../uteis/uteis.h"

typedef struct Cliente {
    Pessoa *pessoa;

    ListaProdutos *produtos;
    time_t tempo_entrada;

} Cliente;

typedef struct ItemCliente{
    Cliente *cliente;
    
    struct ItemCliente *prox;
} ItemCliente;

typedef struct {
    ItemCliente *inicio;
    int n_clientes;
} ListaClientes;

typedef struct {
    ListaClientes *tabela[TAMANHO_HASHING];
} HashingClientes;


//----------------Funções
Cliente* criarCliente(int id, const char *nome);
void adicionarProdutoCliente(Cliente *c, Produto *p, int quantidade);
void imprimirCliente(Cliente *c, int mostrarProdutos);
void apagarCliente(Cliente *c);


//Listas
ListaClientes *criarListaClientes();
void adicionarListaCliente(ListaClientes *l, Cliente *c) ;
void imprimirListaClientes(ListaClientes *l);
void removerListaCliente(ListaClientes *l, Cliente *c);
void esvaziarListaClientes(ListaClientes *l);
ItemCliente *ProcurarListaCliente(ListaClientes *l, int id);
void destruirListaClientes(ListaClientes *l);

//Hashing
int getHashClientes(int id);
HashingClientes *inicializarHashClientes();
void inserirHashClientes(HashingClientes *h, Cliente *c);
ItemCliente* procurarHashClientes(HashingClientes *h, int id);
void destruirHashClientes(HashingClientes *h);
void listarHashClientes(HashingClientes *h);

#endif