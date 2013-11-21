#include <stdlib.h>
#include <stdio.h>

#include "../graph.h"

int main(int argc, char* argv[]){
  Graph g = g_createGraph(10);

  g_addEdge(g, 1, 3);
  g_addEdge(g, 2, 1);
  g_addEdge(g, 5, 7);
  g_addEdge(g, 1, 8);
  g_addEdge(g, 9, 8);
  g_addEdge(g, 2, 4);
  g_addEdge(g, 4, 5);
  g_addEdge(g, 5, 5);

  g_display(g);

  g_freeGraph(g);

  return EXIT_SUCCESS;
}
