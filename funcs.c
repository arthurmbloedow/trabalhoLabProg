#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio_ext.h> //allows __fpurge(stdin); //clears buffer (valeu will)

#define clear() printf("\033[H\033[J") //descobri depois que system(clear); funciona mas muita mao trocar
#define MULTA_DIAS 3 //quantos dias ate receber multa
#define PRECO_PADRAO 5 //5 pilas

char * getClientName(char codigo[10])
{
	FILE* file = fopen("clientes_data.txt", "r");
    char line[120];
    char * match;

	while (fgets(line, sizeof(line), file)) 
	{
		match = strtok(line, ";");

		if (strcmp(codigo, match) == 0)
		{
			match = strtok(NULL, ";");
			strtok(match, "\n");
			fclose(file);
			return match;
		}
	}
	fclose(file);

	return match;
}

int checkCodigoDuplicadoCliente(char codigo[10])
{
	FILE* file = fopen("clientes_data.txt", "r");
    char line[120];
    char * match;

	while (fgets(line, sizeof(line), file)) 
	{
		match = strtok(line, ";");

		if (strcmp(codigo, match) == 0)
		{
			fclose(file);
			return 1;
		}
	}
	fclose(file);
    return 0;
}

void cadastrarCliente() 
{
	clear();
	printf("Digite o nome completo do cliente: ");
	char nomeCliente[100];
	__fpurge(stdin);
	fgets(nomeCliente, sizeof(nomeCliente), stdin);
	strtok(nomeCliente, "\n");

	printf("Digite o codigo do cliente: ");
	char codigoCliente[30];
	__fpurge(stdin);
	fgets(codigoCliente, sizeof(codigoCliente), stdin);
	strtok(codigoCliente, "\n");

	while (checkCodigoDuplicadoCliente(codigoCliente) == 1)
	{
		printf("Codigo de cliente ja existente! Digite o codigo do cliente: ");
		__fpurge(stdin);
		fgets(codigoCliente, sizeof(codigoCliente), stdin);
		strtok(codigoCliente, "\n");
	}

	printf("Digite o email do cliente: ");
	char emailCliente[50];
	__fpurge(stdin);
	fgets(emailCliente, sizeof(emailCliente), stdin);
	strtok(emailCliente, "\n");

	char print[80] = "";
	strcpy(print, codigoCliente);
	strcat(print, ";");
	strcat(print, nomeCliente);
	strcat(print, ";");
	strcat(print, emailCliente);

	FILE *fptr;
	fptr = fopen("clientes_data.txt","a+");
	fprintf(fptr,"%s", print);
	fclose(fptr);

	printf("\nCliente cadastrado com sucesso! \n");
	sleep(1);
}

void editarCliente() {}

