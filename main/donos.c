#include "donos.h"
#include "carros.h"
#include "DISTANCIAS.H"
#include "PASSAGEM.H"


LISTA_DONOS* criarListaDonos()
{
	//Al�oca�ao de memoria da lista de Donos
	LISTA_DONOS* lista = (LISTA_DONOS*)malloc(sizeof(LISTA_DONOS));
	
	//Valida�ao da aloca�ao da lista
	if (lista != NULL) {

		lista->primeiro = NULL;  // ponteiro para o inicio da lista
		lista->ultimo = NULL;   // ponteiro para o fim da lista
		lista->elem = 0; 

	}
	return lista;
}


NODE_DONOS* criarNodeDonos(){

	//Aloca�ao de memoria para elemento da lista de Donos
	NODE_DONOS* node = (NODE_DONOS*)malloc(sizeof(NODE_DONOS));
	
	//Valida�ao da aloc�ao do elemento
	if(!node){
		return NULL;
	}

	//Aloca�ao de memoria para o conteudo dentro do elemento
	node->info = (Donos*)malloc(sizeof(Donos)); //conteudo do elemento Donos
	node->next = NULL; //ponteiro para o proximo � NULL porque � adicionado no fim da lista

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
		if (str_aux[0] == '\n') { // Verifica se a linha est� vazia
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
		printf("Lista n�o existe\n");
		return;
	}

	NODE_DONOS* atual = lista->primeiro;

	printf("*********************************************\n");
	printf("|               Lista de Donos              |\n");
	printf("*********************************************\n");
	printf("Contribuinte\t\tNome\t\tCodigo Postal\n");
		
	while (atual) {
		// Verifica se o n� atual n�o � nulo
		if (atual->info != NULL) {			
			
			// Imprime os dados do dono
			printf("%d\t\t%s\t\t%s\n", atual->info->numCont, atual->info->nome, atual->info->codpost);
			
		}
		// Se o n� atual for nulo, imprime uma mensagem de erro
		else {
			printf("Erro: info do n� atual � NULL\n");
		}
		// Avan�a para o pr�ximo n�
		atual = atual->next;
		
	}

	printf("*********************************************\n");
}

void freeListaDonos(LISTA_DONOS* lista) {
	// Verifica se a lista n�o � nula
	if (!lista) {
		printf("Nao exite lista\n");
		return;
	}
	// Libera todos os n�s da lista
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

//condutor (dono) que circula a maior velocidade m�dia
void maiorVelocidadeMediaDono(LISTA_DONOS* listaDonos, LISTA_HASHC* listaHashCarros, PASSAGEM_LISTA* listaPassagem, DISTANCIAS_LISTA* listaDistancias)
{
	// Valida��o da exist�ncia das listas
	if (!listaHashCarros || !listaPassagem || !listaDistancias || !listaDonos)
	{
		printf("Uma das listas esta vazia!\n");
		return;
	}
	
	PASSAGEM_NODE* nodePassagem = listaPassagem->header; // ponteiro para percorrer a lista das Passagens
	float maiorVelocidade = 0.0f; // vari�vel para atualizar a maior velocidade, � medida que percorre as Passagens
	Donos* donoMaisRapido = NULL; // ponteiro para o conte�do de um n� dono (por causa do dono com a velocidade mais alta)

	// Percorre a lista das Passagens
	while (nodePassagem && nodePassagem->next)
	{
		if (nodePassagem->info->tipoRegisto == 0) // Procura s� nos de entrada (pesquisa mais eficiente)
		{
			// Ponteiro para o s� a seguir do ponteiro nodePassagem por causa de andar na sa�da
			PASSAGEM_NODE* proximo = nodePassagem->next;

			if (proximo && proximo->info->tipoRegisto == 1 && nodePassagem->info->codVeiculo == proximo->info->codVeiculo) // literalmente uma passagem (entrada + sa�da)
			{
				// Distancia percorrida pelo veiculo entre os sensores de entrada e sa�da
				float distancia = distanciaEntreSensor(nodePassagem->info->idSensor, proximo->info->idSensor, listaDistancias);

				// Ignorar se h� distancias inv�lidas (distancia tem de ser positiva)
				if (distancia <= 0.0f)
				{
					nodePassagem = nodePassagem->next;
					continue;
				}

				// Tempo percorrido pelo veiculo entre os sensores de entrada e sa�da
				long tempoMS = calculoDistancia(nodePassagem->info->data, proximo->info->data);

				// Ignorar se h� tempo inv�lido (tempos tamb�m t�m de ser positivos)
				if (tempoMS <= 0)
				{
					nodePassagem = nodePassagem->next;
					continue;
				}

				float tempoHoras = tempoMS / 3600000.0f; // convers�o do tempo percorrido para horas
				float velocidade = distancia / tempoHoras; // c�lculo da velocidade media nessa passagem

				// Atualiza��o da vari�vel maiorVelocidade, caso seja maior que a maiorVelocidade anterior
				if (velocidade > maiorVelocidade)
				{
					maiorVelocidade = velocidade;

					// Indentifica o Carro, com essa velocidade media, atrav�s do codigo do Veiculo
					CARRO* carro = retornaCarro(listaHashCarros, nodePassagem->info->codVeiculo);

					if (carro && carro->dono)
					{
						// Ponteiro para procurar o Dono na lista de Donos
						NODE_DONOS* atual = listaDonos->primeiro;
						
						// Pesquisa do dono na lista Donos, a partir do numero de contribuinte
						while (atual)
						{
							if (atual->info->numCont == carro->dono)
							{
								// Atualiza��o do ponteiro donoMaisRapido
								donoMaisRapido = atual->info;
								break;
							}
							atual = atual->next;
						}
					}
					else
					{
						printf("Carro nao encontrado ou sem dono (codVeiculo: %d)\n", nodePassagem->info->codVeiculo);
					}
				}
			}
		}

		nodePassagem = nodePassagem->next;
	}

	// Print no ecr� do Dono com a Velocidade Media mais alta
	if (donoMaisRapido)
	{
		printf("Dono com a maior velocidade media: %s\n", donoMaisRapido->nome);
		printf("Velocidade media maxima: %.2f km/h\n", maiorVelocidade);
	}
	else
	{
		printf("Nenhum dono com velocidade media encontrada.\n");
	}
}
