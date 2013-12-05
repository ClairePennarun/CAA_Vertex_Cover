#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdbool.h>

#include "graph.h"
#include "list.h"

struct graph{
  Vertex* allVertices; // Tableau des listes de voisinage
  int** neighborhood; // Matrice d'adjacence globale
  int numberOfVertices;
  int numberOfEdges;
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
  newGraph->numberOfEdges = 0;
  newGraph->isConstruct = 0;
  for (int i=0; i<size; i++)
    (newGraph->allVertices)[i] = g_createVertex();
  return newGraph;
}

Graph g_cloneGraph(Graph g){
  int size = g_getSize(g);
  Graph newGraph = malloc(sizeof(struct graph));
  assert(newGraph);
  newGraph->allVertices = malloc(sizeof(struct vertex)*size);
  assert(newGraph->allVertices);
  newGraph->numberOfVertices = size;
  newGraph->numberOfEdges = g_numberOfEdges(g);
  newGraph->isConstruct = g->isConstruct;
  for (int i=0; i<size; i++)
    (newGraph->allVertices)[i] = g_cloneVertex(g->allVertices[i]);
  if (g->isConstruct)
    g_createNeighborhood(newGraph);
  return newGraph;
}

void g_freeGraph(Graph g){
  int nbVert = g->numberOfVertices;
  Vertex v;
  for (int i=0; i<nbVert; i++){
    if (g->isConstruct)
      free((g->neighborhood)[i]);
    v = g_getVertex(g,i);
    if (v != NULL){
      l_freeList(v->neighbors);
      free(v);
    }
  }

  if (g->isConstruct)
    free(g->neighborhood);
  free(g->allVertices);
  free(g);
}

void g_createNeighborhood(Graph g){
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
    deg = g_getDegreeVertex(g,i);
    if (deg > maxDegre)
      maxDegre = deg;
  }
  return (maxDegre);
}

// Retourne le sommet de degré le plus grand
int g_maxDegreeVertex(Graph g){
  int maxVertex = 0;
  int maxDegre = 0;
  int size = g_getSize(g);
  int deg;
  for (int i=0; i<size; i++){
    deg = g_getDegreeVertex(g,i);
    if (deg > maxDegre){
      maxVertex = i;
      maxDegre = deg;
    }
  }
  return maxVertex;
}

// Retourne une feuille (si g est un arbre non vide il y en a toujours une)
int g_findLeafGraph(Graph g){
  int size = g_getSize(g);
  for (int i=0; i<size; i++){
    if (g_getDegreeVertex(g,i) == 1)
      return i;
  }
  return -1;
}

// Supprime les sommets isoles du graphe g
void g_deleteIsolated(Graph g){
  int size = g_getSize(g);
  for (int i=0; i<size; i++){
    if (g_getDegreeVertex(g,i) == 0)
      g_freeVertex(g, i);
  }
}

// Affiche le graphe g
void g_display(Graph g){
  int size = g_getSize(g);
  printf("Graphe :\n");
  for (int i=0; i<size; i++){
    List l = g_getNeighbors(g,i);
    printf("%d: ", i);
    if (l != NULL)
      l_display(l);
    else
      printf("NULL\n");
  }
}

/* ***  Fonctions sur les aretes *** */

// Changement des indices ? (les sommets commenceront a 1 ?)

// Ajout d'une arete entre les sommets i1 et i2
void g_addEdge(Graph g, int i1, int i2){
  List l1 = g_getNeighbors(g, i1);
  List l2 = g_getNeighbors(g, i2);
  l_addInFront(l1, i2);
  l_addInFront(l2, i1);
  if (g->isConstruct){
    (g->neighborhood)[i1][i2] = 1;
    (g->neighborhood)[i2][i1] = 1;
  }
  g->numberOfEdges ++;
}

// Suppression de l'arete entre les sommets i1 et i2
void g_deleteEdge(Graph g, int i1, int i2){
  // Il faut que l'arête existe
  // A discuter
  List l1 = g_getNeighbors(g, i1);
  List l2 = g_getNeighbors(g, i2);
  l_deleteFirstOccur(l1, i2);
  l_deleteFirstOccur(l2, i1);
  if (g->isConstruct){
    (g->neighborhood)[i1][i2] = 0;
    (g->neighborhood)[i2][i1] = 0;
  }
  g->numberOfEdges --;
}

// Suppression des aretes adjacentes au sommet i
void g_deleteEdges(Graph g, int i){
  List l = g_getNeighbors(g, i);       // Voisins de i
  List lTmp;                           // Voisins du sommet variable
  int iTmp;                            // Indice du sommet variable
  l_head(l);
  while (!l_isOutOfList(l)){
    iTmp = l_getVal(l);
    lTmp = g_getNeighbors(g, iTmp);
    l_deleteFirstOccur(lTmp, i);       // On supprime i des voisins de iTmp
    l_deleteFirstOccur(l, iTmp);       // On supprime iTmp des voisins de i
    if (g->isConstruct){
      (g->neighborhood)[i][iTmp] = 0;
      (g->neighborhood)[iTmp][i] = 0;
    }
    g->numberOfEdges --;
    l_head(l);
  }
}

// Test de voisinage
bool g_areNeighbor(Graph g, int i1, int i2){
  if (!g->isConstruct)
    return l_contain(g_getNeighbors(g,i1), i2);
  return ((g->neighborhood)[i1][i2] == 1);
}

int g_numberOfEdges(Graph g){
  return g->numberOfEdges;
}

/* *** Fonctions sur les sommets *** */

// Créer sommet
Vertex g_createVertex(){
  Vertex newVertex = malloc(sizeof(struct vertex));
  assert(newVertex);
  newVertex->neighbors = l_createList();
  return newVertex;
}

Vertex g_cloneVertex(Vertex v){
  Vertex newVertex = malloc(sizeof(struct vertex));
  assert(newVertex);
  if (v != NULL)
    newVertex->neighbors = l_cloneList(v->neighbors);
  else
    return NULL;
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
  Vertex v = g->allVertices[i];
  if (v != NULL)
    return (v->neighbors);
  return NULL;
}

int g_getDegreeVertex(Graph g, int i){
  Vertex v = g->allVertices[i];
  if (v != NULL)
    return l_size(v->neighbors);
  return -1;
}
