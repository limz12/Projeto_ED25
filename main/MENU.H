/**
 * @file MENU.H
 * @brief Definicao das Estruturas relacionadas com os menus e prototipagem das funcoes utilizadas no MENU.c
 */


typedef struct listaSensor LISTA_SENSOR;
typedef struct distanciaLista DISTANCIAS_LISTA;
typedef struct passagemLista PASSAGEM_LISTA;
typedef struct listaCarro LISTA_CARRO;
typedef struct ListaDonos LISTA_DONOS;
typedef struct listaHashCarros LISTA_HASHC;


// PROTOTIPAGEM
int verificarNumero(int max);
int menuPrincipal(LISTA_SENSOR* listaSensor, DISTANCIAS_LISTA* listaDistancias, PASSAGEM_LISTA* listaPassagem, LISTA_CARRO* listaCarro, LISTA_DONOS* listaDonos);
void menuDistancias(DISTANCIAS_LISTA* listaDistancias);
void menuPassagens(PASSAGEM_LISTA* listaPassagens, LISTA_HASHC* listaHashCarros, PASSAGEM_LISTA* listaDistancias);
void menuSensores(LISTA_SENSOR* listaSensores);
void menuCarros(LISTA_HASHC* hashCarros, LISTA_DONOS* listaDonos, PASSAGEM_LISTA* listaPassagens, DISTANCIAS_LISTA* listaDistancias);
void menuDonos(LISTA_DONOS* listaDonos, LISTA_HASHC* hashCarro, PASSAGEM_LISTA* listaPassagens, DISTANCIAS_LISTA* listaDistancias);

