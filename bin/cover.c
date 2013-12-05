#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

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

// Algo 2-approche par arbres couvrants

void spanning(Graph g, int i, int** tabTree){
  List neighbors = g_getNeighbors(g,i);
  l_head(listNeighbors);
  int val_head;
  while(!l_isOutOfList(listNeighbors)){
    val_head = l_getVal(listNeighbors);
    if (tabTree[i][0] == 0){
      if (tabTree[i][0] == 1) // on alterne les couleurs des sommets
	tabTree[val_head][0] = 2;
      else 
	tabTree[val_head][0] = 1;
      if (tabTree[i][1] = NULL) // si i n'a pas encore de successeur, on lui en donne un
	tabTree[i][1] = val_head;
      spanning(g,val_head,tabTree);
    }
  }
}

// retourne un arbre couvrant du graphe G, et pour chaque sommet de l'arbre :
// sa couleur et l'indice de l'un de ses successeurs
int** spanningTree(Graph g){
  int sizeGraph = g_getSize(g);
  int** tabTree = malloc(sizeGraph*sizeof(int*));
  assert(tabTree);
  for (int i=0; i < sizeGraph; i++){
    tabTree[i] = malloc(2*sizeof(int*));
    assert(tabTree[i]);
    tabTree[i][0] = 0;
    tabTree[i][1] = NULL;
  }
  int root = g_getVertex(g,0);
  tabTree[root][0] = 1;
  spanning(g, root, tabTree);
}

int* spanningTreeAlg(Graph g){
  // calcul d'un arbre couvrant A du graphe G par un parcours en profondeur
  // on colorie les sommets de A en deux couleurs
  // on choisit des aretes entre les sommets de la meme couleur les plus nombreux de A et un de leurs successeurs
  // pour chaque arete choisie, on prend une de ses extremites
  int** tabTree = spanningTree(g);
  return NULL;
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
