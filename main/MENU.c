/**
 * @file MENU.c
 * @brief Implementacao das funcoes respetivas aos menus.
 */


// BIBLIOTECAS
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "SENSORES.H"
#include "DISTANCIAS.H"
#include "PASSAGEM.H"
#include "UTEIS.H"
#include "carros.h"
#include "donos.h"


/**
* @brief Funcao responsavel por fazer a validação das escolhas dos menus
* @param max : Recebe um inteiro, que corresponde ao limite maximo das escolhas possiveis
* @return escolha : retorna a opcao, se for um inteiro dentro dos limites das escolhas possiveis
*/
int verificarNumero(int max)
{
	char opcao[2];
	int c, escolha;

	scanf("%1s", &opcao, 2); while ((c = getchar()) != '\n' && c != EOF) {}
	system("cls");

	if (isdigit(opcao[0]))
	{
		escolha = atoi(opcao);
	}
	else
	{
		return max + 1;
	}

	return escolha;
}

/**
* @brief Funcao responsavel por criar o menu principal do programa
* @return escolha : retorna a opcao, se for um inteiro dentro dos limites das escolhas possiveis
*/
int menuPrincipal(LISTA_SENSOR* listaSensor, DISTANCIAS_LISTA* listaDistancias, PASSAGEM_LISTA* listaPassagem, LISTA_HASHC* listaHashCarro,LISTA_DONOS *listaDonos)
{
	//verificar se todas as listas estao presentes
	if (!listaSensor && !listaDistancias && !listaPassagem && !listaHashCarro && !listaDonos)
	{
		printf("ERRO! AS LISTAS NAO EXISTEM (menuPrincipal)\n");
		return -1;
	}

	int escolha;

	do
	{
		printf("# --------------------- MENU PRINCIPAL ----------------------#\n");
		printf("|  (1) Donos                                                 |\n");
		printf("|  (2) Carros                                                |\n");
		printf("|  (3) Distancias                                            |\n");
		printf("|  (4) Passagens                                             |\n");
		printf("|  (5) Sensores                                              |\n");
		printf("|  (6) Memoria Ocupada Estrutura Dados                       |\n");
		printf("|  (7) Guardar Estrutura de Dados                            |\n");
		printf("|------------------------------------------------------------|\n");
		printf("|  (0) SAIR (LIBERTAR MEMORIA)                               |\n");
		printf("#------------------------------------------------------------#\n");
	
		printf("Seleciona uma opcao: \n");
		escolha = verificarNumero(7);
	} while (escolha < 0 || escolha > 7);
	return escolha;
} 

/**
* @brief Funcao responsavel por criar o menu das distancias
* @return VOID
*/
void menuDistancias(DISTANCIAS_LISTA* listaDistancias)
{
	system("cls");
	//verificar se todas as listas estao presentes
	if (!listaDistancias)
	{
		printf("ERRO! AS LISTAS DISTANCIAS nao existe\n");
		return -1;
	}

	int escolha;
	
	do
	{
		printf("# -------------------- MENU DISTANCIAS ----------------------#\n");
		printf("|  (1) Mostrar Lista Distancias                              |\n");
		printf("|------------------------------------------------------------|\n");
		printf("|  (0) Menu Principal                                        |\n");
		printf("#------------------------------------------------------------#\n");
	
		printf("Seleciona uma opcao: \n");
		escolha = verificarNumero(1);
	} while (escolha < 0 || escolha > 1);

	//chamar as funcoes aqui
	switch (escolha)
	{
		case 1:
			system("cls");
			mostrarListaDISTANCIA(listaDistancias);
			printf("\n");
		break;

	}
	
}

