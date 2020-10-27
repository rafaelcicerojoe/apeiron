#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"
#define TRUE 1
#define FALSE !1

#ifndef _Binary_Tree_H
#define _Binary_Tree_H

typedef struct _tree_ Tnode;

int cmp(void *a , void *b);

Tnode *abCreate(void *data);
void *abSearch(Tnode *t, void *key, int (cmp)(void *, void*));
Tnode *abInsert(Tnode *t, void *data, int(*cmp)(void *, void *));
void abp_FILE_Insert(Tnode *t, int dados);
Tnode *abMenor(Tnode *t, int (*cmp)(void*, void*));
int abRemove(Tnode *t, void *data, int(*cmp)(void *, void*));
void Simetrica(Tnode *t);
int Pre_ordem(Tnode *t);
void Pos_ordem(Tnode *t);
#endif