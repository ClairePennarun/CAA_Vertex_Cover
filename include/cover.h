#ifndef COVER_H
#define COVER_H

#include "graph.h"

// Module de recherche de couverture par sommets

// Algorithme glouton : graphes quelconques
List greedyAlg (Graph g);
void deleteVertexDegrees(Graph g, int* degrees, int v);

// Algo optimal : arbres
List treeOptAlg(Graph g);

// Algo optimal : graphes bipartis
List bipartiteOptAlg (Graph g);
int** computeBiPartition(Graph g);

// Algo 2-approche par arbres couvrants
List spanningTreeAlg(Graph g); // Algorithme itératif avec une liste
List spanningTreeAlgRec(Graph g); // Algorithme récursif

// Algo 2-approche par elimination d'aretes
List edgesDeletionAlg(Graph g);

// Algo optimal petite couverture
List littleCover(Graph g, int k);
List littleCoverAlg(Graph g, int k, int size);


#endif
