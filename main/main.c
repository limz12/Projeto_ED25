#include <stdlib.h>
#include <stdio.h>

#include "SENSORES.H"

int main()
{
    printf("PROJETO ED 2025\n");
    //CARREGAR SENSORES
    LISTA_SENSOR* listaSensor = criarListaSensor();
    NODE_SENSOR* nodeSensor = criarNodeSensor();
    carregarSensor(listaSensor);
    libertarNodeSensor(nodeSensor);
    //CARREGAR DISTANCIA
    //CARREGAR PASSAGEM
}

