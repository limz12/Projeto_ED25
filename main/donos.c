/**
 * @file donos.c
 * @brief Implementacao das funcoes respetivas aos donos.
 */


// BIBLIOTECAS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>

#include "donos.h"
#include "carros.h"
#include "PASSAGEM.h"
#include "DISTANCIAS.h"


/**
* @brief Funcao responsavel por criar uma lista que ira conter donos
* @return ponteiro para uma LISTA_DONOS, que e o resultado da alocacao de memoria da estrutura LISTA_DONOS
*/
LISTA_DONOS* criarListaDonos()
{
	//Alçocaçao de memoria da lista de Donos
	LISTA_DONOS* lista = (LISTA_DONOS*)malloc(sizeof(LISTA_DONOS));
	
	//Validaçao da alocaçao da lista
	if (lista != NULL) {

		lista->primeiro = NULL;  // ponteiro para o inicio da lista
		lista->ultimo = NULL;   // ponteiro para o fim da lista
		lista->elem = 0; 

	}
	return lista;
}

/**
* @brief Funcao responsavel por alocar memoria para um node que contem todos os dados de um respetiv dono
* @return retorna um ponteiro para um NODE_DONOS, com todos os valores da estrutura nulos
*/
NODE_DONOS* criarNodeDonos()
{

	//Alocaçao de memoria para elemento da lista de Donos
	NODE_DONOS* node = (NODE_DONOS*)malloc(sizeof(NODE_DONOS));
	
	//Validaçao da alocçao do elemento
	if(!node){
		return NULL;
	}

	//Alocaçao de memoria para o conteudo dentro do elemento
	node->info = (Donos*)malloc(sizeof(Donos)); //conteudo do elemento Donos
	node->next = NULL; //ponteiro para o proximo é NULL porque é adicionado no fim da lista

	return node;
}

/**
* @brief Funcao responsavel por receber um NODE_DONOS e destruir esse mesmo no, libertando toda a memoria e os dados que possui
* @param node : Recebe um ponteiro NODE_DONOS
* @return NULL se o node inserido nao existir
*/
int freeNodeDonos(NODE_DONOS* node)
{
	
	//Entra se o Elemento nao for =NULL
	if (node != NULL) {
		free(node->info); //Libera a memoria alocada para o conteudo do elemento
		free(node); //Liberar a memoria alocada para o elemento
		return 0;
	}
	return 1;
}

/**
* @brief Funcao responsavel por ler o ficheiro "donos.txt", e inserir cada dono presente no ficheiro na estrutura da lista de donos
* @param lista : Recebe um ponteiro de uma LISTA_DONOS
* @return VOID
*/
void carregarDadosDonos(LISTA_DONOS* lista) 
{

	setlocale(LC_ALL, "en_US.UTF-8");

	if (!lista) {
		return;
	}

	//Abe o ficheiro texto em mode leitura
	FILE* ficheiro = fopen("donos.txt", "r");
	
	//verifica se o ficheiro foi aberto corretament
	if (ficheiro == NULL) {
		printf("Erro ao abrir o ficheiro donos.txt\n");
		return;
	}

	char str_aux[200]; // buffer para armazenar a linha lida

	while (fgets(str_aux, sizeof(str_aux), ficheiro)) {
		if (str_aux[0] == '\n') { // Verifica se a linha está vazia
			continue;
		}

		NODE_DONOS* node = criarNodeDonos();
		if (!node) {
			fclose(ficheiro);
			return;
		}

		if (sscanf(str_aux, "%d\t%199[^\t]\t%199[^\n]", &node->info->numCont, node->info->nome, node->info->codpost) != 3) {
			printf("Erro ao ler dados da linha: %s", str_aux);
			freeNodeDonos(node);
			fclose(ficheiro);
			return;
		}

		adicionarListaDonos(lista, node);
	}

	printf("DONOS.TXT CARREGADO COM SUCESSO\n");
	fclose(ficheiro);
}

