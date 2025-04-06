#include "donos.h"


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


NODE_DONOS* criarNodeDonos(){

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



int freeNodeDonos(NODE_DONOS* node){
	
	//Entra se o Elemento nao for =NULL
	if (node != NULL) {
		free(node->info); //Libera a memoria alocada para o conteudo do elemento
		free(node); //Liberar a memoria alocada para o elemento
		return 0;
	}
	return 1;
}

void carregarDadosDonos(LISTA_DONOS* lista) {

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

void adicionarListaDonos(LISTA_DONOS* lista, NODE_DONOS* node) {

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

void registarDonos(LISTA_DONOS* lista) {
	
	//Cria um elemento novo
	NODE_DONOS* novoNode = criarNodeDonos();
	
	printf("Insira Dados do Dono\n");
	printf("Numero de Contribuinte:\n ");
	scanf("%d",&novoNode->info->numCont);
	printf("Nome:\n");
	scanf("%s", novoNode->info->nome);
	printf("Codigo postal:\n");
	scanf("%s", &novoNode->info->codpost);
	
	//adiciona o elemento criado a lista
	adicionarListaDonos(lista, novoNode);
	system("cls");
	printf("Dono adicionado com sucesso!\n");
}

void listarDonos(LISTA_DONOS* lista) {
	if (!lista) {
		printf("Lista não existe\n");
		return;
	}

	NODE_DONOS* atual = lista->primeiro;

	printf("*********************************************\n");
	printf("|               Lista de Donos              |\n");
	printf("*********************************************\n");
	printf("Contribuinte\t\tNome\t\tCodigo Postal\n");
		
	while (atual) {
		// Verifica se o nó atual não é nulo
		if (atual->info != NULL) {			
			
			// Imprime os dados do dono
			printf("%d\t\t%s\t\t%s\n", atual->info->numCont, atual->info->nome, atual->info->codpost);
			
		}
		// Se o nó atual for nulo, imprime uma mensagem de erro
		else {
			printf("Erro: info do nó atual é NULL\n");
		}
		// Avança para o próximo nó
		atual = atual->next;
		
	}

	printf("*********************************************\n");
}

void freeListaDonos(LISTA_DONOS* lista) {
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

//ordenar (alfabeticamente) nome de todos os condutores
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
