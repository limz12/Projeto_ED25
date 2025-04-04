#include <stdlib.h>
#include <stdio.h>
#include "donos.h"

int main() {
	printf("\tMain donos.txt\n");

	LISTA_DONOS* lista = criarListaDonos();
	carregarDadosDonos(lista);

	listarDonos(lista);
}

