#include <stdio.h>
#include <stdlib.h>

// ESTRUTURAS DA VIAGEM
typedef struct
{
	int sensor_entrada;
	int sensor_saida;
	DATA* data_entrada;
	DATA* data_saida;
	float distancia_percorrida;
}VIAGEM;

// NODE DO CARRO
typedef struct nodeviagem
{
	VIAGEM* info;
	struct nodeviagem* next;
}NODE_VIAGEM;

// LISTA CARRO
typedef struct
{
	NODE_VIAGEM* header; // ponteiro para o primeiro NO
	NODE_VIAGEM* ultimo_node; // ponteiro para o último NO
	int num_elem; // número total de viagens
}LISTA_VIAGEM;

//prototipagem
LISTA_VIAGEM* criarListaViagem();
NODE_VIAGEM* criarNodeViagem();
int freeNodeViagem(NODE_VIAGEM* node);
LISTA_VIAGEM* carregarViagens(PASSAGEM_LISTA* listaPassagens, DISTANCIAS_LISTA* listaDistancias);
void freeListaViagens(LISTA_VIAGEM* lista);
float DistanciaEntreSensores(int codS1, int codS2, DISTANCIAS_LISTA* listaDist);
int totalKmsPercorridosListaCarro(LISTA_CARRO* listaCarros, DISTANCIAS_LISTA* listaDistancias, PASSAGEM_LISTA* listaPassagens, int diaInicio, int mesInicio, int anoInicio, int diaFim, int mesFim, int anoFim);
void rankingMarcaPorKm(LISTA_HASHC* listaHash, DISTANCIAS_LISTA* listaDistancia, PASSAGEM_LISTA* listaPassagem, int diaInicio, int mesInicio, int anoInicio, int diaFim, int mesFim, int anoFim);
