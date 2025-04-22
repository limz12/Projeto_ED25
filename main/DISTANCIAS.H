#include <stdlib.h>
#include <stdio.h>

//ESTRUTURA DISTANCIA
typedef struct 
{
	int codSensor1;
	int codSensor2;
	float distanciaPercorrida;
}DISTANCIAS;

//NO da distancias
typedef struct nodeDistancia
{
	DISTANCIAS* info;
	struct nodeDistancia* next;
}DISTANCIAS_NODE;

typedef struct distanciaLista
{
	//aponta para o primeiro no
	DISTANCIAS_NODE* header;
	//aponta par o ultimo no
	DISTANCIAS_NODE* ultimoNode;
	int numelementos;

}DISTANCIAS_LISTA;

//prototipagem
DISTANCIAS_LISTA* criarListaDistancias();
DISTANCIAS_NODE* criarNodeDistancias();
void carregarDistancia(DISTANCIAS_LISTA *lista);
void adicionarLista(DISTANCIAS_LISTA* lista, DISTANCIAS_NODE* node);
void libertarNodeDistancia(DISTANCIAS_NODE* node);
void mostrarListaDISTANCIA(DISTANCIAS_LISTA* lista);
void libertarListaDistancia(DISTANCIAS_LISTA* lista);
float distanciaEntreSensor(int sensor1, int sensor2, DISTANCIAS_LISTA* listaDistancias);
