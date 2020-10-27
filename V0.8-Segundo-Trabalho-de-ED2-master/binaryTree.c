#include "binaryTree.h"

typedef struct _tree_{
  struct _tree_ *l, *r;
  void *data;

}Tnode;



int cmp(void *a , void *b){
  if(a > b){
    return -1;
  }else if (a == b){

    return 0;
  }else{

    return 1;
  }

}
Tnode *abCreate(void *data){
    Tnode *t = (Tnode*)malloc(sizeof(Tnode));
    if(t != NULL){
        t->l = NULL;
        t->r = NULL;
        t->data = data;
        return t;
    }
}
//Seleciona o arquivo que tera seus dados extraidos//

void abp_FILE_Insert(Tnode *t, int dados){


   FILE *arq;
    if(dados == 1){
        arq = fopen("dados/file1000.txt","r");
        printf(".");
    }else if(dados == 2){
        arq = fopen("dados/file5000.txt","r");
    }else if( dados == 3){
      arq = fopen("dados/file10000.txt","r");

    }else if(dados == 4){
      arq = fopen("dados/file50000.txt","r");
    }else if(dados == 5){
      arq = fopen("dados/file100000.txt","r");
    }
    else if(dados == 6){
      arq = fopen("dados/file500000.txt","r");
    }else if(dados == 7){
      arq = fopen("dados/file1000000.txt","r");
    }
    char aux[50];

    while(fgets(aux, 20,arq) != NULL){
      char tmp[20];
      int tmp_aux = 0;
      for(int i = 0 ; aux[i] != '\0' ; i++){

        if(aux[i] != ','){
          if(aux[i] != '[' && aux[i] != ']' && aux[i] != ' '){
          tmp[tmp_aux] = aux[i];

          tmp_aux++;

          }
        }else{
          tmp[tmp_aux] = '\0';

          int nmb = atoi(tmp);
          abInsert(t, nmb, cmp);

          tmp_aux = 0;
        }
      }

    }

    fclose(arq);


}

//Pesquisa na arvore o elemento, tempo O(logn);
void *abSearch(Tnode *t, void *key, int (cmp)(void *, void*)){
  if(t != NULL){
    int stat = cmp(key, t->data);

    if(stat == 0){

        return t->data;
    }else if (stat < 0 ){

      return abSearch(t->r ,key,  cmp);

    }else {

      return abSearch(t->l, key, cmp);
    }
  }

   return NULL;
}

Tnode *abInsert(Tnode *t, void *data, int(*cmp)(void *, void *)){
  int stat; Tnode *newt;

  if(t != NULL){

    stat = cmp(data , t->data);

    if(stat > 0){
      t->l = abInsert(t->l, data, cmp);
    }else if(stat < 0){
      t->r = abInsert(t->r, data, cmp);
    }else{
      return t;
    }

  }else{

    newt = (Tnode*)malloc (sizeof(Tnode));
    if(newt != NULL){
      newt->data = data;
      newt->l = NULL;
      newt->r = NULL;

      return newt;
    }
  }

}
Tnode *abMenor(Tnode *t, int (*cmp)(void*, void*)){
    Tnode* m = NULL, *m2= NULL;
    if(t != NULL){
        m = t;
        m2 = abMenor(t->l, cmp);
        if(m2 != NULL){
            if(m->data <= m2->data){
                return m;
            }
            return m2;
        }
        return m;
    }
    return NULL;
}
int abRemove(Tnode *t, void *data, int(*cmp)(void *, void*)){
    int stat; Tnode *newt;

  if(t != NULL){

    stat = cmp(data , t->data);

    if(stat > 0){

        t->l = abRemove(t->l, data, cmp);


    }else if(stat < 0){

      t->r = abRemove(t->r, data, cmp);


    }else{

        if((t->l == NULL) || (t->r == NULL)){
            Tnode * temp = t->l ? t->l : t->r;
            if (temp == NULL){
                temp = t;
                t = NULL;
            }
            else{
                *t = *temp;
            }
            free(temp);
        }
        else
        {
            Tnode* temp = abMenor(t->r, cmp);
            t->data = temp->data;
            t->r = abRemove(t->r, temp->data, cmp);
        }
    }

        return t;


    }
}


void Simetrica(Tnode *t){

    if(t != NULL){
        Simetrica(t->l);
        printf("%d ", t->data);
        Simetrica(t->r);
    }
}

int Pre_ordem(Tnode *t){

    if(t != NULL){
      int quant = 0;
        printf("%d ", t->data);
        quant += Pre_ordem(t->l);
        quant += Pre_ordem(t->r);
        quant++;
        return quant;
    }
    return 0;
}
void Pos_ordem(Tnode *t){

    if(t != NULL){
        Pos_ordem(t->l);
        Pos_ordem(t->r);
        printf("%d ", t->data);
    }
}

