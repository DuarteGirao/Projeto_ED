#ifndef PESSOA_H_INCLUDED
#define PESSOA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "uteis.h"

#define MAX_NOME 50

typedef struct Pessoa {
    int id;
    char nome[MAX_NOME];

} Pessoa;

typedef struct ItemPessoa{
    Pessoa *pessoa;
    
    struct ItemPessoa *prox;
} ItemPessoa;

typedef struct {
    ItemPessoa *inicio;
    int n_pessoas;
} ListaPessoas;


Pessoa* criarPessoa(int id, const char *nome);
void apagarPessoa(Pessoa *p);

void imprimirPessoa(Pessoa *p);


//Listas
ListaPessoas *criarListaPessoas();
void adicionarListaPessoa(ListaPessoas *l, Pessoa *p);
void imprimirListaPessoas(ListaPessoas *l);
void esvaziarListaPessoas(ListaPessoas *l);
void removerListaPessoa(ListaPessoas *l, Pessoa *p);
ItemPessoa *ProcurarListaPessoa(ListaPessoas *l, int id);
void destruirListaPessoas(ListaPessoas *l);

#endif // PESSOA_H_INCLUDED
