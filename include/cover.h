#ifndef COVER_H
#define COVER_H

#include "graph.h"

// Module de recherche de couverture par sommets

// Algorithme glouton : graphes quelconques
List greedyAlg (Graph g); 

// Algo optimal : arbres
List treeOptAlg(Graph g);

// Algo optimal : graphes bipartis
int* bipartiteOptAlg (Graph g);

// Algo 2-approche par arbres couvrants
int* spanningTreeAlg(Graph g);

// Algo 2-approche par elimination d'aretes
List edgesDeletionAlg(Graph g);

// Algo optimal petite couverture
bool littleCoverAlg(Graph g, int k);

#endif
