#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <fileReader.h>
#include <graph.h>
#include <list.h>
#include <string.h>


void input(Graph g, int p){
  FILE* file = NULL;
  int n = g_getSize(g);
  file = fopen("input", "w");
  fprintf(file, "p cnf %d %d\n",n*p, ((n*p*(n+p-2))/2+g_numberOfEdges(g)));
  for (int i=1; i<=n; i++){
    for (int k=1; k<=p; k++){
      for (int l=k+1; l<=p; l++){
	fprintf(file, "%d %d 0\n",(-(p*(i-1)+k)),(-(p*(i-1)+l)));
	}
      for (int j=i+1; j<=n; j++){
	fprintf(file, "%d %d 0\n",(-(p*(i-1)+k)),(-(p*(j-1)+k)));	
	}
    }
    List listNeighbors = g_getNeighbors(g, i-1);
    l_head(listNeighbors);
    while (!l_isOutOfList(listNeighbors)){
      int j = l_getVal(listNeighbors);
      if (j>=i){
	for (int k=1; k<=p; k++){
	  fprintf(file, "%d %d ",(p*(i-1)+k),(p*(j)+k));
	  }
	fprintf(file, " 0\n");
      }
      l_next(listNeighbors);
    }
    //l_freeList(listNeighbors);
  }
  fclose(file);
}

void minisat(){
  system("minisat input output > /dev/null");
  }

List output(int p){
  FILE* file = NULL;
  char* line = NULL;
  size_t len = 0;
  file = fopen("output", "r");
  List cover = l_createList();
  ssize_t nb = getline(&line, &len, file);
  free(line);
  char* tok;
  if (nb == 4){
    getline(&line, &len, file); 
    tok = strtok(line, " ");
    while (tok){
      if (*tok != '-'){
	int i = atoi(tok);
	if(i>0){
	  l_addInFront(cover, ((i-1)/p));
	}
	if(i==0){
	  fclose(file);
	  return cover;
	}
      }
      tok = strtok(NULL," ");
    }
  }
  if (cover != NULL)
    l_freeList(cover);
  fclose(file);
  return NULL;
}
