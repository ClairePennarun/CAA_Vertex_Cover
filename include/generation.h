#ifndef GENERATION_H
#define GENERATION_H

#include <stdbool.h>

#include "graph.h"

// Module de generation aléatoire de graphes

// Generation d'arbre a n sommets
Graph treeGeneration (int n);

// Generation de graphe avec proba
Graph generation(int n, double proba);

// Generation de graphes bipartis
Graph bipartiteGeneration (int n, double proba);

// Generation de graphe avec petite couverture (pratique pour tests)
Graph littleGeneration (int n, int k, double proba);

int* getRandomVertices(int n);
bool randomEdge(Graph g, int i1, int i2, double proba);
void makeConnected(Graph g, int i, int* tab, int iMin, int iMax, bool isConnected);
void swap(int* t, int i1, int i2);
void initRandom();
int randint(int a, int b);
double random();
int getGraine();

#endif
