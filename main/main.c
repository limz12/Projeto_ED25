#include <stdlib.h>
#include <stdio.h>
#include "donos.h"

int main()
{
    printf("main Donos.txt\n");

	LISTA_DONOS* listaDonos = criarListaDonos();    
    carregarDadosDonos(listaDonos);


}

