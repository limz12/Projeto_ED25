#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>

#include "DISTANCIAS.H"

DISTANCIAS_LISTA *criarListaDistancias()
{
	DISTANCIAS_LISTA* lista = (DISTANCIAS_LISTA*)malloc(sizeof(DISTANCIAS_LISTA));
	if (!lista)
	{
		printf("ERRO a alocar memoria LISTA_DISTANCIAS\n");
		return;
	}
	lista->header = NULL;
	lista->ultimoNode = NULL;
	lista->numelementos = 0;
	
	return lista;
}

DISTANCIAS_NODE* criarNodeDistancias()
{
	DISTANCIAS_NODE* node = (DISTANCIAS_NODE*)malloc(sizeof(DISTANCIAS_NODE));
	if (!node)
	{
		printf("ERRO a alocar memoria DISTANCIAS_NODE\t");
		return;
	}
	//alocar memoria para a struct DISTANCIAS
	node->info = (DISTANCIAS*)malloc(sizeof(DISTANCIAS));

	
	node->next = NULL;

	return node;


}

void carregarDistancia(DISTANCIAS_LISTA* lista)
{
	if(!lista)
	{
		printf("ERRO! A LISTA_DISTANCIA NAO EXISTE\n");
		return;
	}
	//abrir o ficheiro para leitura
	FILE* fich = fopen("distancias.txt", "r");

	//criar um buffer para guardar a linha do ficheiro
	char buffer[500];

	while (fgets(buffer, sizeof(buffer), fich))
	{
		//verificar se tem linhas em branco
		if (strcmp(buffer, "\n") == 0)
		{
			//printf("Linha em branco\n");
		}
		else
		{
			//criar o NODE
			DISTANCIAS_NODE* node = criarNodeDistancias();
			if (!node)
			{
				printf("ERRO AO CRIAR O DISTANCIAS_NODE\n");
				return;
			}
			//adicionar os valores ao node
			sscanf(buffer, "%d\t%d\t%f", &node->info->codSensor1, &node->info->codSensor2, &node->info->distanciaPercorrida);
			//adicionar o NODE A LISTA
			adicionarLista(lista, node);
		}
	}
	fclose(fich);
	printf("DISTANCIA.TXT carregado com sucesso!\n");

}

void adicionarLista(DISTANCIAS_LISTA* lista, DISTANCIAS_NODE* node)
{
	if (!lista || !node)
	{
		printf("ERRO! LISTA E NODE NAO EXISTEM\n");
		return;
	}

	//se for o primeiro elemento da lista
	if (lista->header == NULL)
	{
		lista->header = node;
		lista->ultimoNode = node;
		lista->numelementos++;
	}
	else //se ja existir adiciona no fim da lista o novo no
	{
		lista->ultimoNode->next = node;
		//atualizar o ultimo
		lista->ultimoNode = node;
		lista->numelementos++;
	}
	

}

void mostrarListaDISTANCIA(DISTANCIAS_LISTA* lista)
{
	if (!lista)
	{
		printf("ERRO! A LISTA NAO EXISTE");
		return;
	}
	//mostrar o conteudo da lista

	DISTANCIAS_NODE* aux = lista->header;
	printf("*******************************\n");
	printf("LISTA DISTANCIAS\n");
	printf("*******************************\n");
	printf("COD_SENSOR_1\tCOD_SENSOR_2\tDISTANCIA_PERCORRIDA\n");

	while (aux!= NULL)
	{
		
		printf("%d\t\t%d\t\t%.1f\n", aux->info->codSensor1, aux->info->codSensor2, aux->info->distanciaPercorrida);
		aux = aux->next;
	}
	printf("**********************************************\n");
}

void  libertarNodeDistancia(DISTANCIAS_NODE* node)
{
	if (!node)
	{
		printf("ERRO! NODE DISTANCIAS NAO EXISTE\n");
		return;
	}
	free(node->info);
	free(node);
}

void libertarListaDistancia(DISTANCIAS_LISTA* lista)
{
	if (!lista)
	{
		printf("ERRO! A LISTA DISTANCIA NAO EXISTE \n");
		return;
	}
	//se a lista tiver vazia libertar
	if (lista->header == NULL && lista->ultimoNode == NULL)
	{
		free(lista);
		printf("LISTA DISTANCIA REMOVIDA COM SUCESSO\n");
	}
	else// se a lista possuir NODES eliminar um a um
	{
		//atribuir uma variavel auxiliar para ajudar na eliminacao
		DISTANCIAS_NODE* aux = lista->header;

		while (lista->header != NULL) // vai eliminar do inicio para o fim da fila
		{
			//posicionar o aux no proximo no 
			aux = aux->next;
			//eliminar o no da primeira posicao
			libertarNodeDistancia(lista->header);
			//posicionar o ponteiro header da lista para o auxiliar
			lista->header = aux;
			lista->numelementos--;

		}
		//ao fim de eliminar todos os nos
		free(lista);
		printf("LISTA DISTANCIAS LIBERTADA COM SUCESSO! \n");
	}
}