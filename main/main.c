#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include "SENSORES.H"
#include "DISTANCIAS.H"
#include "PASSAGEM.H"
#include "UTEIS.H"
int main()
{
    //para o compilador reconhecer os caracteres especiais do ficheiro, visto que sem esta linha obtinha caracteres estranhos
    setlocale(LC_ALL, "pt_PT.UTF-8");
    printf("PROJETO ED 2025\n");
    //CARREGAR SENSORES ------------ FEITO

    /*
    LISTA_SENSOR* listaSensor = criarListaSensor();
    NODE_SENSOR* nodeSensor = criarNodeSensor();
    carregarSensor(listaSensor);
    mostrarListaSensores(listaSensor);
    //libertarNodeSensor(nodeSensor);
    //libertarListaSensores(listaSensor);
    */

    //CARREGAR DISTANCIA --------------- FEITO
    
    /*
    DISTANCIAS_LISTA* listaDistancias = criarListaDistancias();
    DISTANCIAS_NODE* nodeDistancia = criarNodeDistancias();
    carregarDistancia(listaDistancias);
    mostrarListaDISTANCIA(listaDistancias);
    //libertarNodeDistancia(nodeDistancia);
    //libertarListaDistancia(listaDistancias);
    */
    
    
    //CARREGAR PASSAGEM --------------- FEITO
    PASSAGEM_LISTA* listaPassagem = criarListaPassagem();
    PASSAGEM_NODE* nodePassagem = criarNodePassagem();
    carregarPassagem(listaPassagem);
    registarPassagem(listaPassagem);
    mostrarListaPassagem(listaPassagem);
    //libertarNodePassagem(nodePassagem);
    //libertarListaPassagem(listaPassagem);
    
    //MEMORIA OCUPADA POR TODA A ESTRUTURA DE DADOS
    
    //memoriaTotalOcupadaED(listaSensor, listaDistancias, listaPassagem);
    
    //NO FIM DE TUDO FEITO CRIAR UM STARTUP QUE INICIE TODOS OS CARREGAMENTOS E VERIFIQUE SE ESTAO CARREGADOS\

}

