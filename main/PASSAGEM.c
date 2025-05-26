#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define MAX_ARRAY_CARROS 100000

#include "PASSAGEM.H"
#include "DISTANCIAS.H"
#include "VIAGENS.H"

//VARIAVEL GLOBAL PARA PODER USAR NO COMPARAR CARROS()
LISTA_HASHC* listaParaComparar = NULL;

//criar a LISTA PASSAGEM
PASSAGEM_LISTA* criarListaPassagem()
{
	//alocar memoria para a lista
	PASSAGEM_LISTA* lista = (PASSAGEM_LISTA*)malloc(sizeof(PASSAGEM_LISTA));
	//verificar se a lista foi criada com sucesso
	if (!lista)
	{
		printf("ERRO! A Lista Passagem nao foi alocada\n");
		return;
	}
	//inicializar a lista a null
	lista->header = NULL;
	lista->ultimoNode = NULL;
	lista->numElementos = 0;

	return lista;
}

//criar o NODE PASSAGEM
PASSAGEM_NODE* criarNodePassagem()
{
	//alocar memoria para o node
	PASSAGEM_NODE* node = (PASSAGEM_NODE*)malloc(sizeof(PASSAGEM_NODE));
	//alocar memoria para a struct PASSAGEM
	node->info = (PASSAGEM*)malloc(sizeof(PASSAGEM));
	//alocar memoria para a struct DATA
	node->info->data = (DATA*)malloc(sizeof(DATA));
	if (!node || !node->info || !node->info->data)
	{
		printf("ERRO a alocar memoria para o NODE PASSAGEM\n");
		return;
	}

	node->next = NULL;
	

	return node;
}

void carregarPassagem(PASSAGEM_LISTA* lista)
{
	if (!lista)
	{
		printf("ERRO, Lista PASSAGEM nao existe\n");
		return;
	}
	//abrir o ficheiro para leitura
	FILE* fich = fopen("passagem.txt", "r");

	//criar buffer para armazenar a linha lida do ficheiro
	char buffer[1000];
	//ler o ficheiro linha a linha e adicionar no buffer
	while (fgets(buffer, sizeof(buffer), fich))
	{
		//detetar linhas em branco
		if (strcmp(buffer, "\n") == 0)
		{
			printf("Linha em branco detetada\n");
		}
		else
		{
			//criar um no e armazenar os conteudos do buffer nesse no
			PASSAGEM_NODE* node = criarNodePassagem();
			
			sscanf(buffer, "%d\t%d\t%d-%d-%d %d:%d:%d.%d\t%d",&node->info->idSensor, &node->info->codVeiculo, &node->info->data->dia, &node->info->data->mes, &node->info->data->ano, &node->info->data->hora, &node->info->data->minuto, &node->info->data->segundo, &node->info->data->milisegundo, &node->info->tipoRegisto);
			
			//printf("%d\t%d\t%d-%d-%d %d:%d:%d.%d\t%d\n", node->info->idSensor, node->info->codVeiculo, node->info->data->dia, node->info->data->mes, node->info->data->ano, node->info->data->hora, node->info->data->minuto, node->info->data->segundo, node->info->data->milisegundo, node->info->tipoRegisto);

			//adicionar o node a lista PASSAGEM
			adicionarListaPassagem(lista, node);
		}
	}
	printf("PASSAGEM.TXT carregado com sucesso!\n");

	fclose(fich);
}

void adicionarListaPassagem(PASSAGEM_LISTA* lista, PASSAGEM_NODE* node)
{
	if (!lista || !node)
	{
		printf("ERRO! LISTA ou NODE PASSAGEM nao existem\n");
		return;
	}
	
	//se nao existir nenhum no na lista
	if (lista->header == NULL)
	{
		lista->header = node;
		lista->ultimoNode = node;
		lista->numElementos++;
	}
	else //se o ja existirem nos, adiciona no fim da lista
	{
		lista->ultimoNode->next = node;
		lista->ultimoNode = node;
		lista->numElementos++;
	}
}

void mostrarListaPassagem(PASSAGEM_LISTA* lista)
{
	//verificar se a lista existe
	if (!lista)
	{
		printf("Erro! A lista Passagem nao existe\n");
		return;
	}

	//criar um node auxiliar para percorrer toda a lista
	PASSAGEM_NODE* aux = lista->header;
	printf("***********************\n");
	printf("\t LISTA PASSAGENS\n");
	printf("***********************\n");
	printf("ID_SENSOR\tCOD_VEICULO\tDATA\tTIPO_REGISTO");

	while (aux != NULL)
	{
		printf("%d\t%d\t%d-%d-%d %d:%d:%d.%d\t%d\n",aux->info->idSensor,aux->info->codVeiculo, aux->info->data->dia, aux->info->data->mes, aux->info->data->ano, aux->info->data->hora, aux->info->data->minuto, aux->info->data->segundo, aux->info->data->milisegundo, aux->info->tipoRegisto);
		aux = aux->next;
	}
}

