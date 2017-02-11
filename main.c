#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "produtos.h"
#include "clientes.h"
#include "faturacao.h"
#include "filial.h"
#include "avl.h"

#define MAXVENDAS 64
#define STRING 10


void delScreen() {
	int i = 0, tam = 50;
	while (i < tam) {
		printf("\n");
		i++;
	}
}

void print_menu_fat(int mes, char* produto) {
	delScreen();
	printf("╔══════════════════════════════════════════════════════════════╗\n");
	if (mes < 10) printf("║ Que faturação pretende consultar [Produto %s] [Mês %d]:   ║\n", produto, mes);
	else printf("║ Que faturação pretende consultar [Produto %s] [Mês %d]:  ║\n", produto, mes);
	printf("║ [1]. Faturação global.                                       ║\n");
	printf("║ [2]. Faturação por filial.                                   ║\n");
	printf("║                                                     Sair [0] ║\n");
	printf("╚══════════════════════════════════════════════════════════════╝\n\n");
}

void print_menu() {
		delScreen();
		printf("                            ╔══════╗                            \n");
		printf("╔═══════════════════════════╣ MENU ╠═══════════════════════════╗\n");
		printf("║                           ╚══════╝                           ║\n");
		printf("║  [1]. Inicializar catálogos (Produtos, Clientes e Vendas).   ║\n");
		printf("║  [2]. Procurar Produto por letra.                            ║\n");
		printf("║  [3]. Gestão de Faturação.                                   ║\n");
		printf("║  [4]. Produtos nunca comprados.                              ║\n");
		printf("║  [5]. Total de compras por Cliente.                          ║\n");
		printf("║  [6]. Dados de Vendas num Certo Intervalo de Meses.          ║\n");
		printf("║  [7]. Clientes que Compraram em todas as filiais.            ║\n");
		printf("║  [8]. Total de clientes que compraram determinado produto    ║\n");
		printf("║       numa dada filial.                                      ║\n");
		printf("║  [9]. Lista de produtos mais comprados por um cliente        ║\n");
		printf("║       num dado mês (ordem descendente).                      ║\n");
		printf("║ [10]. Lista dos N produtos mais vendidos em todo o ano.      ║\n");
		printf("║ [11]. Top 3 dos produtos comprados por um cliente.           ║\n");
		printf("║ [12]. Número de Produtos nunca Comprados e Número de         ║\n");
		printf("║       Clientes sem compras.                                  ║\n");
		printf("║                                                     Sair [0] ║\n");
		printf("╚══════════════════════════════════════════════════════════════╝\n\n\n\n\n");
}

/* Query nº 2 */
int imprime(LstProds l, int indice){
	int j;
	printf("╔══════════════════════════════════════════════════════════════╗\n");

	for (j = indice; j < indice + 30 && j < getSize_P(l); j+=3) {
		if(getSize_P(l) == j + 1)
			printf("║ %s                                                       ║\n", getElem_P(l, j));
		else if(getSize_P(l) == j + 2)
			     printf("║ %s                     %s                            ║\n", getElem_P(l, j), getElem_P(l, j+1));
			 else printf("║ %s                     %s                     %s ║\n", getElem_P(l, j), getElem_P(l, j+1), getElem_P(l, j+2));
	}

	printf("╚══════════════════════════════════════════════════════════════╝\n");

	if (getSize_P(l)%30 == 0) printf("                                               Página %d de %d\n\n",  ((indice)/30) + 1, (getSize_P(l)/30));
	else printf("                                               Página %d de %d\n\n",  ((indice)/30) + 1, (getSize_P(l)/30) + 1);
	if (indice == 0) printf("Página Seguinte [s] | Escolher página [p num] | Sair [q]\n");
	else if ((indice/30) >= (getSize_P(l)/30)) printf("Página Anterior [a] | Escolher página [p num] | Sair [q]\n");
		 else printf("Página Anterior [a] | Página Seguinte [s] | Escolher página [p num] | Sair [q]\n");
	printf("Opção: ");
	return j;
}

