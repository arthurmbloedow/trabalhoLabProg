#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define clear() printf("\033[H\033[J")

void cadastrarFilme()
{
	clear();
	
	char codigo[10];
    printf("Digite o codigo do filme: ");
	fgetc(stdin);
	fgets(codigo, sizeof(codigo), stdin);
	strtok(codigo, "\n");

	while (checkCodigoDuplicado(codigo) == 1)
	{
		printf("Codigo ja existe! Digite um novo codigo: ");
		fgets(codigo, sizeof(codigo), stdin);
		strtok(codigo, "\n");
	}

	char nome[60];
	printf("Digite o nome do filme: ");
	//fgetc(stdin);
	fgets(nome, sizeof(nome), stdin);
	strtok(nome, "\n");

	char locado;
	while (locado != 's' && locado != 'n')
	{
		printf("O filme esta locado? [s/n]: ");
		scanf(" %c", &locado);
	}

	strcat(codigo, ";");
	strcat(codigo, nome);  //n pergunte o pq
	strcpy(nome, codigo);  

	if (locado == 's')
	{
		int dias = 0;
		char sdias[3];
		while (dias <= 0)
		{
			printf("O filme esta locado ha quantos dias? ");
			scanf("%d", &dias);
		}
		sprintf(sdias, "%d;", dias);
		strcat(nome, ";true;");
		strcat(nome, sdias);

		char nomeCliente[30];
		printf("Qual cliente locou o filme? ");
		fgetc(stdin);
		fgets(nomeCliente, sizeof(nomeCliente), stdin);
		strcat(nome, nomeCliente);
	}
	else
		strcat(nome, ";false;0;no_client\n");

	FILE *fptr;
	fptr = fopen("filmes_data.txt","a+");
	fprintf(fptr,"%s", nome);
	fclose(fptr);

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
	fgetc(stdin);
	clear();
	FILE* file = fopen("filmes_data.txt", "r");

    char line[120];
    char print[120] = "";

    printf("Codigo; Nome do filme; Status \n");
    printf("--------------------------------------------------------------------------------\n\n");

	while (fgets(line, sizeof(line), file)) 
	{
		//printf("%s", line);
		int i = 0;
		char * str;

		str = strtok(line, ";"); //codigo
		strcat(print, "[");
		strcat(print, line);
		strcat(print, "] ");

		str = strtok(NULL, ";"); //nome
		strcat(print, str);
		strcat(print, " esta ");

		str = strtok(NULL, ";"); //locado (true false)
		if (strcmp(str, "true") == 0)
		{
			str = strtok(NULL, ";");
			strcat(print, "locado ha ");
			strcat(print, str);
			int multa = atoi(str);
			strcat(print, " dia(s) por ");
			str = strtok(NULL, ";");
			strtok(str, "\n");
			strcat(print, str);
			if (multa > MULTA_DIAS)
			{
				multa = (multa - MULTA_DIAS) * PRECO_PADRAO;
				strcat(print, ", com multa de R$ ");
				char smulta[5];
				sprintf(smulta, "%d", multa);
				strcat(print, smulta);
			}
			strcat(print, ".");
		}
		else
			strcat(print, "disponivel.");

		printf("%s \n", print);
		i = 0;
		strcpy(print, "");
    }

    fclose(file);
	printf("\n\nPressione Enter para continuar...");
	fgetc(stdin);
}

void gerarRelatorio() //pdf
{
	
}

