#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "fileReader.h"
#include "list.h"
#include "cover.h"
#include "generation.h"

void displayTab(int* tab, int size);

int main(int argc, char* argv[]){

  /*Graph g = bipartiteGeneration(20, 0.3);
  Graph g2 = g_cloneGraph(g);

  g_display(g);

  int** parts = computeBiPartition(g);

  printf("Première partition : ");
  displayTab(parts[0], parts[2][0]);

  printf("Deuxième partition : ");
  displayTab(parts[1], parts[2][1]);

  List biPartCouv = bipartiteOptAlg(g);
  printf("Couverture optimale (graphe biparti) : \n");
  l_display(biPartCouv);

  List gloutonCouv = greedyAlg(g2);
  printf("Couverture trouvé par le glouton : \n");
  l_display(gloutonCouv);
  

  return EXIT_SUCCESS;*/

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

  if (strcmp(argv[1],"help")==0){                   // aide
    printf("Premier paramètre : \n");
    printf("Sélectionner un des algorithmes suivants :\n");
    printf("1. Algorithme glouton : greedy \n");
    printf("2. Algorithme optimal pour les arbres : treeOpt \n");
    //printf("3. Algorithme optimal pour les graphes bipartis\n");
    printf("3. Algorithme 2-approché (arbre couvrant) : spanningTree \n");
    printf("4. Algorithme 2-approché (elimination d'aretes) : edgesDeletion \n");
    printf("5. Algorithme paramétrique optimal pour petite couverture : littleCover puis taille \n");
    printf("\nSecond paramètre : chemin vers le fichier à ouvrir (avec extension) ou appel a une fonction de generation \n");
    printf("\nTroisieme parametre : disp si vous voulez afficher le graphe de départ \n");
    return EXIT_SUCCESS;
  }

  if (strcmp(argv[1],"greedy") == 0){               // Alg glouton
    if (argc == 2){
      printf("pas assez d'arguments \n");
      return EXIT_FAILURE;
    }
    
    int i = 3; // indice de disp
    Graph g;
    if (strcmp(argv[2], "treeGen") == 0){
      int k = atoi(argv[3]);
      g = treeGeneration(k);
      i = 4;
    }
    else{
      g = readFile(argv[2]);
      if (g == NULL){
	printf("Le fichier n'est pas lisible \n");
	return EXIT_FAILURE;
      }
    }
    if (strcmp(argv[i],"disp") == 0)                // affichage
      g_display(g);

    printf("Calcul de la couverture (greedyAlg)... ");
    List coverG = greedyAlg(g);
    printf("TERMINE \n");
    printf("Couverture :\n");
    l_display(coverG);
    printf("\n");
    l_freeList(coverG);
    g_freeGraph(g);
    return EXIT_SUCCESS;
  }

  if (strcmp(argv[1],"treeOpt") == 0){               // Alg arbres
    if (argc == 2){
      printf("pas assez d'arguments \n");
      return EXIT_FAILURE;
    }
    Graph g = readFile(argv[2]);
    if (g == NULL){
      printf("Le fichier n'est pas lisible \n");
      return EXIT_FAILURE;
    }
    if (strcmp(argv[3],"disp") == 0)                // affichage
      g_display(g);

    printf("Calcul de la couverture (treeOptAlg)... ");
    List coverG = treeOptAlg(g);
    printf("TERMINE \n");
    printf("Couverture :\n");
    l_display(coverG);
    printf("\n");
    l_freeList(coverG);
    g_freeGraph(g);
    return EXIT_SUCCESS;
  }

  if (strcmp(argv[1],"spanningTree") == 0){               // Alg arbre couvrant
    if (argc == 2){
      printf("pas assez d'arguments \n");
      return EXIT_FAILURE;
    }
    Graph g = readFile(argv[2]);
    if (g == NULL){
      printf("Le fichier n'est pas lisible \n");
      return EXIT_FAILURE;
    }
    if (strcmp(argv[3],"disp") == 0)                // affichage
      g_display(g);

    printf("Calcul de la couverture (spanningTreeAlg)... ");
    List coverG = spanningTreeAlg(g);
    printf("TERMINE \n");
    printf("Couverture :\n");
    l_display(coverG);
    printf("\n");
    l_freeList(coverG);
    g_freeGraph(g);
    return EXIT_SUCCESS;
  }

  if (strcmp(argv[1],"edgesDeletion") == 0){               // Alg elimination d'aretes
    if (argc == 2){
      printf("pas assez d'arguments \n");
      return EXIT_FAILURE;
    }
    Graph g = readFile(argv[2]);
    if (g == NULL){
      printf("Le fichier n'est pas lisible \n");
      return EXIT_FAILURE;
    }
    if (strcmp(argv[3],"disp") == 0)                // affichage
      g_display(g);

    printf("Calcul de la couverture (edgesDeletionAlg)... ");
    List coverG = edgesDeletionAlg(g);
    printf("TERMINE \n");
    printf("Couverture :\n");
    l_display(coverG);
    printf("\n");
    l_freeList(coverG);
    g_freeGraph(g);
    return EXIT_SUCCESS;
  }

  if (strcmp(argv[1],"littleCover") == 0){               // petite couverture
    if (argc <= 3){
      printf("pas assez d'arguments \n");
      return EXIT_FAILURE;
    }
    int k = atoi(argv[2]);
    Graph g = readFile(argv[3]);
    if (g == NULL){
      printf("Le fichier n'est pas lisible \n");
      return EXIT_FAILURE;
    }
    if (strcmp(argv[4],"disp") == 0){        // affichage
      g_display(g);
    }
    if (k >= g_getSize(g)){
      printf("Tous les sommets du graphe sont dans la couverture. \n");
      g_freeGraph(g);
      return EXIT_SUCCESS;
    }
    List littleCov = littleCover(g, k);
    printf("TERMINE \n");
    if (littleCov != NULL && l_size(littleCov) != 0) {
      printf("Couverture de taille %d trouvée : \n", k);
      l_display(littleCov);
    }
    else
      printf("L'algorithme n'a pas trouvé de couverture de taille %d, essayez avec une valeur plus grande !\n", k);
    printf("\n");
    if(littleCov != NULL)
      l_freeList(littleCov);
    g_freeGraph(g);
    return EXIT_SUCCESS;
  }
  else{
    printf("arguments non compris \n");
    return EXIT_FAILURE;
  }
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