void verProdutos(CatProds cps){
	char letra, choice = '_';
	LstProds lista;
	int i = 0, pag;
	printf("Procurar produtos iniciados pela letra: ");
	if(scanf(" %c", &letra))
		if (letra >= 97 && letra <= 122) letra -= 32;
	lista = prodsPorLetra(cps, letra);
	delScreen();
	printf("                 CATÁLOGO DE PRODUTOS POR \"%c\"                 \n", letra);
	i = imprime(lista, i);
	while(choice != 'q'){
		if(scanf(" %c", &choice));
		switch (choice) {
		 	case 'a': 	if (i < 60) printf("Opção indisponível.\nOpção: ");
		 				else {
		 					delScreen();
							printf("                 CATÁLOGO DE PRODUTOS POR \"%c\"                 \n", letra);
							if (i%30 != 0) i = imprime(lista, i - (30 + i%30));
							else i = imprime(lista, i - 60);
						}
						break;
		 	case 's': 	if (i >= getSize_P(lista)) printf("Opção indisponível.\nOpção: ");
		 				else {
		 					delScreen();
							printf("                 CATÁLOGO DE PRODUTOS POR \"%c\"                 \n", letra);
							i = imprime(lista, i);
						}
						break;
		 	case 'q': 	freeLista_P(lista);
					  	break;
			case 'p': 	if (scanf ("%d", &pag));
						if (pag > 0) {
							if (getSize_P(lista)%30 != 0) {
								if (pag > (getSize_P(lista)/30) + 1) {
									delScreen();
									printf("                 CATÁLOGO DE PRODUTOS POR \"%c\"                 \n", letra);
									i = imprime(lista, 30*(getSize_P(lista)/30));
								}
								else {
									delScreen();
									printf("                 CATÁLOGO DE PRODUTOS POR \"%c\"                 \n", letra);
									i = imprime(lista, 30*(pag-1));
								}
							}
							else {
								if (pag > (getSize_P(lista)/30)) {
									delScreen();
									printf("                 CATÁLOGO DE PRODUTOS POR \"%c\"                 \n", letra);
									i = imprime(lista, 30*(getSize_P(lista)/30));
								}
								else {
									delScreen();
									printf("                 CATÁLOGO DE PRODUTOS POR \"%c\"                 \n", letra);
									i = imprime(lista, 30*(pag-1));
								}
							}
						}
						else printf("Página indisponível.\nOpção: ");
						break;
		 	default: 	printf("Opção indisponível.\nOpção: "); break;
		}
	}
}

/* Query nº 3 */
void faturacaoProduto(CatVendas cvs, CatProds cps){
	char produto[7];
	int mes, choice = -1, i, totalVendasN, totalVendasP, totalVendas, vendasFilialN, vendasFilialP, vendasTotaisFilial;
	double faturacaoN, faturacaoP, faturacaoTotal, faturacaoFilialN, faturacaoFilialP, faturacaoTotalFilial;

	printf("Introduza o código do produto a analisar e o mês [Produto Mês]: ");
	if(scanf("%s %d", produto, &mes) == 2) {

		if (existeProduto(cps, produto) == false || (mes < 1 || mes > 12)) {
			 if (existeProduto(cps, produto) == false) printf("Cliente Inválido.\n");
			 else printf("\nMês introduzido inválido.\n");
			 printf("Prima ENTER para continuar.\n");
			 getchar();
			 getchar();
		}
		else {
			print_menu_fat(mes, produto);
			printf("Comando: ");
			while (choice != 0) {
				if(scanf(" %d", &choice));
				switch(choice) {
					case 1:	faturacaoN = faturacaoGlobal (cvs, mes, produto, 0);
							faturacaoP = faturacaoGlobal (cvs, mes, produto, 1);
							faturacaoTotal = faturacaoN + faturacaoP;
							totalVendasN = totalVendasProd_Mes (cvs, mes, produto, 0);
							totalVendasP = totalVendasProd_Mes (cvs, mes, produto, 1);
							totalVendas = totalVendasP + totalVendasN;
							print_menu_fat(mes, produto);
							printf("Total de vendas do produto %s no mês %d: %d\nFaturação total: %.2f\n", produto, mes, totalVendas, faturacaoTotal);
							printf("Vendas N = %d Faturacão N = %.2f\n", totalVendasN, faturacaoN);
							printf("Vendas P = %d Faturacão P = %.2f\n\n", totalVendasP, faturacaoP);
							printf("Comando: ");
							break;
					case 2:	print_menu_fat(mes, produto);
							printf("Vendas do produto %s no mês %d:\n\n", produto, mes);
							for(i = 1; i <=3; i++){
								printf("Filial %d:\n", i);
								vendasFilialN = totalVendasPorFil (cvs, mes, produto, 0, i);
								vendasFilialP = totalVendasPorFil (cvs, mes, produto, 1, i);
								vendasTotaisFilial = vendasFilialN + vendasFilialP;
								faturacaoFilialN = faturacaoPorFil (cvs, mes, produto, 0, i);
								faturacaoFilialP = faturacaoPorFil (cvs, mes, produto, 1, i);
								faturacaoTotalFilial = faturacaoFilialN + faturacaoFilialP;
								printf("Unidades vendidas: %d \nFaturação total: %.2f\n", vendasTotaisFilial, faturacaoTotalFilial);
								printf("Vendas N = %d Faturacão N = %.2f\n", vendasFilialN, faturacaoFilialN);
								printf("Vendas P = %d Faturacão P = %.2f\n\n", vendasFilialP, faturacaoFilialP);
							}
							printf("Comando: ");
							break;
					case 0: delScreen();
							print_menu();
							break;
					default: printf("Opção inválida!\nComando: "); break;
				}
			}
		}
	}
	else
		printf("Erro de introdução.\n");
}