void procurarCliente() 
{
	clear();
	printf("Digite o nome/codigo do cliente que deseja procurar: ");
	char pesquisa[50];
	__fpurge(stdin);
	fgets(pesquisa, sizeof(pesquisa), stdin);
	strtok(pesquisa, "\n");	

	FILE* file = fopen("clientes_data.txt", "r");
    char line[80];

	int found = 0;
	printf("\n");
	while (fgets(line, sizeof(line), file)) {
		
		char * match;
		match = strtok(line, ";");
		char * code = match;

		if (strcmp(pesquisa, match) == 0) 
		{
			found++;
			char print[300] = "";

			strcat(print, "[");
			strcat(print, match);
			strcat(print, "] ");
			match = strtok(NULL, ";");
			strcat(print, match); //nome
			match = strtok(NULL, ";");
			strtok(match, "\n");
			strcat(print, " (");
			strcat(print, match);
			strcat(print, ") ");

			//checar se o cliente tem algum fime locado e exibir aqui
			int hasMovies = 0;
			FILE* filef = fopen("filmes_data.txt", "r");
		    char line[80];
		    char movies[300] = "";
		    char * match;

			while (fgets(line, sizeof(line), filef)) 
			{
				match = strtok(line, ";"); //codigo
				match = strtok(NULL, ";"); //nome
				char movieName[30];
				strcpy(movieName, match);
				match = strtok(NULL, ";"); //status
				match = strtok(NULL, ";"); //dias
				char movieDays[3];
				strcpy(movieDays, match);
				match = strtok(NULL, ";"); //codigo cliente
				strtok(match, "\n");

				if (strcmp(code, match) == 0)
				{
					hasMovies++;;
					strcat(movies, movieName);
					strcat(movies, " por ");
					int multa = atoi(movieDays);
					strcat(movies, movieDays);
					strcat(movies, " dia(s)");
					if (multa > MULTA_DIAS)
					{
						multa = (multa - MULTA_DIAS) * PRECO_PADRAO;
						strcat(print, ", com multa de R$ ");
						char smulta[3];
						sprintf(smulta, "%d", multa);
						strcat(movies, smulta);
					}
					strcat(movies, "\n");
				}
			}
			fclose(filef);
			//--------------------------------------------------------

			if (hasMovies > 0)
			{
				strcat(print, "tem ");
				char howMany[3];
				sprintf(howMany, "%d", hasMovies);
				strcat(print, howMany);
				strcat(print, " filme(s) locado(s): \n\n");
				strcat(print, movies);
			}

			printf("%s \n", print);
    	}

    	if (found == 0)
    	{
    		match = strtok(NULL, ";");
    		if (strcmp(pesquisa, match) == 0)
    		{
    			found++;
				char print[300] = "";

				strcat(print, "[");
				strcat(print, code);
				strcat(print, "] ");
				strcat(print, match); //nome
				match = strtok(NULL, ";");
				strtok(match, "\n");
				strcat(print, " (");
				strcat(print, match);
				strcat(print, ") ");

				//checar se o cliente tem algum fime locado e exibir aqui
				int hasMovies = 0;
				FILE* filef = fopen("filmes_data.txt", "r");
			    char line[80];
			    char movies[300] = "";
			    char * match;

				while (fgets(line, sizeof(line), filef)) 
				{
					match = strtok(line, ";"); //codigo
					match = strtok(NULL, ";"); //nome
					char movieName[30];
					strcpy(movieName, match);
					match = strtok(NULL, ";"); //status
					match = strtok(NULL, ";"); //dias
					char movieDays[3];
					strcpy(movieDays, match);
					match = strtok(NULL, ";"); //codigo cliente
					strtok(match, "\n");

					if (strcmp(code, match) == 0)
					{
						hasMovies++;;
						strcat(movies, movieName);
						strcat(movies, " por ");
						int multa = atoi(movieDays);
						strcat(movies, movieDays);
						strcat(movies, " dia(s)");
						if (multa > MULTA_DIAS)
						{
							multa = (multa - MULTA_DIAS) * PRECO_PADRAO;
							strcat(print, ", com multa de R$ ");
							char smulta[3];
							sprintf(smulta, "%d", multa);
							strcat(movies, smulta);
						}
						strcat(movies, "\n");
					}
				}
				fclose(filef);
				//--------------------------------------------------------

				if (hasMovies > 0)
				{
					strcat(print, "tem ");
					char howMany[3];
					sprintf(howMany, "%d", hasMovies);
					strcat(print, howMany);
					strcat(print, " filme(s) locado(s): \n\n");
					strcat(print, movies);
				}

				printf("%s \n", print);
    		}
    	}
    }

    fclose(file);

	if (found == 0)
	{
		printf("A pesquisa \"%s\" nao encontrou resultados", pesquisa);
	}
	
	fclose(file);
	printf("\n\nPressione Enter para continuar...");
	fgetc(stdin);
}

void gerarRelatorioCliente() {}

