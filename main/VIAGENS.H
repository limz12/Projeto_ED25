#include <stdlib.h>
#include <stdio.h>

#include "carros.h"

typedef struct nodeViagem
{
	float totalKm; // vai armazenar todos os km percorridos em viagem do carro
	CARRO* carro;
	struct nodeViagem* next;
}NODE_VIAGENS;

//lista que vai conter nodesViagens
typedef struct
{
	NODE_VIAGENS* header;
	NODE_VIAGENS* ultimoNode;
}LISTA_VIAGENS;

//prototipagens
LISTA_VIAGENS* criarListaViagens();
NODE_VIAGENS* criarNodeViagens();
int existeCarroListaViagens(LISTA_VIAGENS* listaViagens, int codCarro);
void adicionarNodeListaViagens(NODE_VIAGENS* nodeViagens, LISTA_VIAGENS* listaViagens);