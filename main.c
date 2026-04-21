#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#include "headers/produto.h"
#include "headers/cliente.h"

#include "headers/uteis.h"


#define FICHEIRO_PRODUTOS "dados/produtos.txt"

long long diff_ms(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000LL +
           (end.tv_nsec - start.tv_nsec) / 1000000LL;}


int transferirStock(HashingProdutos *HashStock, Cliente *C, int id, int quantidade)
{
    if (!HashStock || !C || id<0 || quantidade <=0)
    {
        return 0;
    }

    ItemProduto *item = procurarHash(HashStock, id);

    if (item && item->quantidade >0)
    {
        //Há mais stock do que o pedido
        if (item->quantidade >= quantidade)
        {
            item->quantidade -= quantidade;
            adicionarListaProduto(C->produtos, item->produto, quantidade);
            return 1;
        }

        //Há menos stock do que o pedido
        else
        {
            adicionarListaProduto(C->produtos, item->produto, item->quantidade);
            quantidade -= item->quantidade;
            item->quantidade = 0;
            printf("O stock do produto [%d][%s] ficou a 0!\n", item->produto->id,item->produto->nome);
            printf("O cliente ainda queria mais [%d]\n", quantidade);
            return 1;
        }
        
    }
    else
    {
        printf("Item não encontrado ou fora de stock!\n");
    }
    return 1;
}

int carregarDadosProdutos(const char *nf, HashingProdutos *hashProdutos)
{
    FILE *f = fopen(nf, "r");

    if (f == NULL) {
        printf("Erro ao abrir ficheiro!\n");
        return 0;
    }
    char linha[256];

    int id;
    char nome[100];
    float preco, extra1, extra2;

    while (fgets(linha, sizeof(linha), f)) 
    {

        sscanf(linha, "%d\t%[^\t]\t%f\t%f\t%f",
               &id, nome, &preco, &extra1, &extra2);

        Produto *p = criarProduto(id, nome, preco);
        inserirHash(hashProdutos, p, numAleatorio(5,20));
    }

    fclose(f);
    return 1;
}

int main() 
{
    #ifdef _WIN32
    setlocale(LC_ALL, "Portuguese_Portugal.1252");
    #else
    setlocale(LC_ALL, "pt_PT.UTF-8");
    #endif

    srand(time(NULL));

    //############################ TESTES ############################

    // {

    //     printf("\nCliente\n");
    //     Cliente *pere = criarCliente("Pereira");
    //     transferirStock(StockProdutos, pere, StockProdutos->inicio->prox->produto,5);
    //     imprimirCliente(pere);
    //     printf("\n");
    //     imprimirListaProdutos(StockProdutos);


    //     printf("\n(1)\n");
    //     Produto *p = criarProduto(300, "Leite", 1.99);
    //     imprimirProduto(p);

    //     printf("\n(2)\n");
    //     ListaProdutos *lp = criarListaProdutos();
    //     adicionarListaProduto(lp, p, 2);
    //     imprimirListaProdutos(lp);
        
    //     printf("\n(3)\n");
    //     //Produto *p2 = criarProduto("Agua", 3.99);
    //     // adicionarItemProduto(&lp, &p2);
    //     p = criarProduto(301, "Agua", 3.99);
    //     adicionarListaProduto(lp, p, 5);
    //     imprimirListaProdutos(lp);

    //     printf("\n(4)\n");
    //     //Produto *p2 = criarProduto("Agua", 3.99);
    //     // adicionarItemProduto(&lp, &p2);
    //     //apagarProduto(p);
    //     imprimirListaProdutos(lp);
    //     printf("\n\tlista esvaziada, mas não apagada\n");
    //     esvaziarListaProdutos(lp);
    //     imprimirListaProdutos(lp);
    //     printf("\n\tvoltar a adicionar\n");
    //     adicionarListaProduto(lp, p, 4);
    //     imprimirListaProdutos(lp);


    //     printf("\n(5)\n");
    //     Cliente *c = criarCliente("Helder");
    //     imprimirCliente(c);

    //     printf("\n\tproduto adicionado\n");
    //     adicionarProdutoCliente(c, p, 3);
    //     imprimirCliente(c);

    //     printf("\n\tlista esvaziada, mas não apagada\n");
    //     esvaziarListaProdutos(c->produtos);
    //     imprimirCliente(c);

    //     printf("\n\tvoltar a adicionar\n");
    //     adicionarProdutoCliente(c, p, 1);
    //     imprimirCliente(c);

    //     printf("\n\tapagar cliente\n");
    //     apagarCliente(c);
    //     imprimirCliente(c);
    //     printf("\n\tC=NULL\n");
    //     c=NULL;
    //     imprimirCliente(c);



    //     printf("\n(6)\n");
    //     p = criarProduto(305, "teto", 3);
    //     adicionarListaProduto(lp, p, 5);
    //     p = criarProduto(302, "Agua", 3.99);
    //     adicionarListaProduto(lp, p, 2);
    //     p = criarProduto(303, "uvas", 2);
    //     adicionarListaProduto(lp, p, 5);
    //     imprimirListaProdutos(lp);

    //     printf("\nRemover 2 uvas\n");
    //     removerListaProduto(lp, p, 2);
    //     imprimirListaProdutos(lp);


    //     printf("\nRemover 99 agua \n");
    //     p = criarProduto(302, "Agua", 8.99);
    //     removerListaProduto(lp, p, 99);
    //     imprimirListaProdutos(lp);
    // }



    //hashing
    HashingProdutos *StockProdutos = inicializarHash();
    if (!StockProdutos)
    {
        printf("ERRO ao criar hashing");
        return 0;
    }



    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    carregarDadosProdutos(FICHEIRO_PRODUTOS, StockProdutos);

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Tempo para carregar dados: %lld ms\n", diff_ms(start, end));

    //listarHash(StockProdutos);


    
    destruirHash(StockProdutos);
    
    //############################ TESTES ############################
    return 0;
}