/**
* @brief Funcao responsavel por receber um NODE_DONOS e adiciona-lo a uma lista de donos
* @param lista : Recebe um ponteiro para a LISTA_DONOS para onde o dono vai ser "armazenado"
* @param node : Recebe o NODE_DONOS que vai ser inserido no parametro de entrada lista
* @return VOID
*/
void adicionarListaDonos(LISTA_DONOS* lista, NODE_DONOS* node) 
{

	//Verifica se exista a lista e o node
	if (lista == NULL || node == NULL) return;

	NODE_DONOS* aux = lista->primeiro;

	//Se a lista estiver vazia
	if (lista->primeiro == NULL) {
		lista->primeiro = node;
		lista->ultimo = node;
		lista->elem++;
	}

	//Se a lista nao estiver vazia
	else {
		lista->ultimo->next = node;
		lista->ultimo = node;
		lista->elem++;
	}
}

/**
* @brief Funcao responsavel por adicionar um novo dono, a uma lista de donos, pelo utilizador
* @param lista : Recebe um ponteiro para a LISTA_DONOS para onde o dono vai ser "armazenado"
* @return VOID
*/
void registarDonos(LISTA_DONOS* lista)
{
	
	//Cria um elemento novo
	NODE_DONOS* novoNode = criarNodeDonos();
	
	printf("Insira Dados do Dono\n");
	printf("Numero de Contribuinte:\n ");
	scanf("%d",&novoNode->info->numCont);
	printf("Nome:\n");
	scanf("%s", novoNode->info->nome);
	printf("Codigo postal:\n");
	scanf("%s", &novoNode->info->codpost);
	
	int existeDono = verificarDONOexiste(novoNode->info->numCont, lista);
	if (existeDono == 0) // se o dono nao existe
	{
		//adiciona o elemento criado a lista
		adicionarListaDonos(lista, novoNode);
		system("cls");
		printf("Dono adicionado com sucesso!\n");
	}
	else
	{
		printf("ERRO! O DONO JA EXISTE, DADOS FORAM REJEITADOS! \n");
	}
	
}

/**
* @brief Funcao responsavel por listar todos os donos presentes na Lista de donos
* @param lista : Recebe um ponteiro de uma LISTA_DONOS
* @return VOID
*/
//vai avancar para o donoCorreto (pagina)
NODE_DONOS* avancarAteDono(NODE_DONOS* nodeDono, int pos) 
{
	int i = 0;
	NODE_DONOS* atual = nodeDono;
	while (atual && i < pos) {
		atual = atual->next;
		i++;
	}
	return atual;
}

// LISTAR DONOS
void listarDonos(LISTA_DONOS* lista) 
{
	if (!lista) {
		printf("Lista não existe\n");
		return;
	}

	int total = lista->elem; //armazenar o total de donos 
	int paginaAtual = 0; 
	int totalPaginas = (total + DONOS_POR_PAGINA - 1) / DONOS_POR_PAGINA; // calculo do total de paginas
	char opcao[10];

	while (1) {
		system("cls");

		printf("*********************************************\n");
		printf("|               Lista de Donos              |\n");
		printf("*********************************************\n");
		printf("Pagina %d de %d (Total: %d donos)\n", paginaAtual + 1, totalPaginas, total);
		printf("-------------------------------------------------------------\n");
		printf("Contribuinte\t\tNome\t\t\tCodigo Postal\n");
		printf("-------------------------------------------------------------\n");

		NODE_DONOS* atual = avancarAteDono(lista->primeiro, paginaAtual * DONOS_POR_PAGINA);
		int contador = 0;

		while (atual && contador < DONOS_POR_PAGINA) {
			if (atual->info) {
				printf("%-16d\t%-20s\t%s\n",atual->info->numCont,atual->info->nome,atual->info->codpost);
			}
			else {
				printf("Erro: info do node atual é NULL\n");
			}
			atual = atual->next;
			contador++;
		}

		printf("-------------------------------------------------------------\n");
		printf("[N] Proxima pagina | [P] Pagina anterior | [S] Sair\nEscolha: ");
		fgets(opcao, sizeof(opcao), stdin);
		opcao[0] = toupper(opcao[0]);

		if (opcao[0] == 'N') {
			if (paginaAtual < totalPaginas - 1)
				paginaAtual++;
			else {
				printf("Ja esta na ultima pagina.ENTER...\n");
				getchar();
			}
		}
		else if (opcao[0] == 'P') {
			if (paginaAtual > 0)
				paginaAtual--;
			else {
				printf("Ja esta na primeira pagina.ENTER...\n");
				getchar();
			}
		}
		else if (opcao[0] == 'S') {
			system("cls");
			break;
		}
	}
}

