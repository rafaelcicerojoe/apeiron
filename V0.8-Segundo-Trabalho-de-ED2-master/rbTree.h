#ifndef RBT_H
#define RBT_H
#define RED 'R'
#define BLACK 'B'
#define TRUE 1
#define FALSE !1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Implementa��o da �vore Rubro-Negra
	Por: Eduardo Torres
	Aluno de Ci�ncia da Computa��o - UFMA
	rbt.h
*/

typedef struct _rbnode_{
	int key;
	char color;
	struct _rbnode_ * left;
	struct _rbnode_ * right;
	struct _rbnode_ * parent;
}RBNode;

RBNode * rbtNewNode(int key);
int rbtIsOnLeft(RBNode * node);
RBNode * rbtUncle(RBNode * node);
RBNode * rbtSibling(RBNode * node);
void rbtMoveDown(RBNode * node, RBNode * nParent);
int rbtHasRedChild(RBNode * node);
RBNode * rbtSuccessor(RBNode * node);
void rbtLeftRotate(RBNode ** rbt, RBNode * node);
void rbtRightRotate(RBNode ** rbt, RBNode * node);
void rbtSwapColors(RBNode * n1, RBNode * n2);
void rbtSwapValues(RBNode * n1, RBNode * n2);
void rbtFixRedRed(RBNode ** rbt, RBNode * node);
RBNode * rbtDeleteHelper(RBNode * node);
void rbtFixDoubleBlack(RBNode ** rbt, RBNode * node);
int rbtInsert(RBNode ** rbt, int key);
RBNode *RB_FILE_Insert(int dados);
RBNode * rbtSearch(RBNode ** rbt, int key);
void rbtDeleteNode(RBNode ** rbt, RBNode * node);
void rbtDeleteByVal(RBNode ** rbt, int key);
int rbtPreOrder(RBNode * rbt);
void rbtInOrder(RBNode * rbt);
void rbtPosOrder(RBNode * rbt);

void *Return_rbtSearch(RBNode ** rbt, int key);
RBNode *Return_Node_rbtSearch(RBNode ** rbt, int key);

#endif

