#include "caixa.h"

void inicializarCaixa(Caixa *caixa)
{
	if (!caixa)
	{
		return;
	}

	caixa->funcionario.id = 0;
	caixa->funcionario.nome[0] = '\0';
	caixa->clientes.inicio = NULL;
	caixa->clientes.n_clientes = 0;
}

void imprimirCaixa(Caixa *c)
{
	if (!c)
	{
		printf("Caixa inválida\n");
		return;
	}

	printf("Caixa\n");
	printf("Funcionario: ");
	if (c->funcionario.id > 0)
	{
		printf("[%d] %s\n", c->funcionario.id, c->funcionario.nome);
	}
	else
	{
		printf("sem funcionario\n");
	}

	printf("Clientes na fila: %d\n", c->clientes.n_clientes);
	imprimirListaClientes(&c->clientes);
}

void adicionarClienteCaixa(Cliente *cliente, Caixa *caixa)
{
	if (!cliente || !caixa)
	{
		return;
	}

	if (!caixa->clientes.inicio && caixa->clientes.n_clientes == 0)
	{
		caixa->clientes.inicio = NULL;
	}

	adicionarListaCliente(&caixa->clientes, cliente);
}

void removerClienteCaixa(Cliente *cliente, Caixa *caixa)
{
	if (!cliente || !caixa || !caixa->clientes.inicio)
	{
		return;
	}

	ItemCliente *atual = caixa->clientes.inicio;
	ItemCliente *anterior = NULL;

	while (atual)
	{
		if (atual->cliente == cliente)
		{
			if (anterior == NULL)
			{
				caixa->clientes.inicio = atual->prox;
			}
			else
			{
				anterior->prox = atual->prox;
			}

			free(atual);
			caixa->clientes.n_clientes--;
			return;
		}

		anterior = atual;
		atual = atual->prox;
	}
}