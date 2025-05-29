/**
 * @file carros.c
 * @brief Implementacao das funcoes respetivas aos carros.
 */


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


/**
* @brief Funcao responsavel por criar uma lista que ira conter carros
* @return ponteiro para uma Lista_Carro, que e o resultado da alocacao de memoria da estrutura LISTA_CARRO
*/
LISTA_CARRO* criarListaCarro()
{
	//Alocacao de memoria da lista de Carros
	LISTA_CARRO* lista = (LISTA_CARRO*)malloc(sizeof(LISTA_CARRO));

	// Validacao da alocacao da lista
	if (!lista)
	{
		printf("ERRO a alocar a lista de carros!\n");
		return NULL;
	}

	lista->header = NULL; //ponteiro do inicio da lista.
	lista->ultimo_node = NULL; // ponteiro para o ultimo elemento da lista.
	lista->num_elem = 0; // Inicializacao do numero de elementos da lista para 0.

	return lista;
}

/**
* @brief Funcao responsavel por alocar memoria para um node que contem todos os dados de um respetivo carro
* @return retorna um ponteiro para um NODE_CARRO, com todos os valores da estrutura nulos 
*/
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

	return node;
}

/**
* @brief Funcao responsavel por receber um NODE_CARRO e destruir libertando toda a memoria e os dados que possui
* @param node : Recebe um ponteiro NODE_CARRO 
* @return NULL se o node inserido nao existir
*/
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
	
}

/**
* @brief Funcao responsavel por ler o ficheiro "carros.txt", e inserir cada carro presente no ficheiro na estrutura da lista de carros
* @param listaHashCarros : Recebe um ponteiro de uma LISTA_HASHC
* @return VOID
*/
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

/**
* @brief Funcao responsavel por receber um NODE_CARRO e adiciona-lo a uma lista de carros
* @param lista : Recebe um ponteiro para a LISTA_CARRO para onde o carro vai ser "armazenado"
* @param node : Recebe o NODE_CARRO que vai ser inserido no parametro de entrada lista
* @return VOID
*/
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

