#include <assert.h>
#include <malloc.h>
#include <stdbool.h>

#include "graph.h"
#include "list.h"

struct graph{
  Vertex* allVertices; // Tableau des listes de voisinage
  int** neighborhood; // Matrice d'adjacence globale
  int numberOfVertices;
  bool isConstruct;
};

struct vertex{
  List neighbors; // Liste des voisins
};

/* *** Fonctions du graphe *** */

Graph g_createGraph(int size){
  Graph newGraph = malloc(sizeof(struct graph));
  assert(newGraph);
  newGraph->allVertices = malloc(sizeof(struct vertex)*size);
  assert(newGraph->allVertices);
  newGraph->numberOfVertices = size;
  newGraph->isConstruct = 0;
  for (int i=0; i<size; i++)
    (newGraph->allVertices)[i] = g_createVertex();
  return newGraph;
}

void g_freeGraph(Graph g){
  int nbVert = g->numberOfVertices;
  Vertex v;
  for (int i=0; i<nbVert; i++){
    if (g->isConstruct)
      free((g->neighborhood)[i]);
    v = g_getVertex(g,i);
    l_freeList(v->neighbors);
    free(v);
  }

  if (g->isConstruct)
    free(g->neighborhood);
  free(g->allVertices);
  free(g);
}

void
g_createNeighborhood(Graph g){
  if (g->isConstruct)
    return;
  int nbVert = g->numberOfVertices;
  List l;
  int* neighbors;
  g->neighborhood = malloc(sizeof(int*)*nbVert);
  assert(g->neighborhood);
  
  for (int i=0; i<nbVert; i++){
    neighbors = malloc(sizeof(int*)*nbVert);
    assert(neighbors);
    for (int j=0; j<nbVert; j++)
      neighbors[j] = 0;
    l = g_getNeighbors(g, i);
    l_head(l);
    // Suppose qu'aucun sommet n'a pour voisin un sommet inexistant
    // (contre ex: 10 sommets, sommet 1 a pour voisin sommet 12)
    while (!l_isOutOfList(l)){
      neighbors[l_getVal(l)] = 1;
      l_next(l);
    }
    (g->neighborhood)[i] = neighbors;
  }
}   

int g_getSize(Graph g){
  return (g->numberOfVertices);
}

// Retourne le degré du graphe
int g_degreGraph(Graph g){
  int maxDegre = 0;
  int size = g_getSize(g);
  int deg;
  for (int i=0; i<size; i++){
    deg = l_size(g_getNeighbors(g,i));
    if (deg > maxDegre)
      maxDegre = deg;
  }
  return (maxDegre);
}

// Retourne le sommet de degré le plus grand
int g_maxDegreVertex(Graph g){
  int maxVertex = 0;
  int maxDegree = 0;
  int size = g_getSize(g);
  int deg;
  for (int i=0; i<size; i++){
    deg = l_size(g_getNeighbors(g,i));
    if (deg > maxDegree){
      maxVertex = i;
      maxDegree = deg;
    }
  }
  return (maxVertex+1);
}

// Retourne une feuille (si g est un arbre non vide il y en a toujours une)
int g_findLeafGraph(Graph g){
  int size = g_getSize(g);
  for (int i=0; i<size; i++){
    if (g_getDegreVertex(g,i) == 1)
      return (i+1);
  }
  return -1;
}

// ??
int g_findLeaf(int* degrees, int size){
  for (int i=0; i<size; i++){
    if (degrees[i] == 1)
      return i;
  }
  return -1;
}

// Supprime les sommets isolés du graphe g
void g_deleteIsolated(Graph g){
  int size = g_getSize(g);
  for (int i=0; i<size; i++){
    if (g_getDegreVertex(g,i) == 1)
      g_freeVertex(g, i);
  }
}

void g_display(Graph g){
  int size = g_getSize(g);
  for (int i=0; i<size; i++){
    List l = g_getNeighbors(g,i);
    printf("%d: ", i);
    l_display(l);
  }
}

/* ***  Fonctions sur les aretes *** */

// Changement des indices ? (les sommets commenceront a 1 ?)

// Ajout d'une arête entre les sommets i1 et i2
void g_addEdge(Graph g, int i1, int i2){
  List l1 = g_getNeighbors(g, i1-1);
  List l2 = g_getNeighbors(g, i2-1);
  l_addInFront(l1, i2-1);
  l_addInFront(l2, i1-1);
}

// Suppression de l'arete entre les sommets i1 et i2
void g_deleteEdge(Graph g, int i1, int i2){
  // Il faut que l'arête existe
  // A discuter
  List l1 = g_getNeighbors(g, i1-1);
  List l2 = g_getNeighbors(g, i2-1);
  l_deleteFirstOccur(l1, i2);
  l_deleteFirstOccur(l2, i1);
}

// Suppression des aretes adjacentes au sommet i
void g_deleteEdges(Graph g, int i){
  List l = g_getNeighbors(g, i); // Voisins de i
  List lTmp; // Voisins du sommet variable
  int iTmp; // Indice du sommet variable
  l_head(l);
  while (!l_isOutOfList(l)){
    iTmp = l_getVal(l);
    lTmp = g_getNeighbors(g, iTmp);
    l_deleteFirstOccur(lTmp, i-1); // On supprime i des voisins de iTmp
    l_deleteFirstOccur(l, iTmp-1); // On supprime iTmp des voisins de i
    l_next(l);
  }
}

// Test de voisinage
bool g_areNeighbor(Graph g, int i1, int i2){
  if (g->isConstruct == 1)
    return ((g->neighborhood)[i1-1][i2-1] == 1);
  else{
    List l1 = ((g->allVertices)[i1-1])->neighbors;
    return l_contain(l1, i2);
  }
}

/*struct edge findEdge(Graph g){
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
}*/

// test de voisinage
bool areNeighbor(Graph g, int i1, int i2){
  Vertex v1 = (g->allVertices)[i1-1];
  return list_contain(v1->neighbor, i2);
}

/* *** Fonctions sur les sommets *** */

// Créer sommet
Vertex g_createVertex(){
  Vertex newVertex = malloc(sizeof(struct vertex));
  assert(newVertex);
  newVertex->neighbors = l_createList();
  return newVertex;
}

// Supprimer sommet
void g_freeVertex(Graph g, int i){
  Vertex v = g_getVertex(g, i);
  List l = v->neighbors;
  l_freeList(l);
  free(v);
  (g->allVertices)[i] = NULL;
}

Vertex g_getVertex(Graph g, int i){
  return (g->allVertices)[i];
}

List g_getNeighbors(Graph g, int i){
  return ((g->allVertices)[i])->neighbors;
}

int g_getDegreVertex(Graph g, int i){
  return l_size(((g->allVertices)[i])->neighbors);
}
