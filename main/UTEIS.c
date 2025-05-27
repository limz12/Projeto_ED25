/**
 * @file UTEIS.c
 * @brief Implementacao das funcoes uteis.
 */

// BIBLIOTECAS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "SENSORES.H"
#include "DISTANCIAS.H"
#include "PASSAGEM.H"
#include "UTEIS.H"
#include "carros.h"
#include "donos.h"


/**
* @brief Funcao responsavel por determinar a memoria ocupada pela estrutura de dados LISTA_SENSOR
* @param lista : Recebe um ponteiro LISTA_SENSOR
* @return tamanho : retorna a variavel inteira, que corresponde ao tamanho da estrutura em MB
*/
int calcularTamanhoEDSensor(LISTA_SENSOR* lista)
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

/**
* @brief Funcao responsavel por determinar a memoria ocupada pela estrutura de dados DISTANCIAS_LISTA
* @param lista : Recebe um ponteiro DISTANCIAS_LISTA
* @return tamanho : retorna a variavel inteira, que corresponde ao tamanho da estrutura em MB
*/
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

/**
* @brief Funcao responsavel por determinar a memoria ocupada pela estrutura de dados PASSAGEM_LISTA
* @param lista : Recebe um ponteiro PASSAGEM_LISTA
* @return tamanho : retorna a variavel inteira, que corresponde ao tamanho da estrutura em MB
*/
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

/**
* @brief Funcao responsavel por determinar a memoria ocupada pela estrutura de dados LISTA_HASHC
* @param lista : Recebe um ponteiro LISTA_HASHC
* @return tamanho : retorna a variavel inteira, que corresponde ao tamanho da estrutura em MB
*/
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
	
	return tamanho;
}

/**
* @brief Funcao responsavel por determinar a memoria ocupada pela estrutura de dados LISTA_DONOS
* @param lista : Recebe um ponteiro LISTA_DONOS
* @return tamanho : retorna a variavel inteira, que corresponde ao tamanho da estrutura em MB
*/
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

/**
* @brief Funcao responsavel por apresentar todas as funçoes anteriores que calculam o tamanho de todas as estruturas de dados (em MegaBytes)
* @return VOID
*/
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

/**
* @brief Funcao responsavel por inicializar a estrutura de dados, ler os ficheiros / criar listas e carregar todas as informacoes dos respetivos ficheiros
* @return 1 : retorna 1 se carregar todos os ficheiros
*/
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

/**
* @brief Funcao responsavel por exportar a lista de Donos em CSV
* @param lista : Recebe um ponteiro LISTA_DONOS
* @return VOID
*/
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

/**
* @brief Funcao responsavel por exportar a lista de Sensores em CSV
* @param lista : Recebe um ponteiro LISTA_SENSOR
* @return VOID
*/
void exportar_csv_SENSORES(LISTA_SENSOR* listaSensor)
{
	// Cria nó auxiliar para percorrer a lista
	NODE_SENSOR* aux = listaSensor->header;

	// Ponteiro para percorrer o ficheiro em modo Write ("w")
	FILE* f_csv = fopen("sensores.csv", "w");

	// Cabeçalho de cada coluna
	fputs("Codigo do Sensor; Designacao; Latitude; Longitude \n", f_csv);

	// Percorre a lista até ao último nó
	while (aux)
	{
		// Preenche linha a linha, com a informação de nó em nó
		fprintf(f_csv, "%d; %s; %s; %s\n", aux->info->codSensor, aux->info->designacao, aux->info->infoLatitude, aux->info->infoLongitude);

		aux = aux->next;
	}

	// Fim do preenchimento do ficheiro
	fclose(f_csv);

	printf("Ficheiro sensores.csv exportado com sucesso!\n");
}

/**
* @brief Funcao responsavel por exportar a lista de Distancias em CSV
* @param lista : Recebe um ponteiro DISTANCIAS_LISTA
* @return VOID
*/
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