void libertarNodePassagem(PASSAGEM_NODE* node)
{
	if (!node)
	{
		printf("ERRO! O NODE PASSAGENS EXISTE\n");
		return;
	}

	free(node->info->data);
	free(node->info);
	free(node);

}

void libertarListaPassagem(PASSAGEM_LISTA* lista)
{
	if (!lista)
	{
		printf("ERRO! A LISTA DISTANCIA NAO EXISTE \n");
		return;
	}
	//se a lista tiver vazia libertar
	if (lista->header == NULL && lista->ultimoNode == NULL)
	{
		free(lista);
		printf("LISTA DISTANCIA REMOVIDA COM SUCESSO\n");
	}
	else// se a lista possuir NODES eliminar um a um
	{
		//atribuir uma variavel auxiliar para ajudar na eliminacao
		PASSAGEM_NODE* aux = lista->header;

		while (lista->header != NULL) // vai eliminar do inicio para o fim da fila
		{
			//posicionar o aux no proximo no 
			aux = aux->next;
			//eliminar o no da primeira posicao
			libertarNodeDistancia(lista->header);
			//posicionar o ponteiro header da lista para o auxiliar
			lista->header = aux;
			lista->numElementos--;

		}
		//ao fim de eliminar todos os nos
		free(lista);
		printf("LISTA PASSAGEM LIBERTADA COM SUCESSO! \n");
	}
}

//registar uma passagem manualmente
void registarPassagem(PASSAGEM_LISTA* lista)
{
	if (!lista)
	{
		printf("ERRO! A LISTA_PASSAGEM NAO EXISTE!\n");
		return;
	}

	int criar = 1;

	while (criar == 1)
	{

		int verificarSensor = 0;
		int flag = 0;
		//criar um NODE Passagem
		PASSAGEM_NODE* node = criarNodePassagem();
		while (flag == 0)
		{
			printf("Insere o idSensor [inteiro]\n");
			scanf("%d", &verificarSensor);
			//So existem sensores de 1 a 10

			if (verificarSensor > 0 && verificarSensor <= 10)
			{
				node->info->idSensor = verificarSensor;
				flag = 1;
			}
			else
			{
				printf("ERRO! O SENSOR NAO E VALIDO\n");
				return;
			}

		}
		printf("Insere o COD_VEICULO [inteiro] que passou no respetivo Sensor\n");
		scanf("%d", &node->info->codVeiculo);
		system("cls");
		printf("Insere a data em que o veiculo passou no sensor [DIA-MES-ANO]:\n");
		scanf("%d", &node->info->data->dia);
		scanf("%d", &node->info->data->mes);
		scanf("%d", &node->info->data->ano);
		system("cls");
		printf("[HORA - MINUTO - SEGUNDO - MILISEGUNDO]:\n");
		scanf("%d", &node->info->data->hora);
		scanf("%d ", &node->info->data->minuto);
		scanf("%d", &node->info->data->segundo);
		scanf("%d", &node->info->data->milisegundo);
		system("cls");
		int flag3 = 0;
		while (flag3 == 0)
		{
			printf("Qual foi o tipo de registo? [0 -> ENTRADA / 1-> SAIDA]:\n");
			scanf("%d", &node->info->tipoRegisto);
			//verificar os dados intoduzidos
			if (node->info->tipoRegisto > 1 || node->info->tipoRegisto < 0)
			{
				printf("ERRO! OPCAO INVALIDA\n");
				return;
			}
			else
			{
				flag3 = 1;
			}
		}

		
		if (verificarNodeDadosPassagem(node) == 1)
		{
			//depois do utilizador introduzir todas as informacoes vamos guardar na lista
			adicionarListaPassagem(lista, node);
			printf("PASSAGEM INSERIDA COM SUCESSO!\n");
		}
		else
		{
			printf("ERRO! INSERCAO REJEITADA. DADOS INVALIDOS\n");
			return;
		}
		int flag2 = 0;

		while (flag2 == 0)
		{
			printf("Pretende registar mais passagens?\n");
			printf("1 -> SIM | 0 -> NAO\n");
			scanf("%d", &criar);
			//evitar que o user insira outros numeros para alem do 1 e 0
			if (criar < 0 || criar > 1)
			{
				printf("ERRO! OPCAO INVALIDA\n");
			}
			else
			{
				flag2 = 1;
			}
		}
	}


}

