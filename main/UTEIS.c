#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "SENSORES.H"
#include "DISTANCIAS.H"
#include "PASSAGEM.H"
#include "UTEIS.H"
#include "carros.h"
#include "donos.h"
// FALTA MEMORIA OCUPADA POR : DISTANCIA     PASSAGEM

//determinar a memoria ocupada por toda a estrutura de dados
int calcularTamanhoEDSensor(LISTA_SENSOR *lista)
{
	if (!lista)
	{
		printf("ERRO! A lista SENSOR nao existe");
		return;
	}
	//adicionar o tamanho da lista (8bytes)
	int tamanho = sizeof(lista);
	//percorrer a lista e ir somando o tamanho de cada NO e os seus conteudos
	NODE_SENSOR* aux = lista->header;
	while (aux)
	{
		tamanho += sizeof(aux);
		tamanho += sizeof(SENSOR);
		aux = aux->next;
	}

	return tamanho;
}

int calcularTamanhoEDDistancia(DISTANCIAS_LISTA* lista)
{
	if (!lista)
	{
		printf("ERRO! A lista SENSOR nao existe");
		return;
	}
	//adicionar o tamanho da lista (8bytes)
	int tamanho = sizeof(lista);
	//percorrer a lista e ir somando o tamanho de cada NO e os seus conteudos
	DISTANCIAS_NODE* aux = lista->header;
	while (aux)
	{
		tamanho += sizeof(aux);
		tamanho += sizeof(DISTANCIAS);
		aux = aux->next;
	}

	return tamanho;
}

int calcularTamanhoEDPassagem(PASSAGEM_LISTA* lista)
{
	if (!lista)
	{
		printf("ERRO! A lista SENSOR nao existe");
		return;
	}
	//adicionar o tamanho da lista (8bytes)
	int tamanho = sizeof(lista);
	//percorrer a lista e ir somando o tamanho de cada NO e os seus conteudos
	PASSAGEM_NODE* aux = lista->header;
	while (aux)
	{
		tamanho += sizeof(aux);
		tamanho += sizeof(PASSAGEM);
		aux = aux->next;
	}

	return tamanho;
}

int calcularTamanhoEDCarro(LISTA_HASHC* listaHash) //CALCULAR O TAMANHO DE TODA A LISTAHASH
{
	if (!listaHash)
	{
		printf("ERRO! A lista HASH CARRO nao existe");
		return;
	}
	//variavel que vai conter o tamanho da ED em bytes
	int tamanho = 0;

	//tamanho da lista Hash
	tamanho += sizeof(listaHash);
	//auxiliar para percorrer os nodes da listaHash
	NODE_HASHC* nodeHash = listaHash->header;
	//percorrer os nodes Hash todos
	while (nodeHash)
	{
		//tamanho do nodeHash
		tamanho += sizeof(nodeHash);
		//verificar se o nodeHash possui lista
		if (nodeHash->listaCarros != NULL)
		{
			//tamanho da lista que pertenece ao nodeHash
			tamanho += sizeof(LISTA_CARRO);
			//verificar se existem nodes na lista do nodeHash
			if (nodeHash->listaCarros->header != NULL)
			{
				//auxiliar para percorrer a lista do nodeHash
				NODE_CARRO* nodeCarro = nodeHash->listaCarros->header;
				//percorrer os nodes todos e armazenar o tamanho
				while (nodeCarro)
				{
					tamanho += sizeof(nodeCarro);
					tamanho += sizeof(CARRO);
					nodeCarro = nodeCarro->next;
				}
			}
		}		
		nodeHash = nodeHash->next;
	}
	/*
	//calcular o ultimo node que sobrou
	//adicionar tamanho do nodeHash
	tamanho += sizeof(nodeHash);
	//adicionar o tamanho da listaCarros do nodeHash
	tamanho += sizeof(nodeHash->listaCarros);
	//percorrer todos os carros da lista e adicionar o tamanho
	NODE_CARRO* nodeCarro = nodeHash->listaCarros->header;
	while (nodeCarro)
	{
		tamanho += sizeof(nodeCarro);
		nodeCarro = nodeCarro->next;
	}
	*/
	return tamanho;
}

