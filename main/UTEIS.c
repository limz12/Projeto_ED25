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

int calcularTamanhoEDCarro(LISTA_CARRO* lista)
{
	if (!lista)
	{
		printf("ERRO! A lista CARRO nao existe");
		return;
	}
	//adicionar o tamanho da lista (8bytes)
	int tamanho = sizeof(lista);
	//percorrer a lista e ir somando o tamanho de cada NO e os seus conteudos
	NODE_CARRO* aux = lista->header;
	while (aux)
	{
		tamanho += sizeof(aux);
		tamanho += sizeof(aux->info);
		aux = aux->next;
	}

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
void memoriaTotalOcupadaED(LISTA_SENSOR* listaS, DISTANCIAS_LISTA* listaD, PASSAGEM_LISTA* listaP, LISTA_CARRO* listaC, LISTA_DONOS* listaDonos)
{
	int memTotal = calcularTamanhoEDSensor(listaS);
	memTotal += calcularTamanhoEDDistancia(listaD);
	memTotal += calcularTamanhoEDPassagem(listaP);
	memTotal += calcularTamanhoEDCarro(listaC);
	memTotal += calcularTamanhoEDCarro(listaDonos);
	//1 Byte = 0.000001
	printf("A Estrutura de dados ocupa %.2f MB\n", (double)memTotal*0.000001);
}

//vai inicializar a estrutura de dados, ler os ficheiros / criar listas e carregar todas as informacoes dos respetivos ficheiros
int inicializarED(LISTA_SENSOR* listaSensor, DISTANCIAS_LISTA* listaDistancias, PASSAGEM_LISTA* listaPassagem, LISTA_CARRO* listaCarro,LISTA_DONOS* listaDonos)
{
	//tenho que retornar o enderco da LISTA de cada ficheiro carregado

	//******************CARREGAR-DONOS**************************
	carregarDadosDonos(listaDonos);
	//******************CARREGAR-CARROS**************************
	carregarDadosCarro(listaCarro);
	//******************CARREGAR-SENSORES**************************
	carregarSensor(listaSensor);
	//******************CARREGAR-DISTANCIAS**************************
	carregarDistancia(listaDistancias);
	//******************CARREGAR-PASSAGEM**************************
	carregarPassagem(listaPassagem);


	//ITERAR PELA LISTA DONOS E ASSOCIAR O CARRO AO DONO

	return 1;
	
}

