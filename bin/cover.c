#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

#include "cover.h"
#include "graph.h"
#include "list.h"

// Module de recherche de couverture par sommets

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
  	l_deleteFirstOccur(listNeighbors, val_head); // necessaire ?
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
  int iVert1 = g_maxDegreVertex(g); // a voir si besoin de chercher le sommet de plus haut degre
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
bool littleCoverAlg(Graph g, int k){
  int size = g_getSize(g);
  if (size < k){
    printf("Tous les sommets du graphe sont dans la couverture");
    return true;
  }
  if (k<0){
    printf("k est négatif. Pas de couverture trouvée");
    return false;
  }
  if (g_numberOfEdges(g) > k*(size-1)){
    printf("Le graphe a trop d'arêtes. Pas de couverture de taille %d trouvée",k);
    return false;
  }
  if (g_numberOfEdges(g) == 0){
    printf("Le graphe n'a pas d'arêtes. Tous les sommets sont dans la couverture");
    return true; // il faut retourner la liste de tous les sommets
  }
  // creation liste des degres
  int* degrees = malloc(size*sizeof(int));
  for (int i=0; i<size; i++){
    degrees[i] = g_getDegreVertex(g, i);
  }
  int u = 0;
  while(degrees[u] == 0){
    u++;
  }
  //int v = firstPositive(g_getNeighbors(g, u), degrees); // retourne un voisin de u de degre non nul (donc uv est une arete du graphe)
  //return (littleCoverAlg(  ,k-1) || littleCoverAlg(  ,k-1));

  // Pb : comment generer le graphe G moins u (ou G moins v) ???

  return true;
}