int calcularTamanhoEDDonos(LISTA_DONOS* lista)
{
	if (!lista)
	{
		printf("ERRO! A lista DONO nao existe");
		return;
	}
	//adicionar o tamanho da lista (8bytes)
	int tamanho = sizeof(lista);
	//percorrer a lista e ir somando o tamanho de cada NO e os seus conteudos
	NODE_DONOS* aux = lista->primeiro;
	while (aux)
	{
		tamanho += sizeof(aux);
		tamanho += sizeof(Donos);
		aux = aux->next;
	}

	return tamanho;
}

//FALTA FAZER CARROS E DONOS

//JUNTAR NUMA UNICA FUNCAO QUE SOMA TODOS OS RETURNS E DEVOLVE O TOTAL (BYTES)
void memoriaTotalOcupadaED(LISTA_SENSOR* listaS, DISTANCIAS_LISTA* listaD, PASSAGEM_LISTA* listaP, LISTA_HASHC* listaHashCarro, LISTA_DONOS* listaDonos)
{
	int memTotal = calcularTamanhoEDSensor(listaS);
	memTotal += calcularTamanhoEDDistancia(listaD);
	memTotal += calcularTamanhoEDPassagem(listaP);
	memTotal += calcularTamanhoEDCarro(listaHashCarro);
	memTotal += calcularTamanhoEDDonos(listaDonos);
	//1 Byte = 0.000001
	printf("A Estrutura de dados ocupa %.2f MB\n", (double)memTotal*0.000001);
}

//vai inicializar a estrutura de dados, ler os ficheiros / criar listas e carregar todas as informacoes dos respetivos ficheiros
int inicializarED(LISTA_SENSOR* listaSensor, DISTANCIAS_LISTA* listaDistancias, PASSAGEM_LISTA* listaPassagem, LISTA_HASHC* listaHashCarros,LISTA_DONOS* listaDonos)
{
	//tenho que retornar o enderco da LISTA de cada ficheiro carregado

	//******************CARREGAR-DONOS**************************
	carregarDadosDonos(listaDonos);
	//******************CARREGAR-CARROS**************************
	carregarDadosCarro(listaHashCarros);
	//******************CARREGAR-SENSORES**************************
	carregarSensor(listaSensor);
	//******************CARREGAR-DISTANCIAS**************************
	carregarDistancia(listaDistancias);
	//******************CARREGAR-PASSAGEM**************************
	carregarPassagem(listaPassagem);


	//ITERAR PELA LISTA DONOS E ASSOCIAR O CARRO AO DONO

	return 1;
	
}

//EXPORTAÇÔES EM CSV
void exportar_csv_DONOS(LISTA_DONOS* lista)
{
	// Cria nó auxiliar para percorrer a lista
	NODE_DONOS* aux = lista->primeiro;

	// Ponteiro para percorrer o ficheiro em modo Write ("w")
	FILE* f_csv = fopen("donos.csv", "w");

	// Cabeçalho de cada coluna
	fputs("Numero de Contribuinte, Nome, Codigo Postal\n", f_csv);

	// Percorre a lista até ao último nó
	while (aux)
	{
		// Preenche linha a linha, com a informação de nó em nó
		fprintf(f_csv, "%d, %s, %s\n", aux->info->numCont, aux->info->nome, aux->info->codpost);

		aux = aux->next;
	}
	
	// Fim do preenchimento do ficheiro
	fclose(f_csv);

	printf("Ficheiro donos.csv exportado com sucesso!\n");
}

