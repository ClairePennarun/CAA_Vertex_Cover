#ifndef GENERATION_H
#define GENERATION_H
// Module de generation aleatoire de graphes

// generation d'arbre a n sommets
Graph treeGeneration (int n);

// generation de graphe avec proba
Graph generation(int n, double proba);

// generation de graphes bipartis
Graph bipartiteGeneration (int n, double proba);

// generation de graphe avec petite couverture (pratique pour tests)
Graph littleGeneration (int n, int k, double proba);

#endif