/* Query 4 */ 
void verProdutos2(LstProds lista){
	char choice = '_';
	int i = 0, pag;
	printf("                 CATÁLOGO DE PRODUTOS NÃO COMPRADOS                \n");
	i = imprime(lista, i);
	while(choice != 'q'){
		if(scanf(" %c", &choice));
		switch (choice) {
		 	case 'a': 	if (i < 60) printf("Opção indisponível.\nOpção: ");
		 				else {
		 					delScreen();
							printf("                 CATÁLOGO DE PRODUTOS NÃO COMPRADOS                 \n");
							if (i%30 != 0) i = imprime(lista, i - (30 + i%30));
							else i = imprime(lista, i - 60);
						}
						break;
			case 's': 	if (i >= getSize_P(lista)) printf("Opção indisponível.\nOpção: ");
		 				else {
		 					delScreen();
							printf("                 CATÁLOGO DE PRODUTOS NÃO COMPRADOS                \n");
							i = imprime(lista, i);
						}
						break;
		 	case 'q': 	freeLista_P(lista);
					  	break;
			case 'p': 	if (scanf ("%d", &pag));
						if (pag > 0) {
							if (getSize_P(lista)%30 != 0) {
								if (pag > (getSize_P(lista)/30) + 1) {
									delScreen();
									printf("                 CATÁLOGO DE PRODUTOS NÃO COMPRADOS                \n");
									i = imprime(lista, 30*(getSize_P(lista)/30));
								}
								else {
									delScreen();
									printf("                 CATÁLOGO DE PRODUTOS NÃO COMPRADOS                \n");
									i = imprime(lista, 30*(pag-1));
								}
							}
							else {
								if (pag > (getSize_P(lista)/30)) {
									delScreen();
									printf("                 CATÁLOGO DE PRODUTOS NÃO COMPRADOS                \n");
									i = imprime(lista, 30*(getSize_P(lista)/30));
								}
								else {
									delScreen();
									printf("                 CATÁLOGO DE PRODUTOS NÃO COMPRADOS                \n");
									i = imprime(lista, 30*(pag-1));
								}
							}
						}
						else printf("Página indisponível.\nOpção: ");
						break;
		 	default: 	printf("Opção indisponível.\nOpção: ");
		 				break;
		}
	}
}


void query4(CatProds cps, CatVendas cvs){
	int i, size, choice;
	LstProds l, lista;
	delScreen();
	printf("╔══════════════════════════════════════════════════════════════╗\n");
	printf("║ Que lista de produtos não comprados prefere consultar?       ║\n");
	printf("║ [1]. Lista global.                                           ║\n");
	printf("║ [2]. Lista por filial.                                       ║\n");
	printf("╚══════════════════════════════════════════════════════════════╝\n\n");
	printf("Comando: ");
	if(scanf(" %d", &choice));
	switch(choice) {
		case 1: lista = nao_comprados(cps, cvs);
				size = getSize_P(lista);
				delScreen();
				printf("No total, não foram comprados %d produtos.\n", size);
				printf("Aqui está a lista ordenada destes produtos:\n\n\n");
				verProdutos2(lista);
				break;

		case 2: l = lista_produtos(cps);
				for (i = 0; i < 3; i++){
					lista = nao_comprados_porFil(l, cvs, i);
					size = getSize_P(lista);
					delScreen();
					printf("No total, não foram comprados %d produtos na filial %d.\n", size, i+1);
					printf("Aqui está a lista ordenada desses produtos:\n\n\n");
					verProdutos2(lista);
					printf("\n\n\n");
				}
				break;
		default:	printf("Opção indisponível!\nComando: ");
					break;
	}
}

/* Query 5 */

void query5 (CatVendas cvcl) {
	char resposta = 'S';
	int i, j, total = 0;
	char cliente[STRING];
	printf ("Introduza o cliente pretendido: ");
	if (scanf ("%s", cliente)) {
		for (i = 0; i < 3 && resposta == 'S'; i++) {
			delScreen();
			printf("                        ╔══════════╗                           \n");
			printf("                        ║ Filial %d ║                           \n", (i + 1));
			printf("                        ╚══════════╝                           \n");
			printf("╔════════════════════════════════════════════════════════╗\n");
			for (j = 0; j < 12; j++) {
				total = totalQtd (cvcl, j, i, cliente);
				
				if ((j+1) < 10) {
					if (total >= 0 && total < 10) printf("║ [Mês %d]  Comprados %d produtos.                         ║\n", (j + 1), total);
					if (total >= 10 && total < 100) printf("║ [Mês %d]  Comprados %d produtos.                        ║\n", (j + 1), total);
					if (total >= 100 && total < 1000) printf("║ [Mês %d]  Comprados %d produtos.                       ║\n", (j + 1), total);
					if (total >= 1000 && total < 10000) printf("║ [Mês %d]  Comprados %d produtos.                      ║\n", (j + 1), total);
					if (total >= 10000) printf("║ [Mês %d]  Comprados %d produtos.                     ║\n", (j + 1), total);
				} else {
					if (total >= 0 && total < 10) printf("║ [Mês %d] Comprados %d produtos.                         ║\n", (j + 1), total);
					if (total >= 10 && total < 100) printf("║ [Mês %d] Comprados %d produtos.                        ║\n", (j + 1), total);
					if (total >= 100 && total < 1000) printf("║ [Mês %d] Comprados %d produtos.                       ║\n", (j + 1), total);
					if (total >= 1000 && total < 10000) printf("║ [Mês %d] Comprados %d produtos.                      ║\n", (j + 1), total);
					if (total >= 10000) printf("║ [Mês %d] Comprados %d produtos.                     ║\n", (j + 1), total);
				}
			}
			if (i != 3) {
				printf("╚════════════════════════════════════════════════════════╝\n\nContinuar [S/N]: ");
				if(scanf (" %c", &resposta));
			} else {
				resposta = 'N';
			}
		}
	}
	else
		printf("Erro de introdução.\n");
}

