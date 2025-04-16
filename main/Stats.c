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

//--------------------------------------------------------------------------------------------------------

//funcao para criar a lista Viagens
LISTA_VIAGENS* criarListaViagens()
{
    //alocar memoria
    LISTA_VIAGENS* listaViagens = (LISTA_VIAGENS*)malloc(sizeof(LISTA_VIAGENS));
    listaViagens->header = NULL;
    listaViagens->ultimoNode = NULL;
    return listaViagens;
}

//funcao para criar o node da lista Viagens
NODE_VIAGENS* criarNodeViagens()
{
    //alocar mem
    NODE_VIAGENS* nodeViagens = (NODE_VIAGENS*)malloc(sizeof(NODE_VIAGENS));

    nodeViagens->carro = (CARRO*)malloc(sizeof(CARRO));
    nodeViagens->totalKm = 0;
    nodeViagens->next = NULL;
    return nodeViagens;
}

//verificar se o determinado carro existe na lista
int existeCarroListaViagens(LISTA_VIAGENS* listaViagens, int codCarro)
{
    if (!listaViagens || !codCarro)
    {
        return;
    }
    //variavel auxiliar para percorrer a lista
    NODE_VIAGENS* nodeViagens = listaViagens->header;
    while (nodeViagens)
    {
        //o carro existe
        if (nodeViagens->carro->codVeiculo == codCarro)
        {
            return 1;
        }
        nodeViagens = nodeViagens->next;
    }
    //se percorrer a lista toda e nao encontrar
    return 0;
}

CARRO* retornaCarro(LISTA_HASHC* listaHash, int id)
{
    //alocar mem
    NODE_CARRO* nodeCarroEncontrado = (NODE_CARRO*)malloc(sizeof(NODE_CARRO));

    NODE_HASHC* nodeHashCarro = listaHash->header;
    //procurar na lista o ID CARRO
    while (nodeHashCarro)
    {
        NODE_CARRO* nodeCarros = nodeHashCarro->listaCarros->header;
        while (nodeCarros)
        {

            if (nodeCarros->info->codVeiculo == id)
            {
                nodeCarroEncontrado = nodeCarros;

                return nodeCarroEncontrado->info;
            }
            nodeCarros = nodeCarros->next;

        }
        nodeHashCarro = nodeHashCarro->next;
    }
    return NULL;
}

//adiciona o nodeViagem na Lista Viagem
void adicionarNodeListaViagens(NODE_VIAGENS* nodeViagens, LISTA_VIAGENS* listaViagens)
{
    if (!nodeViagens || !listaViagens)
    {
        return;
    }
    // se a lista nao tiver nenhum node
    if (listaViagens->header == NULL)
    {
        listaViagens->header = nodeViagens;
        listaViagens->ultimoNode = nodeViagens;
    }
    else // se a lista ja tiver nodes, adiciona no fim
    {
        listaViagens->ultimoNode->next = nodeViagens;
        listaViagens->ultimoNode = nodeViagens;

    }

}

// -------------------------------------------- EX 9 -----------------------------------------------------