int verificarNodeDadosPassagem(PASSAGEM_NODE* node)
{
	//utilizar a struct tm presente no time.h para obter a data do sistema
	struct tm* tempoAtual;
	time_t t;
	t = time(NULL);
	tempoAtual = localtime(&t);

	//verificar se a hora e a data e possivel existir
	if (node->info->data->dia >= 1 && node->info->data->dia <= 31)
	{
		if (node->info->data->mes >= 1 && node->info->data->mes <= 12)
		{
			if (node->info->data->hora >= 0 && node->info->data->hora <= 24)
			{
				if (node->info->data->minuto >= 0 && node->info->data->minuto <= 60)
				{
					if (node->info->data->segundo >= 0 && node->info->data->segundo <= 60)
					{
						if (node->info->data->ano >= 1900 && node->info->data->ano <= tempoAtual->tm_year + 1900)
						{
							if (node->info->data->milisegundo >= 0 && node->info->data->milisegundo <= 999)
							{
								printf("DADOS VALIDOS\n");
								return 1;
							}
						}
					}
				}
					
			}
		}
	}
	else
	{
		printf("ERRO! DADOS INVALIDOS\n");
		return 0;
	}
	
}

//retorna o NODECarro com o id especificado
NODE_CARRO* procurarPorId(LISTA_HASHC* listaHash, int id)
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

				return nodeCarroEncontrado;
			}
			nodeCarros = nodeCarros->next;

		}
		nodeHashCarro = nodeHashCarro->next;
	}
	return NULL;
}

//retorna o carro com o id especificado
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

