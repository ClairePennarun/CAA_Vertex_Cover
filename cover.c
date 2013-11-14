// Module de recherche de couverture par sommets
#include "cover.h"
#include "graph.h"
#include <malloc.h>

int maxDegreeVertex(int* degrees, int size){
  int maxVertex = 0 ;
  int maxDegree = 0 ;
  for (int i=0; i < size; i++){
    if (degrees[i] > maxDegree)
      maxVertex = i;
  }
  return maxVertex;
}

// Algorithme glouton : graphes quelconques
List greedyAlg (Graph g){
  List cover = list_createList();
  int degmax = 1;
  int* degrees = malloc(size(g)*sizeof(int));
  for (int i = 0; i< size(g); i++){
    degrees[i] = list_size(neighbor(g,i));
  }
  while(degmax !=0){
    int v = maxDegreeVertex(degrees, size(g));
    degmax = degrees[v];
    if (degmax != 0)
      list_insertInHead(cover, v);
    List listNeighbors = neighbor(g,v);
    degrees[v] = 0;
    while (listNeighbors != NULL){
      degrees[list_elemVal(list_head(listNeighbors))] --;
      listNeighbors = list_tail(listNeighbors);
    }
  }
  return cover;
}

// Algo optimal : arbres
int* treeOptAlg(Graph g){
}

// Algo optimal : graphes bipartis
int* bipartiteOptAlg (Graph g){
}

// Algo 2-approche par arbres couvrants
int* spanningTreeAlg(Graph g){
}

// Algo 2-approche par elimination d'aretes
int* edgesDeletionAlg(Graph g){
}

// Algo optimal petite couverture
int* littleCoverAlg(Graph g){
}