void listarClientes()
{
	clear();
	FILE* file = fopen("clientes_data.txt", "r");

    char line[120];
    char print[120] = "";

    printf("Codigo; Nome do Cliente; Email \n");
    printf("--------------------------------------------------------------------------------\n\n");

	while (fgets(line, sizeof(line), file)) 
	{
		char * str;
		char code[20];

		str = strtok(line, ";"); //codigo
		strcpy(code, str);
		strcat(print, "[");
		strcat(print, line);
		strcat(print, "] ");
		str = strtok(NULL, ";"); //nome
		strcat(print, str);
		strcat(print, " (");
		str = strtok(NULL, ";"); //email
		strtok(str, "\n");
		strcat(print, str);
		strcat(print, ")");

		//checar se o cliente tem algum fime locado e exibir aqui
		int hasMovies = 0;
		FILE* filef = fopen("filmes_data.txt", "r");
	    char lineM[80];
	    char * movieMatch;
		while (fgets(lineM, sizeof(lineM), filef)) 
		{
			movieMatch = strtok(lineM, ";"); //codigo
			movieMatch = strtok(NULL, ";"); //nome
			movieMatch = strtok(NULL, ";"); //status
			movieMatch = strtok(NULL, ";"); //dias
			movieMatch = strtok(NULL, ";"); //codigo cliente
			strtok(movieMatch, "\n");

			if (strcmp(code, movieMatch) == 0)
			{
				hasMovies++;
			}
		}
		fclose(filef);
		//--------------------------------------------------------

		strcat(print, " tem ");
		char howMany[3];
		sprintf(howMany, "%d", hasMovies);
		strcat(print, howMany);
		strcat(print, " filme(s) locado(s).");
	}
	printf("%s\n", print);
	fclose(file);
	printf("\n\nPressione Enter para continuar...");
	__fpurge(stdin);
	fgetc(stdin);
}

int checkCodigoDuplicado(char codigo[10])
{
	FILE* file = fopen("filmes_data.txt", "r");
    char line[120];
    char * match;

	while (fgets(line, sizeof(line), file)) 
	{
		match = strtok(line, ";");

		if (strcmp(codigo, match) == 0)
		{
			fclose(file);
			return 1;
		}
	}
	fclose(file);
    return 0;
}