/**
* @brief Funcao responsavel por criar o menu das passagens
* @return VOID
*/
void menuPassagens(PASSAGEM_LISTA* listaPassagens, LISTA_HASHC* listaHashCarros, DISTANCIAS_LISTA* listaDistancias)
{
	system("cls");
	//verificar se todas as listas estao presentes
	if (!listaPassagens)
	{
		printf("ERRO! AS LISTAS PASSAGEM nao existe\n");
		return -1;
	}

	int escolha;

	do
	{
		printf("# -------------------- MENU Passagens ----------------------#\n");
		printf("|  (1) Mostrar Lista Passagens (ATENCAO! LISTA EXTENSA)      |\n");
		printf("|  (2) Registar Passagens                                    |\n");
		printf("|  (3) Listagem Carros Que Circularam no periodo X           |\n");
		printf("|  (4) Listagem Carros Que Circularam no periodo X (TOTAL KM)|\n");
		printf("|  (5) Listagem Infracoes ( +120km/h ) no periodo X          |\n");
		printf("|  (6) Ranking Marcas por Total KM no periodo X              |\n");
		printf("|  (7) Ranking por Total de Infracoes no periodo X           |\n");
		printf("|------------------------------------------------------------|\n");
		printf("|  (0) Menu Principal                                        |\n");
		printf("#------------------------------------------------------------#\n");
	
		printf("Seleciona uma opcao: \n");
		escolha = verificarNumero(7);
	} while (escolha < 0 || escolha > 7);

	//chamar as funcoes aqui
	switch (escolha)
	{
	case 1:
		system("cls");
		mostrarListaPassagem(listaPassagens);
		printf("\n");
	break;
	case 2:
		system("cls");
		registarPassagem(listaPassagens);
		printf("\n");
	break;
	case 3:
		system("cls");
		carrosCircularamduranteX(listaPassagens, listaHashCarros);
		printf("\n");
	break;
	case 4:
		system("cls");
		totalKmCarroDuranteX(listaHashCarros, listaPassagens, listaDistancias);
		printf("\n");
	break;
	case 5:
		system("cls");
		infracoesDuranteX(listaHashCarros, listaPassagens, listaDistancias);
		printf("\n");
		break;
	case 6:
		system("cls");
		totalKmMarcaDuranteX(listaHashCarros, listaPassagens, listaDistancias);
		printf("\n");
	break;
	case 7:
		system("cls");
		totalinfracoesDuranteX(listaHashCarros, listaPassagens, listaDistancias);
		printf("\n");
	break;
	}
}

/**
* @brief Funcao responsavel por criar o menu dos sensores
* @return VOID
*/
void menuSensores(LISTA_SENSOR* listaSensores)
{
	system("cls");
	//verificar se todas as listas estao presentes
	if (!listaSensores)
	{
		printf("ERRO! AS LISTA SENSORES nao existe\n");
		return -1;
	}

	int escolha;

	do
	{
		printf("# -------------------- MENU SENSORES ----------------------#\n");
		printf("|  (1) Mostrar Lista SENSORES                                |\n");
		printf("|------------------------------------------------------------|\n");
		printf("|  (0) Menu Principal                                        |\n");
		printf("#------------------------------------------------------------#\n");
	
		printf("Seleciona uma opcao: \n");
		escolha = verificarNumero(1);
	} while (escolha < 0 || escolha > 1);

	//chamar as funcoes aqui
	switch (escolha)
	{
	case 1:
		system("cls");
		mostrarListaSensores(listaSensores);
		printf("\n");
		break;
	}
}

/**
* @brief Funcao responsavel por criar o menu dos carros
* @return VOID
*/
void menuCarros(LISTA_HASHC* hashCarros, LISTA_DONOS* listaDonos, PASSAGEM_LISTA* listaPassagens, DISTANCIAS_LISTA* listaDistancias)
{
	system("cls");
	//verificar se todas as listas estao presentes
	if (!hashCarros)
	{
		printf("ERRO! A LISTA de SENSORES nao existe\n");
		return -1;
	}

	int escolha;

	do
	{
		printf("# --------------------  MENU CARROS  ----------------------- #\n");
		printf("|  (1) Mostrar Lista Carros (ATENCAO! EXTENSO)               |\n");
		printf("|  (2) Inserir Carro                                         |\n");
		printf("|  (3) Ordenar por Marca Alfabeticamente                     |\n");
		printf("|  (4) Ordenar por Modelo Alfabeticamente                    |\n");
		printf("|  (5) Ordenar por Matricula Alfabeticamente                 |\n");
		printf("|  (6) Marca Carros com Maior Velocidade Media               |\n");
		printf("|  (7) Marca Carros Mais Comum                               |\n");
		printf("|------------------------------------------------------------|\n");
		printf("|  (0) Menu Principal                                        |\n");
		printf("#------------------------------------------------------------#\n");

		printf("Seleciona uma opcao: \n");
		escolha = verificarNumero(7);
	} while (escolha < 0 || escolha > 7);

	//chamar as funcoes aqui
	switch (escolha)
	{
	case 1:
		system("cls");
		mostrarHashCarros(hashCarros);
		printf("\n");
		break;
	case 2:
		system("cls");
		criarCarroUtilizador(hashCarros, listaDonos);
		printf("\n");
		break;
	case 3:
		system("cls");
		ordenarMarcasHashCarrosAlfabeticamente(hashCarros);
		printf("\n");
		break;
	case 4:
		system("cls");
		ordenarModeloHashCarrosAlfabeticamente(hashCarros);
		printf("\n");
		break;
	case 5:
		system("cls");
		ordenarMatriculaHashCarrosAlfabeticamente(hashCarros);
		printf("\n");
		break;
	case 6:
		system("cls");
		maiorVelocidadeMediaMarca(hashCarros, listaPassagens, listaDistancias);
		printf("\n");
		break;
	case 7:
		system("cls");
		marcaMaisComum(hashCarros);
		printf("\n");
		break;
	}
}

