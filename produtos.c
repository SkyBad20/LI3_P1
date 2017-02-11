#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "produtos.h"
#define STRING 10
#define MAXBUFFERVENDAS 64

typedef struct prods{
	Tree catalogo[26];
	int tam[26];
} Produtos;

typedef struct conjProds{
	char** prodsLetra;
	int dim; 
} Conjunto_prods;

typedef struct prod{
	char* produto;
} PROD;

CatProds initCatProds(){
	CatProds cps = (CatProds) malloc(sizeof(struct prods));
	int i;
	for(i = 0; i < 26; i++){
		cps->catalogo[i] = NULL;
		cps->tam[i] = 0;
	}
	return cps;
}

Produto criaProduto(char* codigo){
	Produto prod = (Produto) malloc(sizeof(struct prod));
	prod->produto = malloc(STRING);
	strcpy(prod->produto, codigo);
	return prod;
}

Produto alteraProduto(Produto prod, char* codigo){
	strtok(codigo, "\n\r");
	strcpy(prod->produto, codigo);
	return prod;
}

void removeProduto(Produto prod){
	free(prod->produto);
	free(prod);
}

CatProds insereProduto(CatProds cps, Produto p){
	int index = *p->produto - 'A';
	cps->catalogo[index] = insertTree(cps->catalogo[index], p->produto);
	cps->tam[index]++;
	return cps; 
}

int TreeToList_P(int i, LstProds l, Tree a) {
  if(a){ 
  	if (getLeft(a)) i = TreeToList_P(i,l, getLeft(a));
   
   	*(l->prodsLetra+i) = malloc(STRING);
   	strcpy(*(l->prodsLetra+i), getInfo(a));
   	l->dim++;
   	i++;
   
   	if(getRight(a)) i = TreeToList_P(i,l, getRight(a));
   }
   return i;
}

LstProds prodsPorLetra(CatProds cps, char letra){
	int index;
	LstProds lista = (LstProds) malloc(sizeof(struct conjProds));
	index = letra - 'A';
	lista->prodsLetra = (char**) malloc(sizeof(char*) * cps->tam[index]);
	lista->dim = 0;
	
	TreeToList_P(0, lista, cps->catalogo[index]);
	return lista;
}

int totalProdutos(CatProds cps){
	int sum = 0;
	char letra;
	for (letra = 'A'; letra <= 90; letra++)
		sum += totalProdutosLetra(cps, letra);

	return sum;
}

int totalProdutosLetra(CatProds cps, char letra){
	int index = letra - 'A';
	return conta(cps->catalogo[index], 0);
}

LstProds setLstProds(LstProds l, int fator){
	l = (LstProds) malloc(sizeof(struct conjProds));
	l->prodsLetra = (char**) malloc(sizeof(char*) * fator);
	l->dim = 0;
	return l;
}

void freeLista_P(LstProds lista){
	int i;
	for(i = 0; i < lista->dim; i++)
   		free(*(lista->prodsLetra+i));

	free(lista->prodsLetra);
	free(lista);
}

void removeCatProds(CatProds cps){
	int i;
	for(i = 0; i < 26; i++)
		freeTree(cps->catalogo[i]);
	free(cps);
}

LstProds setArray_P(LstProds lista, char** x) {
	lista->prodsLetra = x;
	return lista;
}

char** getArray_P(LstProds lista){
	return lista->prodsLetra;
}

char* getElem_P(LstProds lista, int index){
	if(*(lista->prodsLetra+index) != NULL) return *(lista->prodsLetra+index);
	else return NULL;
}

LstProds setSize_P(LstProds lista, int tam) {
	lista->dim = tam;
	return lista;
}

int getSize_P(LstProds lista){
	if (lista) return lista->dim;
	else return -1;
}

int getTam_P(CatProds cps){
	int i, tam = 0;
	for (i = 0; i < 26; i++)
		tam += cps->tam[i];
	return tam;
}

