#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include "SENSORES.H"
#include "DISTANCIAS.H"
#include "PASSAGEM.H"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    printf("PROJETO ED 2025\n");
    //CARREGAR SENSORES ------------ carregar info ficheiro ERRO

    /*
    LISTA_SENSOR* listaSensor = criarListaSensor();
    NODE_SENSOR* nodeSensor = criarNodeSensor();
    carregarSensor(listaSensor);
    //FALTA MOSTRAR A LISTA SENSOR
    libertarNodeSensor(nodeSensor);
    */

    //CARREGAR DISTANCIA
    
    DISTANCIAS_LISTA* listaDistancias = criarListaDistancias();
    DISTANCIAS_NODE* nodeDistancia = criarNodeDistancias();
    carregarDistancia(listaDistancias);
    //mostrarListaDISTANCIA(listaDistancias);
    libertarNodeDistancia(nodeDistancia);
    
    
    //CARREGAR PASSAGEM
    PASSAGEM_LISTA* listaPassagem = criarListaPassagem();
    PASSAGEM_NODE* nodePassagem = criarNodePassagem();
    carregarPassagem(listaPassagem);
    //mostrarListaPassagem(listaPassagem);
    libertarNodePassagem(nodePassagem);

    //NO FIM DE TUDO FEITO CRIAR UM STARTUP QUE INICIE TODOS OS CARREGAMENTOS E VERIFIQUE SE ESTAO CARREGADOS
}

