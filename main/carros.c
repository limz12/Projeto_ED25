#include "carros.h"


LISTA_CARRO* criarListaCarro()
{
	// Aloca��o de mem�ria da lista de Carros
	LISTA_CARRO* lista = (LISTA_CARRO*)malloc(sizeof(LISTA_CARRO));

	// Valida��o da aloca��o da lista
	if (!lista)
	{
		printf("ERRO a alocar a lista de carros!\n");
		return;
	}

	lista->header = NULL; // ponteiro do inicio da lista
	lista->ultimo_node = NULL; // ponteiro para o ultimo elemento da lista
	lista->num_elem = 0;

	printf("Lista de Carros criada com sucesso!\n");

	return lista;
}

NODE_CARRO* criarNodeCarro()
{
	// Aloca��o de mem�ria para elemento da lista de Carros
	NODE_CARRO* node = (NODE_CARRO*)malloc(sizeof(NODE_CARRO));

	// Valida��o da aloca��o do elemento
	if (!node)
	{
		printf("ERRO a alocar o elemento da lista de carros!\n");
		return;
	}

	// Aloca��o de mem�ria para o conte�do dentro do elemento
	node->info = (CARRO*)malloc(sizeof(CARRO)); // Conte�do do Elemento = Carro
	node->next = NULL; // ponteiro para o pr�ximo � "= NULL", pois � adicionado no fim da lista

	printf("Elemento da Lista de Carros criado com sucesso!\n");

	return node;
}

int freeNodeCarro(NODE_CARRO* node)
{
	// Valida��o da exist�ncia do elemento na lista de carros
	if (!node)
	{
		printf("ERRO! O elemento nao existe.\n");
		return;
	}

	free(node->info); // Libertar a mem�ria alocada para conte�do/carro dentro do elemento
	free(node); // Libertar a mem�ria alocada para o elemento
	
	printf("Elemento da Lista de Carros libertado com sucesso!\n");
}

void carregarDadosCarro(LISTA_CARRO* lista)
{
	// Reconhecimento de caracteres especiais do ficheiro, por parte do compilador
	setlocale(LC_ALL, "en_US.UTF-8");

	// Valida��o da exist�ncia da lista de carros
	if (!lista)
	{
		printf("ERRO! A lista nao existe.\n");
		return;
	}

	// Abertura do ficheiro de texto em modo leitura/read ("r")
	FILE* f = fopen("carros.txt", "r");

	// Valida��o da correta abertura do ficheiro
	if (!f)
	{
		printf("ERRO ao abrir o ficheiro em modo leitura.\n");
		return;
	}

	char str_aux[50]; // Vari�vel string auxiliar para guardar o conte�do de cada linha do ficheiro

	// Ciclo para ler linha a linha do ficheiro
	while (fgets(str_aux, sizeof(str_aux), f))
	{
		// Verifica��o dos casos de existir linhas em branco
		if (strcmp(str_aux, "\n") == 0)
		{
			// Linha em Branco encontrada
		}
		else // Caso a linha tenha conte�do:
		{
			// Cria o elemento da lista
			NODE_CARRO* node = criarNodeCarro();

			// Valida��o da correta cria��o do elemento
			if (!node)
			{
				printf("ERRO na criacao do elemento.\n");
				return;
			}

			// Adiciona o conte�do � vari�vel string auxiliar
			sscanf(str_aux, "%s\t%s\t%s\t%d\t%d\t%d", 
				node->info->matricula, node->info->marca, node->info->modelo, 
				&node->info->ano, &node->info->dono, &node->info->codVeiculo);

			// Adicionar o elemento/linha � lista de carros
			addListaCarro(lista, node);
		}
	}

	// Depois de ler o ficheiro todo -> Fechar o ficheiro
	fclose(f);
}

void addListaCarro(LISTA_CARRO* lista, NODE_CARRO* node)
{
	// Verifica��o  da exist�ncia da lista de carros e do elemento
	if (!lista || !node)
	{
		printf("ERRO! A lista de carros e o elemento nao existem.\n");
		return;
	}

	// Cria��o de um elemento auxiliar para percorrer a lista
	NODE_CARRO* aux = lista->header;

	// Caso a lista n�o tenha nenhum elemento:
	if (lista->header == NULL)
	{
		lista->header = node;
		lista->ultimo_node = node;
		lista->num_elem++;
	}
	else // Caso a lista j� tenha elementos criados:
	{
		lista->ultimo_node->next = node;
		lista->ultimo_node = node;
		lista->num_elem++;
	}
}
