#include <stdlib.h>
#include "queue.h"

typedef struct queue_node QueueNode;
struct queue_node {
  QueueInfo value;
  QueueNode* next;
};

struct _queue_ {
  int size;
  QueueNode *first, *last;
};

Queue* create_queue() {
  Queue* q = malloc(sizeof(*q));
  q->size = 0;
  q->first = q->last = NULL;

  return q;
}

int queue_size(Queue* q) {
  return q->size;
}

void empty_queue(Queue* q, void (*freeInfo)(QueueInfo)) {
  while (q->size > 0) {
    QueueInfo value = dequeue(q);
    if (freeInfo) freeInfo(value); // desalloc item
  }
}

void enqueue(Queue* q, QueueInfo value) {
  QueueNode* qn = malloc(sizeof(*qn)); // new queue node
  qn->value = value;
  qn->next = NULL;

  // Fix pointers
  if (q->size == 0) {
    q->first = q->last = qn;
  } else {
    q->last->next = qn;
    q->last = qn;
  }
  
  q->size++; // update queue size
}

QueueInfo dequeue(Queue* q) {
  if (q->size == 0) return DEFAULT_VALUE;
  
  QueueNode* qn = q->first;
  QueueInfo value = qn->value;
  
  // Fix pointers
  q->first = qn->next;
  if (q->size == 1) q->last = NULL;
  
  q->size--; // update queue size

  free(qn); // desalloc QueueNode struct
  return value;
}

void free_queue(Queue* q, void (*freeInfo)(QueueInfo)) {
  empty_queue(q, freeInfo);
  free(q); // desalloc struct
}