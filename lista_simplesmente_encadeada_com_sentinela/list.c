#include <stdlib.h>
#include "list.h"

typedef struct _node_ Node;

struct _node_ {
  Item data;
  Node *next;
};

struct _list_ {
  Node *first, *last;
  int length;
};

#define foreach(list)       for(Node* node = list->first; node; node = node->next)
#define invalidIndex(index) (index < 0) || (index >= list->length)

List* create(void) {
  List* list = malloc(sizeof(*list));
  list->first = list->last = NULL;
  list->length = 0;
  return list;
}

bool empty(List* list) {
  return !list->length;
}

int length(List* list) {
  return list->length;
}

Node* createNode(Item item) {
  Node* node = malloc(sizeof(*node));
  node->data = item;
  node->next = NULL;
  return node;
}

void append(List* list, Item item) {
  if (empty(list)){
    list->first = list->last = createNode(item);
  } else {
    list->last = list->last->next = createNode(item);
  }
  list->length++;
}

void insertAt(List* list, Item item, int index) {
  if (invalidIndex(index)) return;

  if (!index){
    if (empty(list)) append(list,item);
    else {
      Node* aux = list->first;
      list->first = createNode(item);
      list->first->next = aux;
      list->length++;
    }
    return;
  }

  int i=0;
  foreach(list) {
    if (i == index-1) {
      Node* aux = node->next;
      node->next = createNode(item);
      node->next->next = aux;
      list->length++;
      return;
    }
    i++;
  }
}

int find(List* list, Item item, int (*cmpItem)(Item,Item)){
  int i = 0;
  foreach(list){
    if (!cmpItem(item,node->data)) return i;
    i++;
  }
  return -1;
}

bool contains(List* list, Item item, int (*cmpItem)(Item,Item)) {
  return find(list,item,cmpItem) >= 0;
}

Node* takeNode(List* list, int index) {
  int i=0;
  foreach(list) {
    if (i == index) {
      return node;
    }
    i++;
  }
}

Item take(List* list, int index) {
  if (invalidIndex(index)) return NULL;
  return takeNode(list,index)->data;
}

void map(List* list, void (*func)(Item)) {
  foreach(list){
    func(node->data);
  }
}

Item pop(List* list) {
  if (empty(list)) return NULL;

  if (list->length == 1) { //Verifica se é o único
    Item item = list->last->data; //Guarda o item
    free(list->last); //Destró o últim onó da lista
    list->first = list->last = NULL; //Atualiza os ponteiros sentinela
    list->length--;
    return item;
  }

  Item item = list->last->data; //Guarda o item
  Node* aux; //Penúltimo nó da lista
  foreach(list) { //Procura o penúltimo nó da lista
    if (node->next == list->last) {
      aux = node;
      break;
    }
  }
  free(list->last); //Destroi seu nó
  list->last = aux->next = NULL;
  list->length--;
  return item;
}

void destroyNode(Node* node, void (*destroyItem)(Item)) {
  destroyItem(node->data);
  free(node);
}

void removeItem(List* list, Item item, int (*cmpItem)(Item,Item), void (*destroyItem)(Item)) {
  Node* prev; //Último nó visitado
  foreach(list) {
    if (!cmpItem(item,node->data)) { //Verifica se é o nó desejado
      if (node == list->last) {
        pop(list);
        return;
      }

      Node* aux;
      if (node == list->first){
        aux = list->first;
        list->first = list->first->next;
      } else {
        aux = node;
        prev->next = node->next;
      }

      destroyNode(aux,destroyItem);
      list->length--;
      return;
    }

    prev = node; //Guarda o último nó visitado
  }
}

Item removeAt(List* list, int index) {
  if (invalidIndex(index)) return NULL;
  if (empty(list)) return NULL;
  if (list->length == index) return pop(list);

  if (!index) {
    Node* aux = list->first;
    Item item = aux->data;
    list->first = list->first->next;
    list->length--;

    free(aux);
    return item;
  }

  Node* prev;
  int i=0;
  foreach(list) {
    if (i == index) {
      Node* aux = node;
      Item item = aux->data;
      prev->next = node->next;

      if(i == list->length-1) list->last = prev;
      list->length--;

      free(aux);
      return item;
    }
    prev = node;
    i++;
  }

}

void destroy(List* list, void (*destroyItem)(Item)) {
  for(Node *next,*node = list->first; node; node = next) {
    next = node->next;
    destroyNode(node, destroyItem);
    node = next;
  }
  free(list);
}
