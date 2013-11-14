#ifndef COVER_H
#define COVER_H
// Module de recherche de couverture par sommets
#include "graph.h"

// Algorithme glouton : graphes quelconques
List greedyAlg (Graph g); 

// Algo optimal : arbres
int* treeOptAlg(Graph g);

// Algo optimal : graphes bipartis
int* bipartiteOptAlg (Graph g);

// Algo 2-approche par arbres couvrants
int* spanningTreeAlg(Graph g);

// Algo 2-approche par elimination d'aretes
int* edgesDeletionAlg(Graph g);

// Algo optimal petite couverture
int* littleCoverAlg(Graph g);

#endif
