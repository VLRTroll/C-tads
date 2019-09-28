#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* A tester program to approve all the definded methods
 * in list.h
*/
void freeItem(Item i) { free(i); }

void printItem(Item i){
  printf("%d,", *i);
}

int cmpItem(Item a, Item b) {
  return *a - *b;
}

void logEmpty(List* list){
  if (empty(list)) printf("A lista esta vazia!\n");
  else             printf("A lista possui %d elemento(s)\n", length(list));
}

void logContains(List* list, Item item){
  if (contains(list,item,cmpItem)) printf("Possui %d!\n", *item);
  else                             printf("Nao possui %d!\n", *item);
}

void logMap(List* list) {
  printf("[");
  map(list,printItem);
  printf("\b]\n");
}

void logTake(List* list, Item item){
  if (contains(list,item,cmpItem)) printf("O indice do %d eh %d!\n",
                                          *take(list,find(list,item,cmpItem)),
                                          find(list,item,cmpItem));
}

int main(int argc, char const *argv[]) {
  List* list = create();
  logEmpty(list);

  int a = 0,x = 1, y = 2, z = 3;
  append(list,&x);
  append(list,&y);
  append(list,&z);
  append(list,&z);
  logEmpty(list);

  logMap(list);
  insertAt(list,&a,1);
  logMap(list);
  logContains(list,&a);

  logTake(list,&x);
  logTake(list,&z);

  pop(list);
  removeItem(list,&y,cmpItem,freeItem);
  logMap(list);
  printf("Tamanho atual da lista: %d\n", length(list));

  removeAt(list,3);
  logMap(list);


  destroy(list, freeItem);
  return 0;
}
