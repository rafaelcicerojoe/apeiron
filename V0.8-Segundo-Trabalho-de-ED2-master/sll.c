#include "sll.h"
#include "binaryTree.h"
#include "avlTree.h"
#include "rbTree.h"


/* Estrutura Primaria chamada List que guarda o primeiro da lista "List", ja "sll" serao as structs
para as novas listas adicionadas.*/

typedef struct sll{
  struct sll *next, *prev;
  void *data;
}sll;

typedef struct List{
  struct sll *first;
}List;

// Cria a lista //
sll *sll_create(void *data){
  sll *t = (sll*)malloc(sizeof(sll));
  if(t!= NULL){
    t->data = data;
    t->prev = t->next = NULL;
    return t;
  }
  return NULL;

}

// Cria o primeiro elemento da lista //
List *list_create(){
  List *l = (List*)malloc(sizeof(List));
  if(l != NULL){
      l->first = NULL;
      return l;
  }
  return NULL;

}

// Mostra toda a lista //
int show_list(List *l){
  if(l!= NULL){
    if(l->first != NULL){
      sll *aux = l->first;
      int quant = 1;
      printf("%d ", aux->data);

      while(aux->next != l->first){
        quant++;
        aux = aux->next;
        printf("%d ", aux->data);
      }
      //quantidade de retornados
      return quant;
    }else{
    printf("Empty list \n");

    }
  }else{
    printf("List not created \n");

  }
  return 0;

}

// Adiciona novos dados nao repetidos na lista , O(n)//

int Insert(List *l, void *data){

  if(l != NULL){
    if(l->first != NULL){

       sll *aux = l->first;

      if(aux->next != l->first){

        while(aux->next != l->first && aux->data != data){
          aux = aux->next;

        }
        if(aux->data == data){
          return FALSE;
        }
        sll *t = sll_create(data);

        aux->next = t;

        t->prev = aux;

        t->next = l->first;

        l->first->prev = t;


        return TRUE;
      }else{
        sll *t =sll_create(data);

        if(t != NULL){
          aux->next = t;
          t->prev = aux;
          t->next = aux;


          return TRUE;
        }
      }

    }else{
      l->first = sll_create(data);
      l->first->next = l->first;

      if(l->first != NULL){


        return TRUE;
      }
    }
  }

  return FALSE;
}

//Seleciona o arquivo para ler os dados //
int Insert_FILE(List *l, int dados){
  FILE *arq;
    if(dados == 1){
        arq = fopen("dados/file1000.txt","r");
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

          Insert(l, nmb);
          tmp_aux = 0;
        }
      }

    }
    fclose(arq);
}
int equals(void *a, void *b){

  if(a == b){
    return 1;
  }
  return 0;
}
// Acha dados em comum entre duas sll's//
int Inter_sll_sll(List *l, List *l2){
  if(l != NULL && l2 != NULL){
    if(l->first != NULL){
      sll *aux = l->first;
      int temp = Search(l2, aux->data, equals);
      if(temp != NULL){
        printf("%d ");
      }
      aux = aux->next;
      while(aux != l->first){
        int temp = Search(l2, aux->data, equals);
        if(temp != NULL){
          printf("%d ");
        }
        aux = aux->next;
      }
      return TRUE;
    }
  }
  return FALSE;
}
//Faz união entre os elementos que diferem entre A e B, e adiciona-o em B//
int Union_sll_sll(List *l, List *l2){
  if(l != NULL && l2 != NULL){
    if(l->first != NULL){
      sll *aux = l->first;
      void *tmp = Search(l2, aux->data, equals);
      if(tmp == NULL){
        Insert(l2,aux->data);
      }
      aux = aux->next;
      while(aux != l->first){
        tmp = Search(l2, aux->data, equals);
        if(tmp == NULL){
        Insert(l2,aux->data);
        }
        aux = aux->next;
      }
      return TRUE;
    }
  }
  return FALSE;
}

