#include <stdlib.h>
#include <stdio.h>

#include "carros.h"
#include "SENSORES.H"
#include "DISTANCIAS.H"
#include "PASSAGEM.H"
#include "UTEIS.H"
#include "MENU.H"
#include "donos.h"
#include "Stats.h"

int totalKmsPercorridosListaCarro(LISTA_CARRO* listaCarro, DISTANCIAS_LISTA* listaDistancia, PASSAGEM_LISTA* listaPassagem)
{
    // Criação de elementos auxiliares para percorrer as listas
    NODE_CARRO* auxC = listaCarro->header;
    DISTANCIAS_NODE* auxD = listaDistancia->header;
    PASSAGEM_NODE* auxP = listaPassagem->header;
    int soma_total_km_lista = 0;

    while (auxC)
    {
        if (auxC->info->codVeiculo == auxP->info->codVeiculo && auxP->info->idSensor == auxD->info->codSensor1) // TESTE
        {
            auxC->info->total_km = auxD->info->distanciaPercorrida;
        }

        soma_total_km_lista += auxC->info->total_km;

        auxC = auxC->next;
        auxD = auxD->next;
        auxP = auxP->next;
    }

    return soma_total_km_lista;
}

//ordenar marcas por mais km's percorridos
void rankingMarcaPorKm(LISTA_HASHC* listaHash, DISTANCIAS_LISTA* listaDistancia, PASSAGEM_LISTA* listaPassagem)
{
    if (!listaHash)
    {
        printf("ERRO! A lista HASH nao existe.\n");
        return;
    }

    // Percorrer a Hash de Carros
    NODE_HASHC* aux = listaHash->header;

    while (aux)
    {
        // Conta os Km's percorridos por cada Marca
        aux->total_Km_marca = totalKmsPercorridosListaCarro(aux->listaCarros, listaDistancia, listaPassagem);

        aux = aux->next;
    }

    // Ordena a Hash por ordem de Marcas com mais km's percorridos
    //bouble sort
    NODE_HASHC* atual;
    NODE_HASHC* proximo;
    LISTA_CARRO* temp; // para trocar as listas dentro dos nós
    char temp_chave[MAX_CHAR_STR]; // para trocar as listas dentro dos nós
    int troca;

    printf("A ORDENAR HASH!\n");

    do
    {
        troca = 0;
        atual = listaHash->header;

        while (atual->next != NULL) // Percorre a Hash
        {
            proximo = atual->next;

            if (atual->total_Km_marca < proximo->total_Km_marca)
            {    // Trocar as listas dos nos
                temp = atual->listaCarros;
                atual->listaCarros = proximo->listaCarros;
                proximo->listaCarros = temp;

                // Trocar as chaves dos nos
                strcpy(temp_chave, atual->chave);
                strcpy(atual->chave, proximo->chave);
                strcpy(proximo->chave, temp_chave);

                troca = 1;
            }

            atual = atual->next;
        }
    } while (troca);//vai parar quando percorrer toda a hash e verificar que realmente nao foram efetuadas trocas

    printf("HASH ORDENADA COM SUCESSO\n");
}