/*Test client for Graph ADT*/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main (int argc, char* argv[]) {
    //number of vertices
    int vert = 20;      

    //List of the shortest path
    List L = newList();

    //build graph
    Graph G = newGraph(vert);   

    //initialize verticies
    for (int i = 1; i < vert; i += 1) {
        if (i % 5 != 0) {
            addEdge(G, i, i + 1);
        }
        if (i <= 15) {
            addEdge(G, i, i + 5);
        }
    }

    //print graph
    printGraph(stdout, G);

    //print order of graph
    printf("Order of graph: %d\n", getOrder(G));
    printf("\n");

    //print size of graph
    printf("Size of graph: %d\n", getSize(G));
    printf("\n");

    //run BFS
    for (int i = 1; i <= getOrder(G); i += 1) {
        BFS(G, i);
    }

    //print source vertex after BFS and parent of it
    printf("Most recent source vertex used: %d\n", getSource(G));
    printf("Parent of source vertex: %d\n", getParent(G, getOrder(G)));
    printf("\n");

    //print distance from source to specified vertex
    int num = 10;
    printf("Distance from source to vertex 5: %d\n", getDist(G, num));
    printf("\n");

    //print shorted path from source to specified vertex
    printf("shortest path: ");
    getPath(L, G, num);
    printList(stdout, L);
    printf("\n");

    //free allocated memory
    freeList(&L);
    freeGraph(&G);

}