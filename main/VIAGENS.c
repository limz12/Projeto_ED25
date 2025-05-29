#include <stdlib.h>
#include <stdio.h>

#include "VIAGENS.H"

//funcao para criar a lista Viagens
LISTA_VIAGENS* criarListaViagens()
{
	//alocar memoria
	LISTA_VIAGENS* listaViagens = (LISTA_VIAGENS*)malloc(sizeof(LISTA_VIAGENS));
	listaViagens->header = NULL;
	listaViagens->ultimoNode = NULL;
	return listaViagens;
}

//funcao para criar o node da lista Viagens
NODE_VIAGENS* criarNodeViagens()
{
	//alocar mem
	NODE_VIAGENS* nodeViagens = (NODE_VIAGENS*)malloc(sizeof(NODE_VIAGENS));
	
	nodeViagens->carro =(CARRO*)malloc(sizeof(CARRO));
	nodeViagens->totalKm = 0;
	nodeViagens->milisegundosPercorridos = 0;
	nodeViagens->next = NULL;
	return nodeViagens;
}

/**
* @brief Funcao responsavel por verificar se o determinado carro existe na lista
* @param codCarro : Recebe um inteiro que e o identificador do carro
* @param listaViagens : Recebe um ponteiro de uma listaViagens
* @return 1 : se carro existe
* @return 0 : se carro nao existe
*/
int existeCarroListaViagens(LISTA_VIAGENS* listaViagens, int codCarro)
{
	if (!listaViagens || !codCarro)
	{
		return;
	}
	// se a lista nao possuir header, nao tem carros
	if (listaViagens->header == NULL)
	{
		return 0;
	}
	//variavel auxiliar para percorrer a lista
	NODE_VIAGENS* nodeViagens = listaViagens->header;
	while (nodeViagens)
	{
		//o carro existe
		if (nodeViagens->carro->codVeiculo == codCarro)
		{
			return 1;
		}
		nodeViagens = nodeViagens->next;
	}
	//se percorrer a lista toda e nao encontrar
	return 0;
}

//adiciona o nodeViagem na Lista Viagem
void adicionarNodeListaViagens(NODE_VIAGENS* nodeViagens, LISTA_VIAGENS* listaViagens)
{
	if (!nodeViagens || !listaViagens)
	{
		return;
	}
	// se a lista nao tiver nenhum node
	if (listaViagens->header == NULL)
	{
		listaViagens->header = nodeViagens;
		listaViagens->ultimoNode = nodeViagens;
	}
	else // se a lista ja tiver nodes, adiciona no fim
	{
		listaViagens->ultimoNode->next = nodeViagens;
		listaViagens->ultimoNode = nodeViagens;

	}

}

//remover da memoria a Lista Viagens
void freeListaViagens(LISTA_VIAGENS* listaViagens)
{
	if (!listaViagens) {
		return;
	}

	NODE_VIAGENS* atual = listaViagens->header;
	while (atual)
	{
		NODE_VIAGENS* temp = atual;
		atual = atual->next;
		free(temp);
	}

	free(listaViagens);

}