//uso do quickSort para ter um guia de como ordenar
int compararCarros(const void* a, const void* b)
{
	//converter o ponteiro generico recebido para um NODE CARRO
	NODE_CARRO* carroA = *(NODE_CARRO**)a;
	NODE_CARRO* carroB = *(NODE_CARRO**)b;
	//verificar SE OS NODES EXISTEM
	if (carroA == NULL && carroB == NULL)
	{
		return 0;
	}
	if (carroA == NULL)
	{
		return 1;
	}
	if (carroB == NULL) 
	{
		return -1;
	}

	// usar a função maiorMatricula
	if (maiorMatricula(carroA->info->codVeiculo, carroB->info->codVeiculo, listaParaComparar) == 1)
		return 1;
	else
		return -1;
}
//listar Ordenadamente matricula passagem na autoestrada durante periodo x (inicio - fim)
void carrosCircularamduranteX(PASSAGEM_LISTA* listaPassagem, LISTA_HASHC* listaHashCarros)
{
	if (!listaPassagem || !listaHashCarros)
	{
		return;
	}
	//guardar input do user o periodo inicial
	DATA* periodoInicial = (DATA*)malloc(sizeof(DATA));
	//guardar input do user o periodo final
	DATA* periodoFinal = (DATA*)malloc(sizeof(DATA));
	if (periodoInicial == NULL || periodoFinal == NULL)
	{
		free(periodoInicial);
		free(periodoFinal);
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

	//percorrer a lista passagem e adicionar a array todos os IDCARROS que satisfazem a condicao
	PASSAGEM_NODE* nodePassagem = listaPassagem->header;

	//guardar numa array todos os CARROS que satizfazem a condicao
	NODE_CARRO* arrayCarros[MAX_ARRAY_CARROS];
	//inicializar a array a null
	for (int j = 0; j < MAX_ARRAY_CARROS; j++)
	{
		arrayCarros[j] = NULL;
	}
	int i = 0;
	printf("PROCURAR CONDICAO PERIODO\n");
	while (nodePassagem)
	{
		//encontrar as datas que satisfacam a condicao
		if (checkPeriodoX(nodePassagem, periodoInicial, periodoFinal) == 1)
		{
			NODE_CARRO* carroEncontrado = procurarPorId(listaHashCarros, nodePassagem->info->codVeiculo);
			if (carroEncontrado != NULL)
			{
				int encontrado = 0;
				for (int j = 0; j < i; j++)
				{
					if (arrayCarros[j] != NULL && arrayCarros[j]->info->codVeiculo == carroEncontrado->info->codVeiculo)
					{
						encontrado = 1;
						break;
					}
				}
				if (!encontrado)
				{
					//adicionar na array o id do carro
					arrayCarros[i] = carroEncontrado;
					//avancar para a proxima casa array
					i++;
				}
			}
		}
		nodePassagem = nodePassagem->next;
	}
	//definir a listaComparar, para poder usar dentro do compararCarros
	listaParaComparar = listaHashCarros;

	//ordenar a array atraves do quickSort
	//faz a troca do indice segundo o que o compararCarros retorna (se tiver a maior matricula troca, senao mantem no indice)
	qsort(arrayCarros, MAX_ARRAY_CARROS, sizeof(NODE_CARRO*), compararCarros);


	//listar os conteudos da array (que ja esta ordenada por matricula)
	// Cabeçalho da lista
	printf("**************************************************************\n");
	printf("|                        LISTA CARROS                        |\n");
	printf("**************************************************************\n");
	printf("\nMatricula\tMarca\t\tModelo\t\tAno\t\tID_Dono\t\tCodigo_Veiculo\n\n");

	for (i = 0; i < MAX_ARRAY_CARROS; i++)
	{
		if (arrayCarros[i] != NULL)
		{
			printf("%s\t%s\t\t%s\t\t%d\t\t%d\t\t%d\n", arrayCarros[i]->info->matricula, arrayCarros[i]->info->marca, arrayCarros[i]->info->modelo, arrayCarros[i]->info->ano, arrayCarros[i]->info->dono, arrayCarros[i]->info->codVeiculo);
		}
	}
	printf("*****************************************************************************\n");

	//libertar a array de carros como a array esta alocada na heap, ele acaba por libertar sozinho no fim da funcao
	//percorrer a array e se existir um indice, dar free
	for (i = 0; i < MAX_ARRAY_CARROS; i++)
	{
		if (arrayCarros[i] != NULL)
		{
			arrayCarros[i] = NULL;
		}
	}

	//free dos periodos
	free(periodoFinal);
	free(periodoInicial);

}

//verifica se esta entre o tempoX e Y
int checkPeriodoX(PASSAGEM_NODE* nodePassagem, DATA* periodoInicial, DATA* periodoFinal)
{
	//verificar se esta antes da data inicial
	if (nodePassagem->info->data->ano < periodoInicial->ano)
	{
		return 0;
	}
	//se tiver o mesmo ano
	if (nodePassagem->info->data->ano == periodoInicial->ano)
	{
		//verificar se o mes e inferior
		if (nodePassagem->info->data->mes < periodoInicial->mes)
		{
			return 0;
		}
		//verificar se tem o dia inferior ao targetInicial
		if (nodePassagem->info->data->mes == periodoInicial->mes && nodePassagem->info->data->dia < periodoInicial->dia)
		{
			return 0;
		}
	}
	//verificar se esta depois da data final
	if (nodePassagem->info->data->ano > periodoFinal->ano)
	{
		return 0;
	}
	if (nodePassagem->info->data->ano == periodoFinal->ano)
	{
		//verificar se o mes e superior
		if (nodePassagem->info->data->mes > periodoFinal->mes)
		{
			return 0;
		}
	
		//verificar se o dia e superior ao limite
		if (nodePassagem->info->data->mes == periodoFinal->mes && nodePassagem->info->data->dia > periodoFinal->dia)
		{
			return 0;
		}
	}
	
		//verificar se a data e inferior ao periodo inicial
		if (nodePassagem->info->data->hora < periodoInicial->hora)
		{
			return 0;
		}
			
		if (nodePassagem->info->data->hora == periodoInicial->hora && nodePassagem->info->data->minuto < periodoInicial->minuto)
		{
			return 0;
		}
			

	//se passou os testes de dia/mes/ano verificar o periodoFinal
		if (nodePassagem->info->data->hora > periodoFinal->hora)
		{
			return 0;
		}
			
		if (nodePassagem->info->data->hora == periodoFinal->hora && nodePassagem->info->data->minuto > periodoFinal->minuto)
		{
			return 0;
		}
			
	//se passou os testes esta dentro do intervalo 
	return 1;
}

//verificar se a seguinte matricula  e maior (por IDCARRO)
int maiorMatricula(int pCarro, int sCarro, LISTA_HASHC* listaHashCarro)
{
	NODE_CARRO* primeiroCarro = NULL;
	NODE_CARRO* segundoCarro = NULL;

	int encontrei1 = 0;
	int encontrei2 = 0;
	//criar o Node para percorrer a lista Hash
	NODE_HASHC* nodeHashCarro = listaHashCarro->header;
	while ( (encontrei1 && encontrei2) == 0) //operacao AND 
	{
		//percorrer a lista dos carros
		NODE_CARRO* nodeCarro = nodeHashCarro->listaCarros->header;
		while (nodeCarro != NULL)
		{
			

			//se encontrar o carro com o mesmo id que o pCarro , adicionar a struct primeiroCarro
			if (nodeCarro->info->codVeiculo == pCarro)
			{
				primeiroCarro = nodeCarro;
				encontrei1 = 1;
			}
			//se for igual ao sCarro
			if (nodeCarro->info->codVeiculo == sCarro)
			{
				segundoCarro = nodeCarro;
				encontrei2 = 1;
			}
			nodeCarro = nodeCarro->next;
		}
	
		nodeHashCarro = nodeHashCarro->next;
		
	}
	//ordem crescente
	if (strcmp(primeiroCarro->info->matricula, segundoCarro->info->matricula) > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//ordena por total de km percorridos por carro
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
	int contador = 0;
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
			//cria um no apenas se ainda nao existir o carro na listaViagens (EVITAR REPETICAO DE DADOS)
			if (existeCarroListaViagens(listaViagens, nodePassagem->info->codVeiculo) == 0) //se nao existir o carro
			{
				//se for o sensor de entrada cria um novo
				if (nodePassagem->info->tipoRegisto == 0)
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
					contador++;
				}
			}
			else // se o carro ja existir
			{				
				// vai adicionar apenas os km da nova passagem se e so se for o sensor de entrada
				if (nodePassagem->info->tipoRegisto == 0)
				{
					idEntrada = 0;
					idSaida = 0;

					NODE_VIAGENS* nodeViagem = listaViagens->header;
					while (nodeViagem)
					{
						//encontrar a posicao do carro e adicionar apenas os novos km
						if (nodeViagem->carro->codVeiculo == nodePassagem->info->codVeiculo)
						{
							//adicionar o ID de entrada e saida
							idEntrada = nodePassagem->info->idSensor;
							idSaida = nodePassagem->next->info->idSensor;
							nodeViagem->totalKm += distanciaEntreSensor(idEntrada, idSaida, listaDistancias);
						}
						nodeViagem = nodeViagem->next;
					}
				}
			}
			
		}
		nodePassagem = nodePassagem->next;
	}
	printf("EXISTEM [%d] carros que satizfazem a condicao\n", contador);
	printf("A ORGANIZAR POR TOTAL KM (DESCENDENTE)\n");
	//organizar os nodesViagens da listaViagens por maior carro distancia percorrida
	NODE_VIAGENS* aux = listaViagens->header;
	//criar um buffer para armazenar o nodeViagens
	NODE_VIAGENS* buffer = NULL;
	int troca = 0;
	do
	{
		//dar reset ao aux
		aux = listaViagens->header;
		troca = 0;
		//so troca se existir um proximo node
		while (aux->next!= NULL)
		{
			//verificar se o atual e menor que o seguinte
			if (aux->totalKm < aux->next->totalKm)
			{
				// troca o conteudo dos nos
				float tempTotalKm = aux->totalKm;
				CARRO* tempCarro = aux->carro;

				aux->totalKm = aux->next->totalKm;
				aux->carro = aux->next->carro;

				aux->next->totalKm = tempTotalKm;
				aux->next->carro = tempCarro;

				troca = 1;
			}
			aux = aux->next;
		}
	} while (troca); // percorre sempre uma ultima vez a lista se nao existirem trocas, a lista esta ordenada
	
	//print da listaViagens
	aux = listaViagens->header;
	// Cabeçalho da lista
	printf("**************************************************************\n");
	printf("|                        LISTA VIAGENS                        |\n");
	printf("**************************************************************\n");
	printf("\nTotalKM\tMatricula\tMarca\t\tModelo\t\tAno\t\tID_Dono\t\tCodigo_Veiculo\n\n");
	while (aux)
	{
		printf("%.2f\t%s\t%s\t\t%s\t\t%d\t\t%d\t\t\t%d\n", aux->totalKm, aux->carro->matricula, aux->carro->marca, aux->carro->modelo, aux->carro->ano, aux->carro->dono, aux->carro->codVeiculo);
		aux = aux->next;
	}
	printf("\n");
	//ELIMINAR MEMORIA PARA A LISTA VIAGENS
	freeListaViagens(listaViagens);
}