int getIndex_P(Produto p){
	return *(p->produto) - 'A';
}

Boolean existeProduto(CatProds cps, char* p){
	int i = p[0] - 'A';
	return existeNodo(cps->catalogo[i], p);
}

/* Query nº 4 */ 

LstProds realoca_P(LstProds l){
	LstProds nova = (LstProds) malloc(sizeof(struct conjProds)); 
	int i, size = 2 * l->dim;
	nova->prodsLetra = (char**) malloc(sizeof(char*) * size);
	nova->dim = l->dim;
	for(i = 0; i < l->dim; i++){
		*(nova->prodsLetra+i) = malloc(STRING);
   		strcpy(*(nova->prodsLetra+i), *(l->prodsLetra+i));
	}
	freeLista_P(l);
	return nova;
}

LstProds nao_comprados(CatProds cps, CatVendas cvs){
	LstProds lista, naoComprados;
	int i, j, k, l, index = 0, size = 0;
	Boolean existe = false;

	lista = (LstProds) malloc(sizeof(struct conjProds));
	naoComprados = (LstProds) malloc(sizeof(struct conjProds));
	
	for (i = 0; i < 26; i++)
		size += cps->tam[i];

	lista->prodsLetra = (char**) malloc(sizeof(char*) * size);
	lista->dim = 0;

	for(i = 0; i < 26; i++)
		index = TreeToList_P(index, lista, cps->catalogo[i]);

	naoComprados->prodsLetra = (char**) malloc(sizeof(char*) * 500);
	naoComprados->dim = 0;
	
	for (i = 0; i < lista->dim; i++){
		existe = false;
		for (j = 0; j < 3 && existe == false; j++){
			for (k = 0; k < 12 && existe == false; k++){
				for (l = 0; l < 2 && existe == false; l++){
					existe = existeNodo(getTree(cvs, j, k, l), *(lista->prodsLetra+i));
				}
			}
		}
		if (existe == false){
			*(naoComprados->prodsLetra + naoComprados->dim) = malloc(STRING);
			strcpy(*(naoComprados->prodsLetra + naoComprados->dim), *(lista->prodsLetra+i));
			naoComprados->dim++;
		}
		if (naoComprados->dim == 500) naoComprados = realoca_P(naoComprados);
	}
	return naoComprados;
}

LstProds lista_produtos(CatProds cps){
	int i, index = 0, size = 0;
	LstProds l;
	l = (LstProds) malloc(sizeof(struct conjProds));

	for (i = 0; i < 26; i++)
		size += cps->tam[i];

	l->prodsLetra = (char**) malloc(sizeof(char*) * size);
	l->dim = 0;

	for(i = 0; i < 26; i++)
		index = TreeToList_P(index, l, cps->catalogo[i]);

	return l;

}

LstProds nao_comprados_porFil(LstProds lista, CatVendas cvs, int filial){
	LstProds naoComprados;
	int i, j, k;
	Boolean existe = false;

	naoComprados = (LstProds) malloc(sizeof(struct conjProds));
	naoComprados->prodsLetra = (char**) malloc(sizeof(char*) * 16000);
	naoComprados->dim = 0;
	
	for (i = 0; i < lista->dim; i++){
		existe = false;
		for (j = 0; j < 12 && existe == false; j++){
			for (k = 0; k < 2 && existe == false; k++){
				existe = existeNodo(getTree(cvs, filial, j, k), *(lista->prodsLetra+i));
			}
		}
		if (existe == false){
			*(naoComprados->prodsLetra + naoComprados->dim) = malloc(STRING);
			strcpy(*(naoComprados->prodsLetra + naoComprados->dim), *(lista->prodsLetra+i));
			naoComprados->dim++;
		}
		if (naoComprados->dim == 16000) naoComprados = realoca_P(naoComprados);
	}
	return naoComprados;
}