/* Query 6 */

void query6 (CatVendas cvs) {
	int mesI, mesF, totalVendas, totalUnidades;
	double faturacaoTotal;

	delScreen();
	printf("Introduza os meses entre os quais quer prosseguir com a consulta [Mês Mês]: ");
	if(scanf("%d %d", &mesI, &mesF) == 2) {

		if ((mesI > 0 && mesF < 13) && (mesI > 0 && mesF < 13)) {
			totalVendas = totalVendasIntMeses (cvs, mesI, mesF);
			faturacaoTotal = totalFatIntMeses (cvs, mesI, mesF);
			totalUnidades = totalUnidadesIntMeses (cvs, mesI, mesF);
			printf("\n  Total de vendas no intervalo [%d ... %d]: %d\n", mesI, mesF, totalVendas);
			printf("  Faturação Total no intervalo [%d ... %d]: %.2f\n", mesI, mesF, faturacaoTotal);
			printf ("  Total de unidades vendidas no intervalo [%d ... %d]: %d\n\n", mesI, mesF, totalUnidades);
		} else printf("Mês Introduzido inválido!\n");
	}
	else printf("\nErro de introdução.\n");

	printf("Prima ENTER para continuar.");
	getchar();
	getchar();
}

/* Query 7 */
int imprime_v2(LstClientes l, int indice){
	int j;
	printf("╔══════════════════════════════════════════════════════════════╗\n");

	for (j = indice; j < indice + 30 && j < getSize_C(l); j+=3) {
		if(getSize_C(l) == j + 1)
			printf("║ %s                                                        ║\n", getElem_C(l, j));
		else if(getSize_C(l) == j + 2)
			     printf("║ %s                    %s                          ║\n", getElem_C(l, j), getElem_C(l, j+1));
			 else printf("║ %s                      %s                       %s ║\n", getElem_C(l, j), getElem_C(l, j+1), getElem_C(l, j+2));
	}

	printf("╚══════════════════════════════════════════════════════════════╝\n");

	if (getSize_C(l)%30 == 0) printf("                                               Página %d de %d\n\n",  ((indice)/30) + 1, (getSize_C(l)/30));
	else printf("                                               Página %d de %d\n\n",  ((indice)/30) + 1, (getSize_C(l)/30) + 1);
	if (indice == 0) printf("Página Seguinte [s] | Escolher página [p num] | Sair [q]\n");
	else if ((indice/30) >= (getSize_C(l)/30)) printf("Página Anterior [a] | Escolher página [p num] | Sair [q]\n");
		 else printf("Página Anterior [a] | Página Seguinte [s] | Escolher página [p num] | Sair [q]\n");
	printf("Opção: ");
	return j;
}

