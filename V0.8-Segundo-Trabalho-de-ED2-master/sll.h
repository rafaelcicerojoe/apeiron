#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "binaryTree.h"
#include "avlTree.h"
#include "rbTree.h"

#define TRUE 1
#define FALSE !1

#ifndef _SLL_H
#define _SLL_H

typedef struct sll sll;
typedef struct List List;

sll *sll_create(void *data);
List *list_create();

//------------ Mostrar,  Inserir, Procurar e Remover ----------//
int show_list(List *l);
int Insert(List *l, void *data);
int Insert_FILE(List *l, int dados);
int equals(void *a, void *b);
void *Search(List *l,void *data, int(equals(void*, void*)));
void *Remove(List *l,void *data, int(equals(void*, void*)));

//------------ Intersecçao, Subtração e União B -> A , Inserir e Remover ----------//
int Inter_sll_sll(List *l, List *l2);
int Union_sll_sll(List *l, List *l2);
int Remove_Equals_sll_sll(List *l, List *l2);

int Inter_sll_Hash(List *l, bank *checker);
int Union_sll_Hash(List *l, bank *checker);
int Remove_Equals_sll_Hash(List *l, bank *checker);

int Inter_sll_BTree(List *l, Tnode *t);
int Union_sll_BTree(List *l, Tnode *t);
int Remove_Equals_sll_BTree(List *l, Tnode *t);

int Inter_sll_AVLTree(List *l, Node *t);
int Union_sll_AVLTree(List *l, Node *t);
int Remove_Equals_sll_AVLTree(List*l, Node *t);

int Inter_sll_RBTree(List *l, RBNode *t);
int Union_sll_RBTree(List *l, RBNode *t);
int Remove_Equals_sll_RBTree(List *l, RBNode *t);

#endif
