#ifndef clientesh
#define clientesh
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avl.h"
#include "faturacao.h"

typedef struct clientes* CatClientes;
typedef struct um_cliente* Cliente;
typedef struct conjClientes* LstClientes;

CatClientes initCatClientes();
CatClientes insereCliente(CatClientes ccs, Cliente c);
int totalClientes(CatClientes ccs);
int totalClientesLetra(CatClientes ccs, char letra);
LstClientes clientesPorLetra(CatClientes ccs, char letra);
void removeCatClientes(CatClientes ccs);
int treeToList_C(int i, LstClientes l, Tree a);
LstClientes lista_clientes(CatClientes ccs);
/* Função que aloca memória para uma LstClientes, devolvendo-a. */
LstClientes setLstClientes(LstClientes l);
LstClientes efetuouCompras();
/* Função que retorna o campo 'dim' de uma LstClientes. */
int getSize_C(LstClientes lista);
void freeLista_C(LstClientes lista);
/* Função que devolve um elemento (String) do campo 'array' de uma LstClientes no índice index. */
char* getElem_C(LstClientes lista, int index);
void removeCliente(Cliente cliente);
Cliente criaCliente(char* codigo);
Cliente alteraCliente(Cliente cliente, char* codigo);
/* Função que retorna o tamanho total do CatClientes. */
int getTam_C(CatClientes ccs);
/* Função que aloca espaço para a struct LstClientes. */
LstClientes getMem();
/* Função que retorna o campo 'array' de uma LstClientes. */
char** getArray_C(LstClientes lista);
/* Função que retorna o índice de um Cliente, onde A é 0, B é 1, e assim sucessivamente. */
int getIndex_C(Cliente c);
/* Função que devolve uma LstClientes onde o campo 'clientesLetra' passa a ser igual a x. */
LstClientes setArray_C(LstClientes lista, char** x);
/* Função que devolve uma LstClientes onde o campo 'dim' passa a ser igual a tam. */
LstClientes setSize_C(LstClientes lista, int tam);
Boolean existeCliente(CatClientes ccs, char* c);
LstClientes realoca_C(LstClientes c);
LstClientes compraram(CatClientes ccs, CatVendas cvcs);


#endif