long int calculoDistancia(DATA* dataEntrada, DATA* dataSaida)
{

	if (!dataEntrada || !dataSaida)
	{
		return;
	}

	long int milisegundosSaida = 0;
	//transformar a data de SAIDA em MS (feedback do prof)
	milisegundosSaida += dataSaida->hora * 3600000;
	milisegundosSaida += dataSaida->minuto * 60000;
	//milisegundosSaida += dataSaida->segundo * 1000;
	//milisegundosSaida += dataSaida->milisegundo;

	long int milisegundosEntrada = 0;
	//transformar a data de Entrada em MS
	milisegundosEntrada += dataEntrada->hora * 3600000;
	milisegundosEntrada += dataEntrada->minuto * 60000;
	//milisegundosEntrada += dataEntrada->segundo * 1000;
	//milisegundosEntrada += dataEntrada->milisegundo;

	long int tempoViagemMS = milisegundosSaida - milisegundosEntrada;
	//verificar se o tempo de viagem e positivo
	if (tempoViagemMS > 0)
	{
		return tempoViagemMS;
	}
	else
	{
		return;
	}
}

void infracoesDuranteX(LISTA_CARRO* listaHashCarros, PASSAGEM_LISTA* listaPassagem, DISTANCIAS_LISTA* listaDistancias)
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
	int contador = 0;
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
			//cria um no apenas se ainda nao existir o carro na listaViagens (EVITAR REPETICAO DE DADOS)
			if (existeCarroListaViagens(listaViagens, nodePassagem->info->codVeiculo) == 0) //se nao existir o carro
			{
				//se for o sensor de entrada cria um novo
				if (nodePassagem->info->tipoRegisto == 0)
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
					//adicionar a diference dntre os tempos de entrada e saida
					nodeViagens->milisegundosPercorridos += calculoDistancia(nodePassagem->info->data, nodePassagem->next->info->data);
					//adicionar a lista nodeViagens a lista Viagens
					adicionarNodeListaViagens(nodeViagens, listaViagens);
					contador++;
				}
			}
			else // se o carro ja existir
			{
				// vai adicionar apenas os km da nova passagem se e so se for o sensor de entrada
				if (nodePassagem->info->tipoRegisto == 0)
				{
					idEntrada = 0;
					idSaida = 0;

					NODE_VIAGENS* nodeViagem = listaViagens->header;
					while (nodeViagem)
					{
						//encontrar a posicao do carro e adicionar apenas os novos km
						if (nodeViagem->carro->codVeiculo == nodePassagem->info->codVeiculo)
						{
							//adicionar o ID de entrada e saida
							idEntrada = nodePassagem->info->idSensor;
							idSaida = nodePassagem->next->info->idSensor;
							nodeViagem->totalKm += distanciaEntreSensor(idEntrada, idSaida, listaDistancias);
							nodeViagem->milisegundosPercorridos += calculoDistancia(nodePassagem->info->data, nodePassagem->next->info->data);
						}
						nodeViagem = nodeViagem->next;
					}
				}
			}

		}
		nodePassagem = nodePassagem->next;
	}
	printf("EXISTEM [%d] carros que satizfazem a condicao\n", contador);
	printf("A ORGANIZAR POR TOTAL KM (DESCENDENTE)\n");
	//organizar os nodesViagens da listaViagens por maior carro distancia percorrida
	NODE_VIAGENS* aux = listaViagens->header;
	//criar um buffer para armazenar o nodeViagens
	NODE_VIAGENS* buffer = NULL;
	int troca = 0;
	do
	{
		//dar reset ao aux
		aux = listaViagens->header;
		troca = 0;
		//so troca se existir um proximo node
		while (aux->next != NULL)
		{
			//verificar se o atual e menor que o seguinte
			if (aux->totalKm < aux->next->totalKm)
			{
				// troca o conteudo dos nos
				float tempTotalKm = aux->totalKm;
				CARRO* tempCarro = aux->carro;

				aux->totalKm = aux->next->totalKm;
				aux->carro = aux->next->carro;

				aux->next->totalKm = tempTotalKm;
				aux->next->carro = tempCarro;

				troca = 1;
			}
			aux = aux->next;
		}
	} while (troca); // percorre sempre uma ultima vez a lista se nao existirem trocas, a lista esta ordenada

	//print da listaViagens
	aux = listaViagens->header;
	// Cabeçalho da lista
	printf("**************************************************************\n");
	printf("|                        LISTA VIAGENS                        |\n");
	printf("**************************************************************\n");
	printf("\nTotalKM\t\tMatricula\tCodigo_Veiculo\tVelocidade Media\n\n");
	while (aux)
	{
		
		//para evitar overflow
		long float horasTotais = aux->milisegundosPercorridos / 3600000.0f;
		long float velocidadeMedia = aux->totalKm / horasTotais;
		if (velocidadeMedia > 120.0)
		{
			printf("%.2f\t\t%s\t%d\t\t%.2lf\n",aux->totalKm, aux->carro->matricula,aux->carro->codVeiculo, velocidadeMedia);
		}
		aux = aux->next;
	}
	printf("\n");
	//ELIMINAR MEMORIA PARA A LISTA VIAGENS
	freeListaViagens(listaViagens);
}

