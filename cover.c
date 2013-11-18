// Module de recherche de couverture par sommets
#include "cover.h"
#include "graph.h"
#include <malloc.h>

int maxDegreeVertex(int* degrees, int size){
  int maxVertex = 0 ;
  int maxDegree = 0 ;
  for (int i=0; i < size; i++){
    if (degrees[i] > maxDegree){
      maxVertex = i;
      maxDegree = degrees[i];
    }
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
  while(degmax !=0){ // tant que le graphe n'est pas vide
    int v = maxDegreeVertex(degrees, size(g)); // on cherche le sommet avec deg max
    degmax = degrees[v];
    if (degmax != 0){
      printf("on rajoute le sommet %d \n", v+1);
      list_insertInHead(cover, v+1); // on le met dans la couverture
      List listNeighbors = neighbor(g,v);
      degrees[v] = 0; // on met a jour les degres
      while (list_head(listNeighbors) != NULL){
	Elem head = list_head(listNeighbors);
	int val_head = list_elemVal(head);
	List neighbors_val_head = neighbor(g,val_head-1);
	list_deleteFirstOccur(neighbors_val_head,v+1);
	degrees[val_head-1] --;
	listNeighbors = list_tail(listNeighbors);
      }
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
