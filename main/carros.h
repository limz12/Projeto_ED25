// CONSTANTES
#define MAX_CHAR_STR 20
#define MAX_CHAR_MATRICULA 8

// ESTRUTURAS DO CARRO
typedef struct 
{
	char matricula[MAX_CHAR_MATRICULA + 1];
	char marca[MAX_CHAR_STR + 1];
	char modelo[MAX_CHAR_STR + 1];
	int ano;
	int dono;
	int codVeiculo;
	int total_km;
}CARRO;

// NODE DO CARRO
typedef struct nodecarro
{
	CARRO* info;
	struct nodecarro* next;
}NODE_CARRO;

// LISTA CARRO
typedef struct
{
	NODE_CARRO* header; // ponteiro para o primeiro NO
	NODE_CARRO* ultimo_node; // ponteiro para o último NO
	int num_elem;
}LISTA_CARRO;

//***************** HASHING *****************
//criar o NODE do hashing

typedef struct nodeHash
{
	char chave[MAX_CHAR_STR];
	int total_Km_marca;
	struct nodeHash* next;
	LISTA_CARRO* listaCarros;
}NODE_HASHC;

//criar a listaHashing
typedef struct
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
//void criarCarroUtilizador(LISTA_CARRO* lista, LISTA_DONOS* listaDonos);
void mostrarListaCarro(LISTA_CARRO* lista);
//int verificarDONOexiste(int idDono, LISTA_DONOS* listaDonos);
//void ligarCarroDono(NODE_CARRO* novo_elem, LISTA_DONOS* listaDonos);

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