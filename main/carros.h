// BIBLIOTECAS
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>


// CONSTANTES
#define MAX_CHAR_STR 20
#define MAX_CHAR_MATRICULA 8


// ESTRUTURAS DO CARRO
typedef struct Carro 
{
	char matricula[MAX_CHAR_MATRICULA + 1];
	char marca[MAX_CHAR_STR + 1];
	char modelo[MAX_CHAR_STR + 1];
	int ano;
	int dono;
	int codVeiculo;
} CARRO;

// NODE DO CARRO
typedef struct nodeCarro
{
	CARRO* info;
	struct nodeCarro* next;
} NODE_CARRO;

// LISTA CARRO
typedef struct ListaCarro
{
	NODE_CARRO* header; // ponteiro para o primeiro NO
	NODE_CARRO* ultimo_node; // ponteiro para o último NO
	int num_elem;
} LISTA_CARRO;

// PROTOTIPAGEM
LISTA_CARRO* criarListaCarro();
NODE_CARRO* criarNodeCarro();
int freeNodeCarro(NODE_CARRO* node);
void carregarDadosCarro(LISTA_CARRO* lista);
void addListaCarro(LISTA_CARRO* lista, NODE_CARRO* node);
void criarCarroUtilizador(LISTA_CARRO* lista);
void mostrarListaSensores(LISTA_CARRO* lista);
void freeListaCarro(LISTA_CARRO* lista);
