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
    getline(&line, &len, tmpfile); // Recuperation de la premiere ligne
    char* tok = strtok(line, "\n"); // Recuperation du nb de sommets
    int nbVertices = atoi(tok);
    Graph graph = g_createGraph(nbVertices);
    int i = 0;
    while(i < nbVertices - 1 ){
      getline(&line, &len, tmpfile); // Recuperation d'une ligne
      tok = strtok(line, ":");
      i = atoi(tok)-1; // Correction de l'indice (de [1, n] -> [0, n-1])

      tok = strtok(NULL, ":");
      while(*tok == ' '){
	tok ++;
      }
      tok = strtok(tok, " ");
      while (tok){
	int vertex = atoi(tok)-1; // Correction de l'indice (de [1, n] -> [0, n-1])
	if (!g_areNeighbor(graph, i, vertex)){
	  g_addEdge(graph, i, vertex);
	}
	tok = strtok(NULL, " ");
      }
    }
    g_createNeighborhood(graph);
    fclose(tmpfile);
    return graph;
  }

  free(line);
  return NULL;
}
