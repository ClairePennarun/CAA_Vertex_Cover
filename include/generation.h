#ifndef GENERATION_H
#define GENERATION_H

#include "graph.h"

// Module de generation aleatoire de graphes

// Generation d'arbre a n sommets
Graph treeGeneration (int n);

// Generation de graphe avec proba
Graph generation(int n, double proba);

// Generation de graphes bipartis
Graph bipartiteGeneration (int n, double proba);

// Generation de graphe avec petite couverture (pratique pour tests)
Graph littleGeneration (int n, int k, double proba);

void initRandom();
int randint(int, int);
double random();

#endif
