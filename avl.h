#ifndef avlh
#define avlh

typedef enum bool { true , false } Boolean;
typedef char* TreeInfo;
typedef struct treenode *Tree;

int max (int a, int b);
int altura (Tree t);
int diferenca (Tree t1, Tree t2);
Tree rotateRight(Tree t);
Tree rotateLeft(Tree t); 
Tree insertTree(Tree t, TreeInfo i);
Tree insertRight(Tree t, TreeInfo i); 
Tree insertLeft(Tree t, TreeInfo i) ;
Tree insertTree_Fat(Tree t, TreeInfo i, char* c, double price, int unid);
Tree insertLeft_Fat(Tree t, TreeInfo i, char* c, double price, int unid);
Tree insertRight_Fat(Tree t, TreeInfo i, char* c, double price, int unid);
Tree insertTree_Plus(Tree t, TreeInfo i, char* c, double price, int unid);
Tree insertRight_Plus(Tree t, TreeInfo i, char* c, double price, int unid);
Tree insertLeft_Plus(Tree t, TreeInfo i, char* c, double price, int unid);
/* Função retorna a árvore à direita de t */
Tree getRight(Tree t);
/* Função que retorna a árvore à esquerda de t */
Tree getLeft(Tree t);
/* Função que aloca espaço para a struct Tree */
Tree get_Tree_mem(Tree t);
/* Função que retorna a Info da Tree t (Produto) */
char* getInfo(Tree t);
/* Função que retorna o preço */
double getPreco(Tree t);
/* Função que retorna a quantidade */
int getQtd(Tree t);
/* Função que retorna o cliente */
char* getCliente(Tree t);
Boolean existeNodo(Tree t, TreeInfo info);
Boolean existeNodo_v2 (Tree t, char* cliente);
int conta(Tree a, int count);
void freeTree(Tree a);

#endif