/**
 * @file DISTANCIAS.H
 * @brief Definicao das Estruturas relacionadas com as distancias e prototipagem das funcoes utilizadas no DISTANCIAS.C
 */


 /**
 * @struct distancia
 * @brief Estrutura que representa uma distancia
 */
typedef struct distancia
{
	int codSensor1;
	int codSensor2;
	float distanciaPercorrida;
}DISTANCIAS;

/**
* @struct nodeDistancia
* @brief Estrutura que serve de node e contem o ponteiro da distancia e do proximo node
*/
typedef struct nodeDistancia
{
	DISTANCIAS* info;
	struct nodeDistancia* next;
}DISTANCIAS_NODE;

/**
* @struct distanciaLista
* @brief Estrutura serve como lista para o conjunto dos DISTANCIAS_NODE
*/
typedef struct distanciaLista
{
	DISTANCIAS_NODE* header; // aponta para o primeiro no
	DISTANCIAS_NODE* ultimoNode; // aponta par o ultimo no
	int numelementos;
}DISTANCIAS_LISTA;

// PROTOTIPAGEM
DISTANCIAS_LISTA* criarListaDistancias();
DISTANCIAS_NODE* criarNodeDistancias();
void carregarDistancia(DISTANCIAS_LISTA *lista);
void adicionarLista(DISTANCIAS_LISTA* lista, DISTANCIAS_NODE* node);
void libertarNodeDistancia(DISTANCIAS_NODE* node);
void mostrarListaDISTANCIA(DISTANCIAS_LISTA* lista);
void libertarListaDistancia(DISTANCIAS_LISTA* lista);
float distanciaEntreSensor(int sensor1, int sensor2, DISTANCIAS_LISTA* listaDistancias);