void verProdutos3(LstClientes lista){
	char choice = '_';
	int i = 0, pag;
	printf("    CATÁLOGO DE CLIENTES QUE COMPRARAM EM TODAS AS FILIAIS        \n");
	i = imprime_v2(lista, i);
	while(choice != 'q'){
		if(scanf(" %c", &choice));
		switch (choice) {
		 	case 'a': 	if (i < 60) printf("Opção indisponível.\nOpção: ");
		 				else {
		 					delScreen();
							printf("    CATÁLOGO DE CLIENTES QUE COMPRARAM EM TODAS AS FILIAIS        \n");
							if (i%30 != 0) i = imprime_v2(lista, i - (30 + i%30));
							else i = imprime_v2(lista, i - 60);
						}
						break;
		 	case 's': 	if (i >= getSize_C(lista)) printf("Opção indisponível.\nOpção: ");
		 				else {
		 					delScreen();
							printf("    CATÁLOGO DE CLIENTES QUE COMPRARAM EM TODAS AS FILIAIS        \n");
							i = imprime_v2(lista, i);
						}
						break;
		 	case 'q': 	freeLista_C(lista);
					  	break;
			case 'p': 	if (scanf ("%d", &pag));
						if (pag > 0) {
							if (getSize_C(lista)%30 != 0) {
								if (pag > (getSize_C(lista)/30) + 1) {
									delScreen();
									printf("    CATÁLOGO DE CLIENTES QUE COMPRARAM EM TODAS AS FILIAIS        \n");
									i = imprime_v2(lista, 30*(getSize_C(lista)/30));
								}
								else {
									delScreen();
									printf("    CATÁLOGO DE CLIENTES QUE COMPRARAM EM TODAS AS FILIAIS        \n");
									i = imprime_v2(lista, 30*(pag-1));
								}
							}
							else {
								if (pag > (getSize_C(lista)/30)) {
									delScreen();
									printf("    CATÁLOGO DE CLIENTES QUE COMPRARAM EM TODAS AS FILIAIS        \n");
									i = imprime_v2(lista, 30*(getSize_C(lista)/30));
								}
								else {
									delScreen();
									printf("    CATÁLOGO DE CLIENTES QUE COMPRARAM EM TODAS AS FILIAIS        \n");
									i = imprime_v2(lista, 30*(pag-1));
								}
							}
						}
						else printf("Página indisponível.\nOpção: ");
						break;
		 	default: 	printf("Opção indisponível.\nOpção: "); break;
		}
	}
}

void query7(CatClientes ccs, CatVendas cvcl){
	LstClientes l, lista;
	l = lista_clientes(ccs);
	lista = comprouEmtodas(cvcl, l);
	verProdutos3(lista);
}

/* QUERY 8 */

void imprime_v3(LstClientes l){
	int j;
	printf("╔══════════════════════════════════════════════════════════════╗\n");

	for (j = 0; j < getSize_C(l); j+=3) {
		if(getSize_C(l) == j + 1) {
			printf("║ %s                                                        ║\n", getElem_C(l, j));
		}
		else {
			if(getSize_C(l) == j + 2){
				printf("║ %s                      %s                             ║\n", getElem_C(l, j), getElem_C(l, j+1));
			}
			else {
				if(getSize_C(l) >= j + 3)
					printf("║ %s                      %s                       %s ║\n", getElem_C(l, j), getElem_C(l, j+1), getElem_C(l, j+2));
			}
		}
	}
	printf("╚══════════════════════════════════════════════════════════════╝\n\n");
}

void query8(CatVendas cvs) {
	int filial;
	clock_t inicio, fim;
	double tempo;
	char produto[STRING];
	LstClientes compraramN = NULL, compraramP = NULL;
	compraramN = setLstClientes(compraramN);
	compraramP = setLstClientes(compraramP);
	
	delScreen();
	printf("Introduza o código do produto a analisar e a filial [Produto Filial]: ");
	if(scanf("%s %d", produto, &filial) == 2) {

		inicio = clock();
		compraramN = comprado_Codigo(cvs, produto, filial-1, 0, compraramN);
		compraramP = comprado_Codigo(cvs, produto, filial-1, 1, compraramP);
		fim = clock();

		if (getSize_C(compraramN) == 0 && getSize_C(compraramP) == 0)
			printf("Nenhum cliente comprou o produto %s, na filial %d.\n", produto, filial);
		else {
			printf("Vendas do produto %s na filial %d:\n", produto, filial);
			if (getSize_C(compraramN) != 0) {
				printf("\nTipo 'N':\n");
				imprime_v3(compraramN);
			}
			if (getSize_C(compraramP) != 0) {
				printf("Tipo 'P':\n");
				imprime_v3(compraramP);
			}
		}

		tempo = (double) (fim-inicio)/CLOCKS_PER_SEC;
		tempo *= 1000000;

		printf("Cálculo efetuado em %.1fµs (Microssegundos)!\n", tempo);
		printf("Prima ENTER para continuar.");
		getchar();
		getchar();
	}
	delScreen();
	print_menu();
	printf("Opção: ");

	freeLista_C(compraramN);
	freeLista_C(compraramP);
}

CatClientes lerClientes(CatClientes ccs, char* file){
	FILE *p;
	clock_t inicio, fim;
	double tempo;
	p = fopen (file, "rt");
	
	inicio = clock();
	
	if (p == NULL)
		printf ("Erro ao abrir o ficheiro.\n");
	else {
		char* tmp_linha = malloc(STRING);
		Cliente cliente = criaCliente("");
		while (fgets (tmp_linha, STRING, p) != NULL)
		{	
			cliente = alteraCliente(cliente, tmp_linha);
			ccs = insereCliente(ccs, cliente);
		}
		free(cliente);
		free (tmp_linha);
		fclose (p);
		printf("...Analisado Clientes.txt com Sucesso!\n");
	}
	fim = clock();
	tempo = (double) (fim - inicio)/CLOCKS_PER_SEC;
	printf("Lidas %d linhas do ficheiro Clientes em %.3f segundos.\n\n", getTam_C(ccs), tempo);
	return ccs;
}

