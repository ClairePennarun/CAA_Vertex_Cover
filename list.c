#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "list.h"
struct elem{
  int val;
  Elem previous;
  Elem next;
};

struct list{
  Elem first;
  Elem last;
  int size;
};

List list_createList(){
  List l = malloc(sizeof(List));
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
  if (previous == NULL) // e etait le premier element, donc next le remplace
    l->first = next;
  else
    previous->next = next;
  if (next == NULL) // e etait le dernier element, donc previous le remplace
    l->last = previous;
  else
    next->previous = previous;
  l->size = l->size - 1;
  free(e);
}

void list_addInFront(List l, int n){ // a renommer addInBack ?
  Elem previous = l->last;
  Elem e = list_createElem(previous, NULL, n);
  if (previous != NULL)
    previous->next = e;
  else // La liste etait vide : l'element ajoute a la fin sera egalement le premier element
    l->first = e;
  l->last = e;
  l->size = l->size + 1;
}

void list_insertInHead(List l, int n){
  Elem next = l->first;
  Elem e = list_createElem(NULL, next, n);
  if (next != NULL)
    next->previous = e;
  else // La liste etait vide : l'element ajoute en tete sera egalement le dernier element
    l->last = e;
  l->first = e;
  l->size = l->size + 1;
}

void list_deleteFirstOccur(List l, int n){
  // On suppose que cette valeur se trouve au moins une fois dans la liste l
  Elem e = l->first;
  while (e->val != n)
    e = e->next;
  list_freeElem(l,e);
}

int list_size(List l){
  return l->size;
}

bool list_contain(List l, int n){
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
    printf(", %d", e->val);
    e = e->next;
  }
  printf("]");
  printf("\n");
}

Elem list_head(List l){
  return l->first;
}

List list_tail(List l){
  list_freeElem(l,list_head(l));
  return l;
}

int list_elemVal(Elem e){
  return e->val;
}
