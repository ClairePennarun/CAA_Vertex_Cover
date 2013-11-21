#include <stdlib.h>
#include <stdio.

#include "list.h"

int main(int argc, char* argv[]){
  List l = l_createList();

  l_addInFront(l, 2);
  l_insertInHead(l, 4);

  l_deleteFirstOccur(l, 4);
  l_display(l);

  l_addInFront(l, 8);
  l_addInFront(l, 10);
  l_addInFront(l, 1);
  l_addInFront(l, 2);
  l_addInFront(l, 11);
  l_display(l);

  l_deleteFirstOccur(l, 2);
  l_display(l);

  printf("Element selectionne numero 0 : %d\n", l_getVal(l));
  l_next(l);
  printf("Element selectionne numero 1 : %d\n", l_getVal(l));

  l_head(l);
  int i = 0;
  while (!l_isOutOfList(l)){
    printf("Element selectionne numero %d : %d\n", i, l_getVal(l));
    i++;
    l_next(l);
  }

  printf("Taille de la list : %d\n", l_size(l));
  l_freeList(l);

  return EXIT_SUCCESS;
}
