#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "fileReader.h"

int main(int argc, char* argv[]){
  Graph g = readFile(argv[1]);
  
  displayVertices(g);
  return EXIT_SUCCESS;
}
