#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "fileReader.h"
#include "list.h"
#include "cover.h"

int main(int argc, char* argv[]){
  Graph g = readFile(argv[1]);
  
  printf("\n");
  g_display(g);
  printf("\n");

  Graph gG = g_cloneGraph(g);
  printf("Calcul de la couverture (greedyAlg)... ");
  List coverG = greedyAlg(gG);
  printf("TERMINE \n");
  printf("Couverture :\n");
  l_display(coverG);
  printf("\n");

  Graph gT = g_cloneGraph(g);
  printf("Calcul de la couverture (treeOptAlg)... ");
  List coverT = treeOptAlg(gT);
  printf("TERMINE \n");
  printf("Couverture :\n");
  l_display(coverT);
  printf("\n");

  Graph gE = g_cloneGraph(g);
  printf("Calcul de la couverture (edgesDeletionAlg)... ");
  List coverE = edgesDeletionAlg(gE);
  printf("TERMINE \n");
  printf("Couverture :\n");
  l_display(coverE);
  printf("\n");

  return EXIT_SUCCESS;
}