void exportar_csv_SENSORES(LISTA_SENSOR* listaSensor)
{
	// Cria nó auxiliar para percorrer a lista
	NODE_SENSOR* aux = listaSensor->header;

	// Ponteiro para percorrer o ficheiro em modo Write ("w")
	FILE* f_csv = fopen("sensores.csv", "w");

	// Cabeçalho de cada coluna
	fputs("Codigo do Sensor, Designacao, Latitude (Graus - º), Latitude (Minutos - '), Latitude (Segundos - ''), Longitude (Graus - º), Longitude (Minutos - '), Longitude (Segundos - '')\n", f_csv);

	// Percorre a lista até ao último nó
	while (aux)
	{
		// Preenche linha a linha, com a informação de nó em nó
		fprintf(f_csv, "%d, %s, %s, %s\n", aux->info->codSensor, aux->info->designacao, aux->info->infoLatitude, aux->info->infoLongitude);

		aux = aux->next;
	}

	// Fim do preenchimento do ficheiro
	fclose(f_csv);

	printf("Ficheiro sensores.csv exportado com sucesso!\n");
}

void exportar_csv_DISTANCIAS(DISTANCIAS_LISTA* listaDistancias)
{
	// Cria nó auxiliar para percorrer a lista
	DISTANCIAS_NODE* aux = listaDistancias->header;

	// Ponteiro para percorrer o ficheiro em modo Write ("w")
	FILE* f_csv = fopen("distancias.csv", "w");

	// Cabeçalho de cada coluna
	fputs("Codigo do Sensor 1, Codigo do Sensor 2, Distancia\n", f_csv);

	// Percorre a lista até ao último nó
	while (aux)
	{	
		// Preenche linha a linha, com a informação de nó em nó
		fprintf(f_csv, "%d, %d, %f\n", aux->info->codSensor1, aux->info->codSensor2, aux->info->distanciaPercorrida);

		aux = aux->next;
	}

	// Fim do preenchimento do ficheiro
	fclose(f_csv);

	printf("Ficheiro distancias.csv exportado com sucesso!\n");
}

void exportar_csv_CARROS(LISTA_HASHC* listaHash)
{
	// Cria nó auxiliar para percorrer a Hash
	NODE_HASHC* aux_hash = listaHash->header;

	// Ponteiro para percorrer o ficheiro em modo Write ("w")
	FILE* f_csv = fopen("carros.csv", "w");

	// Cabeçalho de cada coluna
	fputs("Matricula, Marca, Modelo, Ano, Dono, Codigo do Veiculo\n", f_csv);

	// Percorre a Hash até ao último nó
	while (aux_hash)
	{
		// Cria nó auxiliar para percorrer a lista dentro de cada nó da Hash
		NODE_CARRO* aux = aux_hash->listaCarros->header;

		// Percorre a lista até ao último nó
		while (aux)
		{
			// Preenche linha a linha, com a informação de nó em nó
			fprintf(f_csv, "%s, %s, %s, %d, %d, %d\n", aux->info->matricula,
				aux->info->marca, aux->info->modelo, aux->info->ano, 
				aux->info->dono, aux->info->codVeiculo);
		
			aux = aux->next;
		}

		aux_hash = aux_hash->next;
	}

	// Fim do preenchimento do ficheiro
	fclose(f_csv);

	printf("Ficheiro carros.csv exportado com sucesso!\n");
}

void exportar_csv_PASSAGENS(PASSAGEM_LISTA* listaPassagem)
{
	// Cria nó auxiliar para percorrer a lista
	PASSAGEM_NODE* aux = listaPassagem->header;

	// Ponteiro para percorrer o ficheiro em modo Write ("w")
	FILE* f_csv = fopen("passagem.csv", "w");

	// Cabeçalho de cada coluna
	fputs("ID do Sensor, Codigo do Veiculo, Data, Tipo de Registo\n", f_csv);

	// Percorre a lista até ao último nó
	while (aux)
	{
		// Preenche linha a linha, com a informação de nó em nó
		fprintf(f_csv, "%d, %d, %d-%d-%d %d:%d:%d.%d, %d\n", aux->info->idSensor,
			aux->info->codVeiculo, aux->info->data->dia, aux->info->data->mes, 
			aux->info->data->ano, aux->info->data->hora, aux->info->data->minuto,
			aux->info->data->segundo, aux->info->data->milisegundo, aux->info->tipoRegisto);

		aux = aux->next;
	}

	// Fim do preenchimento do ficheiro
	fclose(f_csv);

	printf("Ficheiro passagem.csv exportado com sucesso!\n");
}