//Subtrai os elementos iguais entre A e B, de B//
int Remove_Equals_sll_sll(List *l, List *l2){
  if(l != NULL && l2 != NULL){
    if(l->first != NULL){
      sll *aux = l->first;
      void *tmp = Search(l2, aux->data, equals);
      if(tmp != NULL){
        Remove(l2,tmp,equals);
      }
      aux = aux->next;
      while(aux != l->first){
        tmp = Search(l2, aux->data, equals);
        if(tmp != NULL){
        Remove(l2, tmp, equals);
        }
        aux = aux->next;
      }
      return TRUE;
    }
  }
  return FALSE;
}

int Inter_sll_Hash(List *l, bank *checker){
  if(l != NULL && checker != NULL){
    if(l->first != NULL){
      sll *aux = l->first;
      Hash_Search(checker, aux->data, 1000000);
      aux = aux->next;
      while(aux != l->first){
        Hash_Search(checker,aux->data, 1000000);
        aux = aux->next;
      }
      return TRUE;
    }
  }
  return FALSE;
}


int Union_sll_Hash(List *l, bank *checker){
  if(l != NULL && checker != NULL){
    if(l->first != NULL){
      sll *aux = l->first;
      void *temp = Hash_Search(checker, aux->data, 1000000);
      if(temp == NULL){
        Hash_insert(checker, aux->data, 1000000);
      }
      aux = aux->next;
      while(aux != l->first){
        void *temp = Hash_Search(checker, aux->data, 1000000);
        if(temp == NULL){
          Hash_insert(checker, aux->data, 1000000);
        }
        aux = aux->next;
      }
      return TRUE;
    }
  }
  return FALSE;
}
int Remove_Equals_sll_Hash(List *l, bank *checker){
  if(l != NULL && checker != NULL){
    if(l->first != NULL){
      sll *aux = l->first;

      Hash_Remove(checker, aux->data, 1000000);

      aux = aux->next;
      while(aux != l->first){

          Hash_Remove(checker, aux->data, 1000000);

        aux = aux->next;
      }
      return TRUE;
    }
  }
  return FALSE;
}

int Inter_sll_BTree(List *l, Tnode *t){
  if(l != NULL && t != NULL){
    if(l->first != NULL){
      sll *aux = l->first;
      void *temp = abSearch(t, aux->data, cmp);
      if(temp != NULL){
        printf("%d ", temp);
      }
      aux = aux->next;
      while(aux != l->first){
        void *temp = abSearch(t, aux->data, cmp);
        if(temp != NULL){
          printf("%d ", temp);
        }
        aux = aux->next;
      }
      return TRUE;
    }
  }
  return FALSE;
}

int Union_sll_BTree(List *l, Tnode *t){
  if(l != NULL && t != NULL){
    if(l->first != NULL){
      sll *aux = l->first;
      void *temp = abSearch(t, aux->data, cmp);
      if(temp == NULL){
        abInsert(t, aux->data, cmp);
      }
      aux = aux->next;
      while(aux != l->first){
        void * temp = abSearch(t, aux->data, cmp);
        if(temp == NULL){
          abInsert(t, aux->data, cmp);
        }
        aux = aux->next;
      }
      return TRUE;
    }
  }
  return FALSE;
}

int Remove_Equals_sll_BTree(List *l, Tnode *t){
  if(l != NULL && t != NULL){
    if(l->first != NULL){
      sll *aux = l->first;
      void *temp = abSearch(t, aux->data, cmp);
      if(temp != NULL){
        abRemove(t, temp, cmp);
      }
      aux = aux->next;
      while(aux != l->first){
        void *temp = abSearch(t, aux->data, cmp);
        if(temp != NULL){
          abRemove(t, temp, cmp);
        }
        aux = aux->next;
      }
      return TRUE;
    }
  }
  return FALSE;
}

int Inter_sll_AVLTree(List *l, Node *t){
  if(l != NULL && t != NULL){
    if(l->first != NULL){
      sll *aux = l->first;
      void *temp = avlSearch(t, aux->data, cmp);
      if(temp != NULL){
        printf("%d ", temp);
      }
      aux = aux->next;
      while(aux != l->first){
        void *temp = avlSearch(t, aux->data, cmp);
        if(temp != NULL){
          printf("%d ", temp);
        }
        aux = aux->next;
      }
      return TRUE;
    }
  }
  return FALSE;
}


