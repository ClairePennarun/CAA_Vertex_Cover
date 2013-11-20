#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "fileReader.h"
#include "list.h"
#include "cover.h"

int main(int argc, char* argv[]){
  Graph g = readFile(argv[1]);
  
  //displayVertices(g);
  List cover = edgesDeletionAlg(g);
  display(cover);
  return EXIT_SUCCESS;
}
