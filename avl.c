#include <stdlib.h>
#include <string.h>
#include "avl.h"
#define STRING 10

typedef struct treenode {
	char* cliente;
	TreeInfo info;
	double preco;
	int qtd;
	Tree left;
	Tree right;
	int altura;
} TreeNode;

int max (int a, int b){
	return (a > b ? a : b);
}

int altura (Tree t){
	if (t)
		return t->altura;
	return 0;
}

int diferenca (Tree t1, Tree t2){
	return altura (t1) - altura (t2);
}

Tree rotateLeft (Tree t){
	Tree aux = t->right;
	t->right = aux->left;
	aux->left = t;
	t->altura = max (altura(t->right), altura(t->left)) + 1;
	aux->altura = max (altura(aux->right), altura(aux->left)) + 1;
	return aux;
}

Tree rotateRight (Tree t){
	Tree aux = t->left;
	t->left = aux->right;
	aux->right = t;
	t->altura = max (altura(t->right), altura(t->left)) + 1;
	aux->altura = max (altura(aux->right), altura(aux->left)) + 1;
	return aux;
}

Tree insertRight (Tree t, TreeInfo i){
	t->right = insertTree (t->right, i);
	if (diferenca (t->right, t->left) == 2){
		Tree aux = t->right;
		if (diferenca (aux->right, aux->left) > 0)
			return rotateLeft (t);
		t->right = rotateRight (t->right);
		return rotateLeft (t);
	}
	t->altura = max (altura(t->right), altura(t->left)) + 1;
	return t;
}

Tree insertLeft (Tree t, TreeInfo i){
	t->left = insertTree (t->left, i);
	if (diferenca (t->left, t->right) == 2){
		Tree aux = t->left;
		if (diferenca (aux->left, aux->right) > 0)
			return rotateRight (t);
		t->left = rotateLeft (t->left);
		return rotateRight (t);
	}
	t->altura = max (altura(t->left), altura(t->right)) + 1;
	return t;
}

Tree insertTree (Tree t, TreeInfo i){
	if (!t){
		t = (Tree) malloc (sizeof (struct treenode));
		t->info = malloc(STRING);
		strcpy(t->info, i);
		t->preco = -1;
		t->qtd = -1;
		t->left = t->right = NULL;
		t->altura = 1;
		return t;
	}
	if (strcmp (i, t->info) > 0)
		return insertRight (t, i);
	return insertLeft (t, i);
}

Tree insertTree_Fat(Tree t, TreeInfo i, char* c, double price, int unid){
	if (t == NULL){
		t = (Tree) malloc (sizeof (struct treenode));
		t->info = malloc(STRING);
		strcpy(t->info, i);
		t->cliente = malloc(STRING);
		strcpy(t->cliente, c);
		t->preco = price;
		t->qtd = unid;
		t->left = NULL;
		t->right = NULL;
		t->altura = 1;
		return t;
	}
	if (strcmp (i, t->info) > 0) return insertRight_Fat (t, i, c, price, unid);
	else return insertLeft_Fat (t, i, c, price, unid);
}

Tree insertTree_Plus(Tree t, TreeInfo i, char* c, double price, int unid){
	if (!t){
		t = (Tree) malloc (sizeof (struct treenode));
		t->info = malloc(STRING);
		strcpy(t->info, i);
		t->cliente = malloc(STRING);
		strcpy(t->cliente, c);
		t->preco = price;
		t->qtd = unid;
		t->left = NULL;
		t->right = NULL;
		t->altura = 1;
		return t;
	}
	if (strcmp (c, t->cliente) > 0)
		return insertRight_Plus (t, i, c, price, unid);
	return insertLeft_Plus (t, i, c, price, unid);
}

Tree insertRight_Plus (Tree t, TreeInfo i, char* c, double price, int unid){
	t->right = insertTree_Plus (t->right, i, c, price, unid);
	if (diferenca (t->right, t->left) == 2){
		Tree aux = t->right;
		if (diferenca (aux->right, aux->left) > 0)
			return rotateLeft (t);
		t->right = rotateRight (t->right);
		return rotateLeft (t);
	}
	t->altura = max (altura(t->right), altura(t->left)) + 1;
	return t;
}

Tree insertLeft_Plus (Tree t, TreeInfo i, char* c, double price, int unid){
	t->left = insertTree_Plus (t->left, i, c, price, unid);
	if (diferenca (t->left, t->right) == 2){
		Tree aux = t->left;
		if (diferenca (aux->left, aux->right) > 0)
			return rotateRight (t);
		t->left = rotateLeft (t->left);
		return rotateRight (t);
	}
	t->altura = max (altura(t->left), altura(t->right)) + 1;
	return t;
}


Tree insertRight_Fat(Tree t, TreeInfo info, char* c, double price, int unid) {
	t->right = insertTree_Fat (t->right, info, c, price, unid);
	if (diferenca (t->right, t->left) == 2){
		Tree aux = t->right;
		if (diferenca (aux->right, aux->left) > 0)
			return rotateLeft (t);
		t->right = rotateRight (t->right);
		return rotateLeft (t);
	}
	else {
		t->altura = max (altura(t->right), altura(t->left)) + 1;
		return t;
	}	
}

Tree insertLeft_Fat(Tree t, TreeInfo info, char* c, double price, int unid) {
	t->left = insertTree_Fat (t->left, info, c, price, unid);
	if (diferenca (t->left, t->right) == 2){
		Tree aux = t->left;
		if (diferenca (aux->left, aux->right) > 0)
			return rotateRight (t);
		t->left = rotateLeft (t->left);
		return rotateRight (t);
	}
	else {
		t->altura = max (altura(t->left), altura(t->right)) + 1;
		return t;
	}
}

Boolean existeNodo (Tree t, TreeInfo info){
        Tree aux = t;
        int i;
        while (aux){
            i = strcmp (info, aux->info);
            if (i == 0)
                return true;
            if (i > 0)
                aux = aux->right;
            else
                aux = aux->left;
        }
        return false;
}

Boolean existeNodo_v2 (Tree t, char* cliente){
        Tree aux = t;
        int i;
        while (aux){
            i = strcmp (cliente, aux->cliente);
            if (i == 0)
                return true;
            if (i > 0)
                aux = aux->right;
            else
                aux = aux->left;
        }
        return false;
}

Tree getLeft(Tree t){
	if (t == NULL) return NULL;
	else return t->left;
}

Tree getRight(Tree t){
	if (t == NULL) return NULL;
	else return t->right;	
}

Tree get_Tree_mem(Tree t) {
	t = (Tree) malloc (sizeof (struct treenode));
	return t;
}

char* getInfo(Tree t){
	if (t == NULL) return "";
	else return t->info;
}

double getPreco(Tree t){
	if (t == NULL) return -1;
	else return t->preco;
}

int getQtd(Tree t){
	if (t == NULL) return -1;
	else return t->qtd;
}

void freeTree (Tree t){
	if (t) {
		freeTree (t->left);
		freeTree (t->right);
		free (t);
	}
}

char* getCliente(Tree t){
	if (t == NULL) return "";
	else return t->cliente;
}

int conta (Tree t, int count){
	if (t) {
		count = conta (t->right, count);
		count++;
		count = conta (t->left, count);
	}
	return count;
}