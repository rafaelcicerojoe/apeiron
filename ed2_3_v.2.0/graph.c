#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h" //inclui os Prot�tipos
#define V 5
#define INT_MAX 10000

//Defini��o do tipo Grafo
struct grafo{
    int ha_peso;
    int n_vertices;
    int grau_max;
    char** arestas;
    float** pesos;
    int* grau;
};

Grafo* cria_Grafo(int n_vertices, int grau_max, int ha_peso){
    Grafo *gr;
    gr = (Grafo*) malloc(sizeof(struct grafo));
    if(gr != NULL){
        int i;
        gr->n_vertices = n_vertices;
        gr->grau_max = grau_max;
        gr->ha_peso = (ha_peso != 0)?1:0;
        gr->grau = (int*) calloc(n_vertices,sizeof(int));

        gr->arestas = (int**) malloc(n_vertices * sizeof(int*));
        for(i=0; i<n_vertices; i++)
            gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));

        if(gr->ha_peso){
            gr->pesos = (float**) malloc(n_vertices * sizeof(float*));
            for(i=0; i<n_vertices; i++)
                gr->pesos[i] = (float*) malloc(grau_max * sizeof(float));
        }

    }
    return gr;
}

void libera_Grafo(Grafo* gr){
    if(gr != NULL){
        int i;
        for(i=0; i<gr->n_vertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);

        if(gr->ha_peso){
            for(i=0; i<gr->n_vertices; i++)
                free(gr->pesos[i]);
            free(gr->pesos);
        }
        free(gr->grau);
        free(gr);
    }
}

int insereAresta(Grafo* gr, char orig, char dest, int eh_digrafo, float peso){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->n_vertices)
        return 0;
    if(dest < 0 || dest >= gr->n_vertices)
        return 0;

    gr->arestas[orig][gr->grau[orig]] = dest;
    if(gr->ha_peso)
        gr->pesos[orig][gr->grau[orig]] = peso;
    gr->grau[orig]++;

    if(eh_digrafo == 0)
        insereAresta(gr,dest,orig,1,peso);
    return 1;
}

int removeAresta(Grafo* gr, char orig, char dest, int eh_digrafo){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->n_vertices)
        return 0;
    if(dest < 0 || dest >= gr->n_vertices)
        return 0;

    int i = 0;
    while(i<gr->grau[orig] && gr->arestas[orig][i] != dest)
        i++;
    if(i == gr->grau[orig])//elemento nao encontrado
        return 0;
    gr->grau[orig]--;
    gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];
    if(gr->ha_peso)
        gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];
    if(eh_digrafo == 0)
        removeAresta(gr,dest,orig,1);
    return 1;
}

void imprime_Grafo(Grafo *gr,int opc){
    if(gr == NULL){
        printf("Sem grafo com este nome!");
        return;
    }
    int i, j;
    if (opc==1){
        for(i=0; i < gr->n_vertices; i++){
            printf("%d: ", i);
            for(j=0; j < gr->grau[i]; j++){
                if(gr->ha_peso)
                    printf("%d(%.2f) -> ", gr->arestas[i][j], gr->pesos[i][j]);
                else
                    printf("%d -> ", gr->arestas[i][j]);
            }printf("\n");
        }
    }else if(opc==2){
        i=0;
        /*while (i< gr->n_vertices){
            printf("  %d", i);
            i++;
        }*/
        printf("\n");
        for(i=0; i < gr->n_vertices; i++){
            printf("%d: ", i);
            for ( j = 0; j < gr->n_vertices; j++){
                int flag=0;
                for(int k=0; k < gr->grau[i]; k++){
                    if (j== gr->arestas[i][k]){ 
                        flag=1;   
                        if(gr->ha_peso){
                            printf("(%.2f) ", gr->arestas[i][j], gr->pesos[i][j]);
                        }else{
                            printf(" 1 ");
                        }
                    }   
                }if (flag == 0){
                    printf(" 0 ");
                }
            }printf("\n");     
        }
    }else if(opc==3){
        for(i=gr->n_vertices; i > 0; i--){
            printf("%d: ", i);
            for(j=gr->grau[i]; j > 0; j--){
                if(gr->ha_peso)
                    printf("%d(%.2f) -> ", gr->arestas[i][j], gr->pesos[i][j]);
                else
                    printf("%d -> ", gr->arestas[i][j]);
            }printf("\n");
        }
    }
    
}

