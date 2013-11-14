#ifndef COVER_H
#define COVER_H
// Module de recherche de couverture par sommets

// Algorithme glouton : graphes quelconques
Cover greedyAlg (Graph g); 

// Algo optimal : arbres
Cover treeOptAlg(Graph g);

// Algo optimal : graphes bipartis
Cover bipartiteOptAlg (Graph g);

// Algo 2-approche par arbres couvrants
Cover spanningTreeAlg(Graph g);

// Algo 2-approche par elimination d'aretes
Cover edgesDeletionAlg(Graph g);

// Algo optimal petite couverture
Cover littleCoverAlg(Graph g);

#endif
