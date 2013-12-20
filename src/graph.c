#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdbool.h>

#include "graph.h"
#include "list.h"

struct graph{
  Vertex* allVertices; // Tableau des listes de voisinage
  int numberOfVertices;
  int numberOfEdges;
  bool isOriented;
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
  newGraph->isOriented = false;
  for (int i=0; i<size; i++)
    (newGraph->allVertices)[i] = g_createVertex();
  return newGraph;
}

Graph g_createOrientedGraph(int size){
  Graph newGraph = g_createGraph(size);
  newGraph->isOriented = true;
  return newGraph;
}

Graph g_cloneGraph(Graph g){
  int size = g_getSize(g);
  Graph newGraph = g_createGraph(size);
  newGraph->numberOfEdges = 0;
  newGraph->isOriented = g->isOriented;

  List neighbors;
  int vert;
  for (int i=0; i<size; i++){
    if(g_getVertex(g,i) != NULL){
      neighbors = g_getNeighbors(g, i);
      l_head(neighbors);
      while (!l_isOutOfList(neighbors)){
	vert = l_getVal(neighbors);
	// Pour ne pas ajouter deux fois les arêtes, on ajoute
	// que les couples (a-b) avec a<b (sauf si le graphe est orienté)
	if (newGraph->isOriented || vert<i)
	  g_addEdge(newGraph, i, vert);	
	l_next(neighbors);
      }
    }
  }
  return newGraph;
}

void g_freeGraph(Graph g){
  int nbVert = g->numberOfVertices;
  Vertex v;
  for (int i=0; i<nbVert; i++){
    v = g_getVertex(g,i);
    if (v != NULL){
      l_freeList(v->neighbors);
      free(v); 
    }
  }
  free(g->allVertices);
  free(g);
}

// Retourne True si le graphe est orienté
bool g_isOriented(Graph g){
  return (g->isOriented);
}

// Retourne la taille du graphe g
int g_getSize(Graph g){
  return (g->numberOfVertices);
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

// Ajout d'une arete entre les sommets i1 et i2
void g_addEdge(Graph g, int i1, int i2){
  List l1 = g_getNeighbors(g, i1);
  List l2 = g_getNeighbors(g, i2);
  l_addInFront(l1, i2);
  if (!(g->isOriented))
    l_addInFront(l2, i1);
  g->numberOfEdges ++;
}

// Suppression des aretes adjacentes partantes du sommet i
void g_deleteEdges(Graph g, int i){
  List l = g_getNeighbors(g, i);       // Voisins de i
  List lTmp;                           // Voisins du sommet variable
  int iTmp;                            // Indice du sommet variable
  l_head(l);
  while (!l_isOutOfList(l)){
    iTmp = l_getVal(l);
    lTmp = g_getNeighbors(g, iTmp);
    if (!(g->isOriented))
      l_deleteFirstOccur(lTmp, i);       // On supprime i des voisins de iTmp
    l_deleteFirstOccur(l, iTmp);       // On supprime iTmp des voisins de i
    g->numberOfEdges --;
    l_head(l);
  }
}

// Test de voisinage
bool g_areNeighbor(Graph g, int i1, int i2){
  return l_contain(g_getNeighbors(g,i1), i2);
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

// Cloner sommet
Vertex g_cloneVertex(Vertex v){
  if (v == NULL)
    return NULL;
  Vertex newVertex = malloc(sizeof(struct vertex));
  assert(newVertex);
  newVertex->neighbors = l_cloneList(v->neighbors);
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

// Retourne l'indice du premier sommet d'indice plus grand que j et de degré positif
int g_getPositiveDegreeVertex(Graph g, int j){
  Vertex v;
  for (int i = j; i < g_getSize(g); i++){
    v = g_getVertex(g,i);
    if (l_size(v->neighbors) > 0)
    return i;
  }
  return -1;
}

// Retourne le sommet d'indice i
Vertex g_getVertex(Graph g, int i){
  return (g->allVertices)[i];
}

// Retourne la liste des voisins du sommet d'indice i
List g_getNeighbors(Graph g, int i){
  Vertex v = g->allVertices[i];
  if (v != NULL)
    return (v->neighbors);
  return NULL;
}

// Retourne le degre du sommet d'indice i
int g_getDegreeVertex(Graph g, int i){
  Vertex v = g->allVertices[i];
  if (v != NULL)
    return l_size(v->neighbors);
  return -1;
}
