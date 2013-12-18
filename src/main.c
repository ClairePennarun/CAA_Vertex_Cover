#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <emmintrin.h>

#include "graph.h"
#include "fileReader.h"
#include "list.h"
#include "cover.h"
#include "generation.h"

Graph selectGraph(int argc, char* argv[], int i);
void displayTab(int* tab, int size);
int getGraine();
uint64_t rdtsc();

int main(int argc, char* argv[]){

  /*Graph g = bipartiteGeneration(20, 0.5);

  g_display(g);

  int** parts = computeBiPartition(g_cloneGraph(g));

  printf("Première partition : ");
  displayTab(parts[0], parts[2][0]);

  printf("Deuxième partition : ");
  displayTab(parts[1], parts[2][1]);

  List biPartCouv = bipartiteOptAlg(g_cloneGraph(g));

  printf("Couverture optimale (graphe biparti) : \n");
  l_display(biPartCouv);

  List gloutonCouv = greedyAlg(g_cloneGraph(g));
  printf("Couverture trouvé par le glouton : \n");
  l_display(gloutonCouv);
  
  return EXIT_SUCCESS;*/

  srand(time(NULL));

  if (strcmp(argv[1],"help")==0){                   // aide
    printf("Premier paramètre : \n");
    printf("Sélectionner un des algorithmes suivants :\n");
    printf("1. Algorithme glouton : greedy \n");
    printf("2. Algorithme optimal pour les arbres : treeOpt \n");
    printf("3. Algorithme optimal pour les graphes bipartis : bipartiteOpt\n");
    printf("4. Algorithme 2-approché (arbre couvrant) : spanningTree \n");
    printf("5. Algorithme 2-approché (elimination d'aretes) : edgesDeletion \n");
    printf("6. Algorithme paramétrique optimal pour petite couverture : littleCover puis taille \n");
    printf("\nSecond paramètre : chemin vers le fichier à ouvrir (avec extension) ou appel a une fonction de generation \n");
    printf("\nTroisieme parametre : disp si vous voulez afficher le graphe de départ \n");
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

int getGraine(){
  return rdtsc();//time(NULL);
}

#ifdef __i386
uint64_t rdtsc() {
  uint64_t x;
  __asm__ volatile ("rdtsc" : "=A" (x));
  return x;
}
#else 
uint64_t rdtsc() {
  uint64_t a, d;
  __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
  return (d<<32) | a;
}
#endif

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
