#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "supermercado/supermercado.h"
#include "uteis/uteis.h"

#define FICHEIRO_PRODUTOS "dados/produtos.txt"
#define FICHEIRO_CLIENTES "dados/clientes.txt"
#define FICHEIRO_FUNCIONARIOS "dados/funcionarios.txt"
#define FICHEIRO_DADOS "dados/Dados.txt"
#define FICHEIRO_CONFIGURACAO "dados/Configuracao.txt"

static void executar_aplicacao(Supermercado *supermercado)
{
    while (!Supermercado_E_Para_Fechar(supermercado))
    {
        ExecutarSimulacao(supermercado);
        wait_segundos(1);
    }
}

int main(void)
{
    printf("Projeto ED - 25-26!\n");

    srand((unsigned int)time(NULL));

    Supermercado *supermercado = CriarSupermercado("Lidl");
    if (!supermercado)
    {
        throwError("Erro ao criar o supermercado!\nReinicie o programa e tente novamente.");
        return EXIT_FAILURE;
    }

    if (!InicializarSupermercado(supermercado, FICHEIRO_CLIENTES, FICHEIRO_FUNCIONARIOS, FICHEIRO_PRODUTOS, FICHEIRO_DADOS, FICHEIRO_CONFIGURACAO))
    {
        printf("Erro ao inicializar o supermercado.\n");
        DestruirSupermercado(supermercado);
        return EXIT_FAILURE;
    }

    executar_aplicacao(supermercado);

    DestruirSupermercado(supermercado);
    return EXIT_SUCCESS;
}
