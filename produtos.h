#ifndef produtosh
#define produtosh
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avl.h"
#include "faturacao.h"

typedef struct prods* CatProds;
typedef struct prod* Produto;
typedef struct conjProds* LstProds;

CatProds initCatProds();
CatProds insereProduto(CatProds cps, Produto p);
int totalProdutos(CatProds cps);
int totalProdutosLetra(CatProds cps, char letra);
LstProds prodsPorLetra(CatProds cps, char letra);
void removeCatProds(CatProds cps);
int treeToList_P(int i, LstProds l, Tree a);
LstProds lista_produtos(CatProds cps);
/* Função que aloca memória para uma LstProds, devolvendo-a. */
LstProds setLstProds(LstProds l, int fator);
LstProds nao_comprados();
/* Função que retorna o campo 'array' de uma LstProds. */
char** getArray_P(LstProds lista);
/* Função que devolve uma LstProds onde o campo 'prodsLetra' passa a ser igual a x. */
LstProds setArray_P(LstProds lista, char** x);
/* Função que devolve um elemento (String) do campo 'array' de uma LstProds no índice index. */
char* getElem_P(LstProds lista, int index);
void removeProduto(Produto prod);
Produto alteraProduto(Produto prod, char* codigo);
Produto criaProduto(char* codigo);
void freeLista_P(LstProds lista);
/* Função que devolve uma LstProds onde o campo 'dim' passa a ser igual a tam. */
LstProds setSize_P(LstProds lista, int tam);
/* Função que retorna o campo 'dim' de uma LstProds. */
int getSize_P(LstProds lista);
/* Função que retorna o tamanho total do CatProds. */
int getTam_P(CatProds cps);
/* Função que retorna o índice de um Produto, onde A é 0, B é 1, e assim sucessivamente. */
int getIndex_P(Produto p);
LstProds nao_comprados_porFil(LstProds l, CatVendas cvs, int filial);
Boolean existeProduto(CatProds cps, char* p);
LstProds realoca_P(LstProds l);

#endif