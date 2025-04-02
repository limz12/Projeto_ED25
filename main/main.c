#include "carros.h"

int main()
{
    printf("\tMAIN CARROS.TXT\n");

    LISTA_CARRO* lista = criarListaCarro();
    carregarDadosCarro(lista);
}
