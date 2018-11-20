#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h> //allows __fpurge(stdin); //clears buffer (valeu will)
#include "funcs.h"

#define clear() printf("\033[H\033[J")

void main()
{
	clear();
	printf("- Sistema de Gerenciamento de Locadora de Filmes -\n");
	printf("1 : Gerenciar Filmes \n");
	printf("2 : Gerenciar Clientes \n");
	printf("3 : Gerar Relatorio em PDF \n");
	printf("0 : Sair\n");
	printf("\nDigite o que deseja fazer: ");

	int x = 0;
	__fpurge(stdin);
	scanf("%d", &x);

	if (x==1)
	{
		clear();
		printf("1 : Cadastrar Filme \n");
		printf("2 : Editar Filme \n");
		printf("3 : Procurar Filme \n");
		printf("4 : Visualizar Filmes \n");
		printf("5 : Gerar Relatorio de Filmes em PDF \n");
		printf("0 : Voltar\n");
		printf("\nDigite o que deseja fazer: ");

		int y = 0;
		__fpurge(stdin);
		scanf("%d", &y);

		if (y==1)
			cadastrarFilme();
		else if (y== 2)
			editarFilme();
		else if (y==3)
			procurarFilme();
		else if (y==4)
			listarFilmes();
		else if (y==5)
		{
			
		}
	}
	else if (x==2)
	{
		clear();
		printf("1 : Cadastrar Cliente \n");
		printf("2 : Editar Cliente \n");
		printf("3 : Procurar Cliente \n");
		printf("4 : Visualizar Clientes \n");
		printf("5 : Gerar Relatorio de Clientes em PDF \n");
		printf("0 : Voltar\n");
		printf("\nDigite o que deseja fazer: ");

		int y = 0;
		__fpurge(stdin);
		scanf("%d", &y);

		if (y==1)
			cadastrarCliente();
		else if (y== 2)
			editarCliente();
		else if (y==3)
			procurarCliente();
		else if (y==4)
			listarClientes();
		else if (y==5)
		{
			
		}

	}
	else if (x==3)
	{
		gerarRelatorio();
	}
	else if (x==0)
	{
		clear();
		exit(0);
	}

	main();
}