void totalKmMarcaDuranteX(LISTA_HASHC* listaHashCarros, PASSAGEM_LISTA* listaPassagem, DISTANCIAS_LISTA* listaDistancias)
{
	// Validação da existência das listas
	if (!listaPassagem || !listaHashCarros || !listaDistancias)
	{
		return;
	}

	// Guardar os dados sobre a data que o User escolhe
	DATA* periodoInicial = (DATA*)malloc(sizeof(DATA));
	DATA* periodoFinal = (DATA*)malloc(sizeof(DATA));

	// Validação da alocação de memória
	if (periodoInicial && periodoFinal == NULL)
	{
		return;
	}

	// Pede a Data Inicial de Pesquisa
	printf("INSIRA O DIA INICIAL DE PESQUISA!\n");
	printf("DIA: ");
	scanf("%d", &periodoInicial->dia);
	printf("MES: ");
	scanf("%d", &periodoInicial->mes);
	printf("ANO: ");
	scanf("%d", &periodoInicial->ano);
	printf("**************************\n");

	// Pede a Data Final de Pesquisa
	printf("INSIRA O DIA FINAL DE PESQUISA!\n");
	printf("DIA: ");
	scanf("%d", &periodoFinal->dia);
	printf("MES: ");
	scanf("%d", &periodoFinal->mes);
	printf("ANO: ");
	scanf("%d", &periodoFinal->ano);
	printf("**************************\n");

	// Pede a Hora Inicial de Pesquisa
	printf("INSIRA A HORA INICIAL DE PESQUISA!\n");
	printf("HORA: ");
	scanf("%d", &periodoInicial->hora);
	printf("MINUTOS: ");
	scanf("%d", &periodoInicial->minuto);

	// Pede a Hora Final de Pesquisa
	printf("INSIRA A HORA FINAL DE PESQUISA!\n");
	printf("HORA: ");
	scanf("%d", &periodoFinal->hora);
	printf("MINUTOS: ");
	scanf("%d", &periodoFinal->minuto);

	// Criação da Lista Viagens
	LISTA_VIAGENS* listaViagens = criarListaViagens();

	// Estrutura para armazenar os totais Km's por marca
	LISTA_HASHC* listaMarcas = listaHashCarros;

	// Validação da situação de haver algum carro que passe na autoestrada durante a data de pesquisa
	PASSAGEM_NODE* nodePassagem = listaPassagem->header;

	int contador = 0; // Contador para ver quantos carros estão dentro da data de pesquisa
	int idEntrada = 0; // ID de Entrada temporário para calcular a distancia entre os sensores
	int idSaida = 0; // ID de Saída temporário para calcular a distancia entre os sensores

	while (nodePassagem) // Percorre a lista das Passagens
	{
		// Encontra as datas que satisfaçam a condição
		if (checkPeriodoX(nodePassagem, periodoInicial, periodoFinal) == 1)
		{
			// Cria um Nó apenas se ainda não existir o carro na Lista Viagens (EVITAR REPETIÇÃO DE DADOS)
			if (existeCarroListaViagens(listaViagens, nodePassagem->info->codVeiculo) == 0)
			{
				// Se for um sensor de entrada cria um novo Nó
				if (nodePassagem->info->tipoRegisto == 0)
				{
					// Criação do NODE_VIAGENS
					NODE_VIAGENS* nodeViagens = criarNodeViagens();

					// Adicionar o carro ao NODE_VIAGENS
					nodeViagens->carro = retornaCarro(listaHashCarros, nodePassagem->info->codVeiculo);

					// Adicionar o ID de entrada e saida
					idEntrada = nodePassagem->info->idSensor;
					idSaida = nodePassagem->next->info->idSensor;

					// Ver a distancia entre o Sensor de ENTRADA e o Sensor de SAIDA
					// De seguida atualiza o somatório
					nodeViagens->totalKm += distanciaEntreSensor(idEntrada, idSaida, listaDistancias);

					// Adicionar a lista nodeViagens a lista Viagens
					adicionarNodeListaViagens(nodeViagens, listaViagens);
					contador++;
				}
			}
			else // se o carro já existir
			{
				// vai adicionar apenas os km da nova passagem se for o sensor de entrada
				if (nodePassagem->info->tipoRegisto == 0)
				{
					idEntrada = 0;
					idSaida = 0;

					NODE_VIAGENS* nodeViagem = listaViagens->header;
					while (nodeViagem)
					{
						// Encontrar a posição do carro e adicionar apenas os novos km
						if (nodeViagem->carro->codVeiculo == nodePassagem->info->codVeiculo)
						{
							// Adicionar o ID de entrada e saída
							idEntrada = nodePassagem->info->idSensor;
							idSaida = nodePassagem->next->info->idSensor;
							nodeViagem->totalKm += distanciaEntreSensor(idEntrada, idSaida, listaDistancias);
						}
						nodeViagem = nodeViagem->next;
					}
				}
			}
		}
		nodePassagem = nodePassagem->next;
	}

	printf("EXISTEM [%d] carros que satisfazem a condicao\n\n", contador);

	// **Agora, devemos somar os quilómetros de cada carro por marca**
	NODE_HASHC* nodeHash = listaMarcas->header;

	while (nodeHash)
	{
		// Resetando o total de km para cada marca
		nodeHash->totalKm_marca = 0;

		// Percorrendo todos os carros desta marca
		NODE_CARRO* nodeCarro = nodeHash->listaCarros->header;
		while (nodeCarro)
		{
			NODE_VIAGENS* nodeViagem = listaViagens->header;
			while (nodeViagem)
			{
				// Se o carro estiver na lista de viagens, soma os km da viagem
				if (nodeCarro->info->codVeiculo == nodeViagem->carro->codVeiculo)
				{
					nodeHash->totalKm_marca += nodeViagem->totalKm;
				}
				nodeViagem = nodeViagem->next;
			}
			nodeCarro = nodeCarro->next;
		}
		nodeHash = nodeHash->next;
	}

	// Ordenção das marcas pelo total de km percorridos (ordem decrescente)

	ordenarListaMarcasPorKm(listaMarcas);

	// Apresentação da Lista de Marcas por Ordem Decrescente de Km's Totais
	nodeHash = listaMarcas->header;

	printf("**************************************************************\n");
	printf("|           RANKING DAS MARCA POR KM'S PERCORRIDOS           |\n");
	printf("**************************************************************\n");

	while (nodeHash)
	{
		printf("Marca: %s | Km Total: %.2f\n", nodeHash->chave, nodeHash->totalKm_marca);
		nodeHash = nodeHash->next;
	}

	printf("\n");
	// Liberar memória para a lista de viagens
	freeListaViagens(listaViagens);
}