/*
Algoritmos para Grafos em C
 via Sedgewick
http://www.ime.usp.br/~pf/algoritmos_para_grafos/
*/
// https://www.cs.auckland.ac.nz/software/AlgAnim/dijkstra.html
// http://www.cprogramming.com/tutorial/computersciencetheory/dijkstra.html
int procuraMenorDistancia(float *dist, int *visitado, int NV){
    int i, menor = -1, primeiro = 1;
    for(i=0; i < NV; i++){
        if(dist[i] >= 0 && visitado[i] == 0){
            if(primeiro){
                menor = i;
                primeiro = 0;
            }else{
                if(dist[menor] > dist[i])
                    menor = i;
            }
        }
    }
    return menor;
}

void menorCaminho_Grafo(Grafo *gr, int ini, int *ant, float *dist){
    int i, cont, NV, ind, *visitado, vert;
    cont = NV = gr->n_vertices;
    visitado = (int*) malloc(NV * sizeof(int));
    for(i=0; i < NV; i++){
        ant[i] = -1;
        dist[i] = -1;
        visitado[i] = 0;
    }
    dist[ini] = 0;
    while(cont > 0){
        vert = procuraMenorDistancia(dist, visitado, NV);
        //printf("u = %d\n",u);
        if(vert == -1)
            break;

        visitado[vert] = 1;
        cont--;
        for(i=0; i<gr->grau[vert]; i++){
            ind = gr->arestas[vert][i];
            if(dist[ind] < 0){
               dist[ind] = dist[vert] + 1;//ou peso da aresta
               ant[ind] = vert;
            }else{
                if(dist[ind] > dist[vert] + 1){
                    dist[ind] = dist[vert] + 1;//ou peso da aresta
                    ant[ind] = vert;
                }
            }
        }
    }

    free(visitado);
}


// http://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/dfs1.html
void buscaProfundidade(Grafo *gr, int ini, int *visitado, int cont){
    int i;
    visitado[ini] = cont;
    for(i=0; i<gr->grau[ini]; i++){
        if(!visitado[gr->arestas[ini][i]])
            buscaProfundidade(gr,gr->arestas[ini][i],visitado,cont+1);
    }
}
void buscaProfundidade_Grafo(Grafo *gr, int ini, int *visitado){
    int i, cont = 1;
    for(i=0; i<gr->n_vertices; i++)
        visitado[i] = 0;
    buscaProfundidade(gr,ini,visitado,cont);

    for(i=0; i < gr->n_vertices; i++)
        printf("%d -> %d\n",i,visitado[i]);
}
// http://en.wikipedia.org/wiki/Breadth-first_search
// http://www.princeton.edu/~achaney/tmve/wiki100k/docs/Breadth-first_search.html

void buscaLargura_Grafo(Grafo *gr, int ini, int *visitado){
    int i, vert, NV, cont = 1;
    int *fila, IF = 0, FF = 0;
    for(i=0; i<gr->n_vertices; i++)
        visitado[i] = 0;

    NV = gr->n_vertices;
    fila = (int*) malloc(NV * sizeof(int));
    FF++;
    fila[FF] = ini;
    visitado[ini] = cont;
    while(IF != FF){
        IF = (IF + 1) % NV;
        vert = fila[IF];
        cont++;
        for(i=0; i<gr->grau[vert]; i++){
            if(!visitado[gr->arestas[vert][i]]){
                FF = (FF + 1) % NV;
                fila[FF] = gr->arestas[vert][i];
                visitado[gr->arestas[vert][i]] = cont;
            }
        }
    }
    free(fila);
    for(i=0; i < gr->n_vertices; i++)
        printf("%d -> %d\n",i,visitado[i]);
}

/* OUTRA VERS�O
void buscaLargura_Grafo(Grafo *gr, int ini, int *visitado){
    int i, vert, NV, cont = 1;
    int *pilha, IP = 0, FP = 0;
    for(i=0; i<gr->n_vertices; i++)
        visitado[i] = 0;

    NV = gr->n_vertices;
    pilha = (int*) malloc(NV * sizeof(int));
    FP++;
    pilha[FP] = ini;
    while(IP != FP){
        IP = (IP + 1) % NV;
        vert = pilha[IP];
        if(!visitado[vert]){
            visitado[vert] = cont;
            cont++;
            for(i=0; i<gr->grau[vert]; i++){
                if(!visitado[gr->arestas[vert][i]]){
                    FP = (FP + 1) % NV;
                    pilha[FP] = gr->arestas[vert][i];
                }
            }
        }
    }
    free(pilha);
    for(i=0; i < gr->n_vertices; i++)
        printf("%d -> %d\n",i,visitado[i]);
}
*/
int minKey(int key[], bool mstSet[]) 
{ 
 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < V; v++) 
        if (mstSet[v] == false && key[v] < min) 
            min = key[v], min_index = v; 
  
    return min_index; 
} 
  

