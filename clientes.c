#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "clientes.h"
#define STRING 10
#define MAXBUFFERVENDAS 64

typedef struct clientes{
	Tree catalogo[26];
	int tam[26];
} Clientes;

typedef struct conjClientes{
	char** clientesLetra;
	int dim; 
} Conjunto_clientes;

typedef struct um_cliente{
	char* nome;
} CLIENTE;

CatClientes initCatClientes(){
	CatClientes ccs = (CatClientes) malloc(sizeof(struct clientes));
	int i;
	for(i = 0; i < 26; i++){
		ccs->catalogo[i] = NULL;
		ccs->tam[i] = 0;
	}
	return ccs;
}

CatClientes insereCliente(CatClientes ccs, Cliente c){
	int index = c->nome[0] - 'A';
	ccs->catalogo[index] = insertTree(ccs->catalogo[index], c->nome);
	ccs->tam[index]++;
	return ccs; 
}

Cliente criaCliente(char* codigo){
	Cliente cliente = (Cliente) malloc(sizeof(struct um_cliente));
	cliente->nome = malloc(STRING);
	strcpy(cliente->nome, codigo);
	return cliente;
}

Cliente alteraCliente(Cliente cliente, char* codigo){
	strtok(codigo, "\n\r");
	strcpy(cliente->nome, codigo);
	return cliente;
}

void removeCliente(Cliente cliente){
	free(cliente->nome);
	free(cliente);
}

int TreeToList_C(int i, LstClientes l, Tree a) {
  if(a){ 
  	if (getLeft(a)) i = TreeToList_C(i,l, getLeft(a));
   
   	*(l->clientesLetra+i) = malloc(STRING);
   	strcpy(*(l->clientesLetra+i), getInfo(a));
   	l->dim++;
   	i++;
   
   	if(getRight(a)) i = TreeToList_C(i,l, getRight(a));
   }
   return i;
}

LstClientes lista_clientes(CatClientes ccs){
	int i, index = 0, size = 0;
	LstClientes l;
	l = (LstClientes) malloc(sizeof(struct conjClientes));

	for (i = 0; i < 26; i++)
		size += ccs->tam[i];

	l->clientesLetra = (char**) malloc(sizeof(char*) * size);
	l->dim = 0;

	for(i = 0; i < 26; i++)
		index = TreeToList_C(index, l, ccs->catalogo[i]);

	return l;

}

LstClientes clientesPorLetra(CatClientes ccs, char letra){
	int index;
	LstClientes lista = (LstClientes) malloc(sizeof(struct conjClientes));
	index = letra - 'A';
	lista->clientesLetra = (char**) malloc(sizeof(char*) * ccs->tam[index]);
	lista->dim = 0;
	
	TreeToList_C(0, lista, ccs->catalogo[index]);
	return lista;
}

Boolean existeCliente(CatClientes ccs, char *c){
	int i = c[0] - 'A';

	return existeNodo(ccs->catalogo[i], c);
}

int totalClientes(CatClientes ccs){
	int sum = 0;
	char letra;
	for (letra = 'A'; letra <= 90; letra++)
		sum += totalClientesLetra(ccs, letra);

	return sum;
}

int totalClientesLetra(CatClientes ccs, char letra){
	int index = letra - 'A';
	return conta(ccs->catalogo[index], 0);
}

void removeCatClientes(CatClientes ccs){
	int i;
	for(i = 0; i < 26; i++)
		freeTree(ccs->catalogo[i]);
	free(ccs);
}

void freeLista_C(LstClientes lista){
	int i;
	for(i = 0; i < lista->dim; i++)
   		free(*(lista->clientesLetra+i));
	free(lista->clientesLetra);
	free(lista);
}

char* getElem_C(LstClientes lista, int index){
	return *(lista->clientesLetra+index);
}

int getSize_C(LstClientes lista){
	return lista->dim;
}

LstClientes setSize_C(LstClientes lista, int tam) {
	lista->dim = tam;
	return lista;
}

int getTam_C(CatClientes ccs){
	int i, tam = 0;
	for (i = 0; i < 26; i++)
		tam += ccs->tam[i];
	return tam;
}

int getIndex_C(Cliente c){
	return *(c->nome) - 'A';
}

LstClientes getMem(){
	LstClientes lista = (LstClientes) malloc(sizeof(struct conjClientes));
	return lista;
}

char** getArray_C(LstClientes lista){
	return lista->clientesLetra;
}

LstClientes setLstClientes(LstClientes l){
	l = (LstClientes) malloc(sizeof(struct conjClientes));
	l->clientesLetra = (char**) malloc(sizeof(char*) * 10);
	l->dim = 0;
	return l;
}


LstClientes setArray_C(LstClientes lista, char** x) {
	lista->clientesLetra = x;
	return lista;
}

LstClientes realoca_C(LstClientes l){
	LstClientes nova = (LstClientes) malloc(sizeof(struct conjClientes)); 
	int i, size = 2 * l->dim;
	nova->clientesLetra = (char**) malloc(sizeof(char*) * size);
	nova->dim = l->dim;
	for(i = 0; i < l->dim; i++){
		*(nova->clientesLetra+i) = malloc(STRING);
   		strcpy(*(nova->clientesLetra+i), *(l->clientesLetra+i));
	}
	freeLista_C(l);
	return nova;
}

LstClientes compraram(CatClientes ccs, CatVendas cvcs){
	LstClientes lista, naoCompraram;
	int i, j, k, l, index = 0, size = 0;
	Boolean existe = false;

	lista = (LstClientes) malloc(sizeof(struct conjClientes));
	naoCompraram = (LstClientes) malloc(sizeof(struct conjClientes));
	
	for (i = 0; i < 26; i++)
		size += ccs->tam[i];

	lista->clientesLetra = (char**) malloc(sizeof(char*) * size);
	lista->dim = 0;

	for(i = 0; i < 26; i++)
		index = TreeToList_C(index, lista, ccs->catalogo[i]);

	naoCompraram->clientesLetra = (char**) malloc(sizeof(char*) * 9000);
	naoCompraram->dim = 0;
	
	for (i = 0; i < lista->dim; i++){
		existe = false;
		for (j = 0; j < 3 && existe == false; j++){
			for (k = 0; k < 12 && existe == false; k++){
				for (l = 0; l < 2 && existe == false; l++){
					existe = existeNodo(getTree(cvcs, j, k, l), *(lista->clientesLetra+i));
				}
			}
		}
		if (existe == false){
			*(naoCompraram->clientesLetra + naoCompraram->dim) = malloc(STRING);
			strcpy(*(naoCompraram->clientesLetra + naoCompraram->dim), *(lista->clientesLetra+i));
			naoCompraram->dim++;
		}
		if (naoCompraram->dim == 9000) naoCompraram = realoca_C(naoCompraram);
	}
	return naoCompraram;
}