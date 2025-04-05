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
	//inserir um ponteiro para a struct dono
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

// PROTOTIPAGEM
LISTA_CARRO* criarListaCarro();
NODE_CARRO* criarNodeCarro();
int freeNodeCarro(NODE_CARRO* node);
void carregarDadosCarro(LISTA_CARRO* lista);
void addListaCarro(LISTA_CARRO* lista, NODE_CARRO* node);
//void criarCarroUtilizador(LISTA_CARRO* lista, LISTA_DONOS* listaDonos);
void mostrarListaCarro(LISTA_CARRO* lista);
void freeListaCarro(LISTA_CARRO* lista);
//int verificarDONOexiste(int idDono, LISTA_DONOS* listaDonos);
