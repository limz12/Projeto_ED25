#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <ctype.h>

#include "carros.h"
#include "SENSORES.H"
#include "DISTANCIAS.H"
#include "PASSAGEM.H"
#include "UTEIS.H"
#include "MENU.H"
#include "donos.h"
#include "Stats.h"

//FALTA CARREGAR  DONOS E CALCULAR TAMANHO sizeof() deste

void main()
{
    //CRIAR AS LISTAS
    LISTA_SENSOR* listaSensor = criarListaSensor();
    DISTANCIAS_LISTA* listaDistancias = criarListaDistancias();
    PASSAGEM_LISTA* listaPassagem = criarListaPassagem();
   // LISTA_CARRO* listaCarro = criarListaCarro(); -> alterar pelo iniciar hashCarro
    LISTA_DONOS* listaDonos = criarListaDonos();
    //LISTA_VIAGEM* listaViagens = criarListaViagem();
    //********** HASHING **************
    //INICIAR A LISTA HASHING
    LISTA_HASHC* listaHashCarros = criarListaHashCarro();
    //**********************************
    //para o compilador reconhecer os caracteres especiais do ficheiro, visto que sem esta linha obtinha caracteres estranhos
    setlocale(LC_ALL, "pt_PT.UTF-8");
    printf("PROJETO ED 2025\n");
    
    //CARREGA TODA A ED
    int ED = inicializarED(listaSensor, listaDistancias, listaPassagem, listaHashCarros, listaDonos); // listaViagens
    if (ED == 1)
    {
        printf("Estrutura de dados carregada com sucesso!\n");
        system("cls");
    }
    else
    {
        printf("ERRO! ESTRUTURA NAO FOI CRIADA\n");
        return -1;
    }
    
   
   
    //este for com ; ; serve para o programa correr infinitamente
    for (; ;)
    {
        switch (menuPrincipal(listaSensor, listaDistancias, listaPassagem,listaHashCarros, listaDonos)) // listaViagens
        {
            case 1:
                //MENU DONOS
                //limpar a linha de comandos
                system("cls");
                menuDonos(listaDonos,listaHashCarros);
            break;
            case 2:
                //MENU CARROS
                system("cls");
                menuCarros(listaHashCarros,listaDonos);
            break;
            case 3:
                //MENU DISTANCIAS
                menuDistancias(listaDistancias);
            break;
            case 4:
                //MENU PASSAGENS
                system("cls");
                menuPassagens(listaPassagem,listaHashCarros);
                
            break;
            case 5:
                //MENU SENSORES
                system("cls");
                menuSensores(listaSensor);
            break;
            case 6:
                //MENU ESTATÍSTICAS
                system("cls");
                menuSTATS(listaSensor, listaDistancias, listaPassagem, listaHashCarros, listaDonos); // listaViagens
                break;
            case 7:
                //CALCULAR MEMORIA TOTAL da ED
                system("cls");
                memoriaTotalOcupadaED(listaSensor, listaDistancias, listaPassagem, listaHashCarros, listaDonos);
                printf("\n");
            break;
            case 0:
                //libertar todos os dados e fechar o programa
                libertarListaDistancia(listaDistancias);
                libertarListaPassagem(listaPassagem);
                libertarListaSensores(listaSensor);
                freeListaHashCarro(listaHashCarros);
                freeListaDonos(listaDonos);
                //freeListaViagens(listaViagens);
                return 0;
           break;

        }
    }


   //*************  PARA TESTES DE BRANCH, COMENTAR TUDO O QUE ESTA ACIMA    ****************************
}
