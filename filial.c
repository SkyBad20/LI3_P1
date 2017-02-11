#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filial.h"
#define STRING 10

/* Usada na resposta à query 10 */
typedef struct topVendas{
	LstProds prods;
	int* quantidades;
	LstClientes* cliPorProd;
} query10;

/* Query 5 */

int contaQtd (Tree t, char* cliente) {
	int total = 0;
	if (t != NULL) {
		if (strcmp (getCliente(t), cliente) == 0) {
			total = getQtd(t);
			total += contaQtd (getLeft(t), cliente) + contaQtd (getRight(t), cliente);
		}
		else total += contaQtd (getLeft(t), cliente) + contaQtd (getRight(t), cliente);
	}
	return total;
}

int totalQtd (CatVendas cvcl, int mes, int filial, char* cliente) {
	int i;
	int total = 0;
	Tree t = NULL;
	for (i = 0; i < 2; i++) {
		t = getTree (cvcl, filial, mes, i);
		total = contaQtd (t, cliente);
	}
	return total;
}

LstClientes comprouEmtodas(CatVendas cvcl, LstClientes ll){
	LstClientes lista;
	int i, j, k, l, size = 0, tam = 24000;
	Boolean comprou = false;

	lista = getMem();
	lista = setArray_C(lista, (char**) malloc(sizeof(char*) * tam));
	lista = setSize_C(lista, 0);

	for (i = 0; i < getSize_C(ll); i++){
		comprou = true;
		for (j = 0; j < 3 && comprou == true; j++){
			comprou = false;
			for (k = 0; k < 12 && comprou == false; k++){
				for (l = 0; l < 2 && comprou == false; l++){
					comprou = existeNodo_v2(getTree(cvcl, j, k, l), getElem_C(ll, i));
				}
			}
		}
		if (comprou == true){
			*(getArray_C(lista) + size) = malloc(STRING);
			strcpy(*(getArray_C(lista) + size), getElem_C(ll, i));
			size++;
			lista = setSize_C(lista, size);
		}
		if (size == tam) {
			tam *= 2;
			lista = realloc(lista, sizeof(char*) * tam);
		}
	}
	return lista;
}

/* Query 8 */
LstClientes comprado_CodigoAUX(Tree t, char* produto, LstClientes compraram, int *size) {
	char* info;
	if (t != NULL) {
		info = getInfo(t);
		if (strcmp(produto, info) == 0) {

			*(getArray_C(compraram) + *size) = malloc(STRING);
			strcpy(*(getArray_C(compraram) + *size), getCliente(t));
			(*size)++;
			if (*size % 10 == 0){
				char ** arr = getArray_C(compraram);
				void* tmp = realloc(arr, (*size + 10) * sizeof(char *));
				if (tmp) {
					arr = tmp;
					compraram = setArray_C(compraram, arr);
				}
				else printf("Erro no realloc\n");	
			}
			compraram = comprado_CodigoAUX(getLeft(t), produto, compraram, size);
			compraram = comprado_CodigoAUX(getRight(t), produto, compraram, size);
		}
		else {
			if(strcmp (produto, info) <= 0) compraram = comprado_CodigoAUX(getLeft(t), produto, compraram, size);
			else compraram = comprado_CodigoAUX(getRight(t), produto, compraram, size);
		}
	}
	return compraram;
}

LstClientes comprado_Codigo (CatVendas cvs, char* produto, int filial, int tipo, LstClientes compraram) {
 	Tree t;
 	int size = 0, mes;
	
	for(mes = 0; mes < 12; mes++) {
		t = getTree(cvs, filial, mes, tipo);
		compraram = comprado_CodigoAUX(t, produto, compraram, &size);
		compraram = setSize_C(compraram, size);
	}
	return compraram;
}

/* Fim da Query 8 */

/* Query 9 */

Boolean elem (LstProds lista, int* quantidades, char* p, int qtd){
	int i;
	for (i = 0; i < getSize_P(lista); i++)
		if (!strcmp(getElem_P(lista, i), p)){
			*(quantidades+i) += qtd;
			return true;
		}
	return false;
}