void ordenarListaMarcasPorKm(LISTA_HASHC* lista) {

	if (!lista || !lista->header)
	{
		printf("ERRO! A lista HASH nao existe.\n");
		return;
	}

	NODE_HASHC* atual;
	NODE_HASHC* proximo;
	char tempMarca[100];
	float tempKm;
	LISTA_CARRO* tempLista;
	int troca;

	do {
		troca = 0;
		atual = lista->header;

		while (atual != NULL && atual->next != NULL) {
			proximo = atual->next;

			if (proximo->totalKm_marca > atual->totalKm_marca) {
				tempKm = atual->totalKm_marca;
				atual->totalKm_marca = proximo->totalKm_marca;
				proximo->totalKm_marca = tempKm;

				strcpy(tempMarca, atual->chave);
				strcpy(atual->chave, proximo->chave);
				strcpy(proximo->chave, tempMarca);

				tempLista = atual->listaCarros;
				atual->listaCarros = proximo->listaCarros;
				proximo->listaCarros = tempLista;

				troca = 1;
			}
			atual = atual->next;
		}
	} while (troca);
}

void totalinfracoesDuranteX(LISTA_CARRO* listaHashCarros, PASSAGEM_LISTA* listaPassagem, DISTANCIAS_LISTA* listaDistancias)
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

	// Criar lista de viagens com infrações
	LISTA_VIAGENS* listaInfracoes = criarListaViagens();

	// Verifica se algum carro passou na autoestrada durante periodo X
	PASSAGEM_NODE* nodePassagem = listaPassagem->header;

	while (nodePassagem && nodePassagem->next)
	{
		// Considera apenas registos de entrada dentro do período X
		if (nodePassagem->info->tipoRegisto == 0 && checkPeriodoX(nodePassagem, periodoInicial, periodoFinal))
		{
			PASSAGEM_NODE* proximo = nodePassagem->next;

			if (!checkPeriodoX(proximo, periodoInicial, periodoFinal))
			{
				nodePassagem = nodePassagem->next;
				continue;
			}

			float distancia = distanciaEntreSensor(nodePassagem->info->idSensor, proximo->info->idSensor, listaDistancias);
			long tempoMilisegundos = calculoDistancia(nodePassagem->info->data, proximo->info->data);
			float horas = tempoMilisegundos / 3600000.0f;
			float velocidade = distancia / horas;

			if (velocidade > 120)
			{
				// Verifica se já existe NODE_VIAGENS para o carro
				NODE_VIAGENS* nodeViagem = listaInfracoes->header;
				int encontrou = 0;

				while (nodeViagem)
				{
					if (nodeViagem->carro->codVeiculo == nodePassagem->info->codVeiculo)
					{
						nodeViagem->totalInfracoes++;
						encontrou = 1;
						break;
					}

					nodeViagem = nodeViagem->next;
				}

				if (!encontrou)
				{
					NODE_VIAGENS* novaViagem = criarNodeViagens();
					novaViagem->carro = retornaCarro(listaHashCarros, nodePassagem->info->codVeiculo);
					novaViagem->totalInfracoes = 1;
					adicionarNodeListaViagens(novaViagem, listaInfracoes);
				}
			}
		}
		nodePassagem = nodePassagem->next;
	}

	// Ordenar lista por totalInfracoes (ordem descendente)
	int troca;
	NODE_VIAGENS* aux;

	do
	{
		troca = 0;
		aux = listaInfracoes->header;

		while (aux && aux->next)
		{
			if (aux->totalInfracoes < aux->next->totalInfracoes)
			{
				// Troca os dados dos nodes
				int tempInfracoes = aux->totalInfracoes;
				float tempKm = aux->totalKm;
				long tempTempo = aux->milisegundosPercorridos;
				CARRO* tempCarro = aux->carro;

				aux->totalInfracoes = aux->next->totalInfracoes;
				aux->totalKm = aux->next->totalKm;
				aux->milisegundosPercorridos = aux->next->milisegundosPercorridos;
				aux->carro = aux->next->carro;

				aux->next->totalInfracoes = tempInfracoes;
				aux->next->totalKm = tempKm;
				aux->next->milisegundosPercorridos = tempTempo;
				aux->next->carro = tempCarro;

				troca = 1;
			}

			aux = aux->next;
		}
	} while (troca);

	// Cabeçalho
	printf("**************************************************************\n");
	printf("|              RANKING DE INFRACOES POR VEICULO              |\n");
	printf("**************************************************************\n");
	printf("\nTotal Infracoes\tMatricula\tMarca\t\tModelo\t\tCodigo_Veiculo\n\n");

	// Mostrar o Ranking
	aux = listaInfracoes->header;

	while (aux)
	{
		printf("%d\t\t%s\t%s\t\t%s\t\t%d\n", aux->totalInfracoes, aux->carro->matricula, aux->carro->marca, aux->carro->modelo, aux->carro->codVeiculo);
		aux = aux->next;
	}

	// Destruir a memória alocada para a Lista e os Períodos
	freeListaViagens(listaInfracoes);
	free(periodoInicial);
	free(periodoFinal);
}
