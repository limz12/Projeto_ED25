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
//void carrosCircularamduranteX(PASSAGEM* listaPassagem, LISTA_HASHC* listaCarros);
int checkPeriodoX(PASSAGEM_NODE* nodePassagem, DATA* periodoInicial, DATA* periodoFinal);
//int maiorMatricula(int pCarro, int sCarro, LISTA_HASHC* listaHashCarro);
//NODE_CARRO* procurarPorId(int id, LISTA_HASHC* listaHash);
//void totalKmCarroDuranteX(LISTA_CARRO* listaHashCarros, PASSAGEM_LISTA* listaPassagem, DISTANCIAS_LISTA* listaDistancias);
//CARRO* retornaCarro(LISTA_HASHC* listaHash, int id);
int compararCarros(const void* a, const void* b);