// Module de recherche de couverture par sommets
#include "cover.h"
#include "graph.h"
#include "list.h"
#include <malloc.h>

int firstPositive(List, int*);

// Algorithme glouton : graphes quelconques
List greedyAlg (Graph g){
  List cover = l_createList();
  int degmax = 1;
  int v;
  while(degmax !=0){                  // Tant que le graphe n'est pas vide
    v = g_maxDegreVertex(g);          // On cherche le sommet avec deg max
    degmax = g_getDegreVertex(g, v);
    if (degmax != 0){
      l_addInFront(cover, v);         // On le met dans la couverture
      g_deleteEdges(g, v);            // On supprime les aretes adjacentes à v  
    }
  }
  return cover;
}

// Algo optimal : arbres
List treeOptAlg(Graph g){
  List cover = l_createList();
  bool nonEmpty = 1;
  int size = g_getSize(g);
  int* degrees = malloc(size*sizeof(int));
  List listNeighbors;
  int val_head;

  for (int i=0; i<size; i++){
    degrees[i] = g_getDegreVertex(g, i);
  }
  while(nonEmpty == 1){                                        // Tant que le graphe n'est pas vide
    int v = g_findLeaf(degrees, size);
    if (v == -1)
      nonEmpty = 0;
    else{
      int w = firstPositive(g_getNeighbors(g, v), degrees);    // On cherche un voisin de v de degre non nul
      l_addInFront(cover, w);                                  // On le met dans la couverture
      degrees[w]= 0;                                           // On met a jour son degre
      listNeighbors = g_getNeighbors(g, w);
      l_head(listNeighbors);
      while (!l_isOutOfList(listNeighbors)){                   // On met a jour les degres de ses voisins
  	val_head = l_getVal(listNeighbors);
  	degrees[val_head]--;
  	l_deleteFirstOccur(listNeighbors, val_head);
      }
    }
  }
  return cover;
}

int firstPositive(List l, int* degrees){
  l_head(l);
  int val;
  while (!l_isOutOfList(l)){
    val = l_getVal(l);
    if (degrees[val] > 0)
      return (val);
    l_next(l);
  }
  return -1;
}

// Algo optimal : graphes bipartis
int* bipartiteOptAlg (Graph g){
  return NULL;
}

// Algo 2-approche par arbres couvrants
int* spanningTreeAlg(Graph g){
  return NULL;
}

// Algo 2-approche par elimination d'aretes
List edgesDeletionAlg(Graph g){
  List cover = l_createList();
  int iVert1 = g_maxDegreVertex(g);
  int deg1 = g_getDegreVertex(g, iVert1);
  int iVert2;
  List neighbors;
  while(deg1 != 0){
    neighbors = g_getNeighbors(g, iVert1);
    l_head(neighbors);
    iVert2 = l_getVal(neighbors);
    l_addInFront(cover, iVert1);
    l_addInFront(cover, iVert2);
    g_deleteEdges(g, iVert1);
    g_deleteEdges(g, iVert2);
    iVert1 = g_maxDegreVertex(g);
    deg1 = g_getDegreVertex(g, iVert1);
  }
  return cover;
}

// Algo optimal petite couverture
int* littleCoverAlg(Graph g){
  return NULL;
}
