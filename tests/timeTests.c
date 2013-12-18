#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <string.h>

#include "graph.h"
#include "generation.h"
#include "cover.h"
#include "list.h"

int main(int argc, char* argv[]){
  clock_t start,finish;
  double duration = 0;
  int graine = time(NULL);
  srand(graine);
  printf("La graine pour l'aléatoire est : %d\n", graine);

  List cover;

  if(strcmp(argv[2], "gen") == 0){

    if(strcmp(argv[4], "greedy") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = generation(atoi(argv[3]), 0.5);
	start = clock();
	cover = greedyAlg(g);
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }
    if(strcmp(argv[4], "spanningTree") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = generation(atoi(argv[3]), 0.5);
	start = clock();
	cover = spanningTreeAlg(g);
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }
    if(strcmp(argv[4], "edgesDeletion") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = generation(atoi(argv[3]), 0.5);
	start = clock();
	cover = edgesDeletionAlg(g);
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }
    if(strcmp(argv[4], "littleCover") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = generation(atoi(argv[3]), 0.5);
	start = clock();
	cover = littleCover(g, atoi(argv[5]));
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }
    if(cover != NULL)
      l_freeList(cover);
    printf("%2.3f seconds \n", duration);
    return EXIT_SUCCESS;
  }


  else if(strcmp(argv[2], "treeGen") == 0){
    if(strcmp(argv[4], "greedy") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = treeGeneration(atoi(argv[3]));
	start = clock();
	cover = greedyAlg(g);
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }    
    }

    if(strcmp(argv[4], "treeOpt") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = treeGeneration(atoi(argv[3]));
	start = clock();
	cover = treeOptAlg(g);
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }

    if(strcmp(argv[4], "spanningTree") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = treeGeneration(atoi(argv[3]));
	start = clock();
	cover = spanningTreeAlg(g);
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }

    if(strcmp(argv[4], "edgesDeletion") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = treeGeneration(atoi(argv[3]));
	start = clock();
	cover = edgesDeletionAlg(g);
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }

    if(strcmp(argv[4], "littleCover") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = treeGeneration(atoi(argv[3]));
	start = clock();
	cover = littleCover(g, atoi(argv[5]));
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }
    l_freeList(cover);
    printf("%2.3f seconds \n", duration);
    return EXIT_SUCCESS;
  }

  else if(strcmp(argv[2], "bipartiteGen") == 0){
    if(strcmp(argv[4], "greedy") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = bipartiteGeneration(atoi(argv[3]), 0.5);
	start = clock();
	cover = greedyAlg(g);
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }    
    }

    if(strcmp(argv[4], "bipartiteOpt") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = bipartiteGeneration(atoi(argv[3]), 0.5);
	start = clock();
	cover = treeOptAlg(g);
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }

    if(strcmp(argv[4], "spanningTree") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = bipartiteGeneration(atoi(argv[3]), 0.5);
	start = clock();
	cover = spanningTreeAlg(g);
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }

    if(strcmp(argv[4], "edgesDeletion") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = bipartiteGeneration(atoi(argv[3]), 0.5);
	start = clock();
	cover = edgesDeletionAlg(g);
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }

    if(strcmp(argv[4], "littleCover") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = bipartiteGeneration(atoi(argv[3]), 0.5);
	start = clock();
	cover = littleCover(g, atoi(argv[5]));
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }
    l_freeList(cover);
    printf("%2.3f seconds \n", duration);
    return EXIT_SUCCESS;
  }  

  else if(strcmp(argv[2], "littleGen") == 0){
    if(strcmp(argv[5], "greedy") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = littleGeneration(atoi(argv[3]), atoi(argv[4]), 0.5);
	start = clock();
	cover = greedyAlg(g);
	printf("taille de couverture trouvee : %d \n", l_size(cover));
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }    
    }

    if(strcmp(argv[5], "bipartiteOpt") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = littleGeneration(atoi(argv[3]), atoi(argv[4]), 0.5);
	start = clock();
	cover = treeOptAlg(g);
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }

    if(strcmp(argv[5], "spanningTree") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = littleGeneration(atoi(argv[3]),atoi(argv[4]), 0.5);
	start = clock();
	cover = spanningTreeAlg(g);
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }

    if(strcmp(argv[5], "edgesDeletion") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = littleGeneration(atoi(argv[3]),atoi(argv[4]), 0.5);
	start = clock();
	cover = edgesDeletionAlg(g);
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }

    if(strcmp(argv[5], "littleCover") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = littleGeneration(atoi(argv[3]),atoi(argv[4]), 0.5);
	start = clock();
	cover = littleCover(g, atoi(argv[6]));
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }
    l_freeList(cover);
    printf("%2.3f seconds \n", duration);
    return EXIT_SUCCESS;
  }

  return EXIT_SUCCESS;
}
