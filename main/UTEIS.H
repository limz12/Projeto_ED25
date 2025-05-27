/**
 * @file UTEIS.H
 * @brief Definicao das Estruturas relacionadas com funcoes uteis e prototipagem das funcoes utilizadas no UTEIS.c
 */


typedef struct listaSensor LISTA_SENSOR;
typedef struct distanciaLista DISTANCIAS_LISTA;
typedef struct passagemLista PASSAGEM_LISTA;
typedef struct listaCarro LISTA_CARRO;
typedef struct ListaDonos LISTA_DONOS;
typedef struct listaHashCarros LISTA_HASHC;


// PROTOTIPAGEM
int calcularTamanhoEDSensor(LISTA_SENSOR* lista);
int calcularTamanhoEDDistancia(DISTANCIAS_LISTA* lista);
int calcularTamanhoEDPassagem(PASSAGEM_LISTA* lista);
int calcularTamanhoEDDonos(LISTA_DONOS* lista);
int calcularTamanhoEDCarro(LISTA_HASHC* listaHash);
void memoriaTotalOcupadaED(LISTA_SENSOR* listaSensor, DISTANCIAS_LISTA* listaDistancias, PASSAGEM_LISTA* listaPassagem, LISTA_HASHC* listaHashCarros, LISTA_DONOS* listaDonos);
int inicializarED(LISTA_SENSOR* listaSensor, DISTANCIAS_LISTA* listaDistancias, PASSAGEM_LISTA* listaPassagem, LISTA_HASHC* listaHashCarros, LISTA_DONOS* listaDonos);

void exportar_csv_DONOS(LISTA_DONOS* lista);
void exportar_csv_SENSORES(LISTA_SENSOR* listaSensor);
void exportar_csv_DISTANCIAS(DISTANCIAS_LISTA* listaDistancias);
void exportar_csv_CARROS(LISTA_HASHC* listaHash);
void exportar_csv_PASSAGENS(PASSAGEM_LISTA* listaPassagem);

void exportar_xml_DONOS(LISTA_DONOS* listaDonos);
void exportar_xml_SENSORES(LISTA_SENSOR* listaSensor);
void exportar_xml_DISTANCIAS(DISTANCIAS_LISTA* listaDistancias);
void exportar_xml_PASSAGENS(PASSAGEM_LISTA* listaPassagens);
void exportar_xml_CARROS(LISTA_HASHC* listaHashCarros);
