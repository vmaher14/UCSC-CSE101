#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *in;
    FILE *out;

    //checks command line for correct number of arguments;
    if (argc != 3) {
        printf("Can only accept 2 arguments, <input file> <output file>\n");
        exit(1);
    }
    //open file for reading
    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file for reading\n");
        exit(1);
    }
    //open file for writing
    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file for writing\n");
        exit(1);
    }

    //number of vertexes
    int num;
    fscanf(in, "%d", &num);

    //make new graph
    Graph G = newGraph(num);

    //loop through file until hit first set of 0
    int vert = 0;
    int edge = 0;
    while (fscanf(in, "%d %d \n", &vert, &edge) && (vert != 0)) {
        addArc(G, vert, edge);
        addEdge(G, vert, edge);
    }
    printGraph(out, G);
    
    //loop through second half of file to get paths
    //create List for getPath and printList()
    while (fscanf(in, "%d %d \n", &vert, &edge) && (vert != 0)) {
        BFS(G, vert);
        List L = newList();
        if (getDist(G, edge) == INF) {
            fprintf(out, "The distance from %d to %d is infinity\n", vert, edge);
            fprintf(out, "No %d-%d path exists\n", vert, edge);
            fprintf(out, "\n");
        } else {
            getPath(L, G, edge);
            fprintf(out, "The distance from %d to %d is %d\n", vert, edge, getDist(G, edge));
            fprintf(out, "A shortest %d-%d path is: ", vert, edge);
            printList(out, L);
            fprintf(out, "\n");
        }
        freeList(&L);

    }

    makeNull(G);
    freeGraph(&G);
    fclose(in);
    fclose(out);
}