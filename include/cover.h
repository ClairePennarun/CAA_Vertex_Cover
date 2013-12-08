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
List spanningTreeAlg(Graph g);

// Algo 2-approche par elimination d'aretes
List edgesDeletionAlg(Graph g);

// Algo optimal petite couverture
List littleCover(Graph g, int k);
List littleCoverAlg(Graph g, int k, int size);


//Fonctions annexes
int firstPositive(List, int*);
void deleteVertexDegrees(Graph, int*, int v);
int findLeaf(int*, Graph g);


#endif
