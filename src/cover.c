#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#include "cover.h"
#include "graph.h"
#include "list.h"

// Module de recherche de couverture par sommets

// retourne le premier sommet de la liste l ayant un degre positif
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

/* On met a jour les valeurs dans le tableau des degres 
et on supprime le sommet dans le voisinage de ses voisins
*/
void deleteVertexDegrees(Graph g, int* degrees, int v){
  degrees[v] = 0;                                           // On met a jour son degre
  List listNeighbors = g_getNeighbors(g, v);
  l_head(listNeighbors);
  int val_head;
  while (!l_isOutOfList(listNeighbors)){                    // On met a jour les degres de ses voisins
    val_head = l_getVal(listNeighbors);
    degrees[val_head]--;
    l_deleteFirstOccur(listNeighbors, val_head);
  }
}

// retourne une feuille (utilise le tableau des degres)
int findLeaf(int* degrees, Graph g){
  for (int i=0; i< g_getSize(g); i++){
    if (degrees[i] == 1)
      return i;
  }
  return -1;
}

// Algorithme glouton : graphes quelconques
List greedyAlg (Graph g){
  List cover = l_createList();
  int degmax = 1;
  int n = g_getSize(g);
  int* degrees = malloc(n*sizeof(int));
  for (int i = 0; i< n; i++){
    degrees[i] = l_size(g_getNeighbors(g,i));
  }
  while(degmax >0){ // tant que le graphe n'est pas vide
    int v = g_maxDegreeVertex(g); // on cherche le sommet avec deg max
    degmax = degrees[v];
    if (degmax > 0){
      l_insertInHead(cover, v); // on le met dans la couverture
      deleteVertexDegrees(g,degrees,v);
    }
  }
  free(degrees);
  return cover;
}

// Algo optimal : arbres
List treeOptAlg(Graph g){
  List cover = l_createList();
  bool nonEmpty = 1;
  int size = g_getSize(g);
  int* degrees = malloc(size*sizeof(int));

  for (int i=0; i<size; i++){
    degrees[i] = g_getDegreeVertex(g, i);
  }
  while(nonEmpty == 1){                                        // Tant que le graphe n'est pas vide
    int v = findLeaf(degrees,g);
    if (v == -1)
      nonEmpty = 0;
    else{
      int w = firstPositive(g_getNeighbors(g, v), degrees);    // On cherche un voisin de v de degre non nul
      l_addInFront(cover, w);                                  // On le met dans la couverture
      deleteVertexDegrees(g,degrees,w);
    }
  }
  free(degrees);
  return cover;
}

// Algo optimal : graphes bipartis
int* bipartiteOptAlg (Graph g){
  return NULL;
}

// Algo 2-approche par arbres couvrants
void dfs(Graph g, int i, List cover, int* color){
  if(color[i] == 1) // on a deja visité le sommet
    return;
  color[i] = 1;
  List listNeighbors = g_getNeighbors(g,i);
  l_head(listNeighbors);
  int val_head;
  bool isInCover = false;
  while(!l_isOutOfList(listNeighbors)){
    val_head = l_getVal(listNeighbors);
    l_next(listNeighbors);
    if (color[val_head] == 0 && !isInCover){
      isInCover = true;
      l_addInFront(cover,i);
    }
    dfs(g,val_head,cover,color);
  }
}

List spanningTreeAlgRec(Graph g){
  List cover = l_createList();
  int sizeGraph = g_getSize(g);
  int* color = malloc(sizeGraph*sizeof(int));
  assert(color);
  for (int i=0; i < sizeGraph; i++){
    color[i] = 0;
  }
  dfs(g, 0, cover, color);
  return cover;
}

List spanningTreeAlg(Graph g){
  List cover = l_createList();
  int sizeGraph = g_getSize(g);
  int* color = malloc(sizeGraph*sizeof(int));
  int* parent = malloc(sizeGraph*sizeof(int));
  List searchList = l_createList();
  assert(color);
  assert(parent);
  for (int i=0; i < sizeGraph; i++){
    color[i] = 0; // 0 = blanc
    parent[i] = -1;
  }
  color[0] = 1; // 1 = gris
  l_insertInHead(searchList,0);
  l_head(searchList);
  while(!l_isOutOfList(searchList)){
    bool isInCover = false;
    int u =  l_getVal(searchList);
    l_deleteFirstOccur(searchList,u);
    if (color[u] != 2){
      color[u] = 2; // 2 = noir
      List neighbors = g_getNeighbors(g,u);
      l_head(neighbors);
      int v;
      while(!l_isOutOfList(neighbors)){
	v = l_getVal(neighbors);
	l_next(neighbors);
	if (color[v] != 2){
	  color[v] = 1;
	  parent[v] = u;
	  l_insertInHead(searchList, v);
	  if (!isInCover){
	    l_addInFront(cover, u);
	    isInCover = true;
	  }
	}
      }
    }
  }
  free(color);
  free(parent);
  return cover;
}

