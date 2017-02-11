#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "faturacao.h"
#define MAXBUFFERVENDAS 64

typedef struct porFilial {
	MES filiais[3];
	int size_fil[3];
} POR_FIL;

typedef struct porMes {
	TIPO meses[12];
	int size_mes[12];
} POR_MES;

/* tipo[0] = N ; tipo[1] = P */
typedef struct porTipo {
	Tree tipo[2];
	int tam[2];
} POR_TIPO;

/* Para separar a informação das vendas */
typedef struct vendas {
	char prod [7];
	float preco;
	int qtd;
	char tipo;
	char cliente [6];
	int mes;
	int filial;
} Venda;

CatVendas initCatVendas () {
	CatVendas cvs = (CatVendas) malloc(sizeof(struct porFilial));
	int i, j, k;
	for(i = 0; i < 3; i++){
		cvs->filiais[i] = (MES) malloc (sizeof(struct porMes));
		cvs->size_fil[i] = 0;
		for (j = 0; j < 12; j++) {
			cvs->filiais[i]->meses[j] = (TIPO) malloc (sizeof (struct porTipo));
			cvs->filiais[i]->size_mes[j] = 0;
			for (k = 0; k < 2; k++) {
				cvs->filiais[i]->meses[j]->tipo[k] = NULL;
				cvs->filiais[i]->meses[j]->tam[k] = 0;
			}
		}
	}
	return cvs;
}

void removeCatVendas(CatVendas cvs){
	int i, j, k;
	for(i = 0; i < 3; i++){
		for (j = 0; j < 12; j++){
			for (k = 0; k < 2; k++){
				freeTree(cvs->filiais[i]->meses[j]->tipo[k]);
			}
			free(cvs->filiais[i]->meses[j]);
		}
		free(cvs->filiais[i]);
	}
	free(cvs);			
}

TIPO split_Tipo(TIPO mes, VENDAS v){
	switch (v->tipo) {
		case 'N':	mes->tipo[0] = insertTree_Fat(mes->tipo[0], v->prod, v->cliente, v->preco, v->qtd);
				  	mes->tam[0]++;
				  	break;
		case 'P': 	mes->tipo[1] = insertTree_Fat(mes->tipo[1], v->prod, v->cliente, v->preco, v->qtd);
				  	mes->tam[1]++;
				  	break;
		default:	return NULL;
					break;
	}
	return mes;
}

MES split_Mes(MES filial, VENDAS v){
	filial->meses[v->mes-1] = split_Tipo(filial->meses[v->mes-1], v);
	if (filial->meses[v->mes-1] == NULL) printf("Erro2\n");
	filial->size_mes[v->filial-1]++;
	return filial;
}

CatVendas split_Filial(CatVendas cvs, VENDAS v){
	cvs->filiais[v->filial-1] = split_Mes(cvs->filiais[v->filial-1], v);
	if (cvs->filiais[v->filial-1] == NULL) printf("Erro1\n");
	cvs->size_fil[v->filial-1]++;
	return cvs;
}

TIPO split_Tipo_V2(TIPO mes, VENDAS v){
	switch (v->tipo) {
		case 'N':	mes->tipo[0] = insertTree_Plus(mes->tipo[0], v->prod, v->cliente, v->preco, v->qtd);
				  	mes->tam[0]++;
				  	break;
		case 'P': 	mes->tipo[1] = insertTree_Plus(mes->tipo[1], v->prod, v->cliente, v->preco, v->qtd);
				  	mes->tam[1]++;
				  	break;
		default:	return NULL;
					break;
	}
	return mes;
}

MES split_Mes_V2(MES filial, VENDAS v){
	filial->meses[v->mes-1] = split_Tipo_V2(filial->meses[v->mes-1], v);
	if (filial->meses[v->mes-1] == NULL) printf("Erro2\n");
	filial->size_mes[v->filial-1]++;
	return filial;
}

CatVendas split_Filial_V2(CatVendas cvs, VENDAS v){
	cvs->filiais[v->filial-1] = split_Mes_V2(cvs->filiais[v->filial-1], v);
	if (cvs->filiais[v->filial-1] == NULL) printf("Erro1\n");
	cvs->size_fil[v->filial-1]++;
	return cvs;
}

VENDAS analisaVendas(char* venda){
	VENDAS aux = (VENDAS) malloc(sizeof(struct vendas));
	printf ("CHEGOU1\n");
	strtok(venda, "\n\r");
	strcpy(aux->prod, strtok(venda, " "));
	aux->preco = atof(strtok(NULL, " "));
	aux->qtd = atoi(strtok(NULL, " "));
	aux->tipo = *(strtok(NULL, " "));
	strcpy(aux->cliente,strtok(NULL, " "));
	aux->mes = atoi(strtok(NULL, " "));
	aux->filial = atoi(strtok(NULL, " "));
	return aux;
}

/* Query 3 */
double auxFaturacaoGlobal (Tree t, char* produto) {
	double total = 0;
	if (t != NULL) {
		if (strcmp (getInfo(t), produto) == 0) {
			total = getPreco(t) * getQtd(t);
			total += auxFaturacaoGlobal (getLeft(t), produto) + auxFaturacaoGlobal (getRight(t), produto);
		}
		else total += auxFaturacaoGlobal (getLeft(t), produto) + auxFaturacaoGlobal (getRight(t), produto);
	}
	return total;
}

