#include <assert.h>
#include <malloc.h>
#include <stdbool.h>

#include "graphe.h"
#include "list.h"

struct graph{
  Vertex* allVertices;
  int** neighborhood;
  int numberOfVertices;
  int isConstruct;
};

struct vertex{
  List neighbor;
};

Graph
createGraph(int size){
  Graph newGraph = malloc(sizeof(struct graph));
  assert(newGraph);
  newGraph->allVertices = malloc(sizeof(struct vertex)*size);
  assert(newGraph->allVertices);
  newGraph->numberOfVertices = size;
  newGraph->isConstruct = 0;
  for (int i=0; i<size; i++)
    (newGraph->allVertices)[i] = createVertex();
  return newGraph;
}

Vertex
createVertex(){
  Vertex newVertex = malloc(sizeof(struct vertex));
  assert(newVertex);
  newVertex->neighbor = list_createList();
  return newVertex;
}

void
addEdge(Graph g, int i1, int i2){
  Vertex v1 = (g->allVertices)[i1];
  Vertex v2 = (g->allVertices)[i2];
  list_addInFront(v1->neighbor, i2);
  list_addInFront(v2->neighbor, i1);
}

void
deleteEdge(Graph g, int i1, int i2){
  // Il faut que l'arete existe reellement
  Vertex v1 = (g->allVertices)[i1];
  Vertex v2 = (g->allVertices)[i2];
  list_deleteFirstOccur(v1->neighbor, i2);
  list_deleteFirstOccur(v2->neighbor, i1);
}

bool
areNeighbor(Graph g, int i1, int i2){
  Vertex v1 = (g->allVertices)[i1];
  return list_contain(v1->neighbor, i2);
}

List
neighbor(Graph g, int i1){
  Vertex v1 = (g->allVertices)[i1];
  return v1->neighbor;
}
  