// Algo 2-approche par elimination d'aretes
List edgesDeletionAlg(Graph g){
  List cover = l_createList();
  int v1 = g_getPositiveDegreeVertex(g,0);
  if (v1 == -1)
    return cover;
  int deg1 = g_getDegreeVertex(g, v1);
  int v2;
  List neighbors;
  while(deg1 > 0){
    neighbors = g_getNeighbors(g, v1);
    l_head(neighbors);
    v2 = l_getVal(neighbors);
    l_addInFront(cover, v1);
    l_addInFront(cover, v2);
    g_deleteEdges(g, v1);
    g_deleteEdges(g, v2);
    v1 = g_getPositiveDegreeVertex(g, v1);
    if (v1 == -1)
      return cover;
    deg1 = g_getDegreeVertex(g, v1);
  }
  return cover;
}

List littleCover(Graph g, int k){
  int l = 0; // Nombre de sommets de degre trop grand
  int m = 0; // Nombre de sommets isoles
  int n = g_getSize(g);

  int* bigDegrees = malloc(n*sizeof(int));
  int* nullDegrees = malloc(n*sizeof(int));
  assert(bigDegrees);
  assert(nullDegrees);

  for (int i = 0; i < n; i++){
    int degree = g_getDegreeVertex(g, i);
    if (degree > k)
      bigDegrees[l++] = i;
    if (degree == 0)
      nullDegrees[m++] = i;
  }
  int k1 = k-l;
  if (k1 <= 0){
    free(bigDegrees);
    free(nullDegrees);
    return NULL;
  }
  if (l > 0){
    for (int i = 0; i<=l; i++){
      int u = bigDegrees[i];
      g_deleteEdges(g,u);
      g_freeVertex(g,u);
    }
  }
  if (m > 0){
    for (int i = 0; i<=m; i++){
      int u = nullDegrees[i];
      g_freeVertex(g,u);
    }
  }
  if (g_numberOfEdges(g) > k*k1){
    free(bigDegrees);
    free(nullDegrees);
    return NULL;
  }
  List cover = littleCoverAlg(g, k1, n-l);
  for (int i = 0; i<=l; i++)
    l_addInFront(cover,bigDegrees[i]);
  free(bigDegrees);
  free(nullDegrees);
  return cover;
}

// Algo optimal petite couverture
List littleCoverAlg(Graph g, int k, int size){
  List cover = l_createList();
  int numberOfEdges = g_numberOfEdges(g);
  int sizeGraph = g_getSize(g);
  if (size <= k){
    for (int i=0; i< sizeGraph; i++)
      if (g_getNeighbors(g,i) != NULL)
	l_addInFront(cover,i);
    return cover;
  }
  if (k < 0){
    free(cover);
    return NULL;
  }
  if (numberOfEdges > k*(size-1)){
    free(cover);
    return NULL;
  }
  int* degrees = malloc(sizeGraph*sizeof(int));
  assert(degrees);
  for (int i=0; i<sizeGraph; i++)
    degrees[i] = g_getDegreeVertex(g, i);
  int u = 0;
  while(degrees[u] <= 0)
    u++;
  List neighbors = g_getNeighbors(g, u);
  int v = firstPositive(neighbors, degrees); 

  Graph g1 = g_cloneGraph(g);
  g_deleteEdges(g1,u);
  g_freeVertex(g1,u);
  if (g_numberOfEdges(g1) == 0){
    l_addInFront(cover,u);
    g_freeGraph(g1);
    free(degrees);
    return cover;
  }

  Graph g2 = g_cloneGraph(g);
  g_deleteEdges(g2,v);
  g_freeVertex(g2,v);
  if (g_numberOfEdges(g2) == 0){
    l_addInFront(cover,v);
    g_freeGraph(g1);
    g_freeGraph(g2);
    free(degrees);
    return cover;
  }

  List coverU = littleCoverAlg(g1, k-1, size-1);
  if (coverU !=NULL && l_size(coverU) == k-1){
    l_freeList(cover);
    cover = coverU;
    l_addInFront(cover, u);
  }
  else {
    List coverV = littleCoverAlg(g2, k-1, size-1);
    if (coverV != NULL && l_size(coverV) == k-1){
      l_freeList(cover);
      cover = coverV;
      l_addInFront(cover, v);
    }
  }
  g_freeGraph(g1);
  g_freeGraph(g2);
  free(degrees);
  return cover;
}
