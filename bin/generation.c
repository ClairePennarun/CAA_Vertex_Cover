#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "generation.h"

// Module de generation aleatoire de graphes

// Generation d'arbre a n sommets
Graph treeGeneration (int n){
  initRandom();
  Graph g = g_createGraph(n);

  for (int i=1; i<n; i++)
    g_addEdge(g, i, randint(0, i));

  return g;
}

// Generation de graphe avec proba
Graph generation(int n, double proba){
  initRandom();
  Graph g = g_createGraph(n);

  // Proba désigne la probabilité que deux sommets quelconques soient reliés
  for (int i=0; i<n; i++)
    for (int j=i+1; j<n; j++)
      if (random() <= proba)
	g_addEdge(g, i, j);

  return g;
}

// Generation de graphes bipartis
Graph bipartiteGeneration (int n, double proba){
  initRandom();
  // Tableau contenant les indices des sommets de chaque partitions (suivi de leurs tailles réelles)
  int* firstPart = malloc(sizeof(int)*n);
  int* secondPart = malloc(sizeof(int)*n);
  assert(firstPart);
  assert(secondPart);
  int size1 = 0;
  int size2 = 0;
  Graph g = g_createGraph(n);

  // Proba désigne la probabilité que deux sommets d'une meme partition soient reliés
  for (int i=0; i<n; i++){
    if (random() < 0.50){
      for (int j=0; j<size1; j++)
	if (random() <= proba)
	  g_addEdge(g, i, firstPart[j]);
      firstPart[size1] = i;
      size1++;
    }
    else{
      for (int j=0; j<size2; j++)
	if (random() <= proba)
	  g_addEdge(g, i, secondPart[j]);
      secondPart[size2] = i;
      size2++;
    }
  }

  free(firstPart);
  free(secondPart);

  return g;
}

// Generation de graphe avec petite couverture (pratique pour tests)
Graph littleGeneration (int n, int k, double proba){
  initRandom();
  
  return NULL;
}

void initRandom(){
  int graine = time(NULL);
  srand(graine);
  printf("La graine pour l'aléatoire est : %d\n", graine);
}

// Retourne un entier dans [a, b[
int randint(int a, int b){
  assert(b>a);
  return rand()%(b-a)+a;
}

// Retourne un double compris entre 0 et 1
double random(){
  return ((float)rand())/((float)(RAND_MAX));
}
