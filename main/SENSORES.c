#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>

#include <windows.h>
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
	
}

void carregarSensor(LISTA_SENSOR* lista)
{
	
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
			sscanf(buffer,"%d\t%s\t%[^\t]\t%[^\t]", &node->info->codSensor, node->info->designacao, node->info->infoLatitude, node->info->infoLongitude);
				
			//adicionar o node para a lista
			adicionarListaSensores(lista, node);
			 
			
		}
		
	}

	fclose(fich);
}

void adicionarListaSensores(LISTA_SENSOR* lista, NODE_SENSOR* node)
{
	//verificacao de entrada
	if (!lista || !node)
	{
		printf("ERRO! LISTA SENSOR E NODE SENSOR NAO EXISTEM\n");
		return;
	}
	NODE_SENSOR* aux = lista->header;

	//se a lista nao possuir nenhum no
	if (lista->header == NULL)
	{
		lista->header = node;
		lista->ultimoNODE = node;
		lista->numElementos++;
	}
	else // se ja existirem NOS na lista, adiciona no fim
	{
		lista->ultimoNODE->next = node;
		lista->ultimoNODE = node;
		lista->numElementos++;
	}
}

void mostrarListaSensores(LISTA_SENSOR* lista)
{
	if (!lista)
	{
		printf("ERRO! A lista nao existe\n");
		return;
	}
	//criar a variavel aux, para percorrer por todos os nos da lista
	NODE_SENSOR* aux = lista->header;
	printf("*******************************\n");
	printf("LISTA SENSORES\n");
	printf("*******************************\n");
	printf("COD_SENSOR\tDESIGNACAO\tLATITUDE\tLONGITUDE\n");

	while (aux)
	{
		printf("%d\t\t%s\t\t%s\t%s\n",aux->info->codSensor, aux->info->designacao, aux->info->infoLatitude, aux->info->infoLongitude);
		aux = aux->next;
	}
	printf("*******************************\n");
}

void libertarListaSensores(LISTA_SENSOR* lista)
{
	if (!lista)
	{
		printf("ERRO! A lista nao existe\n");
		return;
	}
	
	//enquanto existir um header na lista
	while (lista->header)
	{
		//eliminar os nodes 1 a 1 do inicio da lista
		NODE_SENSOR* aux = lista->header;
		lista->header = aux->next;
		libertarNodeSensor(aux);
	}

	printf("LISTA REMOVIDA COM SUCESSO\n");
}