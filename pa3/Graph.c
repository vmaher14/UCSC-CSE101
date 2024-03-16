//------------------------------------------------------------------------------
// Victor Maher - CSE 101 pa3
// CruzID - Vmaher
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Graph.h"

typedef struct GraphObj* Graph;

typedef struct GraphObj {
    List *neighbor;     //An array of Lists whose ith element contains the neighbors of vertex i.
    int *color;         //An array of ints (or chars, or strings) whose ith element is the color (white, gray, black) of vertex i
    int *parent;        //An array of ints whose ith element is the parent of vertex i.
    int *dtime;         //Discover time of vertex when calling DFS
    int *ftime;         //Finish time of vertex when calling DFS
    int order;          //Number of vertices
    int size;           //Number of edges
} GraphObj;

// Constructors-Destructors
//return a reference to a new graph object containing n vertices and no edges
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->neighbor = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->dtime = calloc(n+1, sizeof(int));
    G->ftime = calloc(n+1, sizeof(int));
    G->order = n;
    G->size = 0;
    for (int i = 1; i <= n; i += 1) {
        G->neighbor[i] = newList();
        G->dtime[i] = UNDEF;
        G->ftime[i] = UNDEF;
        G->parent[i] = NIL;
        G->color[i] = WHITE;
    }
    return G;
}

//frees all heap memory associated with a graph and sets its Graph argument to NULL
void freeGraph(Graph* pG) {
    if (pG !=NULL && *pG!=NULL ) {
        makeNull(*pG);
        free((*pG)->neighbor);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->ftime);
        free((*pG)->dtime);
        free(*pG);
        *pG = NULL;
    }
}

// Access functions
//returns the number of vertices in G
int getOrder(Graph G) {
    if (G == NULL) {
        printf("Graph error: calling getOrder() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

//return the appropriate field values for the given vertex
int getSize(Graph G) {
    if (G == NULL) {
        printf("Graph error: calling getSize() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

//return the appropriate field values for the given vertex
/* Pre: 1<=u<=n=getOrder(G) */
int getParent(Graph G, int u) {
    if (G == NULL) {
        printf("Graph error: calling getParent() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    if ((u < 1) || u > getOrder(G)) {
        printf("Graph error: u < 1 || u > getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    if (G->parent[u] != NIL) {
        return G->parent[u];
    }
    return NIL;
}

//return the appropriate field values for the given vertex
/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u) {
    if (G == NULL) {
        printf("Graph error: calling getDiscover() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    if ((u < 1) || u > getOrder(G)) {
        printf("Graph error: u < 1 || u > getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    if (G->dtime[u] != UNDEF) {
        return G->dtime[u];
    }
    return UNDEF;
}

//return the appropriate field values for the given vertex
/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u) {
    if (G == NULL) {
        printf("Graph error: calling getFinish() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    if ((u < 1) || u > getOrder(G)) {
        printf("Graph error: u < 1 || u > getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    if (G->ftime[u] != UNDEF) {
        return G->ftime[u];
    }
    return UNDEF;
}

// Manipulation procedures
//deletes all edges of G, restoring it to its 5 original (no edge) state
//helper function for free graph
void makeNull(Graph G) {
    if (G == NULL) {
      printf("Graph error: calling makeNULL() on NULL graph\n");
      exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i += 1) {
        clear(G->neighbor[i]);
        freeList(&G->neighbor[i]);
    }
    G->size = 0;
}

//inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency
//List of v)
/* Pre: 1<=u<=n, 1<=v<=n */
void addArc(Graph G, int u, int v) {
    if (G == NULL) {
    printf("Graph error: calling addArc() on NULL graph\n");
    exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        printf("Graph error: calling addArc() with ints out of range\n");
        exit(EXIT_FAILURE);
    }
    if (length(G->neighbor[u]) == 0) {
        append(G->neighbor[u], v);
        G->size += 1;
    }   
    bool found = false;
    moveFront(G->neighbor[u]);
    while (found == false) {   
        if (index(G->neighbor[u]) < 0) {
            moveFront(G->neighbor[u]);
        }
        if (get(G->neighbor[u]) == v) {
            break;
        }
        if (get(G->neighbor[u]) < v) {
            moveNext(G->neighbor[u]);
            if (index(G->neighbor[u]) < 0) {
                append(G->neighbor[u], v);
                G->size += 1;
                found = true;
            }
        } else {
            insertBefore(G->neighbor[u], v);
            G->size += 1;
            found = true;
        }
    } 
}

//inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u
/* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
      printf("Graph error: calling addEdge() on NULL graph\n");
      exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        printf("Graph error: calling addEdge() with ints out of range\n");
        exit(EXIT_FAILURE);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size -= 1;
}


//helper function for DFS
void visit(Graph G, int x, int *t) {
    *t += 1;
    G->dtime[x] = *t;
    G->color[x] = GRAY;
    moveFront(G->neighbor[x]);
    while(index(G->neighbor[x]) >= 0) {
        int y = get(G->neighbor[x]);
        moveNext(G->neighbor[x]);
        if (G->color[y] == WHITE) {
            G->parent[y] = x;
            visit(G, y, t);
        }
    }
    G->color[x] = BLACK;
    *t += 1;
    G->ftime[x] = *t;
}

//perform the depth first search algorithm on G
 /* Pre: length(S)==getOrder(G) */
 //need to sort finish time in descending order
void DFS(Graph G, List S) {
    if (G == NULL) {
      printf("Graph error: calling DFS() on NULL graph\n");
      exit(EXIT_FAILURE);
    }
    if (length(S) != getOrder(G)) {
        printf("Graph error: calling DFS() where length(S) != getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i += 1) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }
    int time = 0;
    int *t = &time; 

    moveFront(S);
    while (index(S) >= 0) {
        int x = get(S);
        moveNext(S);
        if (G->color[x] == WHITE) {
            visit(G, x, t);
        }
    }
    //sort in descending order by finish time
    List O = newList();
    append(O, 1);
    for (int i = 2; i <= getOrder(G); i += 1) {
        bool ord = false;
        moveFront(O);
        while ((ord == false)) {
            if (index(O) < 0) {
                moveFront(O);
            }
            if (G->ftime[get(O)] > G->ftime[i]) {
                moveNext(O);
                if (index(O) < 0) {
                    append(O, i);
                    ord = true;
                }
            } else {
                insertBefore(O, i);
                ord = true;
            }
        }
    }
    clear(S);
    moveFront(O);
    while (index(O) >= 0) {
        int x = get(O);
        append(S, x);
        moveNext(O);
    }
    freeList(&O);
}

// Other Functions
//returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G) {
    Graph T = newGraph(G->order);
    for (int i = 1; i <= getOrder(G); i += 1) {
        moveFront(G->neighbor[i]);
        while (index(G->neighbor[i]) >= 0) {
            int x = get(G->neighbor[i]);
            addArc(T, x, i);
            moveNext(G->neighbor[i]);
        }
    }
    return T;
}

//returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G) {
    Graph C = newGraph(G->order);
    for (int i = 1; i <= getOrder(G); i += 1) {
        moveFront(G->neighbor[i]);
        while (index(G->neighbor[i]) >= 0) {
            int x = get(G->neighbor[i]);
            addArc(C, i, x);
            moveNext(G->neighbor[i]);
        }
    }
    return C;
}

//prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out , Graph G) {
    if (G == NULL) {
      printf("Graph error: calling printGraph() on NULL graph\n");
      exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i += 1) {
        fprintf(out, "%d: ", i);
        printList(out, G->neighbor[i]);
    }
    fprintf(out, "\n");
}
