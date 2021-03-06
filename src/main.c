#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "graph.h"
#include "fileReader.h"
#include "list.h"
#include "cover.h"
#include "generation.h"
#include "minisat.h"

Graph selectGraph(int argc, char* argv[], int i);
void displayTab(int* tab, int size);

int main(int argc, char* argv[]){

  srand(time(NULL));

  if (strcmp(argv[1],"help")==0){                   // aide
    printf("Premier paramètre : \n");
    printf("  Sélectionner un des algorithmes suivants :\n");
    printf("    Algorithme glouton : greedy \n");
    printf("    Algorithme optimal pour les arbres : treeOpt \n");
    printf("    Algorithme optimal pour les graphes bipartis : bipartiteOpt\n");
    printf("    Algorithme 2-approché (arbre couvrant) : spanningTree \n");
    printf("    Algorithme 2-approché (elimination d'aretes) : edgesDeletion \n");
    printf("    Algorithme paramétrique optimal pour petite couverture : littleCover puis taille \n");
    printf("\nSecond paramètre : chemin vers le fichier à ouvrir (avec extension) ou appel a une fonction de generation (avec ses paramètres)\n");
    printf("  Génération d'arbres de taille n : treeGen n \n");
    printf("  Génération de graphes de taille n et proba p: gen n p \n");
    printf("  Génération de graphes bipartis de taille n et proba p: bipartiteGen n p \n");
    printf("  Génération de graphes de taille n, proba p et taille de couverture k : littleGen n k p \n");
    printf("\nTroisieme parametre : disp si vous voulez afficher le graphe de départ \n");
    return EXIT_SUCCESS;
  }

  if (strcmp(argv[1],"minisat") == 0){            // Minisat
    if (argc == 2){
      printf("pas assez d'arguments \n");
      return EXIT_FAILURE;
    }
    Graph g = selectGraph(argc,argv,3);
    if(g == NULL)
      return EXIT_FAILURE;
    int p = atoi(argv[2]);
    input(g,p);
    minisat();
    List cover = output(p);
    l_display(cover);
    if (cover != NULL)
      l_freeList(cover);
    g_freeGraph(g);
    return EXIT_SUCCESS;
  }

  if (strcmp(argv[1],"greedy") == 0){               // Alg glouton
    if (argc == 2){
      printf("pas assez d'arguments \n");
      return EXIT_FAILURE;
    }
    Graph g = selectGraph(argc,argv,2);
    if(g == NULL)
      return EXIT_FAILURE;

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

    Graph g = selectGraph(argc, argv,2);
    if(g == NULL)
      return EXIT_FAILURE;

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
    Graph g = selectGraph(argc, argv,2);
    if(g == NULL)
      return EXIT_FAILURE;

    printf("Calcul de la couverture (spanningTreeAlg)... ");
    List coverG = spanningTreeAlg(g);
    printf("TERMINE \n");
    printf("Couverture :\n");
    l_display(coverG);
    printf("\n");
    if(coverG != NULL)
      l_freeList(coverG);
    g_freeGraph(g);
    return EXIT_SUCCESS;
  }


  if (strcmp(argv[1],"bipartiteOpt") == 0){               // Alg optimal bipartis
    if (argc == 2){
      printf("pas assez d'arguments \n");
      return EXIT_FAILURE;
    }

    Graph g = selectGraph(argc,argv,2);
    if(g == NULL)
      return EXIT_FAILURE;

    printf("Calcul de la couverture (bipartiteOptAlg)... ");
    List coverG = bipartiteOptAlg(g);
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
    Graph g = selectGraph(argc,argv,2);
    if (g == NULL)
      return EXIT_FAILURE;

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
    
    Graph g = selectGraph(argc,argv,3);
    if (g == NULL)
      return EXIT_FAILURE;

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


Graph selectGraph(int argc, char* argv[], int i){
    Graph g;
    if (strcmp(argv[i], "treeGen") == 0){
      int n = atoi(argv[i+1]);
      g = treeGeneration(n);
      if (argc >=i+3)
	if (strcmp(argv[i+2],"disp") == 0)                // affichage
	  g_display(g);
    }
    else if(strcmp(argv[i], "gen") == 0){
      int n = atoi(argv[i+1]);
      double proba = atoi(argv[i+2]);
      g = generation(n, proba);
      if (argc >=i+4)
	if (strcmp(argv[i+3],"disp") == 0)                // affichage
	  g_display(g);
    }
    else if(strcmp(argv[i], "bipartiteGen") == 0){
      int n = atoi(argv[i+1]);
      double proba = atoi(argv[i+2]);
      g = bipartiteGeneration(n, proba);
      if (argc >= i+4)
	if (strcmp(argv[i+3],"disp") == 0)                // affichage
	  g_display(g);
    }
    else if(strcmp(argv[i], "littleGen") == 0){
      int n = atoi(argv[i+1]);
      int k = atoi(argv[i+2]);
      double proba = atoi(argv[i+3]);
      g = littleGeneration(n, k, proba);
      if (argc >=i+5)
	if (strcmp(argv[i+4],"disp") == 0)                // affichage
	  g_display(g);
    }
    else{
      g = readFile(argv[i]);
      if (g == NULL){
	printf("Le fichier n'est pas lisible \n");
      }
      if (argc >=i+2)
	if (strcmp(argv[i+1],"disp") == 0)                // affichage
	  g_display(g);
    }
    return g;
}
