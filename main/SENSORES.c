#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>

#include "SENSORES.H"

LISTA_SENSOR* criarListaSensor()
{
	//alocar memoria
	LISTA_SENSOR* lista = (LISTA_SENSOR*)malloc(sizeof(LISTA_SENSOR));
	if (!lista)
	{
		printf("Erro a alocar memoria na LISTA\n");
		return;
	}
	lista->header = NULL;
	lista->ultimoNODE = NULL;
	lista->numElementos = 0;

	return lista;

}

NODE_SENSOR* criarNodeSensor()
{
	//alocar memoria para o NODE
	NODE_SENSOR* node = (NODE_SENSOR*)malloc(sizeof(NODE_SENSOR));
	if (!node)
	{
		printf("Erro a alocar memoria no NODE\n");
		return;
	}
	//alocar memoria para o conteudo
	node->info = (SENSOR*)malloc(sizeof(SENSOR));
	node->next = NULL;

	return node;
}

int libertarNodeSensor(NODE_SENSOR* node)
{
	if (!node)
	{
		printf("ERRO! O NODE SENSOR NAO EXISTE!");
		return;
	}

	free(node->info);
	free(node);
	return 1;
}

void carregarSensor(LISTA_SENSOR* lista)
{
	//para o compilador reconhecer os caracteres especiais do ficheiro, visto que sem esta linha obtinha caracteres estranhos
	setlocale(LC_ALL, "en_US.UTF-8");


	
	if (!lista)
	{
		printf("ERRO! A LISTA NAO EXISTE\n");
		return;
	}
	//abrir o ficheiro em modo leitura
	FILE* fich = fopen("sensores.txt", "r");
	if (!fich)
	{
		printf("ERRO A ABRIR O FICHEIRO sensores.txt\n");
		return;
	}

	//percorrer o ficheiro linha a linha e guardar a info no node
	char buffer[1000];
	
	
	while (fgets(buffer, sizeof(buffer), fich))
	{
		//verificar se estou numa linha em branco
		if (strcmp(buffer, "\n") == 0)
		{
			//printf("LINHA EM BRANCO\n");
		}
		else
		{
			//criar o NODE
			NODE_SENSOR* node = criarNodeSensor();
			if (!node)
			{
				printf("ERRO A CRIAR NODE\n");
				return;
			}
		
			//adicionar os valores do BUFFER para o node;
			sscanf(buffer, "%d\t%[^\t]\t%[^\t]\t%[^\t]", &node->info->codSensor, node->info->designacao, node->info->infoLatitude, node->info->infoLongitude);
				
			//adicionar o node para a lista
			//printf("%s", buffer);
			printf("%d\t%s\t%s\n", node->info->codSensor, node->info->designacao, node->info->infoLatitude, node->info->infoLongitude);
			
			//funcao adicionar a lista
		}
		
	}

	fclose(fich);
}

//falta libertarLISTA()