#include <stdlib.h>
#include <stdio.h>

#include "../graph.h"

int main(int argc, char* argv[]){
  Graph g = g_createGraph(10);

  g_addEdge(g, 1, 3);
  g_addEdge(g, 2, 1);
  g_addEdge(g, 5, 7);
  g_addEdge(g, 1, 8);
  g_addEdge(g, 9, 0);
  g_addEdge(g, 2, 4);
  g_addEdge(g, 4, 5);

  g_display(g);
  printf("\n");

  g_createNeighborhood(g);
  printf("Degre du sommet 2 : %d\n", g_getDegreVertex(g, 2));
  printf("Degre du sommet 6 : %d\n", g_getDegreVertex(g, 6));
  printf("Degre du graphe : %d\n", g_degreGraph(g));
  printf("Sommet au plus grand degre : %d\n", g_maxDegreVertex(g)-1);

  printf("\n-- Supression des sommets isolés --\n\n");

  g_deleteIsolated(g);

  g_display(g);
  printf("\n");
  
  printf("Degre du sommet 6 : %d\n", g_getDegreVertex(g, 6));

  g_freeGraph(g);

  return EXIT_SUCCESS;
}
