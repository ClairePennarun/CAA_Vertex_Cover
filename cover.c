// Module de recherche de couverture par sommets
#include "cover.h"
#include "graph.h"
#include "list.h"
#include <malloc.h>

// Algorithme glouton : graphes quelconques
List greedyAlg (Graph g){
  List cover = list_createList();
  int degmax = 1;
  while(degmax !=0){ // tant que le graphe n'est pas vide
    int v = maxDegreeVertex(g); // on cherche le sommet avec deg max
    degmax = list_size(neighbor(g,v));
    if (degmax != 0){
      list_addInFront(cover, v+1); // on le met dans la couverture
      deleteEdges(g, v); // on supprime les aretes adjacentes à v  
    }
  }
  return cover;
}

// Algo optimal : arbres
List treeOptAlg(Graph g){
  List cover = list_createList();
  bool nonEmpty = 1;
  int* degrees = malloc(size(g)*sizeof(int));
  for (int i=0; i < size(g); i++){
    degrees[i] = list_size(neighbor(g,i));
  }
  while(nonEmpty == 1){ // tant que le graphe n'est pas vide
    int v = findLeaf(degrees, size(g));
    if (v == -1)
      nonEmpty = 0;
    else{
      Elem e = firstPositive(neighbor(g,v), degrees);
      int w = list_elemVal(e);
      list_addInFront(cover, w); // on le met dans la couverture
      degrees[w-1]= 0;
      List listNeighbors = neighbor(g,w-1);
      while (list_head(listNeighbors) != NULL){
  	Elem head = list_head(listNeighbors);
  	int val_head = list_elemVal(head);
  	List neighbors_val_head = neighbor(g,val_head-1);
  	degrees[val_head-1] --;
  	listNeighbors = list_tail(listNeighbors);
      }
    }
  }
  return cover;
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
