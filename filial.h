#ifndef filialh
#define filialh
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avl.h"
#include "faturacao.h"
#include "clientes.h"
#include "produtos.h"

typedef struct topVendas *Q10;

/* Query 5 */
int contaQtd (Tree t, char* cliente);
int totalQtd (CatVendas cvcl, int mes, int filial, char* cliente);
LstClientes comprouEmtodas(CatVendas cvcl, LstClientes ll);

LstClientes comprado_CodigoAUX (Tree t, char* produto, LstClientes compraram, int* size);
LstClientes comprado_Codigo (CatVendas cvs, char* produto, int filial, int tipo, LstClientes compraram);

/* Query 9 */
LstProds maisComprados_Mes(CatVendas cvcl, char* cliente, int mes);
LstProds sort_Dec(LstProds l, int* quantidades);

/* Query 10 */
LstProds ordena(Q10 lista);
void free_Q10(Q10 lista);
LstProds getProds_Q10(Q10 lista);
LstClientes getClientes_Q10(Q10 lista, int index);
int getQtd_Q10(Q10 lista, int index);
int pertence(LstProds lista, char* produto);
Boolean pertence_Cli(LstClientes lista, char* cliente);
LstClientes* init_cliPorProd(Q10 lista, int fator);
Q10 aux_func(Tree t, Q10 lista);
Q10 maisVendidos_porFil(CatVendas cvs, CatProds cps, int filial, int N);

/* Query 11 */
Boolean elem (LstProds lista, int* quantidades, char* p, int qtd);
LstProds prods_comprados(Tree t, char* cliente, LstProds lista, int* quantidades);
LstProds top3(LstProds lista, int* quantidades);
LstProds maisComprados(CatVendas cvcl, char* cliente);

#endif