LstProds prods_comprados(Tree t, char* cliente, LstProds lista, int* quantidades){
	if (t) {
		char* prod = getInfo(t);
		int size = getSize_P(lista);
		int qtd = getQtd(t);

		if (!strcmp(cliente, getCliente(t))){

			if (elem(lista, quantidades, prod, qtd) == false){

				*(getArray_P(lista) + size) = malloc(STRING);
				strcpy(*(getArray_P(lista) + size), prod);
				*(quantidades + size) = qtd;
				size++;
				lista = setSize_P(lista, size);
		
				if ((getSize_P(lista) % 10) == 0){
					char ** arr = getArray_P(lista);
					void* tmp = realloc(arr, (size + 10) * sizeof(char *));
					if (tmp) {
						arr = tmp;
						lista = setArray_P(lista, arr);
						/*printf(":: %d\n",getSize_P(lista));
						printf("%d\n",size+10 );
						tmp = realloc(quantidades, (size + 10) * sizeof(int));
						if (tmp)
							quantidades = tmp;
						else printf("Erro no realloc_2\n");*/
					}				
					else printf("Erro no realloc_1\n");
				}

				lista = prods_comprados(getLeft(t), cliente, lista, quantidades);
			/*	lista = prods_comprados(getRight(t), cliente, lista, quantidades);*/
			}
		}
		else {
			if (strcmp(cliente, getCliente(t)) > 0) 
				lista = prods_comprados(getRight(t), cliente, lista, quantidades);
			else 
				lista = prods_comprados(getLeft(t), cliente, lista, quantidades);
		}
		
	}
	
	return lista;
}

LstProds sort_Dec(LstProds lista, int* quantidades){
	int i, j, aux;
	char* tmp = malloc(STRING);

	for(i = 0; i < getSize_P(lista) - 1; i++)
		for (j = i; j < getSize_P(lista); j++){
			if (*(quantidades+j) > *(quantidades+i)){
				aux = *(quantidades+i);
				*(quantidades+i) = *(quantidades+j);
				*(quantidades+j) = aux;
				strcpy(tmp, getElem_P(lista, i));
				strcpy(getElem_P(lista, i), getElem_P(lista, j));
				strcpy(getElem_P(lista, j), tmp);
			}
		}
	free(tmp);
	return lista;
}

LstProds maisComprados_Mes(CatVendas cvcl, char* cliente, int mes){
	int i, k;
	LstProds lista = NULL;
	int* quantidades; 
	lista = setLstProds(lista, 10);
	quantidades = malloc (75 * sizeof(int));

	for (i = 0; i < 3; i++)
			for (k = 0; k < 2; k++)
				lista = prods_comprados(getTree(cvcl, i, mes, k), cliente, lista, quantidades);

	lista = sort_Dec(lista, quantidades);
	free(quantidades);
	return lista;
}

/* Fim da query 9 */

/* Query 10 */
LstProds ordena(Q10 lista){
	int i, j, aux;
	char* tmp = malloc(STRING);
	LstClientes temp;

	for(i = 0; i < getSize_P(lista->prods) - 1; i++)
		for (j = i; j < getSize_P(lista->prods); j++){
			if (*(lista->quantidades+j) > *(lista->quantidades+i)){
				aux = *(lista->quantidades+i);
				*(lista->quantidades+i) = *(lista->quantidades+j);
				*(lista->quantidades+j) = aux;
				strcpy(tmp, getElem_P(lista->prods, i));
				strcpy(getElem_P(lista->prods, i), getElem_P(lista->prods, j));
				strcpy(getElem_P(lista->prods, j), tmp);
				temp = lista->cliPorProd[i];
				lista->cliPorProd[i] = lista->cliPorProd[j];
				lista->cliPorProd[j] = temp; 
			}
		}
	free(tmp);
	return lista->prods;
}

void free_Q10(Q10 lista){
	int i, size;
	size = getSize_P(lista->prods);
	freeLista_P(lista->prods);
	for (i = 0; i < size; i++){
		freeLista_C(lista->cliPorProd[i]);
	}
	free(lista->quantidades);
}

LstProds getProds_Q10(Q10 lista){
	if (lista) return lista->prods;
	else return NULL; 
}

LstClientes getClientes_Q10(Q10 lista, int index){
	if (lista) return lista->cliPorProd[index];
	else return NULL;
}

int getQtd_Q10(Q10 lista, int index){
	if (lista) return *(lista->quantidades + index);
	else return 0;
}

int pertence(LstProds lista, char* produto){
	int i;
	for (i = getSize_P(lista)-1; i >= 0; i--)
		if (!strcmp(getElem_P(lista, i), produto)) return i;
	return -1;
}

Boolean pertence_Cli(LstClientes lista, char* cliente){
	int i;
	for (i = 0; i < getSize_C(lista); i++) {
		if (!strcmp(getElem_C(lista, i), cliente)) return true;
	}
	return false;
}

LstClientes* init_cliPorProd(Q10 lista, int fator){
	int i;
	lista->cliPorProd = malloc(sizeof(LstClientes) * fator);
	for (i = 0; i < fator; i++)
		lista->cliPorProd[i] = setLstClientes(lista->cliPorProd[i]);
	return lista->cliPorProd;
}

