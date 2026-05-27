#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// #include "headers/produto.h"
// #include "headers/cliente.h"
#include "headers/supermercado.h"

#include "headers/uteis.h"


#define FICHEIRO_PRODUTOS "dados/produtos.txt"
#define FICHEIRO_CLIENTES "dados/clientes.txt"
#define FICHEIRO_FUNCIONARIOS "dados/funcionarios.txt"

#define FICHEIRO_DADOS "dados/Dados.txt"
#define FICHEIRO_CONFIGURACAO "dados/Configuracao.txt"


int Menu()
{
    printf("1 - Listar dados\n");

    printf("\n0 - Sair\n");
    
    int OP = LerInteiro("Qual a Opcao? ");
    return OP;
}

void showCliente(void *d) {
    Cliente *c = (Cliente*)d;
    imprimirCliente(c, 0);
}

void MenuListar(Supermercado *S)
{
    printf("\n--------Menu Listar--------\n");
    printf("1 - Listar Clientes\n");
    printf("2 - Listar Produtos\n");
    printf("3 - Listar Funcionários\n");
    printf("4 - Listar Caixas\n");

    printf("\n5 - Listar Configurações\n");

    printf("\n0 - Sair\n");
    
    switch (LerInteiro("Qual a Opcao? "))
    {
        case 1:
            listarHashClientes_paginado(S->H_Clientes, 10);
            break;

        case 2:
            listarHashProdutos_paginado(S->H_Produtos, 10);
            break;

        case 3:
            imprimirListaPessoas_paginado(S->L_funcionarios, 10);
            break;

        case 4:
            printf("\nTODO: Listar caixas\n");
            break;

            

        case 5:
            printf("\nConfigurações:\n");
            printf("\tMAX_ESPERA: %.2f\n", S->max_espera);
            printf("\tN_CAIXAS: %d\n", S->n_caixas);
            printf("\tTEMPO_ATENDIMENTO_PRODUTO: %.2f\n", S->tempo_atendimento_produto);
            printf("\tMAX_PRECO: %.2f\n", S->max_preco);
            printf("\tMAX_FILA: %d\n", S->max_fila);
            printf("\tMIN_FILA: %d\n\n", S->min_fila);
            break;
        
        default:
            break;
    }
}



void ExecutaAccoesMenu(Supermercado *S)
{

    int OP;
    do
    {
        printf("\n--------Menu Principal--------\n");
        OP = Menu();
        switch(OP)
        {
            case 1: MenuListar(S);
                    break;

            case 0: break;

            default:
                printf("Erro na opção escolhida!\n");
                break;
        }
    } while (OP != 0);

    printf("Saiu do menu.\n");
    

}


long long diff_ms(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000LL +
           (end.tv_nsec - start.tv_nsec) / 1000000LL;}


int transferirStock(HashingProdutos *HashStock, Cliente *C, int id, int quantidade)
{
    if (!HashStock || !C || id<0 || quantidade <=0)
    {
        return 0;
    }

    ItemProduto *item = procurarHashProdutos(HashStock, id);

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


int main() 
{
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
    // HashingProdutos *StockProdutos = inicializarHashProdutos();
    // if (!StockProdutos)
    // {
    //     printf("ERRO ao criar hashing");
    //     return 0;
    // }




    //listarHash(StockProdutos);


    
    // destruirHashProdutos(StockProdutos);


    // int x = LerInteiro("introduza um número: ");
    // printf("[%d]\n",x);

    // for (int i = 'a'; i <= 'z'; i++)
    // {
    //     printf("[%c]\n",ToMaiscula(i));
    // }


    //############################ TESTES ############################
	
	
    printf("Projeto ED - 25-26!\n");
    
    //Cria uma nova seed aleatória, de forma que a função rand() gere números novos todas as execuções
    srand(time(NULL));


    Supermercado *Lidl = CriarSupermercado("Lidal");
    if (!Lidl)
    {
        throwError("Erro ao criar o supermercado!\nReinicie o programa e tente novamente.");
    }

    printf("A carregar dados\n");
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    InicializarSupermercado(Lidl, FICHEIRO_CLIENTES, FICHEIRO_FUNCIONARIOS, FICHEIRO_PRODUTOS, FICHEIRO_DADOS, FICHEIRO_CONFIGURACAO);

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Tempo para carregar dados: %lld ms\n\n\n", diff_ms(start, end));

    //imprimirListaPessoas(Lidl->L_funcionarios);
    //listarHashClientes(Lidl->H_Clientes);
    //listarHashProdutos(Lidl->H_Produtos);


    // printf("MAX_ESPERA: %f\n",Lidl->max_espera);
    // printf("N_CAIXAS: %d\n",Lidl->n_caixas);
    // printf("TEMPO_ATENDIMENTO_PRODUTO: %f\n",Lidl->tempo_atendimento_produto);
    // printf("MAX_PRECO: %f\n",Lidl->max_preco);
    // printf("MAX_FILA: %d\n",Lidl->max_fila);
    // printf("MIN_FILA: %d\n",Lidl->min_fila);



    printf("Bem vindo ao simulador\n");
    ExecutaAccoesMenu(Lidl);
    printf("A sair do programa.\n");





    // int Terminar = 0;
    int Terminar = 1;
    while (!Terminar)
    {
        if (TeclaPressionada())
        {
            ExecutaAccoesMenu(Lidl);
        }
        ExecutarSimulacao(Lidl);
        wait_segundos(1);
        Terminar = Supermercado_E_Para_Fechar(Lidl);
    }
    DestruirSupermercado(Lidl);


    
    


    return 0;
}
