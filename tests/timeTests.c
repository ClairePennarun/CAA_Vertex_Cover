#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <emmintrin.h>

#include <time.h>
#include <string.h>

#include "graph.h"
#include "generation.h"
#include "cover.h"
#include "list.h"
#include "minisat.h"

int getGraine();
uint64_t rdtsc();

int main(int argc, char* argv[]){
  clock_t start,finish;
  double duration = 0;
  int graine = getGraine();
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
    if(strcmp(argv[4], "spanningTreeRec") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = generation(atoi(argv[3]), 0.5);
	start = clock();
	cover = spanningTreeAlgRec(g);
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
      clock_t startCreate;
      clock_t endCreate;
      double durationCreate;
      for (int i = 0; i < atoi(argv[1]); i++){
	startCreate = clock();
	Graph g = generation(atoi(argv[3]), 0.5);
	endCreate = clock();
	start = clock();
	cover = littleCover(g, atoi(argv[5]));
	finish = clock();
	durationCreate += (double)(endCreate - startCreate) / CLOCKS_PER_SEC;
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
      printf("%2.3f seconds creation \n", durationCreate);
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
    if(strcmp(argv[4], "spanningTreeRec") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = treeGeneration(atoi(argv[3]));
	start = clock();
	cover = spanningTreeAlgRec(g);
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
	cover = bipartiteOptAlg(g);
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
    int sizeCoverFound = 0;
    int sizeMaxCover = 0;
    int size = 0;
    if(strcmp(argv[5], "greedy") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = littleGeneration(atoi(argv[3]), atoi(argv[4]), 0.5);
	start = clock();
	cover = greedyAlg(g);
	finish = clock();
	size = l_size(cover);
	printf("taille cover = %d \n", size);
	sizeCoverFound += size;
	if (size > sizeMaxCover)
	  sizeMaxCover = size;
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      } 
      printf("taille de couverture optimale : %d \n", atoi(argv[4]));
      printf("taille moyenne de couverture trouvée : %f \n", (double) sizeCoverFound/(atoi(argv[1])));
      printf("taille maximale de couverture trouvée : %d \n", sizeMaxCover);
    }

    if(strcmp(argv[5], "minisat") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = littleGeneration(atoi(argv[3]), atoi(argv[4]), 0.5);
	start = clock();
	int p = atoi(argv[6]);
	input(g,p);
	minisat();
	cover = output(p);
	finish = clock();
	size = l_size(cover);
	printf("taille cover = %d \n", size);
	sizeCoverFound += size;
	if (size > sizeMaxCover)
	  sizeMaxCover = size;
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      } 
      printf("taille de couverture optimale : %d \n", atoi(argv[4]));
      printf("taille moyenne de couverture trouvée : %f \n", (double) sizeCoverFound/(atoi(argv[1])));
      printf("taille maximale de couverture trouvée : %d \n", sizeMaxCover);
    }

    if(strcmp(argv[5], "bipartiteOpt") == 0){
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = littleGeneration(atoi(argv[3]), atoi(argv[4]), 0.5);
	start = clock();
	cover = bipartiteOptAlg(g);
	finish = clock();
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
    }

    if(strcmp(argv[5], "spanningTree") == 0){
      int sizeCoverFound = 0;
      int sizeMaxCover = 0;
      int size = 0;
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = littleGeneration(atoi(argv[3]),atoi(argv[4]), 0.5);
	g_display(g);
	start = clock();
	cover = spanningTreeAlg(g);
	finish = clock();
	l_display(cover);
	size = l_size(cover);
	printf("taille cover = %d \n", size);
	sizeCoverFound += size;
	if (size > sizeMaxCover)
	  sizeMaxCover = size;
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
      printf("taille de couverture optimale : %d \n", atoi(argv[4]));
      printf("taille moyenne de couverture trouvée : %f \n", (double)sizeCoverFound/atoi(argv[1]));
      printf("taille maximale de couverture trouvée : %d \n", sizeMaxCover);
    }

    if(strcmp(argv[5], "edgesDeletion") == 0){
      int sizeCoverFound = 0;
      int sizeMaxCover = 0;
      int size = 0;
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = littleGeneration(atoi(argv[3]),atoi(argv[4]), 0.5);
	start = clock();
	cover = edgesDeletionAlg(g);
	finish = clock();
	l_display(cover);
	size = l_size(cover);
	printf("taille cover = %d \n", size);
	sizeCoverFound += size;
	if (size > sizeMaxCover)
	  sizeMaxCover = size;
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
      printf("taille de couverture optimale : %d \n", atoi(argv[4]));
      printf("taille moyenne de couverture trouvée : %f \n", (double)sizeCoverFound/ atoi(argv[1]));
      printf("taille maximale de couverture trouvée : %d \n", sizeMaxCover);
    }

    if(strcmp(argv[5], "littleCover") == 0){
      int sizeMin = 0;
      int sizeMax = 0;
      for (int i = 0; i < atoi(argv[1]); i++){
	Graph g = littleGeneration(atoi(argv[3]),atoi(argv[4]), 0.5);
	g_display(g);
	printf("couverture optimale de taille %d \n", atoi(argv[4]));
	sizeMin = atoi(argv[4]);
	start = clock();
	cover = littleCover(g, atoi(argv[6]));
	finish = clock();
	l_display(cover);
	size = l_size(cover);
	if (size < sizeMin)
	  sizeMin = size;
	if (size > sizeMax)
	  sizeMax = size;
	duration += (double)(finish - start) / CLOCKS_PER_SEC;
	g_freeGraph(g);
      }
      printf("taille min trouvée : %d, taille max trouvée : %d \n", sizeMin, sizeMax);
    }
    if(cover != NULL)
      l_freeList(cover);
    printf("%2.3f seconds \n", duration);
    return EXIT_SUCCESS;
  }

  return EXIT_SUCCESS;
}


int getGraine(){
  return rdtsc();
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