/**
* @brief Funcao responsavel por libertar a memoria alocada de toda a lista de donos e todo o seu conteudo
* @param lista : Recebe um ponteiro de uma LISTA_DONOS para ser destruida
* @return VOID
*/
void freeListaDonos(LISTA_DONOS* lista) 
{
	// Verifica se a lista não é nula
	if (!lista) {
		printf("Nao exite lista\n");
		return;
	}
	// Libera todos os nós da lista
	while (lista->primeiro) {
		NODE_DONOS* aux = lista->primeiro;
		lista->primeiro = aux->next;

		freeNodeDonos(aux);
	}
	printf("LISTA DONOS REMOVIDA\n");
}

/**
* @brief Funcao responsavel por ordenar (alfabeticamente) a lista de donos pelo nome de todos os condutores
* @param lista : Recebe um ponteiro de uma LISTA_DONOS
* @return VOID
*/
void ordenarListaDonosAlfabeticamente(LISTA_DONOS* lista)
{
	if (!lista)
	{
		printf("ERRO! A lista donos nao existe\n");
		return;
	}

	//bouble sort
	NODE_DONOS* atual;
	NODE_DONOS* proximo;
	Donos* temp; // apenas para trocar o conteudo
	int troca;

	printf("A ORDENAR LISTA!\n");

	do
	{
		troca = 0;
		atual = lista->primeiro;

		while (atual->next != NULL)
		{
			proximo = atual->next;
			if (strcmp(atual->info->nome, proximo->info->nome) > 0)
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

/**
* @brief Funcao responsavel por ordenar (por ordem crescente) a lista de donos pelo numero de contribuinte de todos os condutores
* @param lista : Recebe um ponteiro de uma LISTA_DONOS
* @return VOID
*/
void ordenarListaDonosContribuinte(LISTA_DONOS* lista)
{
	if (!lista)
	{
		printf("ERRO! A lista donos nao existe\n");
		return;
	}

	//bouble sort
	NODE_DONOS* atual;
	NODE_DONOS* proximo;
	Donos* temp; // apenas para trocar o conteudo
	int troca;


	do
	{
		troca = 0;
		atual = lista->primeiro;

		while (atual->next != NULL)
		{
			proximo = atual->next;
			if (atual->info->numCont > proximo->info->numCont)
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


/**
* @brief Funcao responsavel por calcular e apresentar a maior velocidade média de um condutor (de todas as passagem)
* @param lista : Recebe um ponteiro de uma LISTA_DONOS
* @return VOID
*/
void maiorVelocidadeMediaDonos(LISTA_DONOS* listaDonos, LISTA_HASHC* listaHashCarros, PASSAGEM_LISTA* listaPassagens, DISTANCIAS_LISTA* listaDistancias)
{
	//CONSIDERANDO QUE NO EXERCICIO QUEREMOS SABER APENAS O CONDUTOR COM O CARRO QUE CIRCULA A MAIOR VELOCIDADE MEDIA

	float maiorVelocidadeMediaCarro = 0.0f;
	int idDonoCarroMaisRapido;

	//**************** POPULAR VELOCIDADE MEDIA DE TODOS OS CARROS *************************************

	printf("CALCULAR VELOCIDADE MEDIA DOS CARROS AGUARDE (CERCA DE 2:50 MIN)\n");

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
						//adicionar velocidade media ao carro 
						carro->info->velocidadeMediaKM = carro->info->totalKMPercorridos / (carro->info->totalMinutosPercorridos / 60.00f);
						//TER A REFERENCIA DA MAIOR VELOCIDADE MEDIA
						if (carro->info->velocidadeMediaKM > maiorVelocidadeMediaCarro)
						{
							maiorVelocidadeMediaCarro = carro->info->velocidadeMediaKM;
							idDonoCarroMaisRapido = carro->info->dono;
						}
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
	printf("CALCULO  DE TODAS AS VELOCIDADES MEDIAS POR CARRO FINALIZADO\n");
	system("cls");
	printf("A PROCURA DO DONO CORRESPONDENTE\n");
	//procurar na lista donos pelo id e dar print ao nome
	NODE_DONOS* nodeDono = listaDonos->primeiro;
	int encontrado = 0;
	while (nodeDono && encontrado == 0)
	{
		if (nodeDono->info->numCont == idDonoCarroMaisRapido)
		{
			printf("Maior Velocidade Media : %.2f -> Condutor: %s\n", maiorVelocidadeMediaCarro, nodeDono->info->nome);
			encontrado = 1;
		}
		nodeDono = nodeDono->next;
	}

}



void velocidadeMediaPorCodigoPostal(LISTA_DONOS* listaDonos, LISTA_HASHC* listaHashCarros,
	PASSAGEM_LISTA* listaPassagens, DISTANCIAS_LISTA* listaDistancias,
	const char* codigoPostal)
{
	if (!listaDonos || !listaHashCarros || !listaPassagens || !listaDistancias || !codigoPostal)
	{
		printf("ERRO! Parâmetros inválidos.\n");
		return;
	}

	// Variáveis para acumular totais
	float totalKm = 0.0f;
	float totalMinutos = 0.0f;
	int contadorCarros = 0;
	int donosEncontrados = 0;

	// Percorrer todos os donos
	NODE_DONOS* nodeDono = listaDonos->primeiro;
	while (nodeDono)
	{
		if (strcmp(nodeDono->info->codpost, codigoPostal) == 0)
		{
			donosEncontrados++;

			// Encontrar todos os carros desse dono
			NODE_HASHC* nodeHash = listaHashCarros->header;
			while (nodeHash)
			{
				NODE_CARRO* nodeCarro = nodeHash->listaCarros->header;
				while (nodeCarro)
				{
					if (nodeCarro->info->dono == nodeDono->info->numCont)
					{
						contadorCarros++;

						
						nodeCarro->info->totalKMPercorridos = 0.0f;
						nodeCarro->info->totalMinutosPercorridos = 0;

						// Processar passagens deste carro
						PASSAGEM_NODE* nodePassagem = listaPassagens->header;
						while (nodePassagem && nodePassagem->next)
						{
							if (nodePassagem->info->codVeiculo == nodeCarro->info->codVeiculo &&
								nodePassagem->info->tipoRegisto == 0 &&
								nodePassagem->next->info->tipoRegisto == 1)
							{
								float km = distanciaEntreSensor(nodePassagem->info->idSensor,
									nodePassagem->next->info->idSensor,
									listaDistancias);
								long tempoMs = calculoDistancia(nodePassagem->info->data,
									nodePassagem->next->info->data);
								float minutos = tempoMs / 60000.0f;

								if (km > 0 && minutos > 0)
								{
									nodeCarro->info->totalKMPercorridos += km;
									nodeCarro->info->totalMinutosPercorridos += minutos;
								}
							}
							nodePassagem = nodePassagem->next;
						}

						// Acumular totais
						if (nodeCarro->info->totalMinutosPercorridos > 0)
						{
							totalKm += nodeCarro->info->totalKMPercorridos;
							totalMinutos += nodeCarro->info->totalMinutosPercorridos;
						}
					}
					nodeCarro = nodeCarro->next;
				}
				nodeHash = nodeHash->next;
			}
		}
		nodeDono = nodeDono->next;
	}

	
	printf("\n****************************************************\n");
	if (donosEncontrados == 0)
	{
		printf("NENHUM DONO ENCONTRADO COM CODIGO POSTAL %s\n", codigoPostal);
	}
	else if (contadorCarros > 0 && totalMinutos > 0)
	{
		float velocidadeMediaGeral = totalKm / (totalMinutos / 60.0f);
		printf("RESULTADO PARA CODIGO POSTAL %s\n", codigoPostal);
		printf("Donos: %d | Carros: %d\n", donosEncontrados, contadorCarros);
		printf("VELOCIDADE MEDIA: %.2f km/h\n", velocidadeMediaGeral);
	}
	else
	{
		printf("Donos encontrados: %d\n", donosEncontrados);
		printf("Nenhum dado de viagem valido encontrado.\n");
	}
	printf("****************************************************\n");
}