double faturacaoGlobal (CatVendas cvs, int mes, char* produto, int tipo) {
	double faturacao = 0;
	int i;
	for (i = 0; i < 3; i++) faturacao += auxFaturacaoGlobal (cvs->filiais[i]->meses[mes-1]->tipo[tipo], produto);
	return faturacao;
}

int contaProd_Mes (Tree t, char* produto) {
	double total = 0;
	if (t != NULL) {
		if (strcmp (getInfo(t), produto) == 0) {
			total = 1 + contaProd_Mes (getLeft(t), produto) + contaProd_Mes (getRight(t), produto);
		}
		else total = contaProd_Mes (getLeft(t), produto) + contaProd_Mes (getRight(t), produto);
	}
	return total;
}

int totalVendasProd_Mes (CatVendas cvs, int mes, char* produto, int tipo) {
	int total = 0, i;
	for (i = 0; i < 3; i++) total += contaProd_Mes (cvs->filiais[i]->meses[mes-1]->tipo[tipo], produto);
	return total;
}

double faturacaoPorFil (CatVendas cvs, int mes, char* produto, int tipo, int filial) {
	double faturacao = auxFaturacaoGlobal (cvs->filiais[filial-1]->meses[mes-1]->tipo[tipo], produto);
	return faturacao;
}

int totalVendasPorFil (CatVendas cvs, int mes, char* produto, int tipo, int filial) {
	int total = 0;
	total += contaProd_Mes (cvs->filiais[filial-1]->meses[mes-1]->tipo[tipo], produto);
	return total;
}
/* Fim da Query 3 */

/* Query 6 */
int totalVendasIntMeses (CatVendas cvs, int mesI, int mesF) {
	int total = 0;
	int i, j, k;
	for (i = 0; i < 3; i++) {
		for (j = mesI - 1; j < mesF; j++) {
			for (k = 0; k < 2; k++) total += cvs->filiais[i]->meses[j]->tam[k];
		}
	}
	return total;
}

double auxTotalFatIntMeses (Tree t) {
	double total = 0;
	if (t != NULL) {
		total = getPreco(t) * getQtd(t);
		total += auxTotalFatIntMeses (getLeft(t)) + auxTotalFatIntMeses (getRight(t));
	}
	return total;
}

double totalFatIntMeses (CatVendas cvs, int mesI, int mesF) {
	double total = 0;
	int i, j, k;
	for (i = 0; i < 3; i++) {
		for (j = mesI - 1; j < mesF; j++) {
			for (k = 0; k < 2; k++) {
				total += auxTotalFatIntMeses (cvs->filiais[i]->meses[j]->tipo[k]);
			}
		}
	}
	return total;
}

int auxTotalUnidadesIntMeses (Tree t) {
	int total = 0;
	if (t != NULL) {
		total = getQtd(t);
		total += auxTotalUnidadesIntMeses (getLeft(t)) + auxTotalUnidadesIntMeses (getRight(t));
	}
	return total;
}

int totalUnidadesIntMeses (CatVendas cvs, int mesI, int mesF) {
	int total = 0;
	int i, j, k;
	for (i = 0; i < 3; i++) {
		for (j = mesI - 1; j < mesF; j++) {
			for (k = 0; k < 2; k++) {
				total += auxTotalUnidadesIntMeses (cvs->filiais[i]->meses[j]->tipo[k]);
			}
		}
	}
	return total;
}
/* Fim da Query 6 */

int aQtd(CatVendas cvs){
	return getQtd(cvs->filiais[1]->meses[5]->tipo[0]);
}

int getTam_V(CatVendas cvs){
	int i, tam = 0;
	for (i = 0; i < 3; i++)
		tam += cvs->size_fil[i];
	return tam;
}

Tree getTree(CatVendas cvs, int i, int j, int k){
	if (cvs == NULL) return NULL;
	return cvs->filiais[i]->meses[j]->tipo[k];
}

int getTam_tipo(TIPO mes, int index){
	return mes->tam[index];
}

Tree getTree_tipo(TIPO mes, int index){
	if (mes == NULL) return NULL;
	return mes->tipo[index];
}

TIPO getTipo_mes(MES filial, int index){
	if (filial == NULL) return NULL;
	return filial->meses[index];
}

MES getMes_filial(CatVendas cvcl, int index){
	if (cvcl == NULL) return NULL;
	return cvcl->filiais[index];
}

int getSize_fil(CatVendas cvcl, int index){
	return cvcl->size_fil[index];
}

double precoVenda(VENDAS v){
	return v->preco;
}

int qtdVenda(VENDAS v){
	return v->qtd;
}

char tipoVenda(VENDAS v){
	return v->tipo;
}

char* prodVenda(VENDAS v){
	return v->prod;
}

char* clienteVenda(VENDAS v){
	return v->cliente;
}

int mesVenda(VENDAS v){
	return v->mes;
}

int filialVenda(VENDAS v){
	return v->filial;
}