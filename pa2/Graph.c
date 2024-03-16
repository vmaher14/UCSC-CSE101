#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

typedef struct GraphObj* Graph;

typedef struct GraphObj {
    List *neighbor;     //An array of Lists whose ith element contains the neighbors of vertex i.
    int *color;         //An array of ints (or chars, or strings) whose ith element is the color (white, gray, black) of vertex i
    int *parent;        //An array of ints whose ith element is the parent of vertex i.
    int *distance;      //An array of ints whose ith element is the distance from the (most recent) source to vertex i.
    int order;          //Number of vertices
    int size;           //Number of edges
    int label;          //Vertex that was most recently used as source for BFS
} GraphObj;

/*** Constructors-Destructors ***/
/*returns a Graph pointing to a newly created GraphObj representing a graph having
n vertices and no edges.*/
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->neighbor = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->distance = calloc(n+1, sizeof(int));
    G->order = n;
    G->size = 0;
    G->label = NIL;
    for (int i = 1; i <= n; i += 1) {
        G->neighbor[i] = newList();
        G->parent[i] = NIL;
        G->distance[i] = INF;
        G->color[i] = WHITE;
    }
    return G;
}

/*frees all heap memory associated with the Graph *pG,
then sets the handle *pG to NULL.*/
void freeGraph(Graph* pG) {
    if (pG !=NULL && *pG!=NULL ) {
        makeNull(*pG);
        free((*pG)->neighbor);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/
//returns order
int getOrder(Graph G) {
    if (G == NULL) {
        printf("Graph error: calling getOrder() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

//returns size
int getSize(Graph G) {
    if (G == NULL) {
        printf("Graph error: calling getSize() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

//returns the source vertex most recently used in BFS()
int getSource(Graph G) {
    if (G == NULL) {
        printf("Graph error: calling getSource() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    if (G->label != NIL) {
        return G->label;
    }
    return NIL;
}

//returns the parents of vertex u in the BFS tree created by BFS()
int getParent(Graph G, int u) {
    if (G == NULL) {
        printf("Graph error: calling getParent() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    if ((u < 1) || u > getOrder(G)) {
        printf("Graph error: u < 1 || u > getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) != NIL) {
        return G->parent[u];
    }
    return NIL;
}

/*returns the distance from
the most recent BFS source to vertex u, or INF if BFS() has not yet been called*/
int getDist(Graph G, int u) {
    if (G == NULL) {
      printf("Graph error: calling getDist() on NULL graph\n");
      exit(EXIT_FAILURE);
    }
    if ((u < 1) || u > getOrder(G)) {
        printf("Graph error: u < 1 || u > getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) != NIL) {
        return G->distance[u];
    }
    return INF;
}   

/*appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if
no such path exists.*/
void getPath(List L, Graph G, int u) {
    if (G == NULL) {
        printf("Graph error: calling getPath() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    if ((u < 1) || u > getOrder(G)) {
        printf("Graph error: u < 1 || u > getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NIL) {
        printf("Graph error: getSource(G) NULL\n");
        exit(EXIT_FAILURE);
    }
    
    if (u == getSource(G)) { 
        append(L, getSource(G));
    }
    else if (getParent(G, u) == NIL) { 
        append(L, NIL);
    }
    else {
        getPath(L, G, getParent(G, u));
        append(L, u);
    }
}

/*** Manipulation procedures ***/
/*deletes all edges of G, restoring it to its 5
original (no edge) state.*/
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

/*inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u. */
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

/*inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency
List of v).*/
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

/*runs the BFS algorithm on the Graph G with source s,
setting the color, distance, parent, and source fields of G accordingly.*/
void BFS(Graph G, int s) {
    if (G == NULL) {
      printf("Graph error: calling BFS() on NULL graph\n");
      exit(EXIT_FAILURE);
    }
    G->label = s;
    for (int i = 1; i <= getOrder(G); i += 1) {
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    //create new queue
    List Q = newList();
    append(Q, s);
    while (length(Q) > 0) {
        int x = front(Q);
        deleteFront(Q);
        moveFront(G->neighbor[x]);
        while (index(G->neighbor[x]) >= 0) {
            int y = get(G->neighbor[x]);
            moveNext(G->neighbor[x]); 
            if (G->color[y] == WHITE) {
                G->color[y] = GRAY;
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(Q, y);   
            }
        }
        G->color[x] = BLACK;
    }
    //free List after done
    freeList(&Q);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G) {
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

