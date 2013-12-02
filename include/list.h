#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct elem* Elem;
typedef struct list* List;

List l_createList();
List l_cloneList(List);
Elem l_createElem(Elem, Elem, int);
void l_freeList(List);
void l_freeElem(List, Elem);
void l_addInFront(List, int);
void l_insertInHead(List, int);
void l_deleteFirstOccur(List, int);
void l_head(List);
void l_next(List);
int l_getVal(List);
bool l_contain(List, int);
bool l_isOutOfList(List);
int l_size(List);
void l_display(List);

#endif
