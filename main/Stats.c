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

/*
LISTA_VIAGEM* criarListaViagem()
{
	// Alocação de memória da lista de Viagens
	LISTA_VIAGEM* lista = (LISTA_VIAGEM*)malloc(sizeof(LISTA_VIAGEM));

	// Validação da alocação da lista
	if (!lista)
	{
		printf("ERRO a alocar a lista de viagens!\n");
		return NULL;
	}

	lista->header = NULL; // ponteiro do inicio da lista
	lista->ultimo_node = NULL; // ponteiro para o ultimo elemento da lista
	lista->num_elem = 0;

	return lista;
}

NODE_VIAGEM* criarNodeViagem()
{
	// Alocação de memória para elemento da lista de Viagens
	NODE_VIAGEM* node = (NODE_VIAGEM*)malloc(sizeof(NODE_VIAGEM));

	// Validação da alocação do elemento
	if (!node)
	{
		printf("ERRO a alocar o elemento da lista de viagens!\n");
		return NULL;
	}

	// Alocação de memória para o conteúdo dentro do elemento
	node->info = (VIAGEM*)malloc(sizeof(VIAGEM)); // Conteúdo do Elemento = Dados da Viagem
	node->next = NULL; // ponteiro para o próximo é "= NULL", pois é adicionado no fim da lista

    //printf("Elemento da Lista de Viagens criado com sucesso!\n");

	return node;
}

int freeNodeViagem(NODE_VIAGEM* node)
{
	// Validação da existência do elemento na lista de Viagens
	if (!node)
	{
		printf("ERRO! O elemento nao existe.\n");
		return NULL;
	}

	free(node->info); // Libertar a memória alocada para conteúdo/Viagem dentro do elemento
	free(node); // Libertar a memória alocada para o elemento

	//printf("Elemento da Lista de Viagens libertado com sucesso!\n");
}

LISTA_VIAGEM* carregarViagens(PASSAGEM_LISTA* listaPassagens, DISTANCIAS_LISTA* listaDistancias)
{
    if (!listaPassagens || !listaDistancias)
    {
        printf("Listas de Passagens ou Distâncias não existem!\n");
        return NULL;
    }

    LISTA_VIAGEM* listaViagens = criarListaViagem();

    PASSAGEM_NODE* atual = listaPassagens->header;

    while (atual != NULL)
    {
        // Procuramos apenas passagens de ENTRADA
        if (atual->info->tipoRegisto == 0)
        {
            int codVeiculo = atual->info->codVeiculo;
            int sensorEntrada = atual->info->idSensor;
            DATA* dataEntrada = atual->info->data;

            PASSAGEM_NODE* procuraSaida = atual->next;
            while (procuraSaida != NULL)
            {
                if (procuraSaida->info->codVeiculo == codVeiculo &&
                    procuraSaida->info->tipoRegisto == 1)
                {
                    int sensorSaida = procuraSaida->info->idSensor;
                    DATA* dataSaida = procuraSaida->info->data;

                    // Criar novo nó de viagem
                    NODE_VIAGEM* novoNode = criarNodeViagem();
                    if (!novoNode) return listaViagens; // Falha de alocação

                    novoNode->info->sensor_entrada = sensorEntrada;
                    novoNode->info->sensor_saida = sensorSaida;

                    // Cópia de data
                    novoNode->info->data_entrada = (DATA*)malloc(sizeof(DATA));
                    novoNode->info->data_saida = (DATA*)malloc(sizeof(DATA));
                    *(novoNode->info->data_entrada) = *(dataEntrada);
                    *(novoNode->info->data_saida) =  *(dataSaida);

                    // Buscar distância
                    float distancia = DistanciaEntreSensores(sensorEntrada, sensorSaida, listaDistancias);
                    novoNode->info->distancia_percorrida = distancia;

                    // Inserir na lista
                    if (listaViagens->header == NULL)
                    {
                        listaViagens->header = novoNode;
                        listaViagens->ultimo_node = novoNode;
                    }
                    else
                    {
                        listaViagens->ultimo_node->next = novoNode;
                        listaViagens->ultimo_node = novoNode;
                    }

                    listaViagens->num_elem++;
                    break;
                }

                procuraSaida = procuraSaida->next;
            }
        }

        atual = atual->next;
    }

    printf("Lista das Viagens carregada com sucesso!\n");
    return listaViagens;
}

void freeListaViagens(LISTA_VIAGEM* lista) 
{
    // Verifica se a lista não é nula
    if (!lista) 
    {
        printf("Nao exite lista\n");
        return;
    }

    // Libera todos os nós da lista
    while (lista->header) 
    {
        NODE_VIAGEM* aux = lista->header;
        lista->header = aux->next;

        freeNodeViagem(aux);
    }
    printf("LISTA VIAGENS REMOVIDA\n");
}
*/

