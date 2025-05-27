// BIBLIOTECAS
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>
#include <string.h>

#include "carros.h"
#include "donos.h"
#include "DISTANCIAS.H"
#include "PASSAGEM.H"

//******* TESTE
#define CARROS_POR_PAGINA 20

LISTA_CARRO* criarListaCarro()
{
	// Alocação de memória da lista de Carros
	LISTA_CARRO* lista = (LISTA_CARRO*)malloc(sizeof(LISTA_CARRO));

	// Validação da alocação da lista
	if (!lista)
	{
		printf("ERRO a alocar a lista de carros!\n");
		return NULL;
	}

	lista->header = NULL; // ponteiro do inicio da lista
	lista->ultimo_node = NULL; // ponteiro para o ultimo elemento da lista
	lista->num_elem = 0;

	return lista;
}

NODE_CARRO* criarNodeCarro()
{
	// Alocação de memória para elemento da lista de Carros
	NODE_CARRO* node = (NODE_CARRO*)malloc(sizeof(NODE_CARRO));

	// Validação da alocação do elemento
	if (!node)
	{
		printf("ERRO a alocar o elemento da lista de carros!\n");
		return NULL;
	}

	// Alocação de memória para o conteúdo dentro do elemento
	node->info = (CARRO*)malloc(sizeof(CARRO)); // Conteúdo do Elemento = Carro
	node->next = NULL; // ponteiro para o próximo é "= NULL", pois é adicionado no fim da lista
	node->info->totalKMPercorridos = 0.0;
	node->info->totalMinutosPercorridos = 0;
	node->info->velocidadeMediaKM = 0;
	/*printf("Elemento da Lista de Carros criado com sucesso!\n");*/

	return node;
}

int freeNodeCarro(NODE_CARRO* node)
{
	// Validação da existência do elemento na lista de carros
	if (!node)
	{
		printf("ERRO! O elemento nao existe.\n");
		return NULL;
	}

	free(node->info); // Libertar a memória alocada para conteúdo/carro dentro do elemento
	free(node); // Libertar a memória alocada para o elemento
	
	//printf("Elemento da Lista de Carros libertado com sucesso!\n");
}

void carregarDadosCarro(LISTA_HASHC* listaHashCarros)
{
	// Reconhecimento de caracteres especiais do ficheiro, por parte do compilador
	setlocale(LC_ALL, "en_US.UTF-8");

	// Validação da existência da lista de carros
	if (!listaHashCarros)
	{
		printf("ERRO! A lista nao existe.\n");
		return;
	}

	// Abertura do ficheiro de texto em modo leitura/read ("r")
	FILE* f = fopen("carros.txt", "r");

	// Validação da correta abertura do ficheiro
	if (!f)
	{
		printf("ERRO ao abrir o ficheiro em modo leitura.\n");
		return;
	}

	char str_aux[50]; // Variável string auxiliar para guardar o conteúdo de cada linha do ficheiro

	// Ciclo para ler linha a linha do ficheiro
	while (fgets(str_aux, sizeof(str_aux), f))
	{
		// Verificação dos casos de existir linhas em branco
		if (strcmp(str_aux, "\n") == 0)
		{
			// Linha em Branco encontrada
		}
		else // Caso a linha tenha conteúdo:
		{
			// Cria o elemento da lista
			NODE_CARRO* node = criarNodeCarro();

			// Adiciona o conteúdo à variável string auxiliar
			sscanf(str_aux, "%s\t%s\t%s\t%d\t%d\t%d", 
				node->info->matricula, node->info->marca, node->info->modelo, 
				&node->info->ano, &node->info->dono, &node->info->codVeiculo);
			//************** HASHING *************
			//se nao possuir nos no hash
			if (listaHashCarros->header == NULL)
			{
				//criarNodeHash
				NODE_HASHC* nodeHash = criarNodeHashCarro();
				if (!nodeHash)
				{
					return;
				}
				//inserir Dados / lista no node
				adicionarInfoNodeHash(nodeHash, node);
				//adicionar o nodeHash a lista
				listaHashCarros->header = nodeHash;
				listaHashCarros->ultimo_node = nodeHash;
				listaHashCarros->numElementos++;
			}
			else // se exsitirem NODES NA LISTA HASH
			{
				int flag = 0;
				//percorrer a lista a procura da chave
				NODE_HASHC* aux = listaHashCarros->header;
				while (aux)
				{
					if (strcmp(aux->chave, node->info->marca) == 0) //detetar a chave igual
					{
						addListaCarro(aux->listaCarros, node);
						flag = 1; //serve para indicar que foi inserido o NODE
					}
					aux = aux->next;
				}
				if (flag == 0) //se o node nao foi inserido
				{
					//vais ter de criar um NODEHASH
					NODE_HASHC* nodeHash = criarNodeHashCarro();
					if (!nodeHash)
					{
						return;
					}
					//adicionar a info ao nodeHAsh
					adicionarInfoNodeHash(nodeHash, node);
					//adicionar o nodeHash ao  final da lista HASH
					listaHashCarros->ultimo_node->next = nodeHash;
					listaHashCarros->ultimo_node = nodeHash;
					listaHashCarros->numElementos++;
				}
			}
			
		}
	}
	
	printf("CARROS CARREGADO COM SUCESSO!\n");

	// Depois de ler o ficheiro todo -> Fechar o ficheiro
	fclose(f);
}

