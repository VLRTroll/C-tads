#include <stdlib.h>
#include "stack.h"

typedef struct stack_node StackNode;
struct stack_node {
  StackInfo value;
  StackNode* prev;
};

struct _stack_ {
  int size;
  StackNode *last;
};

Stack* create_stack() {
  Stack* stack = malloc(sizeof(*stack));
  stack->size = 0;
  stack->last = NULL;

  return stack;
}

int stack_size(Stack* stack) {
  return stack->size;
}

void empty_stack(Stack* stack, void (*freeInfo)(StackInfo)) {
  while (stack->size > 0) {
    StackInfo value = pop(stack);
    if (freeInfo) freeInfo(value); // desalloc item
  }
}

void push(Stack* stack, StackInfo value) {
  StackNode* node = malloc(sizeof(*node)); // new stack node
  node->value = value;
  node->prev = stack->size == 0 ? NULL : stack->last;

  // Fix pointers
  stack->last = node;
  stack->size++; // update stack size
}

StackInfo pop(Stack* stack) {
  if (stack->size == 0) return DEFAULT_VALUE;

  StackNode* node = stack->last;
  StackInfo value = node->value;

  // Fix pointers
  stack->last = stack->size == 1 ? NULL : node->prev;
  stack->size--; // update stack size

  free(node); // desalloc StackNode struct
  return value;
}

void free_stack(Stack* stack, void (*freeInfo)(StackInfo)) {
  empty_stack(stack, freeInfo);
  free(stack); // desalloc struct
}