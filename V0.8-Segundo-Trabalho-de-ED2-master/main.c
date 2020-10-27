#include "avlTree.h"
#include "hash.h"
#include "sll.h"
#include "binaryTree.h"
#include "rbTree.h"
#include "time.h"

int main(){

    Node *dadosB_AVL; // referencia Avl

    bank *dadosB_Hash; // referencia Hash

    Tnode *dadosB_BTree; // referencia Árvore binária

    List *dadosA_List; // referencia Lista encadeada
    List *dadosB_List; // referencia Lista encadeada

    RBNode *dadosB_RBTree; // referencia rubro-negra

    int struc; // Estrutura para armazenamento
    int op; // Opcao
    int arc; // qual dos arquivos sera utilizado como maior

    clock_t tInit, tEnd, tInsert, tInter, tUnion, tRemove; // timer

    printf("Armazenar em:\n");
    printf("1 - Lista encadeada\n2 - Hash\n3 - Arvore binaria\n4 - Arvore AVL\n5 - Arvore rubro-negra\nDigite: ");
    scanf("%d",&struc);
    printf("Opcoes?\n");
    printf("1 - Intersecção de A em B\n2 - Inserir em B, o que há somente em A\n3 - Remover de B os elementos comuns de A \nDigite: ");
    scanf("%d",&op);

    printf("\n1 - 1000 \n2 - 5000 \n3 - 10000 \n4 - 50000 \n5 - 100000 \n6 - 500000 \n7 - 1000000 \n");
    scanf("%d", &arc);
// lera o arcuivo e armazenara de arcordo com a esolha feita
    switch(struc){
        case 1:
            dadosA_List = list_create();
            dadosB_List = list_create();

            Insert_FILE(dadosA_List, 1);
            tInit = clock();
            Insert_FILE(dadosB_List, arc);
            tEnd = clock();
            tInsert = ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));

            printf("Dados A (Encadeada):\n");
            show_list(dadosA_List);
            printf("\nDados B (Encadeada): \n");
            show_list(dadosB_List);

            switch(op){
                case 1:
                    printf("\nElementos de A em B : \n");
                    tInit = clock();
                    Inter_sll_sll(dadosA_List, dadosB_List);
                    tEnd = clock();
                    tInter = ((tEnd - tInit) *1000/ (CLOCKS_PER_SEC));
                    printf("\nInsert %d, Inter %d \n", tInsert, tInter);
                    printf("\n");
                break;
                case 2:
                    printf("\nDados de A que estao em B : \n");
                    tInit = clock();
                    Union_sll_sll(dadosA_List, dadosB_List);
                    tEnd = clock();
                    tUnion = ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));
                    printf("\nCom adiçao dos nao iguais  : \n");
                    show_list(dadosB_List);
                    printf("\nInsert %d, Union %d\n",tInsert, tUnion );
                break;
                case 3:
                    printf("\n Dados de A que estao em B removidos de B : \n");
                    tInit = clock();
                    Remove_Equals_sll_sll(dadosA_List, dadosB_List);
                    tEnd = clock();
                    tRemove = ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));
                    printf("\nCom remoçao dos iguais : \n");
                    show_list(dadosB_List);
                    printf("\nInsert %d, Remove %d\n", tInsert, tRemove);
                break;
                tEnd = clock();
            }
        break;
        case 2:
            dadosA_List = list_create();
            dadosB_Hash = Data_Create(1000000);
            Insert_FILE(dadosA_List, 1);
            tInit = clock();
            Hash_FILE_Insert(dadosB_Hash, arc);
            tEnd = clock();
            tInsert = ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));

            printf("dados A (Encadeada): \n");
            show_list(dadosA_List);
            printf("\ndados B : (Hash)\n");
            printf("\nQuant %d ", Show_Hash_list(dadosB_Hash, 1000000));

            switch(op){
                case 1:
                    printf("\nElementos de A que estao em B : \n");
                    tInit = clock();
                    Inter_sll_Hash(dadosA_List, dadosB_Hash);
                    tEnd = clock();
                    tInter = ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));
                    printf("\nInser %d, Inter %d\n",tInsert,tInter);
                    printf("\n");


                break;
                case 2:
                    printf("\n");
                    tInit  = clock();
                    Union_sll_Hash(dadosA_List, dadosB_Hash);
                    tEnd = clock();
                    tUnion= ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));
                    printf("\nCom adiçao : \n");
                    Show_Hash_list(dadosB_Hash, 1000000);
                    printf("\nInsert %d, Union %d \n",tInsert, tUnion);

                break;
                case 3:
                    tInit = clock();
                    Remove_Equals_sll_Hash(dadosA_List, dadosB_Hash);
                    tEnd = clock();
                    tRemove = ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));
                    printf("\nCom remocao dos iguais : \n");
                    Show_Hash_list(dadosB_Hash, 1000000);
                    printf("\nInsert %d, Remove %d\n", tInsert, tRemove);
                break;
            }
            break;
        case 3:
            dadosA_List = list_create();
            Insert_FILE(dadosA_List, 1);
            dadosB_BTree = abCreate(NULL);
            tInit = clock();
            abp_FILE_Insert(dadosB_BTree, arc);
            tEnd = clock();
            tInsert = ((tEnd - tInit) / (CLOCKS_PER_SEC / 1000));

            printf("dados A (Encadeada) : \n");
            show_list(dadosA_List);
            printf("\ndados B (Arvore B, Pre Ord) : \n");
            Pre_ordem(dadosB_BTree);
            switch(op){
                case 1:
                    printf("\nElementos de A que estao em B : \n");
                    tInit = clock();
                    Inter_sll_BTree(dadosA_List, dadosB_BTree);
                    tEnd = clock();
                    tInter = ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));
                    printf("\nInsert %d, Inter %d\n", tInsert, tInter);
                break;
                case 2:
                   tInit = clock();
                    Union_sll_BTree(dadosA_List, dadosB_BTree);
                    tEnd = clock();
                    tUnion = ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));
                    printf("\nCom adicao : \n");
                    Pre_ordem(dadosB_BTree);
                    printf("\nInsert %d, Union %d", tInsert, tUnion);
                break;
                case 3:
                    printf("\nElementos de A que estao em B, removidos de B : \n");
                    tInit = clock();
                    Remove_Equals_sll_BTree(dadosA_List, dadosB_BTree);
                    tEnd = clock();
                    tRemove = ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));
                    printf("\nCom elementos removidos : \n");
                    Pre_ordem(dadosB_BTree);
                    printf("\nInsert %d, Remove %d", tInsert, tRemove);
                break;
            }
            break;
        case 4:
            dadosA_List = list_create();
            tInit = clock();
            Insert_FILE(dadosA_List, 1);
            tEnd = clock();
            tInsert = ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));
            dadosB_AVL = createAvlTree(arc);
            printf("\nDados A: (Encadeada)\n");
            show_list(dadosA_List);
            printf("\n\nDados B: (Arvore AVL)\n");
            preOrdem(dadosB_AVL);
            switch(op){
                case 1:
                    printf("\n\nElementos de A que estao em B:\n");
                    tInit = clock();
                    Inter_sll_AVLTree(dadosA_List, dadosB_AVL);
                    tEnd = clock();
                    tInter = ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));
                    printf("\nInsert %d Inter %d\n", tInsert, tInter);
                    printf("\n");
                break;
                case 2:
                    printf("\nElementos de A que estao nao em B,  adicionados em B :  \n");
                    tInit = clock();
                    Union_sll_AVLTree(dadosA_List, dadosB_AVL);
                    tEnd = clock();
                    tUnion = ((tEnd - tInit) / (CLOCKS_PER_SEC/1000));
                    preOrdem(dadosB_AVL);
                    printf("\nInsert %d Union %d \n", tInsert, tUnion);
                break;
                case 3:
                    printf("\nElementos de A que estao em  B, removidos de B : \n");
                    tInit = clock();
                    Remove_Equals_sll_AVLTree(dadosA_List, dadosB_AVL);
                    tEnd = clock();
                    tRemove = ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));
                    preOrdem(dadosB_AVL);
                    printf("\nInsert %d Remove %d\n", tInsert, tRemove);
                break;
            }
            break;
        case 5:
            dadosA_List = list_create();
            Insert_FILE(dadosA_List, 1);
            tInit = clock();
            dadosB_RBTree = RB_FILE_Insert(arc);
            tEnd = clock();
            tInsert = ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));
            printf("\nDados A: (Encadeada)\n");
            show_list(dadosA_List);
            printf("\n\nDados B: (RBT)\n");
            rbtPreOrder(dadosB_RBTree);
            switch(op){
                case 1:
                    printf("\nElementos de A que estao em B : \n");
                    tInit = clock();
                    Inter_sll_RBTree(dadosA_List, dadosB_RBTree);
                    tEnd = clock();
                    tInter = ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));
                    printf("Insert %d, Inter %d\n", tInsert, tInter);
                break;
                case 2:
                    printf("\nElementos de A que nao estao em B, adicionados em B : \n");
                    tInit = clock();
                    Union_sll_RBTree(dadosA_List, dadosB_RBTree);
                    tEnd = clock();
                    tUnion = ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));
                    printf("\n");
                    rbtPreOrder(dadosB_RBTree);
                    printf("Insert %d, Union %d\n", tInsert, tUnion);
                break;
                case 3:
                    printf("\nCom remocao: \n");
                    tInit = clock();
                    Remove_Equals_sll_RBTree(dadosA_List, dadosB_RBTree);
                    tEnd = clock();
                    tRemove = ((tEnd - tInit)* 1000 / (CLOCKS_PER_SEC ));
                    rbtPreOrder(dadosB_RBTree);
                    printf("Insert %d, Remove %d\n", tInsert, tRemove);
                break;
            }
        break;
        default:
        break;
    }

}