/*
// FUNÇÃO ANTIGA FEITA PELO CHAT
float totalKmsPercorridosListaCarro(LISTA_CARRO* listaHashCarros, PASSAGEM_LISTA* listaPassagem, DISTANCIAS_LISTA* listaDistancias)
{
    if (!listaPassagem || !listaHashCarros || !listaDistancias)
    {
        return;
    }

    //guardar input do user o periodo inicial
    DATA* periodoInicial = (DATA*)malloc(sizeof(DATA));
    //guardar input do user o periodo final
    DATA* periodoFinal = (DATA*)malloc(sizeof(DATA));
    if (periodoInicial && periodoFinal == NULL)
    {
        return;
    }

    //pedir o periodo inicial
    printf("INSIRA O DIA INICIAL DE PESQUISA!\n");
    printf("DIA: ");
    scanf("%d", &periodoInicial->dia);
    printf("MES: ");
    scanf("%d", &periodoInicial->mes);
    printf("ANO: ");
    scanf("%d", &periodoInicial->ano);
    printf("**************************\n");
    //pedir o periodo final
    printf("INSIRA O DIA FINAL DE PESQUISA!\n");
    printf("DIA: ");
    scanf("%d", &periodoFinal->dia);
    printf("MES: ");
    scanf("%d", &periodoFinal->mes);
    printf("ANO: ");
    scanf("%d", &periodoFinal->ano);
    printf("**************************\n");
    //pedir hora inicial
    printf("INSIRA A HORA INICIAL DE PESQUISA!\n");
    printf("HORA: ");
    scanf("%d", &periodoInicial->hora);
    printf("MINUTOS: ");
    scanf("%d", &periodoInicial->minuto);
    //pedir hora final
    printf("INSIRA A HORA FINAL DE PESQUISA!\n");
    printf("HORA: ");
    scanf("%d", &periodoFinal->hora);
    printf("MINUTOS: ");
    scanf("%d", &periodoFinal->minuto);
    //descartamos os segundos

    //criar ListaViagens
    LISTA_VIAGENS* listaViagens = criarListaViagens();

    //verificar se algum carro passou na autoestrada durante periodo X
    PASSAGEM_NODE* nodePassagem = listaPassagem->header;

    int idEntrada = 0;
    int idSaida = 0;
    while (nodePassagem)
    {

        //encontrar as datas que satisfacam a condicao
        if (checkPeriodoX(nodePassagem, periodoInicial, periodoFinal) == 1)
        {
            //verificar se ja existe o carro na lista VIAGENS (EVITAR REPETICAO DE DADOS)
            if (existeCarroListaViagens(listaViagens, nodePassagem->info->codVeiculo) == 0) //se nao existir o carro
            {
                //criar o NODE_VIAGENS
                NODE_VIAGENS* nodeViagens = criarNodeViagens();
                //adicionar o carro ao NODE_VIAGENS
                nodeViagens->carro = retornaCarro(listaHashCarros, nodePassagem->info->codVeiculo);
                //adicionar o ID de entrada e saida
                idEntrada = nodePassagem->info->idSensor;
                idSaida = nodePassagem->next->info->idSensor;

                //ver a distancia entre o ENTRADA E SAIDA E SOMAR (PODE RECEBER [3 - 1] ou [1 - 3], atencao)
                nodeViagens->totalKm += distanciaEntreSensor(idEntrada, idSaida, listaDistancias);

                //adicionar a lista nodeViagens a lista Viagens
                adicionarNodeListaViagens(nodeViagens, listaViagens);
            }
        }
        nodePassagem = nodePassagem->next;
    }

    NODE_VIAGENS* atual = listaViagens->header;

    atual = listaViagens->header;
    while (atual) {
        NODE_VIAGENS* temp = atual;
        atual = atual->next;
        free(temp); // não damos free ao carro, pois é só uma referência
    }
    free(listaViagens);
    free(periodoInicial);
    free(periodoFinal);
}
*/

