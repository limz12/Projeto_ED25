/**
 * @file VIAGENS.c
 * @brief Implementacao das funcoes respetivas a viagens.
 */


// BIBLIOTECAS
#include <stdlib.h>
#include <stdio.h>

#include "VIAGENS.H"


/**
* @brief Funcao responsavel por criar uma lista que ira conter viagens
* @return ponteiro para uma LISTA_VIAGENS, que e o resultado da alocacao de memoria da estrutura LISTA_VIAGENS
*/
LISTA_VIAGENS* criarListaViagens()
{
	//alocar memoria
	LISTA_VIAGENS* listaViagens = (LISTA_VIAGENS*)malloc(sizeof(LISTA_VIAGENS));
	listaViagens->header = NULL;
	listaViagens->ultimoNode = NULL;
	return listaViagens;
}

/**
* @brief Funcao responsavel por alocar memoria para um node que contem todos os dados de uma respetiva viagem
* @return retorna um ponteiro para um NODE_VIAGENS, com todos os valores da estrutura nulos
*/
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

/**
* @brief Funcao responsavel por receber um NODE_VIAGENS e adiciona-lo a uma lista de viagens
* @param listaViagens : Recebe um ponteiro para a PASSAGEM_LISTA para onde a viagem vai ser "armazenada"
* @param nodeViagens : Recebe o NODE_VIAGENS que vai ser inserido no parametro de entrada lista
* @return VOID
*/
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

/**
* @brief Funcao responsavel por libertar a memoria alocada de toda a lista de viagens e todo o seu conteudo
* @param listaViagens : Recebe um ponteiro de uma LISTA_VIAGENS para ser destruida
* @return VOID
*/
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