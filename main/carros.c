#include "carros.h"


LISTA_CARRO* criarListaCarro()
{
	// Aloca��o de mem�ria da lista de Carros
	LISTA_CARRO* lista = (LISTA_CARRO*)malloc(sizeof(LISTA_CARRO));

	// Valida��o da aloca��o da lista
	if (!lista)
	{
		printf("ERRO a alocar a lista de carros!\n");
		return NULL;
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
		return NULL;
	}

	// Aloca��o de mem�ria para o conte�do dentro do elemento
	node->info = (CARRO*)malloc(sizeof(CARRO)); // Conte�do do Elemento = Carro
	node->next = NULL; // ponteiro para o pr�ximo � "= NULL", pois � adicionado no fim da lista

	/*printf("Elemento da Lista de Carros criado com sucesso!\n");*/

	return node;
}

int freeNodeCarro(NODE_CARRO* node)
{
	// Valida��o da exist�ncia do elemento na lista de carros
	if (!node)
	{
		printf("ERRO! O elemento nao existe.\n");
		return NULL;
	}

	free(node->info); // Libertar a mem�ria alocada para conte�do/carro dentro do elemento
	free(node); // Libertar a mem�ria alocada para o elemento
	
	//printf("Elemento da Lista de Carros libertado com sucesso!\n");
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
	
	printf("- Ficheiro lido com sucesso.\n\n");

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

void criarCarroUtilizador(LISTA_CARRO* lista)
{
	// Cria��o de um elemento novo por parte do utilizador
	NODE_CARRO* novo_elem = criarNodeCarro();

	// Inser��o do conte�do do novo elemento = dados do ve�culo
	printf("\tINSIRA DADOS DO VEICULO:");
	printf("\n-> Matricula: ");
	scanf("%s", novo_elem->info->matricula);
	printf("-> Marca: ");
	scanf("%s", novo_elem->info->marca);
	printf("-> Modelo: ");
	scanf("%s", novo_elem->info->modelo);
	printf("-> Ano: ");
	scanf("%d", &(novo_elem->info->ano));
	printf("-> ID do Dono: ");
	scanf("%d", &(novo_elem->info->dono));
	printf("-> Codigo do Veiculo: ");
	scanf("%d", &(novo_elem->info->codVeiculo));

	// Adiciona o elemento � lista
	addListaCarro(lista, novo_elem);
}

void mostrarListaSensores(LISTA_CARRO* lista)
{
	// Valida��o da exist�ncia da lista de carros
	if (!lista)
	{
		printf("ERRO! A lista nao existe.\n");
		return;
	}

	// Cria��o de um elemento auxiliar para percorrer a lista
	NODE_CARRO* aux = lista->header;

	// Cabe�alho da lista
	printf("**************************************************************\n");
	printf("|                        LISTA CARROS                        |\n");
	printf("**************************************************************\n");
	printf("\nMatricula\tMarca\t\tModelo\t\tAno\t\tID_Dono\t\tCodigo_Veiculo\n\n");
	
	// Ciclo para percorrer a lista at� ao fim
	while (aux)
	{
		printf("%s\t%s\t\t%s\t\t%d\t\t%d\t\t%d\n", aux->info->matricula, aux->info->marca, aux->info->modelo, aux->info->ano, aux->info->dono, aux->info->codVeiculo);
		aux = aux->next;
	}

	// Fim da Lista
	printf("**************************************************************\n");
}

void freeListaCarro(LISTA_CARRO* lista)
{
	// Valida��o da exist�ncia da lista de carros
	if (!lista)
	{
		printf("ERRO! A lista nao existe.\n");
		return;
	}

	// Ciclo que n�o para enquanto existir elementos na lista
	while (lista->header)
	{ 
		// Percorre a lista com um ponteiro auxiliar
		NODE_CARRO* aux = lista->header;
		lista->header = aux->next;

		// Elimina��o dos n�s um a um, da lista
		freeNodeCarro(aux);
	}

	printf("Lista removida com sucesso\n");
}