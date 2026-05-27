
#include "../headers/supermercado.h"

extern int Aleatorio(int min, int max);

//---------------------------------------------

Supermercado *CriarSupermercado(char *nome)
{
    Supermercado *S = (Supermercado *)malloc(sizeof(Supermercado));
    if (!S)
    {
        return NULL;
    }
    
    S->NOME = nome;

    //Valores default, útil caso quando forem carregadas as configs, estes dados estejam em falta
     S->max_espera = 120; 
     S->n_caixas = 6;
     S->tempo_atendimento_produto = 6;
     S->max_preco = 40;
     S->max_fila = 7;
     S->min_fila = 3;

    S->Rolex = CriarRelogio(10);

    S->H_Produtos = inicializarHashProdutos();
    S->H_Clientes = inicializarHashClientes();
    S->L_funcionarios = criarListaPessoas();

    //Como o número de caixas não muda ao longo da simulação, usamos um array.
    //Como ainda não carregamos o ficheiro de configurações, não sabemos quantas caixas são
    S->Caixas = NULL;
    return S;
}

int CarregarProdutos(Supermercado *S, const char *nf)
{
    DebugPrint(__FUNCTION__,"");

    FILE *f = fopen(nf, "r");

    if (f == NULL) {
        printf("Erro ao abrir ficheiro! [%s]\n", nf);
        return 0;
    }
    char linha[256];

    int id;
    char nome[100];
    float preco, tempoCompra, tempoCaixa;

    while (fgets(linha, sizeof(linha), f)) 
    {

        sscanf(linha, "%d\t%[^\t]\t%f\t%f\t%f",
               &id, nome, &preco, &tempoCompra, &tempoCaixa);
        
        if (preco > S->max_preco)
        {
            char str[20];
            sprintf(str, "id: %d", id);
            loggar("Preço do produto maior que o máximo permitido!", str);
            if (OBRIGAR_LIMITES)
            {
                preco = S->max_preco;
            }
            
        }
        else if (preco <= 0)
        {
            char str[20];
            sprintf(str, "id: %d", id);
            loggar("Preço do produto menor que o mínimo permitido!", str);
            if (OBRIGAR_LIMITES)
            {
                preco = 1;
            }
            
        }
        

        Produto *p = criarProduto(id, nome, preco, tempoCompra, tempoCaixa);
        inserirHashProdutos(S->H_Produtos, p, Aleatorio(5,20));
    }

    fclose(f);
    return 1;
}

int CarregarClientes(Supermercado *S, const char *nf)
{
    DebugPrint(__FUNCTION__,"");

    FILE *f = fopen(nf, "r");

    if (f == NULL) {
        printf("Erro ao abrir ficheiro! [%s]\n", nf);
        return 0;
    }
    char linha[256];

    int id;
    char nome[100];

    while (fgets(linha, sizeof(linha), f)) 
    {

        sscanf(linha, "%d\t%[^\t]",
               &id, nome);

        Cliente *c = criarCliente(id, nome);
        inserirHashClientes(S->H_Clientes, c);
    }

    fclose(f);
    return 1;
}

int CarregarFuncionarios(Supermercado *S, const char *nf)
{
    DebugPrint(__FUNCTION__,"");

    FILE *f = fopen(nf, "r");

    if (f == NULL) {
        printf("Erro ao abrir ficheiro! [%s]\n", nf);
        return 0;
    }
    char linha[256];

    int id;
    char nome[100];

    while (fgets(linha, sizeof(linha), f)) 
    {

        sscanf(linha, "%d\t%[^\t]",
               &id, nome);

        Pessoa *p = criarPessoa(id, nome);
        adicionarListaPessoa(S->L_funcionarios, p);
    }

    fclose(f);
    return 1;
}

