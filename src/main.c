#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "fileReader.h"
#include "list.h"
#include "cover.h"
#include "generation.h"

void displayTab(int* tab, int size);

int main(int argc, char* argv[]){

  Graph g = bipartiteGeneration(20, 0.3);

  g_display(g);

  int** parts = computeBiPartition(g);

  printf("Première partition : ");
  displayTab(parts[0], parts[2][0]);

  printf("Deuxième partition : ");
  displayTab(parts[1], parts[2][1]);

  /*printf("Nom du fichier à ouvrir (avec l'extension)\n");
  char file[50];
  scanf("%49s", file);
  Graph g = readFile(file);
  while (g == NULL){
    printf("Le fichier n'est pas lisible\n");
    printf("\n");
    printf("Nom du fichier à ouvrir (avec l'extension)\n");
    scanf("%49s", file);
    g = readFile(file);
  }
  
  printf("\n");
  g_display(g);
  printf("%d aretes dans le graphe \n", g_numberOfEdges(g));
  // printf("\n");

  int select = 0;
  int k = 0;
  Graph gCopy;

  printf("Sélectionner un des algorithmes suivants :\n");
  printf("1. Algorithme glouton\n");
  printf("2. Algorithme optimal pour les arbres\n");
  //printf("3. Algorithme optimal pour les graphes bipartis\n");
  printf("3. Algorithme 2-approché (arbre couvrant)\n");
  printf("4. Algorithme 2-approché (elimination d'aretes)\n");
  printf("5. Algorithme paramétrique optimal pour petite couverture \n");
  printf("Sélectionner un algorithme (1-5):");
  scanf("%d", &select);


  switch (select){
  case 1: // Algo glouton
    gCopy = g_cloneGraph(g);
    printf("Calcul de la couverture (greedyAlg)... ");
    List coverG = greedyAlg(gCopy);
    printf("TERMINE \n");
    printf("Couverture :\n");
    l_display(coverG);
    printf("\n");
    g_freeGraph(gCopy);
    break;
  
  case 2: // Algo optimal arbres
    gCopy = g_cloneGraph(g);
    printf("Calcul de la couverture (treeOptAlg)... ");
    List coverT = treeOptAlg(gCopy);
    printf("TERMINE \n");
    printf("Couverture :\n");
    l_display(coverT);
    printf("\n");
    g_freeGraph(gCopy);
    break;

  case 3: // Algo 2-approx arbre couvrant
    gCopy = g_cloneGraph(g);
    printf("Calcul de la couverture (spanningTreeAlg)... ");
    List coverS = spanningTreeAlg(gCopy);
    printf("TERMINE \n");
    printf("Couverture :\n");
    l_display(coverS);
    printf("\n");
    g_freeGraph(gCopy);
    break;

  case 4: // Algo 2-approx elimination d'aretes
    gCopy = g_cloneGraph(g);
    printf("Calcul de la couverture (edgesDeletionAlg)... ");
    List coverE = edgesDeletionAlg(gCopy);
    printf("TERMINE \n");
    printf("Couverture :\n");
    l_display(coverE);
    printf("\n");
    g_freeGraph(gCopy);
    break;

  case 5: // Algo petite couverture
    gCopy = g_cloneGraph(g);
    printf("quelle taille de couverture a rechercher ? :");
    scanf("%d", &k);
    List littleCov = littleCover(gCopy, k);
    printf("TERMINE \n");
    if (l_size(littleCov) != 0) {
      printf("Couverture de taille %d trouvée : \n", k);
      l_display(littleCov);
    }
    else 
      printf("L'algorithme n'a pas trouvé de couverture de taille %d, essayez avec une valeur plus grande !\n", k);
    printf("\n");
    g_freeGraph(gCopy);
    break;

  default:
    printf("Choix invalide  \n");
    break;
    }

    g_freeGraph(g);*/
  return EXIT_SUCCESS;
}

void displayTab(int* tab, int size){
  printf("[");
  for (int i=0; i<size-1; i++)
    printf("%d, ", tab[i]);
  if (size > 0)
    printf("%d]\n", tab[size-1]);
  else
    printf("]\n");
}