// -------------------------------------------- EX 9 -----------------------------------------------------

float DistanciaEntreSensores(int codS1, int codS2, DISTANCIAS_LISTA* listaDist) 
{
    DISTANCIAS_NODE* atual = listaDist->header;
    while (atual != NULL)
    {
        if ((atual->info->codSensor1 == codS1 && atual->info->codSensor2 == codS2) || (atual->info->codSensor1 == codS2 && atual->info->codSensor2 == codS1))
        {
            return atual->info->distanciaPercorrida;
        }
        atual = atual->next;
    }
    return -1; // não encontrado
}

void ordenarPassagensPorTempo(PASSAGEM_LISTA* listaPassagens)
{
    if (!listaPassagens)
    {
        printf("ERRO! A lista passagens nao existe\n");
        return;
    }

    //bubble sort
    PASSAGEM_NODE* atual;
    PASSAGEM_NODE* proximo;
    PASSAGEM* temp; // apenas para trocar o conteudo
    int troca;

    printf("A Ordenar a lista de Passagens...\n");

    do
    {
        troca = 0;
        atual = listaPassagens->header;

        while (atual->next != NULL)
        {
            proximo = atual->next;
            if ((atual->info->data->ano > proximo->info->data->ano) ||
                (atual->info->data->ano == proximo->info->data->ano &&
                    atual->info->data->mes > proximo->info->data->mes) ||
                (atual->info->data->ano == proximo->info->data->ano &&
                    atual->info->data->mes == proximo->info->data->mes &&
                    atual->info->data->dia > proximo->info->data->dia) ||
                (atual->info->data->ano == proximo->info->data->ano &&
                    atual->info->data->mes == proximo->info->data->mes &&
                    atual->info->data->dia == proximo->info->data->dia &&
                    atual->info->data->hora > proximo->info->data->hora) ||
                (atual->info->data->ano == proximo->info->data->ano &&
                    atual->info->data->mes == proximo->info->data->mes &&
                    atual->info->data->dia == proximo->info->data->dia &&
                    atual->info->data->hora == proximo->info->data->hora &&
                    atual->info->data->minuto > proximo->info->data->minuto))
            {
                // Trocar os dados dos nos
                temp = atual->info;
                atual->info = proximo->info;
                proximo->info = temp;

                troca = 1;
            }
            atual = atual->next;
        }
    } while (troca);//vai parar quando percorrer toda a lista e verificar que realmente nao foram efetuadas trocas

    printf("LISTA ORDENADA COM SUCESSO\n");
}

