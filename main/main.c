#include "carros.h"

int main()
{
    printf("\tMAIN CARROS.TXT\n");
    
    int opc;

    // FAZER MENU BONITINHO TRALALERO TRALALA...

    printf("Escolha uma opcao:");
    scanf_s("%d", &opc);

    switch(opc)
    { 
        case 1:
            carregarDados();
         
        default:
            break;
    }
    
    return 0;
}

