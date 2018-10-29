#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define clear() printf("\033[H\033[J")

void cadastrarFilme()
{
	clear();
	
	char codigo[60];
    	printf("Digite o codigo do filme: ");
	fgetc(stdin);
	fgets(codigo, sizeof(codigo), stdin);

	char nome[60];
	printf("Digite o nome do filme: ");
	fgets(nome, sizeof(nome), stdin);

	char locado;
	while (locado != 's' && locado != 'n')
	{
		printf("O filme esta locado? [s/n]: ");
		scanf("%c", &locado);
	}
 

	if (locado == 's')
	{
		int dias = 0;
		char sdias[66];
		while (dias <= 0)
		{
			printf("O filme esta locado ha quantos dias? ");
			scanf("%d", &dias);
		}
		sprintf(sdias, "%d;", dias);

		char nomeCliente[100];
		printf("Qual cliente locou o filme? ");
		fgetc(stdin);
		fgets(nomeCliente, sizeof(nomeCliente), stdin);
	}

	printf("\nFilme cadastrado com sucesso! \n");
	sleep(1);
}

void editarFilme()
{
	clear();

	char pesquisa[256];
	printf("Digite o nome/codigo do filme que quer editar: ");
	fgetc(stdin);
	fgets(pesquisa, sizeof(pesquisa), stdin);
	strtok(pesquisa, "\n");	

	int found = 0;

	if (found == 0)
	{
		printf("A pesquisa \"%s\" nao encontrou resultados", pesquisa);
	}
	else
	{
		printf("\nO que quer editar? ");
		printf("\n1 : Codigo");
		printf("\n2 : Nome");
		printf("\n3 : Status");
		printf("\n0 : Voltar");
		printf("\nInput: ");

		int y = 0;
		scanf("%d", &y);

		if (y==1)
		{
			char new_code[60];
			printf("\nDigite o novo codigo: ");
			fgetc(stdin);
			fgets(new_code, sizeof(new_code), stdin);
		}		
		else if (y==2)
		{
			char new_name[256];
			printf("\nDigite o novo nome: ");
			fgetc(stdin);
			fgets(new_name, sizeof(new_name), stdin);
		}	
		else if (y==3)
		{
			printf("\nO que quer editar? ");
			printf("\n1 : Alterar o status de locacao");
			printf("\n0 : Voltar");
			printf("\nInput: ");
			scanf("%d", &y);
		}
	}
}

void procurarFilme()
{
	clear();

	char pesquisa[256];
	printf("Digite o nome/codigo do filme que quer pesquisar: ");
	fgetc(stdin);
	fgets(pesquisa, sizeof(pesquisa), stdin);
	
	printf("\n\nPressione Enter para continuar...");
	fgetc(stdin);
}

void listarFilmes()
{
	clear();

    	printf("Codigo; Nome do filme; Status \n");
    	printf("--------------------------------------------------------------------------------\n\n");

	printf("\n\nPressione Enter para continuar...");
	fgetc(stdin);
}

void gerarRelatorio() //pdf
{
	
}