void cadastrarFilme()
{
	clear();
	
	char codigo[10];
    printf("Digite o codigo do filme: ");
	__fpurge(stdin);
	fgets(codigo, sizeof(codigo), stdin);
	strtok(codigo, "\n");

	while (checkCodigoDuplicado(codigo) == 1)
	{
		printf("Codigo ja existe! Digite um novo codigo: ");
		__fpurge(stdin);
		fgets(codigo, sizeof(codigo), stdin);
		strtok(codigo, "\n");
	}

	char nome[60];
	printf("Digite o nome do filme: ");
	__fpurge(stdin);
	fgets(nome, sizeof(nome), stdin);
	strtok(nome, "\n");

	char locado;
	while (locado != 's' && locado != 'n')
	{
		printf("O filme esta locado? [s/n]: ");
		__fpurge(stdin);
		scanf("%c", &locado);
	}

	strcat(codigo, ";");
	strcat(codigo, nome);  //n pergunte o pq
	strcpy(nome, codigo);  

	if (locado == 's')
	{
		int dias = 0;
		char sdias[3];
		while (dias < 0)
		{
			printf("O filme esta locado ha quantos dias? ");
			__fpurge(stdin);
			scanf("%d", &dias);
		}
		sprintf(sdias, "%d;", dias);
		strcat(nome, ";true;");
		strcat(nome, sdias);

		printf("Associar um cliente ja existente[1] ou cadastrar um novo[2]? Digite 1 ou 2: ");
		int client = 0;
		__fpurge(stdin);
		scanf("%d", &client);

		if (client == 1)
		{
			printf("Digite o codigo do cliente: ");
			char codigoCliente[30];
			__fpurge(stdin);
			fgets(codigoCliente, sizeof(codigoCliente), stdin);
			strtok(codigoCliente, "\n");

			while (checkCodigoDuplicadoCliente(codigoCliente) == 0)
			{
				printf("Codigo de cliente nao encontrado! Digite o codigo do cliente: ");
				__fpurge(stdin);
				fgets(codigoCliente, sizeof(codigoCliente), stdin);
				strtok(codigoCliente, "\n");

				FILE* file = fopen("clientes_data.txt", "r");
			    char line[120];
			    char * match;
			}
			strcat(nome, codigoCliente);

		}
		if (client == 2)
		{
			printf("Digite o nome completo do cliente: ");
			char nomeCliente[100];
			__fpurge(stdin);
			fgets(nomeCliente, sizeof(nomeCliente), stdin);
			strtok(nomeCliente, "\n");

			printf("Digite o codigo do cliente: ");
			char codigoCliente[30];
			__fpurge(stdin);
			fgets(codigoCliente, sizeof(codigoCliente), stdin);
			strtok(codigoCliente, "\n");

			while (checkCodigoDuplicadoCliente(codigoCliente) == 1)
			{
				printf("Codigo de cliente ja existente! Digite o codigo do cliente: ");
				__fpurge(stdin);
				fgets(codigoCliente, sizeof(codigoCliente), stdin);
				strtok(codigoCliente, "\n");
			}
			strcat(nome, codigoCliente);

			printf("Digite o email do cliente: ");
			char emailCliente[50];
			__fpurge(stdin);
			fgets(emailCliente, sizeof(emailCliente), stdin);
			strtok(emailCliente, "\n");

			char print[200] = "";
			strcpy(print, codigoCliente);
			strcat(print, ";");
			strcat(print, nomeCliente);
			strcat(print, ";");
			strcat(print, emailCliente);

			FILE *fptr;
			fptr = fopen("clientes_data.txt","a+");
			fprintf(fptr,"%s", print);
			fclose(fptr);
		}
	}
	else
	{
		strcat(nome, ";false;0;no_client");
	}

	FILE *fptr;
	fptr = fopen("filmes_data.txt","a+");
	fprintf(fptr,"%s\n", nome);
	fclose(fptr);

	printf("\nFilme cadastrado com sucesso! \n");
	sleep(1);
}

