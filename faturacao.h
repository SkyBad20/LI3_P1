#ifndef faturacaoh
#define faturacaoh
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avl.h"

typedef struct porFilial *CatVendas;
typedef struct porMes* MES;
typedef struct porTipo* TIPO;
typedef struct vendas *VENDAS;


/* Query 3 */
double auxFaturacaoGlobal (Tree t, char* produto);
double faturacaoGlobal (CatVendas cvs, int mes, char* produto, int tipo);
int contaProd_Mes (Tree t, char* produto);
int totalVendasProd_Mes (CatVendas cvs, int mes, char* produto, int tipo);
double faturacaoPorFil (CatVendas cvs, int mes, char* produto, int tipo, int filial);
int totalVendasPorFil (CatVendas cvs, int mes, char* produto, int tipo, int filial);
/* Query 6 */
int totalVendasIntMeses (CatVendas cvs, int mesI, int mesF);
double auxTotalFatIntMeses (Tree t);
double totalFatIntMeses (CatVendas cvs, int mesI, int mesF);
int auxTotalUnidadesIntMeses (Tree t);
int totalUnidadesIntMeses (CatVendas cvs, int mesI, int mesF);

VENDAS analisaVendas(char* venda);
CatVendas initCatVendas ();
void removeCatVendas(CatVendas cvs);
int getTam_V(CatVendas cvs);
Tree getTree(CatVendas cvs, int i, int j, int k);
CatVendas split_Filial(CatVendas cvs, VENDAS v);
CatVendas split_Filial_V2(CatVendas cvcl, VENDAS v);
MES split_Mes(MES filial, VENDAS v);
MES split_Mes_V2(MES filial, VENDAS v);
TIPO split_Tipo(TIPO mes, VENDAS v);
TIPO split_Tipo_V2(TIPO mes, VENDAS v);

/* Função que dada uma struct TIPO, retorna uma struct Tree representante do tipo N (caso index = 0) ou do tipo P (caso index = 1). */
Tree getTree_tipo(TIPO mes, int index);
/* Função que dada uma struct TIPO, retorna o tamanho da struct Tree representante do tipo N (caso index = 0) ou do tipo P (caso index = 1). */
int getTam_tipo(TIPO mes, int index);
/* Função que dada uma struct MES, retorna uma struct TIPO no mês 'index'. */
TIPO getTipo_mes(MES filial, int index);
/* Função que dada uma struct MES, retorna o tamanho da struct TIPO no mês 'index'. */
int getSize_mes(MES filial, int index);
/* Função que dada uma struct CatVendas, retorna uma struct MES na filial 'index'. */
MES getMes_filial(CatVendas cvcl, int index);
/* Função que dada uma struct CatVendas, retorna o tamanho da struct MES na filial 'index'. */
int getSize_fil(CatVendas cvcl, int index);
/* Função que dada uma struct CatVendas, uma filial, um mês e um tipo, devolve a struct Tree correspondente. */
Tree getTree(CatVendas cvs, int i, int j, int k);
/* Função que dada uma struct VENDAS, retorna o preço unitário dessa venda. */
double precoVenda(VENDAS v);
/* Função que dada uma struct VENDAS, retorna a quantidade dessa venda. */
int qtdVenda(VENDAS v);
/* Função que dada uma struct VENDAS, retorna o produto comprado nessa venda. */
char* prodVenda(VENDAS v);
/* Função que dada uma struct VENDAS, retorna o cliente que participou nessa venda. */
char* clienteVenda(VENDAS v);
/* Função que dada uma struct VENDAS, retorna o mês em que ocorreu essa venda. */
int mesVenda(VENDAS v);
/* Função que dada uma struct VENDAS, retorna o tipo dessa venda. */
char tipoVenda(VENDAS v);
/* Função que dada uma struct VENDAS, retorna em que filial ocorreu essa venda. */
int filialVenda(VENDAS v);


#endif