#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#include "list.h"

typedef struct graph* Graph;
typedef struct vertex* Vertex;

/* *** Fonctions du graphe *** */
Graph g_createGraph(int);
Graph g_cloneGraph(Graph);
void g_freeGraph(Graph);
void g_createNeighborhood(Graph);
int g_getSize(Graph);
int g_degreGraph(Graph);
int g_maxDegreVertex(Graph);
int g_findLeafGraph(Graph);
int g_findLeaf(int*, int);
void g_deleteIsolated(Graph);
void g_display(Graph);

/* *** Fonctions sur les aretes *** */
void g_addEdge(Graph, int, int);
void g_deleteEdge(Graph, int, int);
void g_deleteEdges(Graph, int);
bool g_areNeighbor(Graph, int, int);

/* *** Fonctions sur les sommets *** */
Vertex g_createVertex();
Vertex g_cloneVertex(Vertex);
void g_freeVertex(Graph, int);
Vertex g_getVertex(Graph, int);
List g_getNeighbors(Graph, int);
int g_getDegreVertex(Graph, int);

#endif