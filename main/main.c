#include <stdlib.h>
#include <stdio.h>

#include "SENSORES.H"
#include "DISTANCIAS.H"

int main()
{
    printf("PROJETO ED 2025\n");
    //CARREGAR SENSORES
    LISTA_SENSOR* listaSensor = criarListaSensor();
    NODE_SENSOR* nodeSensor = criarNodeSensor();
    carregarSensor(listaSensor);
    libertarNodeSensor(nodeSensor);
    //CARREGAR DISTANCIA
    DISTANCIAS_LISTA* listaDistancias = criarListaDistancias();
    DISTANCIAS_NODE* nodeDistancia = criarNodeDistancias();
    carregarDistancia(listaDistancias);
    mostrarListaDISTANCIA(listaDistancias); //FALTA DESTRUIR NO 
    //CARREGAR PASSAGEM
}

