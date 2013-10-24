#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include <list.h>

struct list{
  Elem first ;
  Elem last;
  int size;
};

struct elem{
  int val;
  Elem previous;
  Elem next;
};

ListeDC list_createList(){
  List l = malloc(sizeof(struct list));
  assert(l);
  l->size = 0;
  l->first = NULL;
  l->last = NULL;
  return l;
}

Elem list_createElem(Elem previous, Elem next, int val){
  Elem e = malloc(sizeof(struct elem));
  assert(e);
  e->previous = previous;
  e->next = next;
  e->val = val;
  return e;
}

void list_freeList(List l){
  Elem e = l->first;
  if (e != NULL){
    Elem tmp;
    while((tmp = e->next) != NULL){
      free(e);
      e = tmp;
    }
    free(e);
  }
  free(l);
}

void list_freeElem(List l, Elem e){
  Elem previous = e->previous;
  Elem next = e->next;
  if (previous == NULL) // e était le premier élément, donc next le remplace
    l->first = next;
  else
    previous->next = next;
  if (next == NULL) // e était le dernier élément, donc previous le remplace
    l->last = previous;
  else
    next->previous = previous;
  l->size = l->size - 1;
  free(e);
}

void list_addInFront(List l, int n){
  Elem previous = l->last;
  Elem e = createElem(previous, NULL, n);
  if (previous != NULL)
    previous->next = e;
  else // La liste était vide : l'élément ajouté à la fin sera également le premier élément
    l->first = e;
  l->last = e;
  l->size = l->size + 1;
}

void list_insertInHead(List l, int n){
  Elem next = l->first;
  Elem e = createElem(NULL, next, n);
  if (next != NULL)
    next->previous = e;
  else // La liste était vide : l'élément ajouté en tête sera également le dernier élément
    l->last = e;
  l->first = e;
  l->size = l->size + 1;
}

void list_deleteFirstOccur(List l, int n){
  // On suppose que cette valeur se trouve au moins une fois dans la liste l
  Elem e = l->first;
  while (e->val != n)
    e = e->next;
  freeElem(e);
}

int list_size(List l){
  return l->size;
}

int list_contain(List l, int n){
  Elem e = l->first;
  while (e != NULL){
    if (e->val == n)
      return true;
    e = e->next;
  }
  return false;
}

void display(List l){
  Elem e = l->first;
  printf("[");
  if (e != NULL)
    printf("%d", e->val);
  e = e->next;
  while (e != NULL){
    print(", %d", e->val)
    e = e->next;
  }
  printf("]");
}
