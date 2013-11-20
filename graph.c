#include <assert.h>
#include <malloc.h>
#include <stdbool.h>

#include "graph.h"
#include "list.h"

struct graph{
  Vertex* allVertices; //tableau des listes de voisinage
  int** neighborhood; //matrice d'adjacence globale
  int numberOfVertices;
  int isConstruct;
};

struct vertex{
  List neighbor; //liste des voisins
};

Graph createGraph(int size){
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

Vertex* vertices(Graph g){
  return g->allVertices;
}

int size(Graph g){
  return g->numberOfVertices;
}

List neighbor(Graph g, int i1){
  Vertex v1 = (g->allVertices)[i1];
  return v1->neighbor;
}

void displayVertices(Graph g){
  for (int i =0; i< size(g); i++){
    List l = neighbor(g,i);
    display(l);
  }
}

Vertex createVertex(){
  Vertex newVertex = malloc(sizeof(struct vertex));
  assert(newVertex);
  newVertex->neighbor = list_createList();
  return newVertex;
}

/* ***  Fonctions sur les aretes *** */

void addEdge(Graph g, int i1, int i2){
  Vertex v1 = (g->allVertices)[i1-1];
  Vertex v2 = (g->allVertices)[i2-1];
  list_addInFront(v1->neighbor, i2);
  list_addInFront(v2->neighbor, i1);
}

// suppression de l'arete entre i1 et i2
void deleteEdge(Graph g, int i1, int i2){
  // Il faut que l'arete existe
  Vertex v1 = (g->allVertices)[i1-1];
  Vertex v2 = (g->allVertices)[i2-1];
  list_deleteFirstOccur(v1->neighbor, i2);
  list_deleteFirstOccur(v2->neighbor, i1);
}

// suppression des aretes adjacentes a v
void deleteEdges(Graph g, int v){
  List listNeighbors = neighbor(g,v);
  while (list_head(listNeighbors) != NULL){
    Elem head = list_head(listNeighbors);
    int val_head = list_elemVal(head);
    List neighbors_val_head = neighbor(g,val_head-1);
    list_deleteFirstOccur(neighbors_val_head,v+1);
    listNeighbors = list_tail(listNeighbors);
  }
}

struct edge findEdge(Graph g){
  //int* edge = malloc(2*sizeof(int));
  struct edge e = {-1, -1};
  for (int i =0; i< size(g); i++){
    List list_neighbors = neighbor(g,i);
    if (list_size(list_neighbors) > 0){
	e.src = i;
	e.tgt = list_elemVal(list_head(list_neighbors));
    }
  }
  return e;
}

// test de voisinage
bool areNeighbor(Graph g, int i1, int i2){
  Vertex v1 = (g->allVertices)[i1-1];
  return list_contain(v1->neighbor, i2);
}


/* *** Fonctions sur les sommets *** */

// retourne le sommet de degre le plus grand
int maxDegreeVertex(Graph g){
  int maxVertex = 0 ;
  int maxDegree = 0 ;
  for (int i=0; i < size(g); i++){
    int deg = list_size(neighbor(g,i));
    if (deg > maxDegree){
      maxVertex = i;
      maxDegree = deg;
    }
  }
  return maxVertex;
}

// retourne une feuille (si g est un arbre non vide il y en a toujours une)

int findLeaf(int* degrees, int size){
  for (int i=0; i<size; i++){
    if (degrees[i] == 1)
      return i;
  }
  return -1;
}