int Union_sll_AVLTree(List*l, Node *t){
  if(l != NULL && t != NULL){
    if(l->first != NULL){
      sll *aux = l->first;
      void *temp = avlSearch(t, aux->data, cmp);
      if(temp == NULL){
        insertNode(t, aux->data);
      }
      aux = aux->next;
      while(aux != l->first){
        void *temp = avlSearch(t, aux->data, cmp);
        if(temp == NULL){
          insertNode(t, aux->data);
        }
        aux = aux->next;
      }
      return TRUE;
    }
  }
  return FALSE;
}
int Remove_Equals_sll_AVLTree(List*l, Node *t){
  if(l != NULL && t != NULL){
    if(l->first != NULL){
      sll *aux = l->first;
      void *temp = avlSearch(t, aux->data, cmp);
      if(temp != NULL){
        removeSpec(t, temp);
      }
      aux = aux->next;
      while(aux != l->first){
        void *temp = avlSearch(t, aux->data, cmp);
        if(temp != NULL){
          removeSpec(t, temp);
        }
        aux = aux->next;
      }
      return TRUE;
    }
  }
  return FALSE;
}

int Inter_sll_RBTree(List *l, RBNode *t){
  if(l != NULL && t != NULL){
    if(l->first != NULL){
      sll *aux = l->first;

      void *temp = Return_rbtSearch(&t, aux->data);
      if(temp != NULL){
        printf("%d ", temp);
      }
      aux = aux->next;
      while(aux != l->first){
        void *temp = Return_rbtSearch(&t, aux->data);
        if(temp != NULL){
          printf("%d ", temp);
        }

        aux = aux->next;
      }
      return TRUE;
    }
  }
  return FALSE;
}

int Union_sll_RBTree(List *l, RBNode *t){
  if(l != NULL && t != NULL){
    if(l->first != NULL){
      sll *aux = l->first;

      void *temp = Return_rbtSearch(&t, aux->data);
      if(temp == NULL){
        rbtInsert(&t, aux->data);
      }
      aux = aux->next;
      while(aux != l->first){
        void *temp = Return_rbtSearch(&t, aux->data);
        if(temp == NULL){
          rbtInsert(&t, aux->data);
        }

        aux = aux->next;
      }
      return TRUE;
    }
  }
  return FALSE;
}
int Remove_Equals_sll_RBTree(List *l, RBNode *t){
  if(l != NULL && t != NULL){
    if(l->first != NULL){
      sll *aux = l->first;

      void *temp = Return_rbtSearch(&t, aux->data);
      if(temp != NULL){
        rbtDeleteByVal(&t, temp);
      }
      aux = aux->next;
      while(aux != l->first){
        void *temp = Return_rbtSearch(&t, aux->data);
        if(temp != NULL){
          rbtDeleteByVal(&t, temp);

        }

        aux = aux->next;
      }
      return TRUE;
    }
  }
  return FALSE;
}
void *Search(List *l,void *data, int(equals(void*, void*))){

  if(l != NULL){
    if(l->first != NULL){
      sll *aux = l->first;
      int stat = equals(aux->data, data);
      aux = aux->next;

      while(aux != l->first && stat != 1){
        aux = aux->next;
        stat  = equals(aux->data, data);

      }
      if(stat == 1){
        return aux->data;
      }
    }
  }
  return NULL;
}
void *Remove(List *l,void *data, int(equals(void*, void*))){
  if(l != NULL){
    if(l->first != NULL){
      sll *aux = l->first;
      int stat = equals(aux->data, data);

      while(aux->next != l->first && stat != 1){
        aux = aux->next;
        stat  = equals(aux->data, data);
      }
      if(stat == 1){
        if(aux == l->first){
          if(aux->next != l->first){
            l->first->next->prev = l->first->prev;
            l->first->prev->next = l->first->next;
            sll *temp = l->first;
            l->first = l->first->next;

            free(temp);

          }else{
            free(l->first);
          }
          return TRUE;
        }else{
          aux->prev->next = aux->next;
          aux->next->prev = aux->prev;
          free(aux);
          return TRUE;
        }
      }
      printf("Not find \n");
    }
  }
  return NULL;
}
