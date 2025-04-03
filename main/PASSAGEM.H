#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	//para os dias em que o carro passou pelo sensor
	int dia;
	int mes;
	int ano;
	//para a hora em que o carro passou no sensor
	int hora;
	int minuto;
	int segundo;
	int milisegundo;

}DATA;

typedef struct
{
	int idSensor;
	int codVeiculo;
	DATA* data;
	int tipoRegisto; //  atributo “tipo de registo” contem um de 2 valores: 0 = entrada, 1 = saída.
	
}PASSAGEM;

typedef struct nodePassagem
{
	PASSAGEM* info;
	struct nodePassagem* next;
}PASSAGEM_NODE;

typedef struct
{
	PASSAGEM_NODE* header;
	PASSAGEM_NODE* ultimoNode;
	int numElementos;
}PASSAGEM_LISTA;

//prototiopagem
PASSAGEM_LISTA* criarListaPassagem();
PASSAGEM_NODE* criarNodePassagem();
void carregarPassagem(PASSAGEM_LISTA* lista);
void adicionarListaPassagem(PASSAGEM_LISTA* lista, PASSAGEM_NODE* node);
void mostrarListaPassagem(PASSAGEM_LISTA* lista);
void libertarNodePassagem(PASSAGEM_NODE* node);
void libertarListaPassagem(PASSAGEM_LISTA* lista);
void registarPassagem(PASSAGEM_LISTA* lista);
int verificarNodeDadosPassagem(PASSAGEM_NODE* node);
