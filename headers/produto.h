#ifndef PRODUTO_H
#define PRODUTO_H

#define MAX_NOME 50

#define TAMANHO_HASHING 101  


typedef struct {
    int id;
    char nome[MAX_NOME];
    float preco;
    float temppoCompra;
    float tempoCaixa;
} Produto;

typedef struct ItemProduto{
    Produto *produto;
    int quantidade;
    
    struct ItemProduto *prox;
} ItemProduto;

typedef struct {
    ItemProduto *inicio;
    int n_itens;
} ListaProdutos;

typedef struct {
    ListaProdutos *tabela[TAMANHO_HASHING];
} HashingProdutos;

//----------------Funções
//Produtos
Produto *criarProduto(int id, const char *nome, float preco, float temppoCompra, float tempoCaixa);
void imprimirProduto(Produto *p);
void apagarProduto(Produto *p);

//Listas
ListaProdutos *criarListaProdutos();
void adicionarListaProduto(ListaProdutos *l, Produto *p, int quantidade) ;
void imprimirListaProdutos(ListaProdutos *l);
void removerListaProduto(ListaProdutos *l, Produto *p, int quantidade);
void esvaziarListaProdutos(ListaProdutos *l);
// int encherListaProdutos(ListaProdutos *l);
ItemProduto *ProcurarListaProduto(ListaProdutos *l, int id);
void destruirListaProdutos(ListaProdutos *l);

//Hashing
int getHashProdutos(int id);
HashingProdutos *inicializarHashProdutos();
void inserirHashProdutos(HashingProdutos *h, Produto *p, int quantidade);
ItemProduto* procurarHashProdutos(HashingProdutos *h, int id);
void destruirHashProdutos(HashingProdutos *h);
void listarHashProdutos(HashingProdutos *h);
void listarHashProdutos_paginado(HashingProdutos *h, int itemsPerPage);

#endif