int CarregarConfiguracoes(Supermercado *S, const char *nf)
{
    DebugPrint(__FUNCTION__,"");

    FILE *f = fopen(nf, "r");

    if (f == NULL) {
        printf("Erro ao abrir ficheiro! [%s]\n", nf);
        //TODO: Usar dados default
        return 0;
    }
    char linha[256];
    char nome[20];
    float valor;

    while (fgets(linha, sizeof(linha), f)) 
    {

        sscanf(linha, "%s %f",
               nome, &valor);

        //printf("[%s][%f]\n", nome, valor);

        if (!strcmp(nome, "MAX_ESPERA"))
            S->max_espera = valor;
        
        else if (!strcmp(nome, "N_CAIXAS"))
            S->n_caixas = (int)valor;
        
        else if (!strcmp(nome, "TEMPO_ATENDIMENTO_PRODUTO"))
            S->tempo_atendimento_produto = valor;
        
        else if (!strcmp(nome, "MAX_PRECO"))
            S->max_preco = valor;
        
        else if (!strcmp(nome, "MAX_FILA"))
            S->max_fila = (int)valor;
        
        else if (!strcmp(nome, "MIN_FILA"))
            S->min_fila = (int)valor;
        
        else
            printf("Configuração inválida [%s][%f]\n", nome, valor);
            
    }

    fclose(f);

    //Agora que sabemos quantas caixas há, inicializam-se as caixas
    S->Caixas = malloc(S->n_caixas * sizeof(Caixa));
    if (!S->Caixas)
    {
        DebugPrint(__FUNCTION__,"Erro ao iniciar as caixas");
        return 0;
    }

    return 1;
}

int CarregarDadosSimulacao(Supermercado *S, const char *nf)
{
    DebugPrint(__FUNCTION__, "TODO");  //TODO
    return 1;
}

int CarregarDados(Supermercado *S, const char *fich_clientes, 
    const char *fich_funcionarios, const char *fich_produtos, 
    const char *fich_dados, const char *fich_configs)
{
    DebugPrint(__FUNCTION__, "A carregar dados");


    if(!CarregarConfiguracoes(S, fich_configs))
        printf("Erro a carregar as configurações!\n");


    if(!CarregarProdutos(S, fich_produtos))
        printf("Erro a carregar os produtos!\n");

    if(!CarregarClientes(S, fich_clientes))
        printf("Erro a carregar os clientes!\n");

    if(!CarregarFuncionarios(S, fich_funcionarios))
        printf("Erro a carregar os funcionarios!\n");

    
    if(!CarregarDadosSimulacao(S, fich_dados))
        printf("Erro a carregar os dados da simulação!\n");

    DebugPrint(__FUNCTION__,"Dados carregados");
}

int InicializarSupermercado(Supermercado *S, const char *fich_clientes, 
    const char *fich_funcionarios, const char *fich_produtos, 
    const char *fich_dados, const char *fich_configs)
{
    CarregarDados(S, fich_clientes, fich_funcionarios, fich_produtos, fich_dados, fich_configs);
    //TODO
    // S->HoraInicio = 8;
    S->CadenciaEntradaClientes = 30;
    return 1;
}

int ExecutarSimulacao(Supermercado *S)
{
    printf("Estou a trabalhar...\n");
    EntradaPessoaSupermercado(S);

    EstadoPagamentoIrCaixa(S);

    return 1;
}

/*
int IrCaixa(Pessoa *P, Supermercado *S)
{
    //time_t T = GetTempo(S->Rolex);
    //Se (T >=  gfdglkfdglkfdg)
    //    return 1;
    return 0;
}
*/

void EstadoPagamentoIrCaixa(Supermercado *S)
{
    //Para todas as Pessoas P da S->LClientes
    //    Se (IrCaixa(P, S))
        {
            // Escolher Caixa e Retirar essa pessoa de S->Clientes
            // e ir para o Hashing das Caixas
        }
}

void EntradaPessoaSupermercado(Supermercado *S)
{
    int X = Aleatorio(0, 100);
    //printf("X = %d\n", X);
    if (X < S->CadenciaEntradaClientes)
    {
        //Pessoa *P = CriarPessoa();
        //AddLista(S->LCliente, P);
        printf("Mais um Cliente a Entrar!\n");
    }
    //---------------------
}

int Supermercado_E_Para_Fechar(Supermercado *S)
{
        //... fazer
    return 0;
}

void DestruirSupermercado(Supermercado *S)
{
    free(S->Rolex);
    free(S);

    //TODO
    //Destruir caixas
    //Destruir clientes
    //Destruir Produtos
}