CatProds lerProdutos(CatProds cps, char* file){
	FILE *p;
	clock_t inicio, fim;
	double tempo;
	p = fopen (file, "rt");
	
	inicio = clock();

	if (p == NULL)
		printf ("Erro ao abrir o ficheiro.\n");
	else {
		char* tmp_linha = malloc(STRING);
		Produto prod = criaProduto("");
		while (fgets (tmp_linha, STRING, p) != NULL)
		{	
			prod = alteraProduto(prod, tmp_linha);
			cps = insereProduto(cps, prod);
		}
		free(prod);
		free (tmp_linha);
		fclose (p);
		printf("...Analisado Produtos.txt com Sucesso!\n");
	}
	fim = clock();
	tempo = (double) (fim - inicio)/CLOCKS_PER_SEC;
	printf("Lidas %d linhas do ficheiro Produtos em %.3f segundos.\n\n", getTam_P(cps), tempo);

	return cps;
}

Boolean vendaValida(CatClientes ccs, CatProds cps, VENDAS venda) {
	Boolean valida = false;
	if ((existeCliente(ccs, clienteVenda(venda)) == true) &&
		(existeProduto(cps, prodVenda(venda)) == true) &&
		(mesVenda(venda) > 0 && mesVenda(venda) < 13) &&
		(filialVenda(venda) > 0 && filialVenda(venda) < 4) &&
		(precoVenda(venda) >= 0 && precoVenda(venda) < 1000) &&
		(qtdVenda(venda) > 0 && qtdVenda (venda) < 201) &&
		(tipoVenda(venda) == 'N' || tipoVenda(venda) == 'P'))
			valida = true;
	return valida;
}

CatVendas lerVendas (FILE *p, char path[], CatVendas cvs, CatVendas cvcl, CatProds cps, CatClientes ccs) {
	int i = 0;
	char* tmp_linha = malloc (MAXVENDAS);
	VENDAS venda = NULL;

	while (fgets (tmp_linha, MAXVENDAS, p) != NULL){	
		venda = analisaVendas(tmp_linha);
		if (vendaValida(ccs, cps, venda) == true) {
			cvs = split_Filial(cvs, venda);
			cvcl = split_Filial_V2(cvcl, venda);
		}
		i++;
	}
	free(venda);
	free (tmp_linha);
	printf("...Analisado %s com Sucesso!\n", path);
	printf("Validadas %d das %d linhas existentes no ficheiro Vendas.\n", getTam_V(cvs), i);
	
	return cvs;
}

/* QUERY 9 */
void imprime_v4(LstProds l){
	int j;
	printf("╔══════════════════════════════════════════════════════════════╗\n");

	for (j = 0; j < getSize_P(l); j+=3) {
		if(getSize_P(l) == j + 1) {
			printf("║ %s                                                       ║\n", getElem_P(l, j));
		}
		else {
			if(getSize_P(l) == j + 2){
				printf("║ %s                     %s                            ║\n", getElem_P(l, j), getElem_P(l, j+1));
			}
			else {
				if(getSize_P(l) >= j + 3)
					printf("║ %s                     %s                     %s ║\n", getElem_P(l, j), getElem_P(l, j+1), getElem_P(l, j+2));
			}
		}
	}
	printf("╚══════════════════════════════════════════════════════════════╝\n\n");
}

void query9(CatVendas cvcl, CatClientes ccs) {
	LstProds lista = NULL;
	clock_t inicio, fim;
	double tempo;
	char cliente[STRING];
	int mes;
	char* choice = malloc(STRING);
	printf("Introduza o cliente pretendido e o mês [Cliente Mês]: ");
	if (scanf ("%s %d", cliente, &mes) == 2) {
	
		if (mes < 1 || mes > 12) {
			delScreen();
			printf("Mês Inválido, introduza um valor entre 1 e 12.\n");
		}
		else {
			inicio = clock();
			lista = maisComprados_Mes(cvcl, cliente, (mes-1));
			fim = clock();
			tempo = (double) (fim-inicio)/CLOCKS_PER_SEC;
			tempo *= 1000000;
		}

		if(getSize_P(lista) == 0 && (mes > 0 && mes < 13)) {
			delScreen();
			if (existeCliente(ccs, cliente) == false) printf("Cliente Inválido.\n");
			else printf("O Cliente introduzido não efetuou compras no mês %d.\n", mes);
			freeLista_P(lista);
		}
		else {
			if (mes > 0 && mes < 13) {
				delScreen();
				printf("Os produtos mais comprados pelo cliente %s no mês %d foram:\n\n", cliente, mes);
				imprime_v4(lista);
				freeLista_P(lista);
			}
		}
		
		printf("Cálculo efetuado em %.1fµs (Microssegundos).\n", tempo);
		printf("Prima ENTER para continuar.");
		getchar();
		getchar();
		free(choice);
	}
	else printf("Input inválido!\n");
}

