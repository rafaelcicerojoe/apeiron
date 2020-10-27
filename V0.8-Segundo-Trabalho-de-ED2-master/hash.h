#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE !1

#ifndef _Hash_H
#define _Hash_H

typedef struct nb bank;

int hash_key(int aux);
bank *Data_Create(int n);
//------------ Printar,  Inserir, Procurar e Remover ----------//
int Hash_insert(bank *checker, void *aux, int checker_tam);
void Hash_FILE_Insert(bank *Checker, int dados);
void *Hash_Search(bank *checker, void *aux, int checker_tam);
void *Hash_Remove(bank *checker, void *aux, int checker_tam);
int Show_Hash_list(bank *checker,int checker_tam);
#endif
