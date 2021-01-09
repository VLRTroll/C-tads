#include <stdio.h>
#include "queue.h"

int main(void) {
  Queue* q = create_queue();
  printf("Queue created\n");

  enqueue(q, 1);
  enqueue(q, 2);
  enqueue(q, 3);
  printf("Three items added into the queue\n");
  printf("Queue size: %d\n", queue_size(q));

  printf("%d dequeued\n", dequeue(q));
  printf("Queue size: %d\n", queue_size(q));

  free_queue(q, NULL);
  return 0;
}