#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "fileReader.h"
#include "list.h"
#include "cover.h"
#include "generation.h"

int main(int argc, char* argv[]){

  printf("Nom du fichier à ouvrir (avec l'extension)\n");
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
  //printf("4. Algorithme 2-approché (1)\n");
  printf("3. Algorithme 2-approché (2)\n");
  printf("4. Algorithme paramétrique optimal pour petite couverture \n");
  printf("Sélectionner un algorithme (1-4):");
  scanf("%d", &select);


  switch (select){
  case 1:
    gCopy = g_cloneGraph(g);
    printf("Calcul de la couverture (greedyAlg)... ");
    List coverG = greedyAlg(gCopy);
    printf("TERMINE \n");
    printf("Couverture :\n");
    l_display(coverG);
    printf("\n");
    break;
  
  case 2:
    gCopy = g_cloneGraph(g);
    printf("Calcul de la couverture (treeOptAlg)... ");
    List coverT = treeOptAlg(gCopy);
    printf("TERMINE \n");
    printf("Couverture :\n");
    l_display(coverT);
    printf("\n");
    break;

  case 3:
    gCopy = g_cloneGraph(g);
    printf("Calcul de la couverture (edgesDeletionAlg)... ");
    List coverE = edgesDeletionAlg(gCopy);
    printf("TERMINE \n");
    printf("Couverture :\n");
    l_display(coverE);
    printf("\n");
    break;

  case 4:
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
    break;

  default:
    printf("Choix invalide  \n");
    break;
    }

  return EXIT_SUCCESS;
}
