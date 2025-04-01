#pragma once

// BIBLIOTECAS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>


// CONSTANTES

#define MAX_CHAR_GRANDE 20
#define MAX_CHAR_MATRICULA 8


// ESTRUTURAS

typedef struct Carro
{
	char* marca[MAX_CHAR_GRANDE + 1];
	char* modelo[MAX_CHAR_GRANDE + 1];
	char* matricula[MAX_CHAR_MATRICULA + 1];
	int ano;
	int dono;
	int codVeiculo;
	CARRO* ptr;
}CARRO;


// PROTOTIPAGEM

void carregarDados();