void editarFilme()
{
	clear();

	char pesquisa[60];
	printf("Digite o nome/codigo do filme que quer editar: ");
	__fpurge(stdin);
	fgets(pesquisa, sizeof(pesquisa), stdin);
	strtok(pesquisa, "\n");	

	FILE* file = fopen("filmes_data.txt", "r");
    char line[120];

    char old_code[10];
    char old_name[60];
    char old_status[8];
    char old_days[3];
    char old_client[10];

	int found = 0;
	int where = 0;

	printf("\n");
	while (fgets(line, sizeof(line), file)) {
		
		if (found==0)
    		where++;

		char * match;
		match = strtok(line, ";");
		char * code = match;

		if (strcmp(pesquisa, match) == 0) //||
		{
			found++;
			char print[120] = "";

			strcat(print, "[");
			strcat(print, match);
			strcat(print, "] ");
			match = strtok(NULL, ";");
			//strcat(print, "\n");
			strcat(print, match); //nome
			strcat(print, " esta "); //nome
			strcpy(old_code, code); //to edit
			strcpy(old_name, match); //to edit

			match = strtok(NULL, ";");

			if (strcmp(match, "true") == 0)
			{
				match = strtok(NULL, ";");
				int multa = atoi(match);
				strcat(print, "locado ha ");
				strcpy(old_status, "true"); //to edit
				strcpy(old_days, match); //to edit
				strcat(print, match);
				strcat(print, " dia(s) por ");
				match = strtok(NULL, ";");
				strtok(match, "\n");
				strcat(print, getClientName(match));
				if (multa > MULTA_DIAS)
				{
					multa = (multa - MULTA_DIAS) * PRECO_PADRAO;
					strcat(print, ", com multa de R$ ");
					char smulta[5];
					sprintf(smulta, "%d", multa);
					strcat(print, smulta);
				}
				strcpy(old_client, match); //to edit
				strcat(print, ".");
			}
			else
			{
				strcat(print, "disponivel.");
				strcpy(old_status, "false"); //to edit
				strcpy(old_days, "0"); //to edit
				strcpy(old_client, "no_client"); //to edit
			}

			printf("%s \n", print);
    	}

    	if (found == 0)
    	{
    		match = strtok(NULL, ";");
    		if (strcmp(pesquisa, match) == 0)
    		{
    			found++;
    			char print[120] = "";

    			strcat(print, "[");
				strcat(print, code);
				strcat(print, "] ");
    			strcat(print, match);
				strcat(print, " esta ");
				strcpy(old_code, code); //to edit
				strcpy(old_name, match); //to edit
				match = strtok(NULL, ";");

				if (strcmp(match, "true") == 0)
				{
					match = strtok(NULL, ";");
					int multa = atoi(match);
					strcat(print, "locado ha ");
					strcpy(old_status, "true"); //to edit
					strcpy(old_days, match); //to edit
					strcat(print, match);
					strcat(print, " dia(s) por ");
					match = strtok(NULL, ";");
					strtok(match, "\n");
					strcat(print, getClientName(match));
					if (multa > MULTA_DIAS)
					{
						multa = (multa - MULTA_DIAS) * PRECO_PADRAO;
						strcat(print, ", com multa de R$ ");
						char smulta[5];
						sprintf(smulta, "%d", multa);
						strcat(print, smulta);
					}
					strcat(print, ".");
					strcpy(old_client, match); //to edit
				}
				else
				{
					strcat(print, "disponivel.");
					strcpy(old_status, "false"); //to edit
					strcpy(old_days, "0"); //to edit
					strcpy(old_client, "no_client"); //to edit
				}

				printf("%s \n", print);
    		}
    	}
    }

	if (found == 0)
	{
		printf("A pesquisa \"%s\" nao encontrou resultados", pesquisa);
	}
	else
	{
		fclose(file);

		char new_code[10]; 
		strcpy(new_code, old_code);
		char new_name[60]; 
		strcpy(new_name, old_name);
		char new_status[8]; 
		strcpy(new_status, old_status);
		char new_days[3]; 
		strcpy(new_days, old_days);
		char new_client[30]; 
		strcpy(new_client, old_client);

		int change = 0;

		printf("\nO que quer editar? ");
		printf("\n1 : Codigo");
		printf("\n2 : Nome");
		printf("\n3 : Status");
		printf("\n0 : Voltar");
		printf("\nInput: ");

		int y = 0;
		__fpurge(stdin);
		scanf("%d", &y);

		if (y==1)
		{
			change++;
			printf("\nDigite o novo codigo: ");
			__fpurge(stdin);
			fgets(new_code, sizeof(new_code), stdin);
			strtok(new_code, "\n");

			while(checkCodigoDuplicado(new_code) || strcmp(new_code, old_code) == 0)
			{
				printf("Codigo duplicado! Digite um novo codigo: ");
				__fpurge(stdin);
				fgets(new_code, sizeof(new_code), stdin);
				strtok(new_code, "\n");
			}
			printf("\nAlteracao feita com sucesso!");
		}		
		else if (y==2)
		{
			change++;
			printf("\nDigite o novo nome: ");
			__fpurge(stdin);
			fgets(new_name, sizeof(new_name), stdin);
			strtok(new_name, "\n");

			while(strcmp(old_name, new_name) == 0)
			{
				printf("Nome igual ao antigo! Digite um NOVO nome: ");
				__fpurge(stdin);
				fgets(new_name, sizeof(new_name), stdin);
				strtok(new_name, "\n");
			}
			printf("\nAlteracao feita com sucesso!");
		}	
		else if (y==3)
		{
			//printf("codigo: %s \n\n\n", old_code);
			if (strcmp(old_status, "true") == 0)
			{
				printf("\nO que quer editar? ");
				printf("\n1 : Alterar o status de locacao para Disponivel");
				printf("\n2 : Alterar ha quantos dias esta locado");
				printf("\n3 : Alterar o cliente");
				printf("\n0 : Voltar");
				printf("\nInput: ");
				__fpurge(stdin);
				scanf("%d", &y);

				if (y==1)
				{
					change++;
					strcpy(new_status, "false");
					strcpy(new_days, "0");
					strcpy(new_client, "no_client");
					printf("\n");
					printf("Status do filme \"%s\" alterado para disponivel", new_name);
				}
				else if (y==2)
				{
					change++;
					printf("\nDigite o numero de dias para o qual deseja alterar: ");
					__fpurge(stdin);
					fgets(new_days, sizeof(new_days), stdin);
					strtok(new_days, "\n");

					while(strcmp(old_days, new_days) == 0)
					{
						printf("Numero de dias igual ao antigo! Digite um NOVO numero: ");
						__fpurge(stdin);
						fgets(new_days, sizeof(new_days), stdin);
						strtok(new_days, "\n");
					}

					printf("\nAlteracao feita com sucesso!");
				}
				else if (y==3)
				{
					change++;

					printf("\nAssociar um cliente ja existente[1] ou cadastrar um novo[2]? Digite 1 ou 2: ");
					int client = 0;
					__fpurge(stdin);
					scanf("%d", &client);

					if (client == 1)
					{
						printf("Digite o codigo do cliente: ");
						char codigoCliente[30];
						__fpurge(stdin);
						fgets(codigoCliente, sizeof(codigoCliente), stdin);
						strtok(codigoCliente, "\n");

						while (checkCodigoDuplicadoCliente(codigoCliente) == 0)
						{
							printf("Codigo de cliente nao encontrado! Digite o codigo do cliente: ");
							__fpurge(stdin);
							fgets(codigoCliente, sizeof(codigoCliente), stdin);
							strtok(codigoCliente, "\n");

							FILE* file = fopen("clientes_data.txt", "r");
						    char line[120];
						    char * match;
						}
						strcpy(new_client, codigoCliente);

					}
					if (client == 2)
					{
						printf("Digite o nome completo do cliente: ");
						char nomeCliente[100];
						__fpurge(stdin);
						fgets(nomeCliente, sizeof(nomeCliente), stdin);
						strtok(nomeCliente, "\n");

						printf("Digite o codigo do cliente: ");
						char codigoCliente[30];
						__fpurge(stdin);
						fgets(codigoCliente, sizeof(codigoCliente), stdin);
						strtok(codigoCliente, "\n");

						while (checkCodigoDuplicadoCliente(codigoCliente) == 1)
						{
							printf("Codigo de cliente ja existente! Digite o codigo do cliente: ");
							__fpurge(stdin);
							fgets(codigoCliente, sizeof(codigoCliente), stdin);
							strtok(codigoCliente, "\n");
						}
						strcpy(new_client, codigoCliente);

						char print[200] = "";
						strcpy(print, codigoCliente);
						strcat(print, ";");
						strcat(print, nomeCliente);

						FILE *fptr;
						fptr = fopen("clientes_data.txt","a+");
						fprintf(fptr,"%s", print);
						fclose(fptr);
					}

					/*printf("\nDigite o codigo do cliente para o qual deseja alterar: ");
					fgetc(stdin);
					fgets(new_client, sizeof(new_client), stdin);
					strtok(new_client, "\n");

					while(strcmp(old_client, new_client) == 0)
					{
						printf("Nome do cliente ao antigo! Digite um NOVO nome: ");
						fgets(new_client, sizeof(new_client), stdin);
						strtok(new_client, "\n");
					}*/
					printf("\nAlteracao feita com sucesso!");
				}
			}
			else
			{
				change++;
				strcpy(new_status, "true");
				printf("\nO filme esta locado ha quantos dias? ");
				__fpurge(stdin);
				fgets(new_days, sizeof(new_days), stdin);
				strtok(new_days, "\n");

				printf("\nQual cliente locou o filme? ");
				__fpurge(stdin);
				fgets(new_client, sizeof(new_client), stdin);
				strtok(new_client, "\n");

				printf("\nAlteracao feita com sucesso!");
			}
		}

		if (change > 0)
		{
			FILE* fileo = fopen("filmes_data.txt", "r");
			FILE* filec = fopen("filmes_data_c.txt", "w");

		    char line[120];

			int x = 1;

			while (fgets(line, sizeof(line), fileo)) 
			{
				if (x < where || x > where)
					fprintf(filec,"%s", line);
				else if (x == where)
				{
					fprintf(filec,"%s", new_code);
					fprintf(filec,"%s", ";");
					fprintf(filec,"%s", new_name);
					fprintf(filec,"%s", ";");
					fprintf(filec,"%s", new_status);
					fprintf(filec,"%s", ";");
					fprintf(filec,"%s", new_days);
					fprintf(filec,"%s", ";");
					fprintf(filec,"%s", new_client);
					fprintf(filec,"%s", "\n");
				}
				x++;
			}
			fclose(fileo);
			fclose(filec);

			remove("filmes_data.txt");
			rename("filmes_data_c.txt", "filmes_data.txt");
		}	

	}
	printf("\n\nPressione Enter para continuar...");
	fgetc(stdin);
}

