/**
 * @file carros.h
 * @brief Definicao das Estruturas relacionadas com os carros e prototipagem das funcoes utilizadas no carros.c
 */

// CONSTANTES
#define MAX_CHAR_STR 20
#define MAX_CHAR_MATRICULA 8

typedef struct ListaDonos LISTA_DONOS;
typedef struct passagemLista PASSAGEM_LISTA;
typedef struct distanciaLista DISTANCIAS_LISTA;
typedef struct listaHashCarros LISTA_HASHC;

/**
* @struct carro
* @brief Estrutura que representa um carro
*/
typedef struct carro
{
	char matricula[MAX_CHAR_MATRICULA + 1];
	char marca[MAX_CHAR_STR + 1];
	char modelo[MAX_CHAR_STR + 1];
	int ano;
	int dono;
	int codVeiculo;
	int totalInfracoes; // vai armazenar as infracoes cometidas pelo carro
	float totalKMPercorridos; //vai armazenar o total de km percorridos pelo carro
	float totalMinutosPercorridos;
	float velocidadeMediaKM;
}CARRO;

/**
* @struct nodecarro
* @brief Estrutura que serve de node e contem o ponteiro do carro e do proximo
*/
typedef struct nodecarro
{
	CARRO* info;
	struct nodecarro* next;
}NODE_CARRO;

/**
* @struct listaCarro
* @brief Estrutura serve como lista para o conjunto dos NODE_CARRO
*/
typedef struct listaCarro
{
	NODE_CARRO* header; // ponteiro para o primeiro NO
	NODE_CARRO* ultimo_node; // ponteiro para o último NO
	int num_elem;
}LISTA_CARRO;

//***************** HASHING *****************



/**
* @struct nodeHash
* @brief Estrutura que serve de Hashing, sendo a chave a Marca do respetivo carro e contem um ponteiro para o proximo nodeHash
*/
typedef struct nodeHash
{
	char chave[MAX_CHAR_STR]; // marca do carro
	float totalKm_marca;
	float minutosTotalPercorrido;
	struct nodeHash* next;
	LISTA_CARRO* listaCarros;
}NODE_HASHC;

/**
* @struct listaHashCarros
* @brief Estrutura que serve de Lista para os nodeHash
*/
typedef struct listaHashCarros
{
	NODE_HASHC* header;//ponteiro para o inicio da lista
	NODE_HASHC* ultimo_node; // ponteiro para o ultimo node da lista
	int numElementos;
}LISTA_HASHC;

// PROTOTIPAGEM
LISTA_CARRO* criarListaCarro();
NODE_CARRO* criarNodeCarro();
int freeNodeCarro(NODE_CARRO* node);
void carregarDadosCarro(LISTA_HASHC* listaHashCarros);
void addListaCarro(LISTA_CARRO* lista, NODE_CARRO* node);
void criarCarroUtilizador(LISTA_CARRO* lista, LISTA_DONOS* listaDonos);
void mostrarListaCarro(LISTA_CARRO* lista);
int verificarDONOexiste(int idDono, LISTA_DONOS* listaDonos);
void ligarCarroDono(NODE_CARRO* novo_elem, LISTA_DONOS* listaDonos);
// ***************** HASHING **********************
LISTA_HASHC* criarListaHashCarro();
NODE_HASHC* criarNodeHashCarro();
void adicionarInfoNodeHash(NODE_HASHC* nodeHash, NODE_CARRO* nodeCarro);
void mostrarHashCarros(LISTA_HASHC* listaHash);
void inserirNodeHashListaHash(LISTA_HASHC* listaHash, NODE_HASHC* nodeHash);
void freeListaHashCarro(LISTA_HASHC* listaHashCarro);
void ordenarMarcasHashCarrosAlfabeticamente(LISTA_HASHC* listaHash);
void ordenarModeloHashCarrosAlfabeticamente(LISTA_HASHC* listaHash);
void ordenarMatriculaHashCarrosAlfabeticamente(LISTA_HASHC* listaHash);
NODE_CARRO* procuraCarroPorID(int codVeiculo, LISTA_HASHC* listaHashCarros);
void maiorVelocidadeMediaMarca(LISTA_HASHC* listaHashCarros, PASSAGEM_LISTA* listaPassagens, DISTANCIAS_LISTA* listaDistancias);
void marcaMaisComum(LISTA_HASHC* listaHashCarros);
int verificarMatriculaExiste(char* matricula, LISTA_CARRO* listaCarro);