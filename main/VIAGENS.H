/**
 * @file VIAGENS.H
 * @brief Definicao das Estruturas relacionadas com as viagens e prototipagem das funcoes utilizadas no VIAGENS.c
 */


 // BIBLIOTECAS
#include "carros.h"


/**
* @struct nodeViagem
* @brief Estrutura que serve de node, contem o conteudo da viagem e o ponteiro do proximo
*/
typedef struct nodeViagem
{
	float totalKm; // vai armazenar todos os km percorridos em viagem do carro
	int totalInfracoes; // vai armazenar as infracoes cometidas pelo carro
	CARRO* carro;
	long int milisegundosPercorridos; //vai armazenar o tempo em MS durante o periodo X que o carro viajou
	struct nodeViagem* next;
}NODE_VIAGENS;

/**
* @struct listaviagem
* @brief Estrutura serve como lista para o conjunto dos NODE_VIAGENS
*/
typedef struct
{
	NODE_VIAGENS* header;
	NODE_VIAGENS* ultimoNode;
}LISTA_VIAGENS;


// PROTOTIPAGEM
LISTA_VIAGENS* criarListaViagens();
NODE_VIAGENS* criarNodeViagens();
int existeCarroListaViagens(LISTA_VIAGENS* listaViagens, int codCarro);
void adicionarNodeListaViagens(NODE_VIAGENS* nodeViagens, LISTA_VIAGENS* listaViagens);
void freeListaViagens(LISTA_VIAGENS* listaViagens);