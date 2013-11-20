#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include "list.h"

typedef struct graph* Graph;
typedef struct vertex* Vertex;

struct edge{
  int src;
  int tgt;
};

Graph createGraph(int size);
Vertex createVertex();
int size(Graph); // retourne le nombre de sommets du graphe
void displayVertices(Graph);
List neighbor(Graph, int);

/* *** Fonctions sur les aretes *** */
void addEdge(Graph, int i1, int i2);
void deleteEdge(Graph, int i1, int i2);
void deleteEdges(Graph, int v);
bool areNeighbor(Graph, int i1, int i2);
struct edge findEdge(Graph);

/* *** Fonctions sur les sommets *** */
int maxDegreeVertex(Graph);
int findLeafGraph(Graph);
int findLeaf(int* degrees, int size);
void deleteIsolated(Graph);



#endif
