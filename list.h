#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct elem* Elem;
typedef struct list* List;

List list_createList();
Elem list_createElem(Elem prev, Elem next, int val);
void list_freeList(List);
void list_freeElem(List, Elem);
void list_addInFront(List, int);
void list_insertInHead(List, int);
void list_deleteFirstOccur(List, int);
int list_size(List);
bool list_contain(List, int);
Elem firstPositive(List, int*);
void display(List);

Elem list_head(List);
List list_tail(List);
int list_elemVal(Elem);

#endif