void addListaCarro(LISTA_CARRO* lista, NODE_CARRO* node)
{
	// Verificação  da existência da lista de carros e do elemento
	if (!lista || !node)
	{
		printf("ERRO! A lista de carros e o elemento nao existem.\n");
		return;
	}

	// Criação de um elemento auxiliar para percorrer a lista
	NODE_CARRO* aux = lista->header;

	// Caso a lista não tenha nenhum elemento:
	if (lista->header == NULL)
	{
		lista->header = node;
		lista->ultimo_node = node;
		lista->num_elem++;
	}
	else // Caso a lista já tenha elementos criados:
	{
		lista->ultimo_node->next = node;
		lista->ultimo_node = node;
		lista->num_elem++;
	}
}

void criarCarroUtilizador(LISTA_HASHC* hashCarro, LISTA_DONOS* listaDonos)
{
	if (!hashCarro && !listaDonos)
	{
		printf("ERRO! A lista hash do carro nao existe");
		return;
	}
	// Criação de um elemento novo por parte do utilizador
	NODE_CARRO* novo_elem = criarNodeCarro();

	// Inserção do conteúdo do novo elemento = dados do veículo
	printf("\tINSIRA DADOS DO VEICULO:");
	printf("\n-> Matricula: ");
	scanf("%s", novo_elem->info->matricula);
	printf("-> Marca: ");
	scanf("%s", novo_elem->info->marca);
	printf("-> Modelo: ");
	scanf("%s", novo_elem->info->modelo);
	printf("-> Ano: ");
	scanf("%d", &novo_elem->info->ano);
	printf("-> ID do Dono: ");
	scanf("%d", &(novo_elem->info->dono));
	printf("-> Codigo do Veiculo: ");
	scanf("%d", &novo_elem->info->codVeiculo);

	//flag para detetar se exite um nodeHash com a chave 
	int flag = 0;
	//verificar se o ID do DONO EXISTE
	if (verificarDONOexiste(novo_elem->info->dono,listaDonos) == 1)
	{
		//percorrer pelos nos da listaHash se a chave existe
		NODE_HASHC* nodeHash = hashCarro->header;
		while (nodeHash)
		{
			//se existir um nodeHash com a mesma chave
			if (_stricmp(nodeHash->chave, novo_elem->info->marca) == 0)
			{
				//adiciona  a lista do nodeHash o novo elemento
				addListaCarro(nodeHash->listaCarros,novo_elem);
				printf("CARRO ADICIONADO COM SUCESSO!\n");
				flag = 1;
			}
			nodeHash = nodeHash->next;
		}
		if (flag == 0)//se percorreu a ListaHash e nao encontrou a chave
		{
			//criar um novo nodeHash
			NODE_HASHC* novoNodeHash = criarNodeHashCarro();
			//adicionar os dados ao novoNodeHash
			adicionarInfoNodeHash(novoNodeHash, novo_elem);
			//ligar o nodeHash a listaHash
			inserirNodeHashListaHash(hashCarro, novoNodeHash);
			printf("CARRO ADICIONADO COM SUCESSO!\n");
		}
	}
	else
	{
		printf("ERRO! O DONO NAO EXISTE\n");
	}

	
}