float totalKmsPercorridosListaCarro(LISTA_CARRO* listaCarros, DISTANCIAS_LISTA* listaDistancias, PASSAGEM_LISTA* listaPassagens, int diaInicio, int mesInicio, int anoInicio, int diaFim, int mesFim, int anoFim)
{
    if (!listaCarros || !listaDistancias || !listaPassagens)
    {
        printf("ERRO! A lista HASH nao existe.\n");
        return;
    }

    // Percorre a lista de CARROS
    NODE_CARRO* aux_carro = listaCarros->header;

    float soma_total_KM_por_marca = 0;
    int sensorEntrada = 0; // Numero do Sensor de Entrada
    int sensorSaida = 0; // Numero do Sensor de Saída
    
    while(aux_carro)
    {
        aux_carro->info->total_km = 0;

        // Percorre a lista das Passagens
        PASSAGEM_NODE* aux_passagem = listaPassagens->header;
        while (aux_passagem)
        {
            // SE codVeiculo (CARROS) == codVeiculo (Passagens) :)
            if (aux_carro->info->codVeiculo == aux_passagem->info->codVeiculo) // Encontrou uma passagem desse veículo
            {
                // SE Tipo Registo (Passagens) == 0 -> Entrada
                if (aux_passagem->info->tipoRegisto == 0)
                {
                    // idSensor (Passagens) == codSensor1 (Distancias)
                    // Guarda Numero do Sensor de Entrada
                    sensorEntrada = aux_passagem->info->idSensor;
                }
                // SE Tipo Registo (Passagens) == 1 -> Saída
                else if (aux_passagem->info->tipoRegisto == 1)
                {
                    // idSensor (Passagens) == codSensor2 (Distancias)
                    // Guarda Numero do Sensor de Saída
                    sensorSaida = aux_passagem->info->idSensor;
                }
            }

            // Juntar as distâncias a cada 
            if (sensorEntrada != NULL && sensorSaida != NULL)
            {
                DISTANCIAS_NODE* aux_distancias = listaDistancias->header;
                while (aux_distancias)
                {
                    // Verificação para sensores trocados nas distancias
                    if ((sensorEntrada == aux_distancias->info->codSensor1 && sensorSaida == aux_distancias->info->codSensor2)
                        || (sensorSaida == aux_distancias->info->codSensor1 && sensorEntrada == aux_distancias->info->codSensor2))
                    {
                        // Soma total de KM do mesmo carro
                        aux_carro->info->total_km += aux_distancias->info->distanciaPercorrida;
                    }
                    aux_distancias = aux_distancias->next;
                }
            }

            aux_passagem = aux_passagem->next;
        }

        // Percorrer a lista das Distancias e ver a distancia percorrida
        // nesses dois sensores e guarda no total_km do carro
        soma_total_KM_por_marca += aux_carro->info->total_km;
        aux_carro = aux_carro->next;
    }
        
    return soma_total_KM_por_marca;
}

//ordenar marcas por mais km's percorridos
void rankingMarcaPorKm(LISTA_HASHC* listaHash, DISTANCIAS_LISTA* listaDistancia, PASSAGEM_LISTA* listaPassagem, int diaInicio, int mesInicio, int anoInicio, int diaFim, int mesFim, int anoFim)
{
    if (!listaHash)
    {
        printf("ERRO! A lista HASH nao existe.\n");
        return;
    }

    // Percorrer a Hash de Carros
    NODE_HASHC* aux = listaHash->header;
    int i = 0;

    while (aux)
    {
        printf("%d ELEMENTOS DA HASH ENCONTRADOS!\n", i);
        // Conta os Km's percorridos por cada Marca
        aux->total_Km_marca = totalKmsPercorridosListaCarro(aux->listaCarros, listaDistancia, listaPassagem, diaInicio, mesInicio, anoInicio, diaFim, mesFim, anoFim);

        aux = aux->next;
        i++;
    }

    // Ordena a Hash por ordem de Marcas com mais km's percorridos
    //bouble sort
    printf("A ORDENAR HASH!\n");

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
                // Troca: total, chave, e listaCarros
                int tmp_km = atual->total_Km_marca;
                atual->total_Km_marca = prox->total_Km_marca;
                prox->total_Km_marca = tmp_km;

                char tmp_chave[MAX_CHAR_STR];
                strcpy(tmp_chave, atual->chave);
                strcpy(atual->chave, prox->chave);
                strcpy(prox->chave, tmp_chave);

                LISTA_CARRO* tmp_lista = atual->listaCarros;
                atual->listaCarros = prox->listaCarros;
                prox->listaCarros = tmp_lista;

                trocou = 1;
            }
            atual = atual->next;
        }
    } while (trocou);

    // 3. Exibir o ranking
    printf("\n=== RANKING DE MARCAS POR KM PERCORRIDOS ===\n");
    int pos = 1;
    aux = listaHash->header;
    while (aux != NULL)
    {
        printf("%dº - Marca: %s | Total Km Acumulados: %d\n", pos, aux->chave, aux->total_Km_marca);
        pos++;
        aux = aux->next;
    }
}