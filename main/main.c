#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include "SENSORES.H"
#include "DISTANCIAS.H"
#include "PASSAGEM.H"
#include "UTEIS.H"
#include "MENU.H"
//FALTA CARREGAR CARROS - DONOS E CALCULAR TAMANHO sizeof() destes 2 

void main()
{
    //CRIAR AS LISTAS
    LISTA_SENSOR* listaSensor = criarListaSensor();
    DISTANCIAS_LISTA* listaDistancias = criarListaDistancias();
    PASSAGEM_LISTA* listaPassagem = criarListaPassagem();
    //**********************************
    //para o compilador reconhecer os caracteres especiais do ficheiro, visto que sem esta linha obtinha caracteres estranhos
    setlocale(LC_ALL, "pt_PT.UTF-8");
    printf("PROJETO ED 2025\n");
    
    //CARREGA TODA A ED
    int ED = inicializarED(listaSensor, listaDistancias, listaPassagem);
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
        switch (menuPrincipal(listaSensor, listaDistancias, listaPassagem))
        {
            case 1:
                //MENU DONOS
                //limpar a linha de comandos
                system("cls");
            break;
            case 2:
                //MENU CARROS
                system("cls");
            break;
            case 3:
                //MENU DISTANCIAS
                menuDistancias(listaDistancias);
            break;
            case 4:
                //MENU PASSAGENS
                system("cls");
                menuPassagens(listaPassagem);
                
            break;
            case 5:
                //MENU SENSORES
                system("cls");
                menuSensores(listaSensor);
            break;
            case 6:
                system("cls");
                memoriaTotalOcupadaED(listaSensor, listaDistancias, listaPassagem);
                printf("\n");
            break;
            case 0:
                //libertar todos os dados e fechar o programa
                libertarListaDistancia(listaDistancias);
                libertarListaPassagem(listaPassagem);
                libertarListaSensores(listaSensor);
                return 0;
           break;

        }
    }

    
   //*************  PARA TESTES DE BRANCH, COMENTAR TUDO O QUE ESTA ACIMA    ****************************

}