int printMST(int parent[], int graph[V][V]) 
{ 
    printf("Aresta\tPeso\n"); 
    for (int i = 1; i < V; i++) 
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]); 
} 
// Editado para TAD Grafo
// Function to construct and print MST for 
// a graph represented using adjacency 
// matrix representation 

void primMST(Grafo *graph) 
{ 
    // Array to store constructed MST 
    int parent[V]; 
    // Key values used to pick minimum weight edge in cut 
    int key[V]; 
    // To represent set of vertices not yet included in MST 
    bool mstSet[V]; 
  
    // Initialize all keys as INFINITE 
    for (int i = 0; i < V; i++) 
        key[i] = INT_MAX, mstSet[i] = false; 
  
    // Always include first 1st vertex in MST. 
    // Make key 0 so that this vertex is picked as first vertex. 
    key[0] = 0; 
    parent[0] = -1; // First node is always root of MST 
  
    // The MST will have V vertices 
    for (int count = 0; count < V - 1; count++) { 
        // Pick the minimum key vertex from the 
        // set of vertices not yet included in MST 
        int u = minKey(key, mstSet); 
  
        // Add the picked vertex to the MST Set 
        mstSet[u] = true; 
  
        // Update key value and parent index of 
        // the adjacent vertices of the picked vertex. 
        // Consider only those vertices which are not 
        // yet included in MST 
        for (int v = 0; v < V; v++) 
  
            // graph[u][v] is non zero only for adjacent vertices of m 
            // mstSet[v] is false for vertices not yet included in MST 
            // Update the key only if graph[u][v] is smaller than key[v] 
            if (graph->arestas[u][v] && mstSet[v] == false && graph->arestas[u][v] < key[v]) 
                parent[v] = u, key[v] = graph->arestas[u][v]; 
    } 
  
    // print the constructed MST 
    printMST(parent, graph); 
}

// A structure to represent a subset for union-find 
struct subset 
{ 
    int parent; 
    int rank; 
}; 
  
// A utility function to find set of an element i 
// (uses path compression technique) 
int find(struct subset subsets[], int i) 
{ 
    // find root and make root as parent of i  
    // (path compression) 
    if (subsets[i].parent != i) 
        subsets[i].parent = find(subsets, subsets[i].parent); 
  
    return subsets[i].parent; 
} 
  
// A function that does union of two sets of x and y 
// (uses union by rank) 
void Union(struct subset subsets[], int x, int y) 
{ 
    int xroot = find(subsets, x); 
    int yroot = find(subsets, y); 
  
    // Attach smaller rank tree under root of high  
    // rank tree (Union by Rank) 
    if (subsets[xroot].rank < subsets[yroot].rank) 
        subsets[xroot].parent = yroot; 
    else if (subsets[xroot].rank > subsets[yroot].rank) 
        subsets[yroot].parent = xroot; 
  
    // If ranks are same, then make one as root and  
    // increment its rank by one 
    else
    { 
        subsets[yroot].parent = xroot; 
        subsets[xroot].rank++; 
    } 
} 
  
// Compare two edges according to their weights. 
// Used in qsort() for sorting an array of edges 

  
// The main function to construct MST using Kruskal's algorithm 
void KruskalMST(Grafo *graph) 
{ 
    int nV = graph->n_vertices;  // Tnis will store the resultant MST 
    int e = 0;  // An index variable, used for result[] 
    int i = 0;  // An index variable, used for sorted edges 
  
    // Step 1:  Sort all the edges in non-decreasing  
    // order of their weight. If we are not allowed to  
    // change the given graph, we can create a copy of 
    // array of edges 
    qsort(graph->arestas, graph->grau_max, sizeof(graph->arestas[0]),1); 
  
    // Allocate memory for creating V ssubsets 
    struct subset *subsets = 
        (struct subset*) malloc( nV * sizeof(struct subset) ); 
  
    // Create V subsets with single elements 
    for (int v = 0; v < V; ++v) 
    { 
        subsets[v].parent = v; 
        subsets[v].rank = 0; 
    } 
  
    // Number of edges to be taken is equal to V-1 
    while (e < V - 1 && i < graph->grau_max) 
    { 
        // Step 2: Pick the smallest edge. And increment  
        // the index for next iteration 
  
        int x = find(subsets, next_edge.src); 
        int y = find(subsets, next_edge.dest); 
  
        // If including this edge does't cause cycle, 
        // include it in result and increment the index  
        // of result for next edge 
        if (x != y) 
        { 
            result[e++] = next_edge; 
            Union(subsets, x, y); 
        } 
        // Else discard the next_edge 
    } 
  
    // print the contents of result[] to display the 
    // built MST 
    printf("Following are the edges in the constructed MST\n"); 
    for (i = 0; i < e; ++i) 
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, 
                                                 result[i].weight); 
    return; 
} 