/**
* @brief Funcao responsavel por exportar a lista de Carros em CSV
* @param lista : Recebe um ponteiro LISTA_HASHC
* @return VOID
*/
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

/**
* @brief Funcao responsavel por exportar a lista de Passagens em CSV
* @param lista : Recebe um ponteiro PASSAGEM_LISTA
* @return VOID
*/
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

/**
* @brief Funcao responsavel por exportar a lista de Donos em XML
* @param lista : Recebe um ponteiro LISTA_DONOS
* @return VOID
*/
void exportar_xml_DONOS(LISTA_DONOS* listaDonos)
{
	if (!listaDonos)
	{
		printf("ERRO! A lista DONOS nao existe\n");
		return;
	}
	//criar um ficheiro
	FILE* fich = fopen("donos.xml", "w");
	if (!fich)
	{
		printf("Erro ao criar o ficheiro donos.xml");
		return;
	}

	//cabecalho do xml
	fprintf(fich, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(fich, "<DONOS>\n");
	//percorrer a lista donos
	NODE_DONOS* nodeDonos = listaDonos->primeiro;

	while (nodeDonos)
	{
		fprintf(fich, "  <Registo>\n");
		fprintf(fich, "    <numContribuinte>%d</numContribuinte>\n", nodeDonos->info->numCont);
		fprintf(fich, "    <nome>%s</nome>\n", nodeDonos->info->nome);
		fprintf(fich, "    <codPostal>%s</codPostal>\n", nodeDonos->info->codpost);
		fprintf(fich, "  </Registo>\n");

		nodeDonos = nodeDonos->next;
	}

	fprintf(fich, "</DONOS>\n");
	fclose(fich);
	printf("ED DONOS exportada com sucesso!\n");
}

/**
* @brief Funcao responsavel por exportar a lista de Sensores em XML
* @param lista : Recebe um ponteiro LISTA_SENSOR
* @return VOID
*/
void exportar_xml_SENSORES(LISTA_SENSOR* listaSensor)
{
	if (!listaSensor)
	{
		printf("ERRO! A lista sensor nao existe \n");
		return;
	}
	
	//criar um ficheiro
	FILE* fich = fopen("sensores.xml", "w");
	if (!fich)
	{
		printf("Erro ao criar ficheiro!\n");
		return;
	}
	fprintf(fich, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(fich, "<Sensores>\n");

	//ponteiro para os sensores
	NODE_SENSOR* nodeSensor = listaSensor->header;
	while (nodeSensor)
	{
		fprintf(fich, "  <Sensor>\n");
		fprintf(fich, "    <codSensor>%d</codSensor>\n", nodeSensor->info->codSensor);
		fprintf(fich, "    <Designacao>%s</Designacao>\n", nodeSensor->info->designacao);
		fprintf(fich, "    <Latitude>%s</Latitude>\n", nodeSensor->info->infoLatitude);
		fprintf(fich, "    <Longitude>%s</Longitude>\n", nodeSensor->info->infoLongitude);
		fprintf(fich, "  </Sensor>\n");

		nodeSensor = nodeSensor->next;
	}

	fprintf(fich, "</Sensores>\n");
	fclose(fich);

	printf("ED Sensores exportada com sucesso!\n");
}

/**
* @brief Funcao responsavel por exportar a lista de Distancias em XML
* @param lista : Recebe um ponteiro DISTANCIAS_LISTA
* @return VOID
*/
void exportar_xml_DISTANCIAS(DISTANCIAS_LISTA* listaDistancias)
{
	if (!listaDistancias)
	{
		printf("A lista Distancias nao existe");
		return;
	}

	//criar ficheiro
	FILE* fichDist = fopen("distancias.xml", "w");
	if (!fichDist)
	{
		printf("Erro ao criar o ficheiro\n");
		return;
	}

	fprintf(fichDist, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(fichDist, "<Distancias>\n");

	DISTANCIAS_NODE* node = listaDistancias->header;

	while (node)
	{
		fprintf(fichDist, "  <Distancia>\n");
		fprintf(fichDist, "    <codSensor1>%d</codSensor1>\n", node->info->codSensor1);
		fprintf(fichDist, "    <codSensor2>%d</codSensor2>\n", node->info->codSensor2);
		fprintf(fichDist, "    <distancia>%.3f</distancia>\n", node->info->distanciaPercorrida);
		fprintf(fichDist, "  </Distancia>\n");


		node = node->next;
	}

	fprintf(fichDist, "</Distancias>\n");

	fclose(fichDist);
	printf("ED Distancias exportada com sucesso!\n");
}

/**
* @brief Funcao responsavel por exportar a lista de Passagens em XML
* @param lista : Recebe um ponteiro PASSAGEM_LISTA
* @return VOID
*/
void exportar_xml_PASSAGENS(PASSAGEM_LISTA* listaPassagens)
{
	if (!listaPassagens)
	{
		printf("ERRO! lista passagens nao existe\n");
		return;
	}
	//criar o ficheiro
	FILE* f = fopen("passagens.xml", "w");
	if (!f)
	{
		printf("Erro a criar o ficheiro!");
		return;
	}
	fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(f, "<Registos>\n");


	//percorrer a lista
	PASSAGEM_NODE* node = listaPassagens->header;
	while (node)
	{
		fprintf(f, "  <Registo>\n");
		fprintf(f, "    <idSensor>%d</idSensor>\n", node->info->idSensor);
		fprintf(f, "    <codVeiculo>%d</codVeiculo>\n", node->info->codVeiculo);
		fprintf(f, "    <data>%d-%d-%d %d:%d</data>\n", node->info->data->dia, node->info->data->mes, node->info->data->ano, node->info->data->hora, node->info->data->minuto);
		fprintf(f, "    <TipoRegisto>%d</TipoRegisto>\n", node->info->tipoRegisto);
		fprintf(f, "  </Registo>\n");
		
		
		node = node->next;
	}

	fprintf(f, "</Registos>\n");
	fclose(f);
	printf("ED Passagens  exportada com sucesso!\n");
}

/**
* @brief Funcao responsavel por exportar a lista de Carros em XML
* @param lista : Recebe um ponteiro LISTA_HASHC
* @return VOID
*/
void exportar_xml_CARROS(LISTA_HASHC* listaHashCarros)
{
	if (!listaHashCarros)
	{
		printf("ERRO! A lista Carros nao existe\n");
		return;
	}

	FILE* fichCarros = fopen("carros.xml", "w");
	if (!fichCarros)
	{
		printf("Erro a criar o ficheiro!\n");
		return;
	}

	fprintf(fichCarros, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(fichCarros, "<Veiculos>\n");


	//nodeHash
	NODE_HASHC* nodeHash = listaHashCarros->header;
	while (nodeHash)
	{
		//percorrer a lista dos carros do nodeHash
		NODE_CARRO* nodeCarro = nodeHash->listaCarros->header;
		while (nodeCarro)
		{
			fprintf(fichCarros, "  <Veiculo>\n");
			fprintf(fichCarros, "    <matricula>%s</matricula>\n", nodeCarro->info->matricula);
			fprintf(fichCarros, "    <marca>%s</marca>\n", nodeCarro->info->marca);
			fprintf(fichCarros, "    <modelo>%s</modelo>\n", nodeCarro->info->modelo);
			fprintf(fichCarros, "    <ano>%d</ano>\n", nodeCarro->info->ano);
			fprintf(fichCarros, "    <dono>%d</dono>\n", nodeCarro->info->dono);
			fprintf(fichCarros, "    <codVeiculo>%d</codVeiculo>\n", nodeCarro->info->codVeiculo);
			fprintf(fichCarros, "  </Veiculo>\n");


			nodeCarro = nodeCarro->next;
		}
		nodeHash = nodeHash->next;
	}

	fprintf(fichCarros, "</Veiculos>\n");
	fclose(fichCarros);
	printf("ED carros exportada com sucesso!\n");
}
