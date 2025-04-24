#include <stdio.h>
#include <stdlib.h>


typedef struct listaSensor LISTA_SENSOR;
typedef struct distanciaLista DISTANCIAS_LISTA;
typedef struct passagemLista PASSAGEM_LISTA;
typedef struct listaCarro LISTA_CARRO;
typedef struct ListaDonos LISTA_DONOS;
typedef struct listaHashCarros LISTA_HASHC;



int calcularTamanhoEDSensor(LISTA_SENSOR* lista);
int calcularTamanhoEDDistancia(DISTANCIAS_LISTA* lista);
int calcularTamanhoEDPassagem(PASSAGEM_LISTA* lista);

//******************** ERRO QUANDO DOU PROTOT ******************************
int calcularTamanhoEDDonos(LISTA_DONOS* lista);
int calcularTamanhoEDCarro(LISTA_HASHC* listaHash);
void memoriaTotalOcupadaED(LISTA_SENSOR* listaSensor, DISTANCIAS_LISTA* listaDistancias, PASSAGEM_LISTA* listaPassagem, LISTA_HASHC* listaHashCarros, LISTA_DONOS* listaDonos);
int inicializarED(LISTA_SENSOR* listaSensor, DISTANCIAS_LISTA* listaDistancias, PASSAGEM_LISTA* listaPassagem, LISTA_HASHC* listaHashCarros, LISTA_DONOS* listaDonos);
