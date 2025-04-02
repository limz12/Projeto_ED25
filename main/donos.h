#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NOME_SIZE 100
#define MAX_CODPOST_SIZE 10

// ESTRUTURAS DO DONO
typedef struct Donos
{
    int numCont;
    char nome[MAX_NOME_SIZE];
    char codpost[MAX_CODPOST_SIZE];
    struct Donos* prox;  // Ponteiro para o próximo nó da lista
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

