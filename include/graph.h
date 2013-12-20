#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#include "list.h"

typedef struct graph* Graph;
typedef struct vertex* Vertex;

/* *** Fonctions du graphe *** */
Graph g_createGraph(int);
Graph g_createOrientedGraph(int);
Graph g_cloneGraph(Graph);
void g_freeGraph(Graph);
bool g_isOriented(Graph);
int g_getSize(Graph);
void g_display(Graph);

/* *** Fonctions sur les aretes *** */
void g_addEdge(Graph, int, int);
void g_deleteEdges(Graph, int);
bool g_areNeighbor(Graph, int, int);
int g_numberOfEdges(Graph);

/* *** Fonctions sur les sommets *** */
int g_maxDegreeVertex(Graph);
Vertex g_createVertex();
Vertex g_cloneVertex(Vertex);
void g_freeVertex(Graph, int);
int g_getPositiveDegreeVertex(Graph,int i);
Vertex g_getVertex(Graph, int);
List g_getNeighbors(Graph, int);
int g_getDegreeVertex(Graph, int);

#endif
