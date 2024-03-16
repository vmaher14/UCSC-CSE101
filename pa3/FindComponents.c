//------------------------------------------------------------------------------
// Victor Maher - CSE 101 pa3
// CruzID - Vmaher
//------------------------------------------------------------------------------
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
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

    //run DFS on G and G transposed
    List S = newList();
    for (int i = 1; i <= getOrder(G); i += 1) {
        append(S, i);
    }
    DFS(G, S);
    Graph T = transpose(G);
    DFS(T, S);

    //print out strongly connected components
    int cnt = 0;
    moveBack(S);
    while (index(S) >= 0) {
        int x = get(S);
        movePrev(S);
        if (getParent(T, x) == NIL) {
            cnt += 1;
        }
    }
    fprintf(out, "G contains %d strongly connected components:\n", cnt);

    //reverse list
    int cmp = 0;
    List O = copyList(S);
    moveBack(S);
    moveBack(O);
    while (index(O) >= 0) {
        int x = get(S);
        movePrev(S);
        movePrev(O);
        if (getParent(T, x) == NIL) {
            cmp += 1;
            fprintf(out, "Component %d: ", cmp);
            fprintf(out, "%d ", x);
            moveNext(S);
            if (index(S) < 0) {
                moveFront(S);
            }
            while ((getParent(T, x) != NIL) || (index(S) >= 0)) {
                if (index(S) == length(S) - 1) {
                    break;
                }
                moveNext(S);
                x = get(S);
                if (getParent(T, x) == NIL) {
                    break;
                } 
                fprintf(out, "%d ", x);
                
            }
            fprintf(out, "\n");
        }
        while (index(O) != index(S)) {
            movePrev(S);
        }
    }


    //free allocated memory by lists and graphs
    freeList(&S);
    freeList(&O);
    freeGraph(&G);
    freeGraph(&T);

    //close files
    fclose(in);
    fclose(out);
    
}
