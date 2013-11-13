#include <assert.h>
#include <malloc.h>
#include <stdbool.h>

#include "graphe.h"
#include "list.c"

struct graph
{
  Vertice* allVertices;
  int** neighborhood;
  int numberOfVertices;
  int isConstruct;
}

struct vertice
{
  List neighbor;
};

Graph
createGraph(int size){
  Graph newGraph = malloc(sizeof(struct graph));
  assert(newGraph);
  newGraph->allVertice = malloc(sizeof(struct vertice)*size);
  assert(newGraph->allVertice);
  newGraph->numberOfVertices = size;
  newGraph->isConstruct = 0;
  for (int i=0; i<size; i++)
    (newGraph->allVertice)[i] = createVertice();
  return newGraph;
}

Vertice
createVertice(){
  Vertice newVertice = malloc(sizeof(struct vertice));
  assert(newVertice);
  newVertice->neighbor = list_createList();
  return newVertice;
}

void
addEdge(Graph g, int i1, int i2){
  Vertice v1 = (g->allVertices)[i1];
  Vertice v2 = (g->allVertices)[i2];
  list_addInFront(v1->neighbor, i2);
  list_addInFront(v2->neighbor, i1);
}

void
deleteEdge(Graph g, int i1, int i2){
  // Il faut que l'arête existe réellement
  Vertice v1 = (g->allVertices)[i1];
  Vertice v2 = (g->allVertices)[i2];
  list_deleteFirstOccur(v1->neighbor, i2);
  list_deleteFirstOccur(v2->neighbor, i1);
}

boolean
areNeighbor(Graph g, int i1, int i2){
  Vertice v1 = (g->allVertices)[i1];
  return list_contain(v1->neighbor, i2);
}

List
neighbor(Graph g, int i1){
  Vertice v1 = (g->allVertices)[i1];
  return v1->neighbor;
}
  
