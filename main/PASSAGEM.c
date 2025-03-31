#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>

#include "PASSAGEM.H"

//criar a LISTA PASSAGEM
PASSAGEM_LISTA* criarListaPassagem()
{
	//alocar memoria para a lista
	PASSAGEM_LISTA* lista = (PASSAGEM_LISTA*)malloc(sizeof(PASSAGEM_LISTA));
	//verificar se a lista foi criada com sucesso
	if (!lista)
	{
		printf("ERRO! A Lista Passagem nao foi alocada\n");
		return;
	}
	//inicializar a lista a null
	lista->header = NULL;
	lista->ultimoNode = NULL;
	lista->numElementos = 0;

	return lista;
}

//criar o NODE PASSAGEM
PASSAGEM_NODE* criarNodePassagem()
{
	//alocar memoria para o node
	PASSAGEM_NODE* node = (PASSAGEM_NODE*)malloc(sizeof(PASSAGEM_NODE));
	//alocar memoria para a struct PASSAGEM
	node->info = (PASSAGEM*)malloc(sizeof(PASSAGEM));
	//alocar memoria para a struct DATA
	node->info->data = (DATA*)malloc(sizeof(DATA));
	if (!node || !node->info || !node->info->data)
	{
		printf("ERRO a alocar memoria para o NODE PASSAGEM\n");
		return;
	}

	node->next = NULL;
	

	return node;
}

void carregarPassagem(PASSAGEM_LISTA* lista)
{
	if (!lista)
	{
		printf("ERRO, Lista PASSAGEM nao existe\n");
		return;
	}
	//abrir o ficheiro para leitura
	FILE* fich = fopen("passagem.txt", "r");

	//criar buffer para armazenar a linha lida do ficheiro
	char buffer[1000];
	//ler o ficheiro linha a linha e adicionar no buffer
	while (fgets(buffer, sizeof(buffer), fich))
	{
		//detetar linhas em branco
		if (strcmp(buffer, "\n") == 0)
		{
			printf("Linha em branco detetada\n");
		}
		else
		{
			//criar um no e armazenar os conteudos do buffer nesse no
			PASSAGEM_NODE* node = criarNodePassagem();
			
			sscanf(buffer, "%d\t%d\t%d-%d-%d %d:%d:%d.%d\t%d",&node->info->idSensor, &node->info->codVeiculo, &node->info->data->dia, &node->info->data->mes, &node->info->data->ano, &node->info->data->hora, &node->info->data->minuto, &node->info->data->segundo, &node->info->data->milisegundo, &node->info->tipoRegisto);
			
			printf("%d\t%d\t%d-%d-%d %d:%d:%d.%d\t%d\n", node->info->idSensor, node->info->codVeiculo, node->info->data->dia, node->info->data->mes, node->info->data->ano, node->info->data->hora, node->info->data->minuto, node->info->data->segundo, node->info->data->milisegundo, node->info->tipoRegisto);

			//adicionar o node a lista PASSAGEM

		}
	}




	fclose(fich);
}

