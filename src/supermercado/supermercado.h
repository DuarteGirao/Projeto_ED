#ifndef SUPERMERCADO_H_INCLUDED
#define SUPERMERCADO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "../pessoas/pessoa.h"
#include "../clientes/cliente.h"
#include "../produtos/produto.h"
#include "../relogio/relogio.h"
#include "../uteis/uteis.h"
#include "../caixas/caixa.h"

//esta constante, quando é 1, obriga os valores a estarem nos seus intrevalos definidos.
//caso contrário só envia um aviso para o ficheiro das logs
#define OBRIGAR_LIMITES 1

typedef struct
{
    char *NOME;
    int CadenciaEntradaClientes;
    float max_espera;
    int n_caixas;
    float tempo_atendimento_produto;
    float max_preco;
    int max_fila;
    int min_fila;
    

    HashingClientes *H_Clientes;
    HashingProdutos *H_Produtos;
    ListaPessoas *L_funcionarios;
    Caixa *Caixas;

    //HoraInicio, HoraFim;
    Relogio *Rolex;
}Supermercado;

Supermercado *CriarSupermercado(char *nome);
int CarregarProdutos(Supermercado *S, const char *nf);
int CarregarClientes(Supermercado *S, const char *nf);
int CarregarFuncionarios(Supermercado *S, const char *nf);

int CarregarDados(Supermercado *S, const char *fich_clientes, 
    const char *fich_funcionarios, const char *fich_produtos, 
    const char *fich_dados, const char *fich_configs);
int InicializarSupermercado(Supermercado *S, const char *fich_clientes, 
    const char *fich_funcionarios, const char *fich_produtos, 
    const char *fich_dados, const char *fich_configs);
int ExecutarSimulacao(Supermercado *S);
void EntradaPessoaSupermercado(Supermercado *S);
int Supermercado_E_Para_Fechar(Supermercado *S);
void DestruirSupermercado(Supermercado *S);
void EstadoPagamentoIrCaixa(Supermercado *S);


#endif // SUPERMERCADO_H_INCLUDED