/**
* @brief Funcao responsavel por criar o menu dos donos
* @return VOID
*/
void menuDonos(LISTA_DONOS* listaDonos, LISTA_HASHC* hashCarro, PASSAGEM_LISTA* listaPassagens, DISTANCIAS_LISTA* listaDistancias)
{
	system("cls");
	//verificar se todas as listas estao presentes
	if (!listaDonos)
	{
		printf("ERRO! A LISTA de Donos nao existe\n");
		return -1;
	}

	int escolha;

	do
	{
		printf("# --------------------  MENU DONOS  -------------------------#\n");
		printf("|  (1) Mostrar Lista Donos (ATENCAO EXTENSO!)                |\n");
		printf("|  (2) Registar Dono                                         |\n");
		printf("|  (3) Ordenar Lista Alfabeticamente                         |\n");
		printf("|  (4) Ordenar Donos por Numero de Contribuinte              |\n");
		printf("|  (5) Dono com a maior velocidade media		     |\n");
		printf("|------------------------------------------------------------|\n");
		printf("|  (0) Menu Principal                                        |\n");
		printf("#------------------------------------------------------------#\n");
	
		printf("Seleciona uma opcao: \n");
		escolha = verificarNumero(5);
	} while (escolha < 0 || escolha > 5);

	//chamar as funcoes aqui
	switch (escolha)
	{
	case 1:
		system("cls");
		listarDonos(listaDonos);
		printf("\n");
		break;
	case 2:
		system("cls");
		registarDonos(listaDonos);
		printf("\n");
		break;
	case 3:
		system("cls");
		ordenarListaDonosAlfabeticamente(listaDonos);
		printf("\n");
		break;
	case 4:
		system("cls");
		ordenarListaDonosContribuinte(listaDonos);
		printf("\n");
		break;
	case 5:
		system("cls");
		maiorVelocidadeMediaDonos(listaDonos, hashCarro, listaPassagens, listaDistancias);
		printf("\n");
		break;
	}
}

/**
* @brief Funcao responsavel por criar o menu das exportacoes 
* @return VOID
*/
void menuGuardarEDFicheiro(LISTA_SENSOR* listaSensor,DISTANCIAS_LISTA* listaDistancias,PASSAGEM_LISTA* listaPassagem,LISTA_HASHC* listaHashCarros,LISTA_DONOS* listaDonos)
{
	system("cls");
	//verificar se todas as listas estao presentes
	if (!listaSensor || !listaDistancias || !listaPassagem || !listaHashCarros || !listaDonos)
	{
		printf("ERRO! A LISTA de SENSORES nao existe\n");
		return -1;
	}

	int escolha;
	do
	{
		printf("# --------------------  MENU GUARDAR ED  --------------------#\n");
		printf("|  (1) Guardar ED em CSV                                     |\n");
		printf("|  (2) Guardar ED em XML                                     |\n");
		printf("|------------------------------------------------------------|\n");
		printf("|  (0) Menu Principal                                        |\n");
		printf("#------------------------------------------------------------#\n");
		printf("Seleciona uma opcao: \n");
		escolha = verificarNumero(2);
	} while (escolha < 0 || escolha > 2);

	//chamar as funcoes aqui
	switch (escolha)
	{
	case 1:
		system("cls");
		exportar_csv_DONOS(listaDonos);
		exportar_csv_SENSORES(listaSensor);
		exportar_csv_DISTANCIAS(listaDistancias);
		exportar_csv_CARROS(listaHashCarros);
		exportar_csv_PASSAGENS(listaPassagem);
		printf("\n");
		break;
	case 2:
		system("cls");
		exportar_xml_DONOS(listaDonos);
		exportar_xml_SENSORES(listaSensor);
		exportar_xml_DISTANCIAS(listaDistancias);
		exportar_xml_CARROS(listaHashCarros);
		exportar_xml_PASSAGENS(listaPassagem);
		printf("\n");
		break;
	}
}