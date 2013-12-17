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
    printf("degmax : %d \n", degmax);
    if (degmax > 0){
      printf("on rajoute le sommet %d \n", v);
      l_insertInHead(cover, v+1); // on le met dans la couverture
      deleteVertexDegrees(g,degrees,v);
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
  return cover;
}

// Algo optimal : graphes bipartis
int* bipartiteOptAlg (Graph g){
  return NULL;
}

// Retourne le graphe orienté H construit à partir de G pour l'algo des graphes biparti, s l'avant dernier sommet et t le dernier
Graph orientedGraph(Graph g){
  int size = g_getSize(g);

  /*int ** parts = computeBiPartition(g);
  int* part1 = parts[0];
  int* part2 = parts[1];
  int size1 = parts[2][0];
  int size2 = parts[2][1];
  free(parts[2]);
  free(parts);*/
  
  Graph h = g_createOrientedGraph(size);

  //free(part1);
  //free(part2);
  
  return h;
}

int** computeBiPartition(Graph g){
  // Calcul de la bipartition de g

  int n = g_getSize(g);

  int* sizes = malloc(sizeof(int)*2);
  sizes[0] = 0;
  sizes[1] = 0;
  // Les deux premiers tableaux sont les partitions et le troisième
  // contient les tailles respectives des deux partitions
  int** parts = malloc(sizeof(int*)*3);
  assert(parts);
  parts[0] = malloc(sizeof(int)*n);
  parts[1] = malloc(sizeof(int)*n);
  parts[2] = sizes;
  assert(parts[0]);
  assert(parts[1]);
  assert(sizes);
  
  bool* isVisited = malloc(sizeof(bool)*n);
  assert(isVisited);
  for (int i=0; i<n; i++)
    isVisited[i] = false;
  // Les deux listes sont synchronisées : - 'toTest' contient tout les sommets a tester (ajouter leurs voisins)
  // - 'partOfVertices' contient les numéro des partions auquels appartiennent les sommets a tester
  // Ex: Si 's' est a tester et est dans la partition 0, on ajoute tout ses voisins dans 'toTest' avec une partition 1
  List toTest = l_createList();
  List partsOfVertices = l_createList();
  List neighbors;
  l_addInFront(toTest, 0); // On ajoute le premier sommet
  l_addInFront(partsOfVertices, 0); // Et on lui donne arbitrairement la partition numéro 0
  isVisited[0] = true;

  int currentVertex;
  int currentPart;
  int tmp;
  while(!l_isEmpty(toTest)){

    currentVertex = l_getFirstVal(toTest);
    currentPart = l_getFirstVal(partsOfVertices);
    l_deleteHead(toTest);
    l_deleteHead(partsOfVertices);

    neighbors = g_getNeighbors(g, currentVertex);
    l_head(neighbors);

    // On parcours tout les voisins du sommet courant
    while (!l_isOutOfList(neighbors)){
      tmp = l_getVal(neighbors);
      if (!isVisited[tmp]){ // Si on a pas encore visité ce voisin
	isVisited[tmp] = true;
	l_addInFront(toTest, tmp); // On l'ajoute
	l_addInFront(partsOfVertices, 1-currentPart); // Avec la partition opposée
      }
      l_next(neighbors);
    }
    // On ajoute le sommet courant dans la partition demandée
    parts[currentPart][sizes[currentPart]] = currentVertex;
    sizes[currentPart]++;
  }

  free(isVisited);
  l_freeList(partsOfVertices);
  l_freeList(toTest);

  return parts;
}

// Algo 2-approche par arbres couvrants
void spanning(Graph g, int i, List cover, int* tabTree){
  if(tabTree[i] == 1) // on a deja visité le sommet
    return;
  tabTree[i] = 1;
  List listNeighbors = g_getNeighbors(g,i);
  l_head(listNeighbors);
  int val_head;
  bool hasSuccessor = false;
  while(!l_isOutOfList(listNeighbors)){
    val_head = l_getVal(listNeighbors);
    l_next(listNeighbors);
    if (tabTree[val_head] == 0 && !hasSuccessor){
      hasSuccessor = true;
      l_addInFront(cover,i);
    }
    spanning(g,val_head,cover,tabTree);
  }
}

List spanningTreeAlg(Graph g){
  List cover = l_createList();
  int sizeGraph = g_getSize(g);
  int* tabTree = malloc(sizeGraph*sizeof(int));
  assert(tabTree);
  for (int i=0; i < sizeGraph; i++){
    tabTree[i] = 0;
  }
  spanning(g, 0, cover, tabTree);
  return cover;
}

// Algo 2-approche par elimination d'aretes
List edgesDeletionAlg(Graph g){
  List cover = l_createList();
  int iVert1 = g_maxDegreeVertex(g); // a voir si besoin de chercher le sommet de plus haut degre
  int deg1 = g_getDegreeVertex(g, iVert1);
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
    iVert1 = g_maxDegreeVertex(g);
    deg1 = g_getDegreeVertex(g, iVert1);
  }
  return cover;
}

List littleCover(Graph g, int k){
  return littleCoverAlg(g, k, g_getSize(g));
}

// Algo optimal petite couverture
List littleCoverAlg(Graph g, int k, int size){
  List cover = l_createList();
  int numberOfEdges = g_numberOfEdges(g);
  int sizeGraph = g_getSize(g);
  //printf("\n il y a %d aretes et %d sommets \n", numberOfEdges, size);
  //g_display(g);
  if (size <= k){
    //printf("Tous les sommets du graphe sont dans la couverture \n");
    for (int i=0; i< size; i++)
      if (g_getNeighbors(g,i) != NULL)
	l_addInFront(cover,i);
    //l_display(cover);
    return cover;
  }
  if (k < 0){
    //printf("k est négatif. Pas de couverture trouvée \n");
    return NULL;
  }
  if (numberOfEdges > k*(size-1)){
    //printf("Le graphe a trop d'arêtes. Pas de couverture de taille %d trouvée \n",k);
    return NULL;
  }
  // creation liste des degres
  int* degrees = malloc(size*sizeof(int));
  for (int i=0; i<sizeGraph; i++){
    degrees[i] = g_getDegreeVertex(g, i);
  }
  int u = 0;
  while(degrees[u] <= 0){
    //printf("degre de %d : %d\n",u, degrees[u]);
    u++;
  }
  //printf("degre de u = %d : %d \n", u, degrees[u]);
  List neighbors = g_getNeighbors(g, u);
  int v = firstPositive(neighbors, degrees); // retourne un voisin de u de degre non nul (donc uv est une arete du graphe)
  //printf("degre de v = %d : %d \n", v, degrees[v]);

  Graph g1 = g_cloneGraph(g);
  g_deleteEdges(g1,u);
  g_freeVertex(g1,u);
  if (g_numberOfEdges(g1) == 0){
    l_addInFront(cover,u);
    //l_display(cover);
    return cover;
  }

  Graph g2 = g_cloneGraph(g);
  g_deleteEdges(g2,v);
  g_freeVertex(g2,v);
  if (g_numberOfEdges(g2) == 0){
    l_addInFront(cover,v);
    //l_display(cover);
    return cover;
  }

  List coverU = littleCoverAlg(g1, k-1, size-1);
  if (coverU !=NULL && l_size(coverU) == k-1){
    cover = coverU;
    l_addInFront(cover, u);
  }
  else {
    List coverV = littleCoverAlg(g2, k-1, size-1);
    if (coverV != NULL && l_size(coverV) == k-1){
      cover = coverV;
      l_addInFront(cover, v);
    }
  }
  //l_display(cover);

  return cover;
}
