// Module de recherche de couverture par sommets
#include "cover.h"
#include "graph.h"
#include <malloc.h>

// Algorithme glouton : graphes quelconques
List greedyAlg (Graph g){
  List cover = list_createList();
  int degmax = 1;
  while(degmax !=0){ // tant que le graphe n'est pas vide
    int v = maxDegreeVertex(g); // on cherche le sommet avec deg max
    degmax = list_size(neighbor(g,v));
    if (degmax != 0){
      //printf("on rajoute le sommet %d \n", v+1);
      list_addInFront(cover, v+1); // on le met dans la couverture
      deleteEdges(g, v); // on supprime les aretes adjacentes à v  
    }
  }
  return cover;
}

// Algo optimal : arbres
List treeOptAlg(Graph g){
  List cover = list_createList();
  int degmax = 1;
  while(degmax !=0){ // tant que le graphe n'est pas vide
    int v = findLeaf(g);
    int w = list_elemVal(list_head(neighbor(g,v))); // voisin (unique) de v
    //printf("on rajoute le sommet %d \n", w);
    list_addInFront(cover, w); // on le met dans la couverture
    deleteEdges(g, w); // on supprime les aretes adjacentes à w
    deleteIsolated(g);
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