// Avança para o no correto, por exemplo da display dos 20 primeiros nodes,
// na proxima pagina avanca ate esses 20 e comeca o display apartir dai , 
// para nao existir repeticao dos dados
NODE_CARRO* avancarAte(NODE_CARRO* pertencelista, int pos) {
	int i = 0;
	NODE_CARRO* atual = pertencelista;
	while (atual && i < pos) {
		atual = atual->next;
		i++;
	}
	return atual;
}



void mostrarListaCarro(LISTA_CARRO* lista)
{
	// Validação da existência da lista de carros
	if (!lista)
	{
		printf("ERRO! A lista nao existe.\n");
		return;
	}
	int total = lista->num_elem; 
	int paginaAtual = 0; // variavel que guarda o numero da pagina atual
	int totalPaginas = (total + CARROS_POR_PAGINA - 1) / CARROS_POR_PAGINA; //calculo do max de paginas possiveis (relacionado com o tamanho da lista do carro)
	char opcao[10];
	
	while (1) {
        // cabecalho
        printf("Pagina %d de %d (Total de carros: %d)\n", paginaAtual + 1, totalPaginas, total);
        printf("----------------------------------------------------------------------------------------\n");
        printf("Matricula\tMarca\t\tModelo\t\tAno\tDono\t\tCod. Veiculo\n");
        printf("----------------------------------------------------------------------------------------\n");

        // mostrar 20 carros por pagina
        NODE_CARRO* atual = avancarAte(lista->header, paginaAtual * CARROS_POR_PAGINA);
        int contador = 0;
		 //apresentar os primeiros 20 carros da lista
        while (atual && contador < CARROS_POR_PAGINA) {
            CARRO* c = atual->info;
            printf("%-10s\t%-10s\t%-10s\t%d\t%d\t\t%d\n", c->matricula, c->marca, c->modelo, c->ano, c->dono, c->codVeiculo);

            atual = atual->next;
            contador++;
        }

        // opcoes 
        printf("--------------------------------------------------------------------------\n");
        printf("[N] Proxima pagina | [P] Pagina anterior | [S] Sair desta marca\nEscolha: ");
        fgets(opcao, sizeof(opcao), stdin);
        opcao[0] = toupper(opcao[0]); // para ter a certeza que se o user meter minuscula passa o input para Maiusucla

        if (opcao[0] == 'N') {
            if (paginaAtual < totalPaginas - 1)
                paginaAtual++;
            else {
                printf("Ja esta na ultima pagina. ENTER para continuar...\n");
                getchar();
            }
        } else if (opcao[0] == 'P') {
            if (paginaAtual > 0)
                paginaAtual--;
            else {
                printf("Ja esta na primeira pagina.ENTER para continuar...\n");
                getchar();
            }
        } else if (opcao[0] == 'S') {
			system("cls");
            break;
        }
    }
}

void freeListaHashCarro(LISTA_HASHC* listaHashCarro)
{
	
	if (!listaHashCarro)
	{
		printf("ERRO! A lista HASH nao existe.\n");
		return;
	}

	// Enquanto houver nodes na lista HASH
	while (listaHashCarro->header != NULL)
	{
		NODE_HASHC* nodeHash = listaHashCarro->header;
		listaHashCarro->header = nodeHash->next; 

		// se existir lista no NodeHash
		if (nodeHash->listaCarros)
		{
			//percorrer todos os carros da lista
			NODE_CARRO* nodeCarro = nodeHash->listaCarros->header;
			while (nodeCarro != NULL)
			{
				NODE_CARRO* aux = nodeCarro;
				nodeCarro = nodeCarro->next;
				freeNodeCarro(aux);
			}
			//eliminar a lista
			free(nodeHash->listaCarros);
		}

		free(nodeHash);
	}

	free(listaHashCarro);
	printf("Lista HASH CARRO removida com sucesso!\n");
}

