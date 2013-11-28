#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "list.h"

struct list{
  Elem first;
  Elem last;
  Elem current;
  int size;
};

struct elem{
  int val;
  Elem previous;
  Elem next;
};

List l_createList(){
  List newlist = malloc(sizeof(struct list));
  assert(newlist);
  newlist->size = 0;
  newlist->first = NULL;
  newlist->current = NULL;
  newlist->last = NULL;
  return newlist;
}

List l_cloneList(List l){
  List newList = malloc(sizeof(struct list));
  assert(newList);
  newList->size = 0;
  newList->first = NULL;
  newList->current = NULL;
  newList->last = NULL;
  l_head(l);
  while(!l_isOutOfList(l)){
    l_addInFront(newList, l_getVal(l));
    l_next(l);
  }
  return newList;
}

Elem l_createElem(Elem previous, Elem next, int val){
  Elem e = malloc(sizeof(struct elem));
  assert(e);
  e->previous = previous;
  e->next = next;
  e->val = val;
  return e;
}

void l_freeList(List l){
  Elem tmp;
  Elem e = l->first;
  if (e != NULL){
    while((tmp = e->next) != NULL){
      free(e);
      e = tmp;
    }
    free(e);
  }
  free(l);
}

void l_freeElem(List l, Elem e){
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
  if (l->current == e)
    l->current = l->first;
  l->size = l->size - 1;
  free(e);
}

void l_addInFront(List l, int n){ // a renommer addInBack ?
  Elem previous = l->last;
  Elem e = l_createElem(previous, NULL, n);
  if (previous != NULL)
    previous->next = e;
  else{ // La liste etait vide : l'element ajoute a la fin sera egalement le premier element
    l->first = e;
    l->current = e;
  }
  l->last = e;
  l->size = l->size + 1;
}

void l_insertInHead(List l, int n){
  Elem next = l->first;
  Elem e = l_createElem(NULL, next, n);
  if (next != NULL)
    next->previous = e;
  else{ // La liste etait vide : l'element ajoute en tete sera egalement le dernier element
    l->last = e;
    l->current = e;
  }
  l->first = e;
  l->size = l->size + 1;
}

// Je préférais l'ancienne version
// a discuter
void l_deleteFirstOccur(List l, int n){
  Elem e = l->first;
  while (e->val != n && e != NULL)
    e = e->next;
  if (e->val == n)
    l_freeElem(l,e);
}

void l_head(List l){
  l->current = l->first;
}

void l_next(List l){
  // On suppose qu'on était pas out of list (l->current != NULL)
  Elem e = l->current;
  l->current = e->next;
}

int l_getVal(List l){
  return ((l->current)->val);
}

bool l_contain(List l, int n){
  Elem e = l->first;
  while (e != NULL){
    if (e->val == n)
      return true;
    e = e->next;
  }
  return false;
}

bool l_isOutOfList(List l){
  return (l->current == NULL);
}

int l_size(List l){
  return l->size;
}

void l_display(List l){
  if (l_size(l) == 0)
    printf("[ ] \n");
  else{
    Elem e = l->first;
    printf("[");
    if (e != NULL)
      printf("%d", e->val);
    e = e->next;
    while (e != NULL){
      printf(", %d", e->val);
      e = e->next;
    }
    printf("]\n");
  }
}
