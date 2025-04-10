#include <stdlib.h>
#include <stdio.h>


#include "SENSORES.H"
#include "DISTANCIAS.H"
#include "PASSAGEM.H"
#include "UTEIS.H"
#include "carros.h"
#include "donos.h"
//RESPONSAVEL POR CRIAR TODOS OS MENUS DO PROGRAMA
int menuPrincipal(LISTA_SENSOR* listaSensor, DISTANCIAS_LISTA* listaDistancias, PASSAGEM_LISTA* listaPassagem, LISTA_CARRO* listaCarro,LISTA_DONOS *listaDonos)
{

	//verificar se todas as listas estao presentes
	if (!listaSensor && !listaDistancias && !listaPassagem && !listaCarro && !listaDonos)
	{
		printf("ERRO! AS LISTAS NAO EXISTEM (menuPrincipal)\n");
		return -1;
	}

	int escolha;
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
	do 
	{
		printf("Seleciona uma opcao: \n");
		scanf("%d", &escolha);
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
	printf("# -------------------- MENU DISTANCIAS ----------------------#\n");
	printf("|  (1) Mostrar Lista Distancias                              |\n");
	printf("|------------------------------------------------------------|\n");
	printf("|  (0) Menu Principal                                        |\n");
	printf("#------------------------------------------------------------#\n");
	do
	{
		printf("Seleciona uma opcao: \n");
		scanf("%d", &escolha);
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

void menuPassagens(PASSAGEM_LISTA* listaPassagens)
{
	system("cls");
	//verificar se todas as listas estao presentes
	if (!listaPassagens)
	{
		printf("ERRO! AS LISTAS PASSAGEM nao existe\n");
		return -1;
	}

	int escolha;
	printf("# -------------------- MENU Passagens ----------------------#\n");
	printf("|  (1) Mostrar Lista Passagens (ATENCAO! LISTA EXTENSA)      |\n");
	printf("|  (2) Registar Passagens                                    |\n");
	printf("|------------------------------------------------------------|\n");
	printf("|  (0) Menu Principal                                        |\n");
	printf("#------------------------------------------------------------#\n");
	do
	{
		printf("Seleciona uma opcao: \n");
		scanf("%d", &escolha);
	} while (escolha < 0 || escolha > 2);

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
	printf("# -------------------- MENU SENSORES ----------------------#\n");
	printf("|  (1) Mostrar Lista SENSORES                                |\n");
	printf("|------------------------------------------------------------|\n");
	printf("|  (0) Menu Principal                                        |\n");
	printf("#------------------------------------------------------------#\n");
	do
	{
		printf("Seleciona uma opcao: \n");
		scanf("%d", &escolha);
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

void menuCarros(LISTA_CARRO* listaCarros, LISTA_DONOS* listaDonos)
{
	system("cls");
	//verificar se todas as listas estao presentes
	if (!listaCarros)
	{
		printf("ERRO! A LISTA de SENSORES nao existe\n");
		return -1;
	}

	int escolha;
	printf("# --------------------  MENU CARROS  ----------------------#\n");
	printf("|  (1) Mostrar Lista Carros (ATENCAO! EXTENSO)               |\n");
	printf("|  (2) Inserir Carro                                         |\n");
	printf("|------------------------------------------------------------|\n");
	printf("|  (0) Menu Principal                                        |\n");
	printf("#------------------------------------------------------------#\n");
	do
	{
		printf("Seleciona uma opcao: \n");
		scanf("%d", &escolha);
	} while (escolha < 0 || escolha > 2);

	//chamar as funcoes aqui
	switch (escolha)
	{
	case 1:
		system("cls");
		mostrarListaCarro(listaCarros);
		break;
	case 2:
		system("cls");
		criarCarroUtilizador(listaCarros,listaDonos);
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
	printf("# --------------------  MENU DONOS  -------------------------#\n");
	printf("|  (1) Mostrar Lista Donos (ATENCAO EXTENSO!)                |\n");
	printf("|  (2) Registar Dono                                         |\n");
	printf("|  (3) Ordenar Lista Alfabeticamente                         |\n");
	printf("|  (4) Ordenar Donos por Numero de Contribuinte              |\n");
	printf("|------------------------------------------------------------|\n");
	printf("|  (0) Menu Principal                                        |\n");
	printf("#------------------------------------------------------------#\n");
	do
	{
		printf("Seleciona uma opcao: \n");
		scanf("%d", &escolha);
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