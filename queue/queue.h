#ifndef __QUEUE_H__
#define __QUEUE_H__

// Value returned when trying to dequeue an empty queue
#define DEFAULT_VALUE 0
typedef int QueueInfo; /* use void* for a generic queue */

typedef struct _queue_ Queue;

/* Alloc a new queue */
Queue* create_queue();

/* Return the quantity of queue items */
int queue_size(Queue* q);

/* Remove all items of the queue */
void empty_queue(Queue* q, void (*freeInfo)(QueueInfo));

/* Add a new value at the end of the queue */
void enqueue(Queue* q, QueueInfo value);

/* Remove and return the first item of the queue */
QueueInfo dequeue(Queue* q);

/* Desallocate queue content */
void free_queue(Queue* q, void (*freeInfo)(QueueInfo));

#endif
