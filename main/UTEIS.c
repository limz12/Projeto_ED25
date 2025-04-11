#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "SENSORES.H"
#include "DISTANCIAS.H"
#include "PASSAGEM.H"
#include "UTEIS.H"
#include "carros.h"
#include "donos.h"
// FALTA MEMORIA OCUPADA POR : DISTANCIA     PASSAGEM

//determinar a memoria ocupada por toda a estrutura de dados
int calcularTamanhoEDSensor(LISTA_SENSOR *lista)
{
	if (!lista)
	{
		printf("ERRO! A lista SENSOR nao existe");
		return;
	}
	//adicionar o tamanho da lista (8bytes)
	int tamanho = sizeof(lista);
	//percorrer a lista e ir somando o tamanho de cada NO e os seus conteudos
	NODE_SENSOR* aux = lista->header;
	while (aux)
	{
		tamanho += sizeof(aux);
		tamanho += sizeof(aux->info);
		aux = aux->next;
	}

	return tamanho;
}

int calcularTamanhoEDDistancia(DISTANCIAS_LISTA* lista)
{
	if (!lista)
	{
		printf("ERRO! A lista SENSOR nao existe");
		return;
	}
	//adicionar o tamanho da lista (8bytes)
	int tamanho = sizeof(lista);
	//percorrer a lista e ir somando o tamanho de cada NO e os seus conteudos
	DISTANCIAS_NODE* aux = lista->header;
	while (aux)
	{
		tamanho += sizeof(aux);
		tamanho += sizeof(aux->info);
		aux = aux->next;
	}

	return tamanho;
}

int calcularTamanhoEDPassagem(PASSAGEM_LISTA* lista)
{
	if (!lista)
	{
		printf("ERRO! A lista SENSOR nao existe");
		return;
	}
	//adicionar o tamanho da lista (8bytes)
	int tamanho = sizeof(lista);
	//percorrer a lista e ir somando o tamanho de cada NO e os seus conteudos
	PASSAGEM_NODE* aux = lista->header;
	while (aux)
	{
		tamanho += sizeof(aux);
		tamanho += sizeof(aux->info);
		aux = aux->next;
	}

	return tamanho;
}

int calcularTamanhoEDCarro(LISTA_HASHC* listaHash) //ALTERAR ISTO PARA CALCULAR O TAMANHO DA LISTAHASH
{
	if (!listaHash)
	{
		printf("ERRO! A lista HASH CARRO nao existe");
		return;
	}
	//variavel que vai conter o tamanho da ED em bytes
	int tamanho = 0;

	//tamanho da lista Hash
	tamanho += sizeof(listaHash);
	//auxiliar para percorrer os nodes da listaHash
	NODE_HASHC* nodeHash = listaHash->header;
	//percorrer os nodes Hash todos
	while (nodeHash)
	{
		//tamanho do nodeHash
		tamanho += sizeof(nodeHash);
		//verificar se o nodeHash possui lista
		if (nodeHash->listaCarros != NULL)
		{
			//tamanho da lista que pertenec ao nodeHash
			tamanho += sizeof(nodeHash->listaCarros);
			//verificar se existem nodes na lista do nodeHash
			if (nodeHash->listaCarros->header != NULL)
			{
				//auxiliar para percorrer a lista do nodeHash
				NODE_CARRO* nodeCarro = nodeHash->listaCarros->header;
				//percorrer os nodes todos e armazenar o tamanho
				while (nodeCarro)
				{
					tamanho += sizeof(nodeCarro);
					nodeCarro = nodeCarro->next;
				}
			}
		}		
		nodeHash = nodeHash->next;
	}
	/*
	//calcular o ultimo node que sobrou
	//adicionar tamanho do nodeHash
	tamanho += sizeof(nodeHash);
	//adicionar o tamanho da listaCarros do nodeHash
	tamanho += sizeof(nodeHash->listaCarros);
	//percorrer todos os carros da lista e adicionar o tamanho
	NODE_CARRO* nodeCarro = nodeHash->listaCarros->header;
	while (nodeCarro)
	{
		tamanho += sizeof(nodeCarro);
		nodeCarro = nodeCarro->next;
	}
	*/
	return tamanho;
}

int calcularTamanhoEDDonos(LISTA_DONOS* lista)
{
	if (!lista)
	{
		printf("ERRO! A lista DONO nao existe");
		return;
	}
	//adicionar o tamanho da lista (8bytes)
	int tamanho = sizeof(lista);
	//percorrer a lista e ir somando o tamanho de cada NO e os seus conteudos
	NODE_DONOS* aux = lista->primeiro;
	while (aux)
	{
		tamanho += sizeof(aux);
		tamanho += sizeof(aux->info);
		aux = aux->next;
	}

	return tamanho;
}

//FALTA FAZER CARROS E DONOS

//JUNTAR NUMA UNICA FUNCAO QUE SOMA TODOS OS RETURNS E DEVOLVE O TOTAL (BYTES)
void memoriaTotalOcupadaED(LISTA_SENSOR* listaS, DISTANCIAS_LISTA* listaD, PASSAGEM_LISTA* listaP, LISTA_HASHC* listaHashCarro, LISTA_DONOS* listaDonos)
{
	int memTotal = calcularTamanhoEDSensor(listaS);
	memTotal += calcularTamanhoEDDistancia(listaD);
	memTotal += calcularTamanhoEDPassagem(listaP);
	memTotal += calcularTamanhoEDCarro(listaHashCarro);
	memTotal += calcularTamanhoEDDonos(listaDonos);
	//1 Byte = 0.000001
	printf("A Estrutura de dados ocupa %.2f MB\n", (double)memTotal*0.000001);
}

//vai inicializar a estrutura de dados, ler os ficheiros / criar listas e carregar todas as informacoes dos respetivos ficheiros
int inicializarED(LISTA_SENSOR* listaSensor, DISTANCIAS_LISTA* listaDistancias, PASSAGEM_LISTA* listaPassagem, LISTA_HASHC* listaHashCarros,LISTA_DONOS* listaDonos)
{
	//tenho que retornar o enderco da LISTA de cada ficheiro carregado

	//******************CARREGAR-DONOS**************************
	carregarDadosDonos(listaDonos);
	//******************CARREGAR-CARROS**************************
	carregarDadosCarro(listaHashCarros);
	//******************CARREGAR-SENSORES**************************
	carregarSensor(listaSensor);
	//******************CARREGAR-DISTANCIAS**************************
	carregarDistancia(listaDistancias);
	//******************CARREGAR-PASSAGEM**************************
	carregarPassagem(listaPassagem);


	//ITERAR PELA LISTA DONOS E ASSOCIAR O CARRO AO DONO

	return 1;
	
}