//vai percorrer a lista de donos pelo ID e verificar se existe
int verificarDONOexiste(int idDono, LISTA_DONOS* listaDonos)
{
	if (!listaDonos) {
		printf("Lista DONOS não existe\n");
		return;
	}

	NODE_DONOS* atual = listaDonos->primeiro;

	while (atual) {
		// Verifica se o nó atual não é nulo
		if (atual->info != NULL) {

			//compara o ID
			if (idDono == atual->info->numCont)
			{
				//printf("O DONO É VALIDO!\n");
				return 1;
			}
		}
		// Se o nó atual for nulo, imprime uma mensagem de erro
		else {
			printf("Erro: info do nó atual é NULL\n");
		}
		// Avança para o próximo nó
		atual = atual->next;

	}
	return 0;

}

//***************** HASHING ************************


LISTA_HASHC* criarListaHashCarro()
{
	//alocar memoria para a lista hash
	LISTA_HASHC* lista = (LISTA_HASHC*)malloc(sizeof(LISTA_HASHC));
	//iniciar a lista a null
	lista->header = NULL;
	lista->ultimo_node = NULL;
	lista->numElementos = 0;

	return lista;
}

NODE_HASHC* criarNodeHashCarro()
{
	NODE_HASHC* nodeHash = (NODE_HASHC*)malloc(sizeof(NODE_HASHC));
	//strcpy(nodeHash->chave ,'\0');
	nodeHash->listaCarros = NULL;

	nodeHash->next = NULL;

}

void adicionarInfoNodeHash(NODE_HASHC* nodeHash, NODE_CARRO* nodeCarro)
{
	//adicionar a chave ao nodeHash
	strcpy(nodeHash->chave, nodeCarro->info->marca);
	//verificar se uma lista ja exsite no node 
	if (nodeHash->listaCarros == NULL)
	{
		//se nao existir criar uma listaCarros
		LISTA_CARRO* listaCarros = criarListaCarro();
		//adicionar o NODECARRO A LISTA
		addListaCarro(listaCarros, nodeCarro);
		//adicionar a ligacao do node a lista Carros
		nodeHash->listaCarros = listaCarros;
		nodeHash->next = NULL;
	}
	else //se existir a lista adicioar carro a lista
	{
		addListaCarro(nodeHash->listaCarros, nodeCarro);
		nodeHash->next = NULL;
	}
}

//listar todo o conteudo da HASH DOS CARROS
void mostrarHashCarros(LISTA_HASHC* listaHash)
{
	//percorrer os NODES_HASH
	NODE_HASHC* nodesHash = listaHash->header;
	while (nodesHash)
	{
		printf("***********************************\n");
		printf("\t MARCA: %s\n", nodesHash->chave);
		printf("***********************************\n");
		//percorrer a lista enquanto existirem nodes
		mostrarListaCarro(nodesHash->listaCarros);
		nodesHash = nodesHash->next;
	}
}

//liga o NODEHASH PRENCHIDO a LISTA HASH
void inserirNodeHashListaHash(LISTA_HASHC* listaHash, NODE_HASHC* nodeHash)
{
	if (!listaHash || !nodeHash)
	{
		return;
	}
	//inserir o NodeHash no fim da lista
	listaHash->ultimo_node->next = nodeHash;
	listaHash->ultimo_node = nodeHash;
	listaHash->numElementos++;
}

