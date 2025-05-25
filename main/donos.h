#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>

typedef struct listaSensor LISTA_SENSOR;
typedef struct distanciaLista DISTANCIAS_LISTA;
typedef struct passagemLista PASSAGEM_LISTA;
typedef struct listaCarro LISTA_CARRO;
typedef struct ListaDonos LISTA_DONOS;
typedef struct listaHashCarros LISTA_HASHC;

#define MAX_NOME_SIZE 60
#define MAX_CODPOST_SIZE 10

// ESTRUTURAS DO DONO
typedef struct Donos
{
    char nome[MAX_NOME_SIZE];
    char codpost[MAX_CODPOST_SIZE];
    int numCont;
    //struct Donos* prox;  // Ponteiro para o próximo nó da lista
} Donos;

// NODE DO DONO
typedef struct nodeDonos
{
    Donos* info;
    struct nodeDonos* next;
} NODE_DONOS;

// LISTA DONO
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