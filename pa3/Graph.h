//------------------------------------------------------------------------------
// Victor Maher - CSE 101 pa3
// CruzID - Vmaher
//------------------------------------------------------------------------------
#include <stdio.h>
#include "List.h"

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#define UNDEF -1
#define NIL 0

#define WHITE -2
#define GRAY -3
#define BLACK -4

typedef struct GraphObj* Graph;
// Constructors-Destructors
Graph newGraph(int n);
void freeGraph(Graph* pG);
// Access functions
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
// Manipulation procedures
void makeNull(Graph G); //Helper function
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void visit(Graph G, int x, int *time); //Helper function
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */
// Other Functions
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);

#endif