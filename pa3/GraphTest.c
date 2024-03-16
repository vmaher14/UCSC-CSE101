/*Test client for Graph ADT*/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main (int argc, char* argv[]) {
    //number of vertices
    int vert = 20;      

    //build graph
    Graph G = newGraph(vert);   

    //initialize verticies
    for (int i = 1; i <= vert; i += 1) {
        if (i % 5 != 0) {
            addArc(G, i, i + 1);
        }
        if (i <= 15) {
            addArc(G, i, i + 5);
        }
    }

    //print graph
    printGraph(stdout, G);

    //print order of graph
    printf("Order of graph: %d\n", getOrder(G));
    printf("\n");

    // //print size of graph
    printf("Size of graph: %d\n", getSize(G));
    printf("\n");

    // //run DFS
    List S = newList();
    for (int i = 1; i <= getOrder(G); i += 1) {
        append(S, i);
    }
    DFS(G, S);

    //print parent, discover and finish time
    for (int i = 1; i <= getOrder(G); i += 1) {
        printf("Parent: %d, Discover: %d, Finish: %d\n", getParent(G,i), getDiscover(G, i), getFinish(G, i));
    }
    printf("\n");

    //print copy and tranpose of graph
    Graph T = NULL;
    Graph C = NULL;
    T = transpose(G);
    C = copyGraph(G); 
    printf("Tranpose of G:\n");
    printGraph(stdout, T);
    printf("Copy of G:\n");
    printGraph(stdout, C);
    
    //free allocated memory
    freeList(&S);
    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);

}