/* QUERY 10 */
void query10(CatVendas cvs, CatProds cps) {
	Q10 lista;
	int i, j;
	char* N = malloc(STRING);
	char* choice = malloc(STRING);
	char resposta = 'S';

	printf("Em primeiro lugar, defina quantos produtos a lista terá.\nN = ");
	if(scanf("%s", N));
	while (atoi(N) == 0 || atoi(N) > 171009) {
		printf("Input inválido. Por favor, reintroduza o N.\nN = ");
		if(scanf("%s", N));
	}
	for (i = 0; i < 3; i++){
		lista = maisVendidos_porFil(cvs, cps, i, atoi(N));
		printf("\nLista dos %d produtos mais vendidos em todo o ano na filial %d\n", atoi(N), i+1);
		for (j = 0; j < atoi(N); j++){
			printf("\n%d. %s\n", j+1, getElem_P(getProds_Q10(lista), j));
			printf("Produto comprado por %d clientes.\n", getSize_C(getClientes_Q10(lista, j)));
			printf("Foram vendidas %d unidades deste produto em todo o ano.\n", getQtd_Q10(lista, j));	
		}
		if (i < 2){
			printf("\n                                Continuar [S/N]\n");
			getchar();
			resposta = getchar();
			if (resposta != 83 && resposta != 78)
				printf("Introduza S ou N\n");
			if (resposta == 78) break;
		}
		printf("\n");
	}

		printf("                                                   Sair [0] \n");
		getchar();
		while (choice[0] != 48) {
			choice = fgets(choice, STRING, stdin);	
			if (strlen(strtok(choice, "\n")) > 1 || choice[0] != 48) printf("\n    -- 0 para sair -- \n");
			else {
				print_menu();
				break;
			}
		}
		free_Q10(lista);
		free(choice);
		free(N);
}

/* QUERY 11 */
void query11(CatVendas cvcl, CatClientes ccs) {
	LstProds lista;
	clock_t inicio, fim;
	double tempo;
	char cliente[STRING];

	printf ("Introduza o cliente pretendido: ");
	if (scanf ("%s", cliente)) {
		inicio = clock();
		delScreen();
		if (existeCliente(ccs, cliente) == false) printf("Cliente Inválido.\n");
		else {

			lista = maisComprados(cvcl, cliente);

			printf("╔══════════════════════════════════════════════════════════════╗\n");
			printf("║ Os 3 produtos mais comprados pelo cliente %s foram:       ║\n", cliente);
			printf("║                                                              ║\n");
			printf("║ 1. %s                                                    ║\n", getElem_P(lista, 0));
			printf("║ 2. %s                                                    ║\n", getElem_P(lista, 1));
			printf("║ 3. %s                                                    ║\n", getElem_P(lista, 2));
			printf("╚══════════════════════════════════════════════════════════════╝\n\n");

			freeLista_P(lista);

		}
		
		fim = clock();
		tempo = (double) (fim - inicio)/CLOCKS_PER_SEC;
		tempo *= 1000000;

		printf("Cálculo efetuado em %.1fµs (Microssegundos).\n", tempo);
		printf("Prima ENTER para continuar.");
		getchar();
		
	}
	else printf("Cliente Inválido!\n");
	getchar();
	return;
}

/* QUERY 12 */
void query12(CatClientes ccs, CatProds cps, CatVendas cvs) {
	clock_t inicio, fim;
	double tempo;
	LstProds lista_p;
	LstClientes lista_c;
	int size = 0;

	print_menu();
	inicio = clock();
	lista_p = nao_comprados(cps, cvs);
	size = getSize_P(lista_p);
	printf("Produtos nunca comprados: %d\n", size);
	lista_c = compraram(ccs, cvs);
	size = getTam_C(ccs) - getSize_C(lista_c);
	printf("Clientes que nunca compraram: %d\n", size);
	fim = clock();
	tempo = (double) (fim - inicio)/CLOCKS_PER_SEC;
	printf("Cálculo efetuado em %.3f segundos.\n\nComando: ", tempo);
}