//ordenar (alfabeticamente) marcas
void ordenarMarcasHashCarrosAlfabeticamente(LISTA_HASHC* listaHash)
{
	if (!listaHash)
	{
		printf("ERRO! A lista HASH nao existe.\n");
		return;
	}

	//bouble sort
	NODE_HASHC* atual;
	NODE_HASHC* proximo;
	LISTA_CARRO* temp; // para trocar as listas dentro dos nós
	char* temp_chave[MAX_CHAR_STR]; // para trocar as listas dentro dos nós
	int troca;

	printf("A ORDENAR HASH!\n");

	do
	{
		troca = 0;
		atual = listaHash->header;

		while (atual->next != NULL) // Percorre a Hash
		{
			proximo = atual->next;
			
			if (_stricmp(atual->chave, proximo->chave) > 0) 
			{				// Trocar as listas dos nos
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

//ordenar (alfabeticamente) modelo
void ordenarModeloHashCarrosAlfabeticamente(LISTA_HASHC* listaHash)
{
	if (!listaHash)
	{
		printf("ERRO! A lista HASH nao existe.\n");
		return;
	}

	//bouble sort
	NODE_HASHC* node_atual;
	NODE_CARRO* atual;
	NODE_CARRO* proximo;
	CARRO* temp; // apenas para trocar o conteudo
	int troca;

	printf("A ORDENAR HASH!\n");

	do
	{
		troca = 0;
		node_atual = listaHash->header;

		while (node_atual->next != NULL) // Percorre a Hash
		{
			atual = node_atual->listaCarros->header;

			while (atual->next != NULL)
			{
				proximo = atual->next;

				if (strcmp(atual->info->modelo, proximo->info->modelo) > 0)
				{				// Trocar as listas dos nos
					temp = atual->info;
					atual->info = proximo->info;
					proximo->info = temp;

					troca = 1;
				}

				atual = atual->next;
			}

			node_atual = node_atual->next;
		}
	} while (troca);//vai parar quando percorrer toda a hash e verificar que realmente nao foram efetuadas trocas

	printf("HASH ORDENADA COM SUCESSO\n");
}

void ordenarMatriculaHashCarrosAlfabeticamente(LISTA_HASHC* listaHash)
{
	if (!listaHash)
	{
		printf("ERRO! A lista HASH nao existe.\n");
		return;
	}

	//bouble sort
	NODE_HASHC* node_atual;
	NODE_CARRO* atual;
	NODE_CARRO* proximo;
	CARRO* temp; // apenas para trocar o conteudo
	int troca;

	printf("A ORDENAR HASH!\n");

	do
	{
		troca = 0;
		node_atual = listaHash->header;

		while (node_atual->next != NULL) // Percorre a Hash
		{
			atual = node_atual->listaCarros->header;

			while (atual->next != NULL)
			{
				proximo = atual->next;

				if (strcmp(atual->info->matricula, proximo->info->matricula) > 0)
				{				// Trocar as listas dos nos
					temp = atual->info;
					atual->info = proximo->info;
					proximo->info = temp;

					troca = 1;
				}

				atual = atual->next;
			}

			node_atual = node_atual->next;
		}
	} while (troca);//vai parar quando percorrer toda a hash e verificar que realmente nao foram efetuadas trocas

	printf("HASH ORDENADA COM SUCESSO\n");
}

//devolver o carro encontrado pelo ID
NODE_CARRO* procuraCarroPorID(int codVeiculo, LISTA_HASHC* listaHashCarros)
{
	if (!codVeiculo)
	{
		return;
	}
	//auxiliar para percorrer o listaHashCarros
	NODE_HASHC* auxNodeHash = listaHashCarros->header;
	while (auxNodeHash)
	{
		//auxiliar para percorrer a lista Carros
		NODE_CARRO* nodeCarro = auxNodeHash->listaCarros->header;
		while (nodeCarro)
		{
			if (nodeCarro->info->codVeiculo == codVeiculo)
			{
				return nodeCarro;
			}
			nodeCarro = nodeCarro->next;
		}


		auxNodeHash = auxNodeHash->next;
	}

	if (auxNodeHash == NULL)
	{
		printf("O CARRO NAO EXITE! \n");
		return NULL;
	}

}

void maiorVelocidadeMediaMarca(LISTA_HASHC* listaHashCarros, PASSAGEM_LISTA* listaPassagens, DISTANCIAS_LISTA* listaDistancias)
{
	if (!listaHashCarros || !listaPassagens || !listaDistancias)
		return;

	printf("CALCULAR DISTANCIAS, POR FAVOR AGUARDE! (CERCA DE 1:30 MIN)\n");

	PASSAGEM_NODE* atual = listaPassagens->header;

	while (atual && atual->next)
	{
		PASSAGEM* entrada = atual->info;
		PASSAGEM* saida = atual->next->info;

		// verificar se o par e valido (entrada seguida de saida perternce ao mesmo carro)
		if (entrada->tipoRegisto == 0 && saida->tipoRegisto == 1 && entrada->codVeiculo == saida->codVeiculo)
		{
			float km = distanciaEntreSensor(entrada->idSensor, saida->idSensor, listaDistancias);
			long tempoMs = calculoDistancia(entrada->data, saida->data);
			float minutos = tempoMs / 60000.0f;
			if (km >= 0 && minutos > 0)
			{

				NODE_CARRO* carro = procuraCarroPorID(entrada->codVeiculo, listaHashCarros);
				if (carro)
				{
					if (km > 0 && minutos > 0) // evitar viagens e kilometros negativos
					{
						carro->info->totalKMPercorridos += km;
						carro->info->totalMinutosPercorridos += minutos;
					}
					
				}
			}
			atual = atual->next->next; // (par ja processado)
		}
		else
		{
			atual = atual->next; // se o par de entrada/saida for invalido avanca um node apenas
		}
	}

	// adicionar velocidade media aos nodeHash
	NODE_HASHC* marcaAtual = listaHashCarros->header;
	float maiorVelMedia = 0.0;
	char* marcaMaisRapida = NULL;

	while (marcaAtual)
	{
		float totalKm = 0.0f;
		float totalMin = 0.0f;

		NODE_CARRO* carro = marcaAtual->listaCarros;
		while (carro)
		{
			totalKm += carro->info->totalKMPercorridos;
			totalMin += carro->info->totalMinutosPercorridos;
			carro = carro->next;
		}

		if (totalMin > 0)
		{
			float velMedia = totalKm / (totalMin / 60.0f); // converter minutos para km/h
			if (velMedia > maiorVelMedia)
			{
				maiorVelMedia = velMedia;
				marcaMaisRapida = marcaAtual->chave;
			}
		}

		marcaAtual = marcaAtual->next;
	}

	// Apresentar resultados
	printf("**************************************************************\n");
	printf("|              MARCA COM MAIOR VELOCIDADE MEDIA             |\n");
	printf("**************************************************************\n");

	if (marcaMaisRapida)
	{
		printf("%s -> Velocidade Media: %.2f KM/h\n", marcaMaisRapida, maiorVelMedia);
		printf("**************************************************************\n");
	}
	else
		printf("Nenhuma marca com dados válidos.\n");
}

// 16. Determinar qual a marca de automóvel mais comum?
void marcaMaisComum(LISTA_HASHC* listaHashCarros)
{
	// Verificação da existência da Hash
	if (!listaHashCarros)
	{
		printf("ERRO! A lista HASH nao existe.\n");
		return;
	}

	// Variáveis para guardar o numero de elementos e o nome da marca mais comum
	int elem_marca_maior = 0;
	char marca_maior[MAX_CHAR_STR + 1];
	// Ponteiro para percorrer a Hash de Carros
	NODE_HASHC* node_atual = listaHashCarros->header;

	// Ciclo para percorrer a Hash de Carros
	while (node_atual)
	{
		// Determinação da Marca Mais Comum
		if (node_atual->listaCarros->num_elem > elem_marca_maior)
		{
			elem_marca_maior = node_atual->listaCarros->num_elem;
			strcpy(marca_maior, node_atual->chave);
		}

		node_atual = node_atual->next;
	}

	// Output para o User
	printf("MARCA mais comum: %s\n", marca_maior);
	printf("Numero de veiculos dessa marca: %d \n\n", elem_marca_maior);
}