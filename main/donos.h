/**
 * @file donos.h
 * @brief Definicao das Estruturas relacionadas com os donos e prototipagem das funcoes utilizadas no donos.c
 */


typedef struct listaSensor LISTA_SENSOR;
typedef struct distanciaLista DISTANCIAS_LISTA;
typedef struct passagemLista PASSAGEM_LISTA;
typedef struct listaCarro LISTA_CARRO;
typedef struct ListaDonos LISTA_DONOS;
typedef struct listaHashCarros LISTA_HASHC;

// CONSTANTES
#define MAX_NOME_SIZE 60
#define MAX_CODPOST_SIZE 10
#define DONOS_POR_PAGINA 20 // max de donos por pagina


 /**
 * @struct Donos
 * @brief Estrutura que representa uma Donos
 */
typedef struct Donos
{
    char nome[MAX_NOME_SIZE];
    char codpost[MAX_CODPOST_SIZE];
    int numCont;
} Donos;

/**
* @struct nodeDonos
* @brief Estrutura que serve de node e contem o ponteiro do Dono e do proximo node
*/
typedef struct nodeDonos
{
    Donos* info;
    struct nodeDonos* next;
} NODE_DONOS;

/**
* @struct ListaDonos
* @brief Estrutura serve como lista para o conjunto dos NODE_DONOS
*/
typedef struct ListaDonos
{
    NODE_DONOS* primeiro; // Ponteiro para o primeiro nó
    NODE_DONOS* ultimo; // Ponteiro para o último nó
	int elem;   // Número de elementos na lista
} LISTA_DONOS;

// PROTOTIPAGEM
LISTA_DONOS* criarListaDonos();
NODE_DONOS* criarNodeDonos();
int freeNodeDonos(NODE_DONOS* node);
void carregarDadosDonos(LISTA_DONOS* lista);
void adicionarListaDonos(LISTA_DONOS* lista, NODE_DONOS* node);
void registarDonos(LISTA_DONOS* lista);
void listarDonos(LISTA_DONOS* lista);
void freeListaDonos(LISTA_DONOS* lista);
void ordenarListaDonosAlfabeticamente(LISTA_DONOS* lista);
void ordenarListaDonosContribuinte(LISTA_DONOS* lista); // ex 5
void maiorVelocidadeMediaDonos(LISTA_DONOS* listaDnos, LISTA_HASHC* listaHashCarros, PASSAGEM_LISTA* listaPassagens, DISTANCIAS_LISTA* listaDistancias);
void velocidadeMediaPorCodigoPostal(LISTA_DONOS* listaDonos, LISTA_HASHC* listaHashCarros,PASSAGEM_LISTA* listaPassagens, DISTANCIAS_LISTA* listaDistancias,const char* codigoPostal);
NODE_DONOS* avancarAteDono(NODE_DONOS* nodeDono, int pos);