void interpretador(){
	int choice = -1;
	char *cmd = malloc(STRING);
	char path[100], choiceC[30];
	Boolean init = false;
	FILE *p;
	clock_t inicio, fim;
	double tempo;

	CatProds cps = initCatProds();
	CatClientes ccs = initCatClientes();
	CatVendas cvs = initCatVendas();
	CatVendas cvcl = initCatVendas();

	print_menu();
	printf("Comando: ");
	while (choice != 0) {
		if(scanf("%s", cmd) == 0) {
			printf("Opção Inválida!\nComando: ");
			choice = -1;
		}
		else {
			if(atoi(cmd) == 0 && strcmp(cmd, "0")) choice = -1;
			else choice = atoi(cmd);
			switch (choice) {
				case 1:		if (init == true) {
								removeCatProds(cps);
								cps = initCatProds();
								removeCatClientes(ccs);
								ccs = initCatClientes();
								removeCatVendas(cvs);
								cvs = initCatVendas();
								removeCatVendas(cvcl);
								cvcl = initCatVendas();
								init = false;
							}

							delScreen();
							printf("╔══════════════════════════════════════════════════════════════╗\n");
							printf("║ Que ficheiro de vendas pretende analisar:                    ║\n");
							printf("║ [1]. Vendas_1M.txt                                           ║\n");
							printf("║ [2]. Vendas_3M.txt                                           ║\n");
							printf("║ [3]. Vendas_5M.txt                                           ║\n");
							printf("╚══════════════════════════════════════════════════════════════╝\n\n");
							printf("Opção: ");
							if (scanf("%s", choiceC));
							choice = atoi(choiceC);
							switch(choice) {
								case 1: strcpy(path, "Vendas_1M.txt"); break;
								case 2: strcpy(path, "Vendas_3M.txt"); break;
								case 3: strcpy(path, "Vendas_5M.txt"); break;
								default: print_menu(); printf("Opção indisponível\nOpção: ");break;
							}
							choice = -1;
							if(!strcmp(choiceC, "1") || !strcmp(choiceC, "2") || !strcmp(choiceC, "3")) {
								delScreen();
								print_menu();
								printf("A abrir ficheiros...\n");

								cps = lerProdutos(cps, "Produtos.txt");
								ccs = lerClientes(ccs, "Clientes.txt");
							
								p = fopen (path, "rt");
								if (p == NULL) printf ("Erro ao abrir o ficheiro.\nComando: ");
								else {
									inicio = clock();
									cvs = lerVendas(p, path, cvs, cvcl, cps, ccs);
									fclose(p);
									fim = clock();
									tempo = (double) (fim - inicio)/CLOCKS_PER_SEC;
									printf("Tempo de Validação e leitura: %.3f segundos.\n\nComando: ", tempo);
								}
								init = true;
							}
							break;
				case 2:		if(init == false) printf("Catálogo de Produtos não inicializado.\nComando: ");
							else {
								verProdutos(cps);
								print_menu();
								printf("Comando: ");
							}
							break;
				case 3:		if (init == false) printf("Catálogo de Vendas não inicializado.\nComando: ");
							else faturacaoProduto(cvs, cps);
							print_menu();
							printf("Comando: ");
							break;
				case 4:		if (init == false) printf("Catálogo de Produtos não inicializado.\nComando: ");
							else {
								query4 (cps, cvs);
								print_menu ();
								printf("Comando: ");
							}
							break;
				case 5:		if (init == false) printf("Catálogo de Vendas não inicializado.\nComando: ");
							else {
								query5(cvcl);
								printf("Comando: ");
							}
							break;
				case 6:		if (init == false) printf("Catálogo de Vendas não inicializado.\nComando: ");
							else {
								query6 (cvs);
								delScreen();
								print_menu();
								printf ("Comando: ");
							}
							break;
				case 7:		if (init == false) printf("Catálogo de Vendas e Clientes não inicializados.\nComando: ");
							else {
								query7(ccs, cvcl);
								print_menu();
								printf("Comando: ");
							}
							break;
				case 8:		if (init == false) printf("Produtos e Vendas não inicializados.\n Comando: ");
							else query8(cvs);
							break;
				case 9: 	if (init == false) printf("Catálogo de Produtos e Vendas não inicializados.\nComando: ");
							else {
								query9(cvcl, ccs);
								delScreen();
								print_menu();
								printf("Comando: ");
							}
							break;
				case 10:	if (init == false) printf("Catálogo de Produtos e Vendas não inicializados.\nComando: ");
							else query10(cvs, cps);
							printf("Comando: ");
							break;
				case 11:	if (init == false) printf("Catálogo de Produtos e Vendas não inicializados.\nComando: ");
							else {
								query11(cvcl, ccs);
								delScreen();
								print_menu();
								printf("Comando: ");
							}
							break;
				case 12:	if (init == false) printf("Catálogo de Produtos e Clientes não inicializados.\nComando: ");
							else query12(ccs, cps, cvs);
							break;
				case 0:		if(init == true) {
								removeCatProds(cps);
								printf("Libertado espaço alocado para Produtos.\n");
								removeCatClientes(ccs);
								printf("Libertado espaço alocado para Clientes.\n");
								removeCatVendas(cvs);
								removeCatVendas(cvcl);
								printf("Libertado espaço alocado para Vendas.\n");
							}
							init = false;
							printf("A terminar processo.\n");
							break;
				default:	print_menu();
							printf("Opção Inválida!\nComando: ");
							break;
			}
		}
	}
	free(cmd);
}

int main() {
	interpretador();
	return 0;
}