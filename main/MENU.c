#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "SENSORES.H"
#include "DISTANCIAS.H"
#include "PASSAGEM.H"
#include "UTEIS.H"
#include "carros.h"
#include "donos.h"

int verificarNumero(int max) // para a validação das escolhas dos menus
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

//RESPONSAVEL POR CRIAR TODOS OS MENUS DO PROGRAMA
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
		printf("|------------------------------------------------------------|\n");
		printf("|  (0) SAIR (LIBERTAR MEMORIA)                               |\n");
		printf("#------------------------------------------------------------#\n");
	
		printf("Seleciona uma opcao: \n");
		escolha = verificarNumero(6);
	} while (escolha < 0 || escolha > 6);
	return escolha;
} 

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
		break;

	}
	
}

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
		printf("|  (6) Ranking por Total de Infracoes no periodo X           |\n");
		printf("|------------------------------------------------------------|\n");
		printf("|  (0) Menu Principal                                        |\n");
		printf("#------------------------------------------------------------#\n");
	
		printf("Seleciona uma opcao: \n");
		escolha = verificarNumero(6);
	} while (escolha < 0 || escolha > 6);

	//chamar as funcoes aqui
	switch (escolha)
	{
	case 1:
		system("cls");
		mostrarListaPassagem(listaPassagens);
	break;
	case 2:
		system("cls");
		registarPassagem(listaPassagens);
	break;
	case 3:
		system("cls");
		carrosCircularamduranteX(listaPassagens, listaHashCarros);
	break;
	case 4:
		totalKmCarroDuranteX(listaHashCarros, listaPassagens, listaDistancias);
	break;
	case 5:
		infracoesDuranteX(listaHashCarros, listaPassagens, listaDistancias);
		break;
	case 6:
		totalinfracoesDuranteX(listaHashCarros, listaPassagens, listaDistancias);
		break;
	}
}

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
		break;
	}
}

void menuCarros(LISTA_HASHC* hashCarros, LISTA_DONOS* listaDonos)
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
		mostrarHashCarros(hashCarros);
		break;
	case 2:
		system("cls");
		criarCarroUtilizador(hashCarros, listaDonos);
		break;
	case 3:
		system("cls");
		ordenarMarcasHashCarrosAlfabeticamente(hashCarros);
		break;
	case 4:
		system("cls");
		ordenarModeloHashCarrosAlfabeticamente(hashCarros);
		break;
	case 5:
		system("cls");
		ordenarMatriculaHashCarrosAlfabeticamente(hashCarros);
		break;
	}
}

void menuDonos(LISTA_DONOS* listaDonos)
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
		printf("|------------------------------------------------------------|\n");
		printf("|  (0) Menu Principal                                        |\n");
		printf("#------------------------------------------------------------#\n");
	
		printf("Seleciona uma opcao: \n");
		escolha = verificarNumero(4);
	} while (escolha < 0 || escolha > 4);

	//chamar as funcoes aqui
	switch (escolha)
	{
	case 1:
		system("cls");
		listarDonos(listaDonos);
		break;
	case 2:
		system("cls");
		registarDonos(listaDonos);
		break;
	case 3:
		system("cls");
		ordenarListaDonosAlfabeticamente(listaDonos);
		break;
	case 4:
		system("cls");
		ordenarListaDonosContribuinte(listaDonos);
		break;
	}
}