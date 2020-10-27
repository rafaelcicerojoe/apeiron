#include "hash.h"

// Struct do Hash//
typedef struct nb {
  void *data;
  int jumps;
  char flag ;
}bank;

//O Modulo é proporcional ao tamanho alocado para o Hash, logo, evitando colisoes, mas despende muita memoria

int hash_key(int aux){

  return aux % 1000000;

}

bank *Data_Create(int n){
  return (bank*)malloc (n*sizeof(bank));
}

//Insere na posiçao resultante do mod entre aux e o tamanho alocado, tempo O(1)//

int Hash_insert(bank *checker, void *aux, int checker_tam){

  int pos = hash_key(aux);
    //Se a flag for diferente de T , significa que esse espaço está disponivel//
    if(checker[pos].flag != 'T'){

      checker[pos].data = malloc(20);

      checker[pos].data = aux;
      checker[pos].jumps = 0;
      checker[pos].flag = 'T';

      if(checker[pos].data == aux){


        return 1;
      }
      checker[pos].flag = 'F';
      printf("Insert error \n");
    }else if(checker[pos].data != aux){
      /*Se a posiçao primaria da funçao hash para esse valor ja está ocupada, entao o programa irá utilizar o
      metodo linear para achar um espaço vazio != T para armazenar o dado  O(n)*/

      int aux2 = pos+1;
      while(aux2 < checker_tam && checker[aux2].flag == 'T' && checker[aux2].data != aux){

        aux2++;
      }
      if(checker[aux2].data == aux){
        printf("Equals %d %d just one in Hash\n", checker[aux2].data, aux);
        return 0;
      }
      if(aux2 < checker_tam && checker[aux2].flag != 'T'){
        checker[aux2].data = malloc(1);
        checker[aux2].data = aux;
        checker[aux2].jumps = aux2-pos;
        checker[aux2].flag = 'T';

        return 1;
      }
      printf("Space not found %d %d\n", pos , aux);
    }
    return 0;
}
//Seleciona o arquivo que terá os dados lidos //
void Hash_FILE_Insert(bank *Checker, int dados){
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

          Hash_insert(Checker, nmb, 1000000);

          tmp_aux = 0;
        }
      }

    }

    fclose(arq);
}
/*procura pelo elemento declarado, caso nao esteja na posiçao fornecida por Hash_key, tentará encontrar pelo mé-
todo linear */
void *Hash_Search(bank *checker, void *aux, int checker_tam){

  int pos = hash_key(aux);

  if(checker[pos].data != NULL && checker[pos].flag == 'T'){

    if(checker[pos].data == aux){


    return checker[pos].data;
    }

  }
  int aux2 = pos+1;
    int stat = -1;
    while(aux2 < checker_tam && stat != 0){

      if(checker[aux2].data != NULL && checker[aux2].flag == 'T'){

        if((int)checker[aux2].data == aux){

          stat = 0;
        }

      }if(stat != 0){
          aux2++;
      }
    }
    if(stat == 0){
    printf("%d ", checker[aux2].data);
      return checker[aux2].data;
    }
  return NULL;
}

/*Remove o elemento declarado, caso nao esteja na posiçao fornecida por Hash_key, tentará encontrar pelo mé-
todo linear */
void *Hash_Remove(bank *checker, void *aux, int checker_tam){

  int pos = hash_key(aux);

  if(checker[pos].data != NULL && checker[pos].flag != 'F'){

    if(checker[pos].data == aux){

      void *temp = checker[pos].data;

      checker[pos].flag = 'F';


      return temp;
    }
  }
  int aux2 = pos+1;
    int stat = -1;
    while(aux2 < checker_tam && stat != 0){

      if(checker[aux2].data != NULL && checker[aux2].flag != 'F'){
        if((int)checker[aux2].data == aux){

          stat = 0;
        }

      }
      if(stat != 0){
          aux2++;
      }
    }
    if(stat == 0){
      void *temp = checker[aux2].data;


      checker[aux2].flag = 'F';

      return temp;
    }
  return NULL;
}
//Mostra a lista //
int Show_Hash_list(bank *checker,int checker_tam){
  int aux = 0;
  int quant = 0;
  while(aux < checker_tam-1){
    if(checker[aux].flag == 'T'){
      printf("%d ", checker[aux].data);
     quant++;
    }
    aux++;
  }
  return quant;

}
