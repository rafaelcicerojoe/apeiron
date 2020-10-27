#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
#include "graph.c"
int main(){
    FILE *arch;
    arch= fopen("grafos.txt","r");
    int n, linha=0, grau;
    float peso;
    Grafo *gr;
    char aux[10],ponderado;
        while(fgets(aux, 20, arch) != NULL){
            char tmp[20];
            if(linha == 0){ // Primeira linha, pega a quantidade de vertices
                n = atoi(aux);
                linha++;
            }else if(linha == 1){ // Segunda linha, pega se é ponderado ou nao
                 if(aux[0] == 't'){
                    ponderado = 't';
                }else{
                    ponderado = 'f';
                }
                linha++;
            }else if(linha == 2){// Terceira linha, pega a quantidade de grau maximo
                grau = atoi(aux);
                if(ponderado == 't'){
                    gr = cria_Grafo(n, grau, 1);
                }else if (ponderado == 'f'){
                    gr = cria_Grafo(n, grau, 0);
                }

                linha++;
            }else{ // Seguintes linhas : adiciona grafos
                char numb_aux[4], cont = 0;
                int orig = -1 ;
                int dest = -1 , peso = -1 ;
                for(int i = 0 ; i < strlen(aux) ; i++){ // cria string auxiliar para pegar os numeros para converter em int
                    if(orig == -1){
                        if(aux[i] != ' '){
                            numb_aux[cont] = aux[i];
                            cont++;
                        }else{
                            numb_aux[cont] = '\0';
                            cont = 0;
                            orig = atoi(numb_aux);
                        }
                    }
                    else if(dest == -1){
                        if(aux[i] != ' '){
                            numb_aux[cont] = aux[i];
                            cont++;
                        }else{
                            numb_aux[cont] = '\0';
                            cont = 0;
                            dest = atoi(numb_aux);
                        }
                    }
                    else if(peso == -1){
                        if(aux[i] != ' '){
                            numb_aux[cont] = aux[i];

                            cont++;
                        }else{
                            numb_aux[cont] = '\0';
                            cont = 0;
                            peso = atoi(numb_aux);

                        }
                    }
                }
                numb_aux[cont] = '\0';
                cont = 0;
                peso = atoi(numb_aux);
                if (dest==-1){
                    dest=peso;
                }
                insereAresta(gr, orig, dest, 0, peso); // 0 indica o grafo  não direcionado
            }
        }

    fclose(arch);
    printf("\nBusca \n");
    int menu,opc;
    printf("--------------------------------  Menu  ---------------------\n");
    printf("1 - Listagem\n2 - BFS\n3 - Excentricidade\n4 - Geradora minima\n5 - Caso \nDigite: ");

    scanf("%d", &menu);

    switch(menu){
        case 1:
            printf("1 - Lista de Adj\n2 - Matriz de Adj\n 3 - Lista Invertida \nDigite: ");
            scanf("%d", &opc);
            switch(opc){
                case 1:
                    imprime_Grafo(gr,1); 
                break;
                case 2:
                    imprime_Grafo(gr,2);
                break;
                case 3:
                    imprime_Grafo(gr,3);
                break;
            }
        break;
        case 2:
            printf("Digite sua origem e destino: ");
            int ori,*des,destf,flag=0;
            scanf("%d %d", &ori,&destf);
            buscaLargura_Grafo(gr, ori, des);
            for(int i=0;i<len(des[i]);i++){
                if (destf==i){
                    flag=1;
                    printf("%d",des[i]);
                }
            }
            if (flag==0){
                printf("Dado Incorreto");
            } 
        break;
        case 3:
            printf("1 - Excent de V\n2 - Diametro G\n 3 - Raio G \nDigite: ");
            int ini, *ant,fim;
            int ori=0,*des,destf,flag=0;
            scanf("%d %d", &ori,&destf);
            buscaLargura_Grafo(gr, ori, des);
            float *dist;
            scanf("%d", &opc);
            switch(opc){
                case 1:
                    destf=0;
                    printf("Digite sua origem: ");
                    scanf("%d", &ori);
                    buscaLargura_Grafo(gr, ori, des);
                    for(int i=0;i<len(des[i]);i++){
                        if (des[i]>destf){
                            flag=1;
                            destf=des[i];
                        }
                    }
                    printf("Maior Excentricidade");
                    printf("%d",destf);
                    if (flag==0){
                    printf("Dado Incorreto");
                    } 
                break;
                case 2:
                    destf=1;
                    printf("O Raio de G:");
                    for (ori = 0; ori <gr->n_vertices ; ori++){
                        buscaLargura_Grafo(gr, ori, des);
                        for(int i=0;i<len(des[i]);i++){
                            if (des[i]<=destf){
                                flag=1;
                                printf("%d-> (%d) -> %d",ori,des[i],i);
                            }
                        }
                    }
                    if (flag==0){
                    printf("Dado Incorreto");
                    }
                break;
                case 3:
                    destf=0;
                    printf("O Diametro de G:");
                    for (ori = 0; ori <gr->n_vertices ; ori++){
                        buscaLargura_Grafo(gr, ori, des);
                        for(int i=0;i<len(des[i]);i++){
                            if (des[i]>destf){
                                flag=1;
                                destf=des[i];
                                fim=i;
                            }
                        }
                        printf("%d-> (%d) -> %d",ori,destf,fim);
                    }
                    if (flag==0){
                    printf("Dado Incorreto");
                    }
                break;
            }
        case 4:
            printf("1 - Prim\n2 - Kruskal\nDigite: ");
            scanf("%d", &opc);
            switch(opc){
                case 1:
                    primMST(gr); 
                break;
                case 2:
                    kruskalMST(gr);
                break;
            }
        break;
        case 5:
            printf("Digite sua origem e raio de procura: ");
            int orig,raio;
            scanf("%d %d", &orig,&raio);
            buscaLargura_Grafo(gr, ori, des);
                for(int i=0;i<len(des[i]);i++){
                    if (raio>=des[i]){
                        flag=1;
                        printf("%d",des[i]);
                    }
                }
            if (flag==0){
            printf("Dado Incorreto");
            }
        break;
    }
    int vis[5];
    // http://www.thelearningpoint.net/computer-science/algorithms-graph-traversal---breadth-linha-search-with-c-program-source-code
    //buscaProfundidade_Grafo(gr, 0, vis);
    //buscaLargura_Grafo(gr, 0, vis);
    system("pause");
    return 0;
}
