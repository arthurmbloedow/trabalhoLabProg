#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

#define clear() printf("\033[H\033[J")

void main() //fflush(stdin);
{
	clear();
	printf("- Sistema de Gerenciamento de Locadora de Filmes -\n");
	printf("1 : Cadastrar Filme \n");
	printf("2 : Editar Filme \n");
	printf("3 : Procurar Filme \n");
	printf("4 : Visualizar Filmes \n");
	printf("5 : Gerar Relatorio de Filmes em PDF \n");
	printf("0 : Sair\n");
	printf("\nDigite o que deseja fazer: ");

	int y = 0;
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
		gerarRelatorio();
	else if (y==0)
	{
		clear();
		exit(0);
	}

	main();
}
