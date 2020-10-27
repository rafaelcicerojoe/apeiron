#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE !1
#ifndef _AVLTREE_H_
#define _AVLTREE_H_

typedef struct node_tree Node;
Node* createAvlTree(int dados);
int max(int a, int b);
int height(Node *N);
Node *newNode(int key);
Node *rightRotate(Node *y);
Node *leftRotate(Node *x);
int getBalance(Node *N);
Node *insertNode(Node *node, int key);
Node *minValueNode(Node *node);
Node *removeSpec(Node *root, int key);
int preOrdem(Node *root);
int compara(int a, Node *b);
void interBA(Node *a, Node *b);
Node *inserirBA(Node *a, Node *b);
Node *removeBA(Node *a, Node *b);

void *avlSearch(Node *t, void *key, int (cmp)(void *, void*));

#endif // _AVLTREE_H_