Q10 aux_func(Tree t, Q10 lista){
	if (t){
		int size, qtd, tam, opt;
		char* info, *cliente;
		size = getSize_P(lista->prods);
		info = getInfo(t);
		qtd = getQtd(t);
		cliente = getCliente(t);
		
		opt = pertence(lista->prods, info);
		if (opt == -1){

			*(getArray_P(lista->prods) + size) = malloc(STRING);
			strcpy(*(getArray_P(lista->prods) + size), info);
			*(lista->quantidades + size) = qtd;
			if (pertence_Cli(lista->cliPorProd[size], cliente) == false){

				tam = getSize_C(lista->cliPorProd[size]);
				*(getArray_C(lista->cliPorProd[size]) + tam) = malloc(STRING);
				strcpy(*(getArray_C(lista->cliPorProd[size]) + tam), cliente);
				setSize_C(lista->cliPorProd[size], tam + 1);
			}
			size++;
			lista->prods = setSize_P(lista->prods, size);
		}
		else {
			*(lista->quantidades + opt) += qtd;
			if (pertence_Cli(lista->cliPorProd[opt], cliente) == false){
	
				tam = getSize_C(lista->cliPorProd[opt]);
				*(getArray_C(lista->cliPorProd[opt]) + tam) = malloc(STRING);
				strcpy(*(getArray_C(lista->cliPorProd[opt]) + tam), cliente);
				setSize_C(lista->cliPorProd[opt], tam + 1);
				if (((tam+1) % 10) == 0){
					char ** arr = getArray_C(lista->cliPorProd[opt]);
					void* tmp = realloc(arr, ((tam+1) + 10) * sizeof(char *));
					if (tmp) {
						arr = tmp;
						lista->cliPorProd[opt] = setArray_C(lista->cliPorProd[opt], arr);
					}
					else printf("Erro no realloc\n");
				}
			} 
		}
		lista = aux_func(getLeft(t), lista);
		lista = aux_func(getRight(t), lista);	
	}
	return lista; 
}

Q10 maisVendidos_porFil(CatVendas cvs, CatProds cps, int filial, int N){
	Q10 lista;
	int mes, tipo, size;
	size = totalProdutos(cps);
	
	lista = (Q10) malloc(sizeof(struct topVendas));
	lista->prods = setLstProds(lista->prods, size);
	lista->quantidades = malloc(sizeof(int) * size);
	lista->cliPorProd = init_cliPorProd(lista, size);

	for (mes = 0; mes < 12; mes++)
		for (tipo = 0; tipo < 2; tipo++){
			lista = aux_func(getTree(cvs, filial, mes, tipo), lista);
		}

	lista->prods = ordena(lista);
	return lista;
}

/* Fim da Query 10 */

/* Query 11 */

LstProds top3(LstProds lista, int* quantidades){
	int i, maior, segundo, terceiro;
	
	if (*(quantidades + 0) > *(quantidades + 1)){
		if (*(quantidades + 0) > *(quantidades + 2)){
			maior = 0;
			if (*(quantidades + 1) > *(quantidades + 2)){
				segundo = 1;
				terceiro = 2;
			}
			else { 
				segundo = 2;
				terceiro = 1;
			}
		}
		else {
			maior = 2;
			segundo = 0;
			terceiro = 1;
		}
	}
	else {
		if (*(quantidades + 2) > *(quantidades + 1)){
			maior = 2;
			segundo = 1;
			terceiro = 0;
		}
		else {
			maior = 1;
			if (*(quantidades + 0) > *(quantidades + 2)){
				segundo = 0;
				terceiro = 2;
			}
			else {
				segundo = 2;
				terceiro = 0;
			}
		}
	}

	for (i = 3; i < getSize_P(lista); i++){
		if (*(quantidades + i) > *(quantidades + maior)){
			terceiro = segundo;
			segundo = maior;
			maior = i;
		}
		else 
			if (*(quantidades + i) > *(quantidades + segundo)){
					terceiro = segundo;
					segundo = i;
				}
			else 
				if (*(quantidades + i) > *(quantidades + terceiro))
					terceiro = i;
	}

	strcpy(*getArray_P(lista), getElem_P(lista, maior));
	strcpy(*(getArray_P(lista)+1), getElem_P(lista, segundo));
	strcpy(*(getArray_P(lista)+2), getElem_P(lista, terceiro));
	return lista;
}

LstProds maisComprados(CatVendas cvcl, char* cliente){
	int i, j, k;
	LstProds lista = NULL;
	int* quantidades; 
	lista = setLstProds(lista, 10);
	quantidades = malloc (300 * sizeof(int));

	for (i = 0; i < 3; i++)
		for (j = 0; j < 12; j++)
			for (k = 0; k < 2; k++)
				lista = prods_comprados(getTree(cvcl, i, j, k), cliente, lista, quantidades);

	lista = top3(lista, quantidades);
	free(quantidades);
	return lista;
}

/* Fim da Query 11 */