/*
void totalKmCarroDuranteX(LISTA_CARRO* listaHashCarros, PASSAGEM_LISTA* listaPassagem, DISTANCIAS_LISTA* listaDistancias)
{
    if (!listaPassagem || !listaHashCarros || !listaDistancias)
    {
        return;
    }

    //guardar input do user o periodo inicial
    DATA* periodoInicial = (DATA*)malloc(sizeof(DATA));
    //guardar input do user o periodo final
    DATA* periodoFinal = (DATA*)malloc(sizeof(DATA));
    if (periodoInicial && periodoFinal == NULL)
    {
        return;
    }

    //pedir o periodo inicial
    printf("INSIRA O DIA INICIAL DE PESQUISA!\n");
    printf("DIA: ");
    scanf("%d", &periodoInicial->dia);
    printf("MES: ");
    scanf("%d", &periodoInicial->mes);
    printf("ANO: ");
    scanf("%d", &periodoInicial->ano);
    printf("**************************\n");
    //pedir o periodo final
    printf("INSIRA O DIA FINAL DE PESQUISA!\n");
    printf("DIA: ");
    scanf("%d", &periodoFinal->dia);
    printf("MES: ");
    scanf("%d", &periodoFinal->mes);
    printf("ANO: ");
    scanf("%d", &periodoFinal->ano);
    printf("**************************\n");
    //pedir hora inicial
    printf("INSIRA A HORA INICIAL DE PESQUISA!\n");
    printf("HORA: ");
    scanf("%d", &periodoInicial->hora);
    printf("MINUTOS: ");
    scanf("%d", &periodoInicial->minuto);
    //pedir hora final
    printf("INSIRA A HORA FINAL DE PESQUISA!\n");
    printf("HORA: ");
    scanf("%d", &periodoFinal->hora);
    printf("MINUTOS: ");
    scanf("%d", &periodoFinal->minuto);
    //descartamos os segundos

    //criar ListaViagens
    LISTA_VIAGENS* listaViagens = criarListaViagens();

    //verificar se algum carro passou na autoestrada durante periodo X
    PASSAGEM_NODE* nodePassagem = listaPassagem->header;

    int idEntrada = 0;
    int idSaida = 0;
    while (nodePassagem)
    {

        //encontrar as datas que satisfacam a condicao
        if (checkPeriodoX(nodePassagem, periodoInicial, periodoFinal) == 1)
        {
            //verificar se ja existe o carro na lista VIAGENS (EVITAR REPETICAO DE DADOS)
            if (existeCarroListaViagens(listaViagens, nodePassagem->info->codVeiculo) == 0) //se nao existir o carro
            {
                //criar o NODE_VIAGENS
                NODE_VIAGENS* nodeViagens = criarNodeViagens();
                //adicionar o carro ao NODE_VIAGENS
                nodeViagens->carro = retornaCarro(listaHashCarros, nodePassagem->info->codVeiculo);
                //adicionar o ID de entrada e saida
                idEntrada = nodePassagem->info->idSensor;
                idSaida = nodePassagem->next->info->idSensor;

                //ver a distancia entre o ENTRADA E SAIDA E SOMAR (PODE RECEBER [3 - 1] ou [1 - 3], atencao)
                nodeViagens->totalKm += distanciaEntreSensor(idEntrada, idSaida, listaDistancias);

                //adicionar a lista nodeViagens a lista Viagens
                adicionarNodeListaViagens(nodeViagens, listaViagens);
            }

        }
        nodePassagem = nodePassagem->next;
    }
    //ao fim da listaViagens prenchida, falta organizar por distancia de ordem crescente

    //listar listaViagens (* carro - kmPercorridos)
    //ELIMINAR MEMORIA PARA A LISTA VIAGENS

    //----------------------------------------------------------------------------------

        // ---------------------------------------------
    // ORDENAR A LISTA VIAGENS POR KM (CRESCENTE)
    // ---------------------------------------------

    // Algoritmo simples de bubble sort na lista ligada
    int troca;
    do {
        troca = 0;
        NODE_VIAGENS* atual = listaViagens->header;
        while (atual && atual->next) {
            if (atual->totalKm > atual->next->totalKm) {
                // Trocar os dados dos nodes
                CARRO* tempCarro = atual->carro;
                float tempKm = atual->totalKm;

                atual->carro = atual->next->carro;
                atual->totalKm = atual->next->totalKm;

                atual->next->carro = tempCarro;
                atual->next->totalKm = tempKm;

                troca = 1;
            }
            atual = atual->next;
        }
    } while (troca);

    // ---------------------------------------------
    // IMPRIMIR OS RESULTADOS
    // ---------------------------------------------

    printf("\nCARROS QUE PERCORRERAM A AUTOESTRADA NO PERÍODO SELECIONADO:\n");
    printf("-------------------------------------------------------------\n");
    NODE_VIAGENS* atual = listaViagens->header;
    while (atual) {
        printf("Carro: %s | Total Km: %f km\n", atual->carro->matricula, atual->totalKm);
        atual = atual->next;
    }

    // ---------------------------------------------
    // LIBERTAR MEMÓRIA DA LISTA VIAGENS
    // ---------------------------------------------

    atual = listaViagens->header;
    while (atual) {
        NODE_VIAGENS* temp = atual;
        atual = atual->next;
        free(temp); // não damos free ao carro, pois é só uma referência
    }
    free(listaViagens);
    free(periodoInicial);
    free(periodoFinal);

}
*/

