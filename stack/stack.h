#ifndef __STACK_H__
#define __STACK_H__

// Value returned when trying to pop from an empty stack
#define DEFAULT_VALUE 0
typedef int StackInfo; /* use void* for a generic stack */

typedef struct _stack_ Stack;

/* Alloc a new stack */
Stack* create_stack();

/* Return the quantity of stack items */
int stack_size(Stack* stack);

/* Remove all items of the stack */
void empty_stack(Stack* stack, void (*freeInfo)(StackInfo));

/* Add a new value at the end of the stack */
void push(Stack* stack, StackInfo value);

/* Remove and return the first item of the stack */
StackInfo pop(Stack* stack);

/* Desallocate stack content */
void free_stack(Stack* stack, void (*freeInfo)(StackInfo));

#endif
