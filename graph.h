#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include "list.h"

typedef struct graph* Graph;
typedef struct vertex* Vertex;

Graph createGraph(int size);
Vertex createVertex();
void addEdge(Graph, int i1, int i2);
void deleteEdge(Graph, int i1, int i2);
bool areNeighbor(Graph, int i1, int i2);
List neighbor(Graph, int);

int size(Graph); // retourne le nombre de sommets du graphe

#endif