void procurarFilme()
{
	clear();

	char pesquisa[60];
	printf("Digite o nome/codigo do filme que quer pesquisar: ");
	__fpurge(stdin);
	fgets(pesquisa, sizeof(pesquisa), stdin);
	strtok(pesquisa, "\n");	

	FILE* file = fopen("filmes_data.txt", "r");
    char line[120];

	int found = 0;
	printf("\n");
	while (fgets(line, sizeof(line), file)) {
		
		char * match;
		match = strtok(line, ";");
		char * code = match;

		if (strcmp(pesquisa, match) == 0) //||
		{
			found++;
			char print[120] = "";

			strcat(print, "[");
			strcat(print, match);
			strcat(print, "] ");
			match = strtok(NULL, ";");
			//strcat(print, "\n");
			strcat(print, match); //nome
			strcat(print, " esta "); //nome

			match = strtok(NULL, ";");

			if (strcmp(match, "true") == 0)
			{
				match = strtok(NULL, ";");
				int multa = atoi(match);
				strcat(print, "locado ha ");
				strcat(print, match);
				strcat(print, " dia(s) por ");
				match = strtok(NULL, ";");
				strtok(match, "\n");
				strcat(print, getClientName(match));
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
    	}

    	if (found == 0)
    	{
    		match = strtok(NULL, ";");
    		if (strcmp(pesquisa, match) == 0)
    		{
    			found++;
    			char print[120] = "";

    			strcat(print, "[");
				strcat(print, code);
				strcat(print, "] ");
    			strcat(print, match); //nome
				strcat(print, " esta "); //nome

				match = strtok(NULL, ";");

				if (strcmp(match, "true") == 0)
				{
					match = strtok(NULL, ";");
					int multa = atoi(match);
					strcat(print, "locado ha ");
					strcat(print, match);
					strcat(print, " dia(s) por ");
					match = strtok(NULL, ";");
					strtok(match, "\n");
					strcat(print, getClientName(match));
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
    		}
    	}
    }

	if (found == 0)
	{
		printf("A pesquisa \"%s\" nao encontrou resultados", pesquisa);
	}
	
	fclose(file);
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
			//char * clientNome = getClientName(str);
			strcat(print, getClientName(str));
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