float totalKmsPercorridosListaCarro(LISTA_CARRO* listaCarros, DISTANCIAS_LISTA* listaDistancias, PASSAGEM_LISTA* listaPassagens,
    int diaInicio, int mesInicio, int anoInicio,
    int diaFim, int mesFim, int anoFim)
{
    // FAZER DEPOIS REAPROVEITANDO PARTES DA FUNÇÃO "totalKmCarroDuranteX"
}

void rankingMarcaPorKm(LISTA_HASHC* listaHash, DISTANCIAS_LISTA* listaDistancia, PASSAGEM_LISTA* listaPassagem)
{
    if (!listaHash)
    {
        printf("ERRO! A lista HASH nao existe.\n");
        return;
    }

    // Pedir o Intervalo de Tempo ao Utilizador
    int diaInicio, mesInicio, anoInicio;
    int diaFim, mesFim, anoFim;

    printf("INSIRA O DIA INICIAL DE PESQUISA!\n");
    printf("DIA: "); scanf("%d", &diaInicio);
    printf("MES: "); scanf("%d", &mesInicio);
    printf("ANO: "); scanf("%d", &anoInicio);
    printf("**************************\n");

    printf("INSIRA O DIA FINAL DE PESQUISA!\n");
    printf("DIA: "); scanf("%d", &diaFim);
    printf("MES: "); scanf("%d", &mesFim);
    printf("ANO: "); scanf("%d", &anoFim);
    printf("**************************\n");

    // Percorre a Hash de Carros
    NODE_HASHC* aux = listaHash->header;
    int i = 0;

    printf("PROGRESSO:\n");
    
    while (aux)
    {
        printf("\t%d MARCAS ORGANIZADAS!\n", i);
        // Conta os Km's percorridos por cada Marca
        aux->total_Km_marca = totalKmsPercorridosListaCarro(aux->listaCarros, listaDistancia, listaPassagem, diaInicio, mesInicio, anoInicio, diaFim, mesFim, anoFim);
        i++;
        aux = aux->next;
    }

    // Ordena a Hash por ordem de Marcas com mais km's percorridos (aka Ranking)
    // bubble sort
    int trocou;
    do
    {
        trocou = 0;
        NODE_HASHC* atual = listaHash->header;

        while (atual != NULL && atual->next != NULL)
        {
            NODE_HASHC* prox = atual->next;
            if (atual->total_Km_marca < prox->total_Km_marca)
            {
                // Troca a informação sobre o total de Km's feitos pela Marca
                float tmp_km = atual->total_Km_marca;
                atual->total_Km_marca = prox->total_Km_marca;
                prox->total_Km_marca = tmp_km;

                // Troca as chaves dos nodes da Hash
                char tmp_chave[MAX_CHAR_STR];
                strcpy(tmp_chave, atual->chave);
                strcpy(atual->chave, prox->chave);
                strcpy(prox->chave, tmp_chave);

                // Troca as listas de Carros
                LISTA_CARRO* tmp_lista = atual->listaCarros;
                atual->listaCarros = prox->listaCarros;
                prox->listaCarros = tmp_lista;

                trocou = 1;
            }
            atual = atual->next;
        }
    } while (trocou);

    // Mostra o Ranking
    printf("\n=== RANKING DE MARCAS POR KM PERCORRIDOS ===\n");
    int pos = 1;
    aux = listaHash->header;
    while (aux != NULL)
    {
        printf("%dº - Marca: %s | Total Km Acumulados: %f km\n", pos, aux->chave, aux->total_Km_marca);
        pos++;
        aux = aux->next;
    }
}
