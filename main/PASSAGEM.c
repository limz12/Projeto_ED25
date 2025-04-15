#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define MAX_ARRAY_CARROS 100000

#include "PASSAGEM.H"
#include "carros.h"
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

//retorna o Carro com o id especificado
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
	scanf("%d", &periodoFinal ->minuto);
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
			//para combater a repeticao dos IDCARRO presente na lista das passagens
			if (i > 0)
			{
				if (nodePassagem->info->codVeiculo != arrayCarros[i - 1]->info->codVeiculo)
				{
					//adicionar na array o id do carro
					arrayCarros[i] = procurarPorId(listaHashCarros,nodePassagem->info->codVeiculo);
					//avancar para a proxima casa array
					i++;
				}					
			}
			else 
			{
				//adicionar na array o id do carro
				arrayCarros[i] = procurarPorId(listaHashCarros, nodePassagem->info->codVeiculo);
				//avancar para a proxima casa array
				i++;
			}
			
		}
		nodePassagem = nodePassagem->next;
	}

	//*******************************************
	//bubble sort da Array carros (organizar alfabeticamente matriculas)
	int troca;
	NODE_CARRO* buffer = NULL;
	//percorrer toda a Array dos carros
	printf("A ORDENAR! (DEPENDENDO DO RANGE DA PESQUISA PODE DEMORAR!)\n");
	int contador = 0;
	for (int k = 0; k < MAX_ARRAY_CARROS - 1; k++)
	{
		if (arrayCarros[k] != NULL)
		{
			contador += 1;
		}
	}
	printf("Existem [%d] Carros que satisfazem a condicao\n", contador);
	do
	{
		troca = 0;
		//para nao passar do ultimo indice, resolver o problema out of bounds tamanho da array
		for (i = 0; i < MAX_ARRAY_CARROS - 1; i++)
		{
			//se nao existir o proximo quer dizer que esta no ultimo indice, entao nao faz a troca
			if(arrayCarros[i+1] != NULL)
			{ 
				//se a segunda matricula for maior
				if (maiorMatricula(arrayCarros[i]->info->codVeiculo, arrayCarros[i + 1]->info->codVeiculo, listaHashCarros) == 1)
				{
					//trocar a posicao do indice atual com o segundo
					buffer = arrayCarros[i];
					arrayCarros[i] = arrayCarros[i + 1];
					arrayCarros[i + 1] = buffer;
					troca = 1;
					
				}
			}
		}
	} while (troca);
	
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
	for (i = 0; i < MAX_ARRAY_CARROS - 1; i++) // - 1 para nao passar do bound da array
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




