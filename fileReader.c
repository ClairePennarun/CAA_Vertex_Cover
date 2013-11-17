#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

Graph readFile(char* file){

  FILE* tmpfile = NULL;
  char* line = NULL;
  size_t len = 0;
  
  tmpfile = fopen(file, "r");
  
  if (tmpfile != NULL) {
    getline(&line, &len, tmpfile); // recuperation de la premiere ligne
    char* tok = strtok(line, "\n"); // recuperation du nb de sommets
    int nbVertices = atoi(tok);
    Graph graph = createGraph(nbVertices);

    int i = 0;
    while(i < nbVertices){
      getline(&line, &len, tmpfile); // recuperation d'une ligne
      tok = strtok(line, ":");
      i = atoi(tok);

      tok = strtok(NULL, ":");
      while(*tok == ' '){
	tok ++;
      }
      tok = strtok(tok, " ");
      while (tok){
	int vertex = atoi(tok);
	addEdge(graph, i, vertex);
	tok = strtok(NULL, " ");
      }
    }  
    fclose(tmpfile);
    return graph;
  }

  free(line);
  return NULL;
}
