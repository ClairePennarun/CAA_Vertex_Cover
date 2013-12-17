#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include "graph.h"
#include "generation.h"
#include "cover.h"

int main(int argc, char* argv[]){
  clock_t start,finish;
  double duration = 0;
  int graine = time(NULL);
  srand(graine);
  printf("La graine pour l'aléatoire est : %d\n", graine);
  for (int i = 0; i < atoi(argv[1]); i++){
    Graph g = generation(atoi(argv[2]), 0.5);

    start = clock();
    List cover = greedyAlg(g);
    finish = clock();
    duration += (double)(finish - start) / CLOCKS_PER_SEC;
    g_freeGraph(g);
    l_freeList(cover);
  }
  printf("%2.3f seconds \n", duration);
  return EXIT_SUCCESS;
}
