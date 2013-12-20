#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

#include "generation.h"

// Module de generation aleatoire de graphes
// Proba désignera la probabilité que deux sommets soient reliés

// Generation d'arbre a n sommets
Graph treeGeneration(int n){
  Graph g = g_createGraph(n);
  int* vertices = getRandomVertices(n);

  for (int i=1; i<n; i++)
    g_addEdge(g, vertices[i], vertices[randint(0, i)]);

  free(vertices);
  return g;
}

// Generation de graphe avec proba
Graph generation(int n, double proba){
  Graph g = g_createGraph(n);
  int* vertices = getRandomVertices(n);
  bool isConnected;

  for (int i=0; i<n; i++){
    for (int j=i+1; j<n; j++)
      isConnected = randomEdge(g, vertices[i], vertices[j], proba) || isConnected;
    makeConnected(g, vertices[i], vertices, i, n, isConnected);
  }

  free(vertices);
  return g;
}

// Generation de graphes bipartis
Graph bipartiteGeneration (int n, double proba){
  Graph g = g_createGraph(n);
  int* vertices = getRandomVertices(n);
  assert(n>=2);
  bool isConnected;
  int* part1 = malloc(sizeof(int)*n);
  int* part2 = malloc(sizeof(int)*n);
  assert(part1);
  assert(part2);
  int size1 = 1;
  int size2 = 1;
  part1[0] = vertices[0];
  part2[0] = vertices[1];
  g_addEdge(g, vertices[0], vertices[1]);

  for (int i=2; i<n; i++){
    isConnected = false;
    if (random() < 0.50){ // Sommet i dans part1
     for (int j=0; j<size2; j++)
       isConnected = randomEdge(g, vertices[i], part2[j], proba) || isConnected;
     makeConnected(g, vertices[i], part2, 0, size2, isConnected);
     part1[size1] = vertices[i];
     size1++;
    }
    else{                 // Sommet i dans part2
      for (int j=0; j<size1; j++)
	isConnected = randomEdge(g, vertices[i], part1[j], proba) || isConnected;
      makeConnected(g, vertices[i], part1, 0, size1, isConnected);
      part2[size2] = vertices[i];
      size2++;
    }
  }

  free(vertices);
  free(part1);
  free(part2);
  return g;
}

// Generation de graphe avec petite couverture (pratique pour tests)
Graph littleGeneration (int n, int k, double proba){
  assert(k<=n/2);  // Tout graphe connexe admet, au pire des cas, une couverture de taille n/2
  Graph g = g_createGraph(n);
  int* vertices = getRandomVertices(n); // Les k premières valeurs seront la couverture

  for(int ki=0; ki<k; ki++)
    g_addEdge(g, vertices[ki], vertices[k+ki]); // Les sommets "exclusifs" sont relié a un et un seul sommet de la couverture

  bool isConnected;
  for(int gi=2*k; gi<n; gi++){
    isConnected = false;
    for(int ki=0; ki<k; ki++)
      isConnected = randomEdge(g, vertices[gi], vertices[ki], proba) || isConnected;
    makeConnected(g, vertices[gi], vertices, 0, k, isConnected);
  }
  free(vertices);
  return g;
}

int* getRandomVertices(int n){
  int* vertices = malloc(sizeof(int)*n);
  assert(vertices);

  for (int i=0; i<n; i++)
    vertices[i] = i;
  // Mélange des sommets
  for (int i=0; i<n; i++)
    swap(vertices, i, randint(i, n));
  
  return vertices;
}

bool randomEdge(Graph g, int i1, int i2, double proba){
  if (random() > proba)
    return false;
  g_addEdge(g, i1, i2);
  return true;
}

// Si le sommet n'est pas connecté, le relie au hasard avec un sommet dans [iMin, iMax[ de tab
void makeConnected(Graph g, int i, int* tab, int iMin, int iMax, bool isConnected){
  if (isConnected || iMin >= iMax)
    return;
  int pos = randint(iMin, iMax);
  if (tab != NULL)
    g_addEdge(g, i, tab[pos]);
  else
    g_addEdge(g, i, pos);
}

// Echange dans t les cases d'indice i1 et i2
void swap(int* t, int i1, int i2){
  int tmp = t[i1];
  t[i1] = t[i2];
  t[i2] = tmp;
}

// Retourne un entier dans [a, b[
int randint(int a, int b){
  if (a==b)
    return a;
  assert(b>a);
  return rand()%(b-a)+a;
}

// Retourne un double compris entre 0 et 1
double random(){
  return ((float)rand())/((float)(RAND_MAX));
}
