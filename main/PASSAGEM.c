#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>

#include "PASSAGEM.H"

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
		printf("LISTA DISTANCIAS LIBERTADA COM SUCESSO! \n");
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
		printf("Insere a data em que o veiculo passou no sensor [DIA-MES-ANO]:\n");
		scanf("%d", &node->info->data->dia);
		scanf("%d", &node->info->data->mes);
		scanf("%d", &node->info->data->ano);
		printf("[HORA - MINUTO - SEGUNDO - MILISEGUNDO]:\n");
		scanf("%d", &node->info->data->hora);
		scanf("%d ", &node->info->data->minuto);
		scanf("%d", &node->info->data->segundo);
		scanf("%d", &node->info->data->milisegundo);
		printf("Qual foi o tipo de registo? [0 -> ENTRADA / 1-> SAIDA]:\n");
		scanf("%d", &node->info->tipoRegisto);
		//verificar os dados intoduzidos
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

		printf("Pretende registar mais passagens?\n");
		printf("1 -> SIM | 0 -> NAO\n");
		scanf("%d", &criar);

	}


}

int verificarNodeDadosPassagem(PASSAGEM_NODE* node)
{
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
						if (node->info->data->ano >= 1900)
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

