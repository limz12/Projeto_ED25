#include <stdlib.h>
#include <stdio.h>

#define MAX_CHAR 50


//ESTRUTURA DO SENSOR
typedef struct
{
	int codSensor;
	char designacao[MAX_CHAR];
	char infoLatitude[MAX_CHAR];
	char infoLongitude[MAX_CHAR];
}SENSOR;

//NODE DO SENSOR
typedef struct nodeSensor
{
	SENSOR* info;
	struct nodeSensor* next;
}NODE_SENSOR;

//LISTA SENSOR
typedef struct
{
	//ponteiro para o primeiro NO
	NODE_SENSOR* header;
	//ponteiro para o ultimo NO
	NODE_SENSOR* ultimoNODE;
	int numElementos;
}LISTA_SENSOR;

//PROTOTIPAGEM

LISTA_SENSOR* criarListaSensor();
NODE_SENSOR* criarNodeSensor();
int libertarNodeSensor(NODE_SENSOR* node);
void carregarSensor(LISTA_SENSOR* lista);
void adicionarListaSensores(LISTA_SENSOR* lista, NODE_SENSOR* node);
