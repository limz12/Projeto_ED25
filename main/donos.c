#include "donos.h"


LISTA_DONOS* criarListaDonos()
{
	LISTA_DONOS* lista = (LISTA_DONOS*)malloc(sizeof(LISTA_DONOS));
	if (lista != NULL) {
		lista->primeiro = NULL;
		lista->ultimo = NULL;
		lista->elem = 0;
	}
	return lista;
}



NODE_DONOS* criarNodeDonos(Donos dono){
	NODE_DONOS* node = (NODE_DONOS*)malloc(sizeof(NODE_DONOS));
	if (node != NULL) {
		node->info = (Donos*)malloc(sizeof(Donos));
		if (node->info != NULL) {
			*(node->info) = dono;
			node->next = NULL;
		}
		else{
			free(node);
			return NULL;
		}
	}
	return node;
}



int freeNodeDonos(NODE_DONOS* node){
	if (node != NULL) {
		free(node->info);
		free(node);
		return 0;
	}
	return 1;
}



void adicionarListaDonos(LISTA_DONOS* lista, NODE_DONOS* node) {
	if (lista == NULL || node == NULL) return;

	if(lista->primeiro == NULL){
		lista->primeiro = node;
	}
	else {
		lista->ultimo->next = node;
	}
	lista->ultimo = node;
	lista->elem++;
}



void carregarDadosDonos(LISTA_DONOS* lista) {
	if (lista == NULL) {
		return;
	}

	FILE* ficheiro = fopen("donos.txt", "a");
	if (ficheiro == NULL) {
		printf("Erro ao abrir o ficheiro donos.txt\n");
		return;
	}

	Donos dono;	
	while (fscanf(ficheiro, "%d $s %s", &dono.numCont, dono.nome, dono.codpost) == 3) {
		NODE_DONOS* node = criarNodeDonos(dono);
		if (node != NULL) {
			adicionarListaDonos(lista, node);
		}
	}
	fclose(ficheiro);
}