/**
* @brief Funcao responsavel por criar e adicionar um novo carro a pedido do utilizador
* @param hashCarro : Recebe um ponteiro de uma LISTA_HASHC, que ja contem todos os carros organizados por marca
* @param listaDonos : Recebe um ponteiro de uma LISTA_DONOS com todos os donos para fazer verificacoes se os donos a que os carros estao associados existem
* @return VOID
*/
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
			//se existir um nodeHash com a mesma chave, e se a matricula for unica pode se proceder ao registo
			if (_stricmp(nodeHash->chave, novo_elem->info->marca) == 0)
			{
				if (verificarMatriculaExiste(novo_elem->info->matricula, nodeHash->listaCarros) == 0)
				{
					//adiciona  a lista do nodeHash o novo elemento
					addListaCarro(nodeHash->listaCarros, novo_elem);
					printf("CARRO ADICIONADO COM SUCESSO!\n");
					flag = 1;
				}
				else
				{
					printf("ERRO! A matricula inserida nao ja existe\n");
					return;
				}
				
			}
			nodeHash = nodeHash->next;
		}
		if (flag == 0)//se percorreu a ListaHash e nao encontrou a chave
		{
			//percorrer pelos nos da listaHash se a  matricula existe
			int matriculaEncontrada = 0;
			NODE_HASHC* nodeHash = hashCarro->header;
			while (nodeHash)
			{
				 matriculaEncontrada = verificarMatriculaExiste(novo_elem->info->matricula, nodeHash->listaCarros);
				 if (matriculaEncontrada == 1)
				 {
					 printf("ERRO! JA EXISTE UM CARRO COM ESSA MATRICULA\n");
					 return;
				 }
				nodeHash = nodeHash->next;
			}
			//se nao existir nenhum carro registado com a matricula cria um novo
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

/**
* @brief Funcao responsavel por listar todos os carros presentes na Lista de carros
* @param lista : Recebe um ponteiro de uma LISTA_CARRO, que ja contem todos os carros pertencentes uma determinada marca
* 
* @return VOID
*/
void mostrarListaCarro(LISTA_CARRO* lista)
{
	// Validação da existência da lista de carros
	if (!lista)
	{
		printf("ERRO! A lista nao existe.\n");
		return;
	}

	// Criação de um elemento auxiliar para percorrer a lista
	NODE_CARRO* aux = lista->header;

	// Cabeçalho da lista
	printf("**************************************************************\n");
	printf("|                        LISTA CARROS                        |\n");
	printf("**************************************************************\n");
	printf("\nMatricula\tMarca\t\tModelo\t\tAno\t\tID_Dono\t\tCodigo_Veiculo\n\n");
	
	// Ciclo para percorrer a lista até ao fim
	while (aux)
	{
		printf("%s\t%s\t\t%s\t\t%d\t\t%d\t\t%d\n", aux->info->matricula, aux->info->marca, aux->info->modelo, aux->info->ano, aux->info->dono, aux->info->codVeiculo);
		aux = aux->next;
	}

	// Fim da Lista
	printf("**************************************************************\n");
}

/**
* @brief Funcao responsavel por libertar a memoria alocada de toda a listaHash e todo o seu conteudo
* @param ListaHashCarro : Recebe um ponteiro de uma LISTA_HASHC para ser destruida
* @return VOID
*/
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

/**
* @brief Funcao responsavel por percorrer a lista de donos pelo ID e verificar se o dono ja existe
* @param idDono : Recebe um inteiro que e o numero de contribuinte do dono
* @param listaDonos : Recebe um ponteiro de uma LISTA_DONOS com todos os donos para fazer verificacoes se o dono com o numero de contribuinte existe
* @return 1 : se numero de contribuinte existe
* @return 0 : se numero de contribuinte nao existe
*/
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

/**
* @brief Funcao responsavel por percorrer a lista de carros e verificar se a matricula ja pertence a algum carro
* @param matricula : Recebe um char que e a matricula que se pretende verificar 
* @param listaCarro : Recebe um ponteiro de uma LISTA_CARROS com todos os carros da mesma marca 
* @return existe : Retorna um inteiro sendo que 1 -> matricula existe | 0 -> matricula nao existe
* 
*/
int verificarMatriculaExiste(char* matricula, LISTA_CARRO* listaCarro)
{
	if (!matricula || !listaCarro)
	{
		printf("ERRO! matricula ou listaCarro nao estao presentes! \n");
		return;
	}
	int existe = 0; //este e o valor por defeito, se nao for alterado quer dizer que a matricula aunda nao foi registada

	//percorrer pela lista do carro a procura da mesma matricula
	NODE_CARRO* nodecarro = listaCarro->header;
	while (nodecarro)
	{
		if (_stricmp(matricula, nodecarro->info->matricula) == 0) // se a matricula ja existir
		{
			return 1;
		}
		nodecarro = nodecarro->next;
	}

	return existe;


}


//***************** HASHING ************************


/**
* @brief Funcao responsavel por criar uma Lista hash que vai armazenar os nodes hash organizados por marcas.
* @return retorna um ponteiro LISTA_HASH vazia
*/
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

/**
* @brief Funcao responsavel por criar um node hash, que possui uma chave "Marca dos carros"e a lista com os respetivos carros da mesma marca
* @return existe : Retorna um ponteiro para um NODE_HASHC vazio
*/
NODE_HASHC* criarNodeHashCarro()
{
	NODE_HASHC* nodeHash = (NODE_HASHC*)malloc(sizeof(NODE_HASHC));
	//strcpy(nodeHash->chave ,'\0');
	nodeHash->listaCarros = NULL;

	nodeHash->next = NULL;

}

/**
* @brief Funcao responsavel por percorrer preencher o nodeHash, com a respetiva chave e adicionar o carro a sua lista carros
* @param nodeHash : recebe um ponteiro NODE_HASHC em vai ser inserido o carro
* @param nodeCarro : Recebe um ponteiro NODE_CARRO com um carro preenchido para ser inserido na respetiva hash
* @return VOID
*
*/
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

/**
* @brief Funcao responsavel por listar todo o conteudo da LISTA_HASHC
* @param listaHash : recebe um ponteiro LISTA_HASCH com todos os NODE_HASHC e os carros agrupados por marca
* @return VOID
*/
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

/**
* @brief Funcao responsavel por inserir um NODE_HASHC na LISTA_HASHC
* @param listaHash : recebe um ponteiro LISTA_HASCH
* @param nodeHash : recebe um ponteiro NODE_HASHC que vai ser inserido na LISTA_HASCH
* @return VOID
*/
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

/**
* @brief Funcao responsavel por ordenar (alfabeticamente) por marcas a LISTA_HASHC
* @param listaHash : recebe um ponteiro LISTA_HASCH
* @return VOID
*/
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


/**
* @brief Funcao responsavel por ordenar (alfabeticamente) pelo modelo do carro dentro da marca
* @param listaHash : recebe um ponteiro LISTA_HASCH
* @return VOID
*/
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

/**
* @brief Funcao responsavel por ordenar (alfabeticamente) pela matricula do carro
* @param listaHash : recebe um ponteiro LISTA_HASCH com a lista de carros
* @return VOID
*/
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

/**
* @brief Funcao responsavel por encontrar se o carro atraves do codVeiculo na LISTA_HASHC
* @param codVeiculo : recebe um inteiro com o codigo de veiculo para ser verificado
* @param listaHashCarros : recebe a LISTA_HASHC 
* @return nodeCarro:  ponteiro NODE_CARRO para o carro que foi encontrado
*/
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

/**
* @brief Funcao responsavel por calcular a maior velocidade media de todas as marcas presentes na LISTA_HASHC e apresentar o resultado
* @param listaHashCarros : recebe um ponteiro para a LISTA_HASHC
* @param listaPassagens : recebe um ponteiro para a PASSAGEM_LISTA
* @param listaDistancias : recebe um ponteiro para a DISTANCIAS_LISTA
* @return VOID
*/
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
					if (minutos > 0) // evitar viagens e kilometros negativos
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


/**
* @brief Funcao responsavel por calcular qual e a marca com mais automoveis e apresentar a mesma
* @param listaHashCarros : recebe um ponteiro para a LISTA_HASHC
* @return VOID
*/
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