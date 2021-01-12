#include <stdio.h>
#include "stack.h"

int main(void) {
  Stack* s = create_stack();
  printf("Stack created\n");

  printf("Item removed from stack (empty): %d\n", pop(s));

  push(s, 1);
  push(s, 2);
  push(s, 3);
  printf("Three items added into the stack\n");
  printf("Stack size: %d\n", stack_size(s));

  printf("%d popped\n", pop(s));
  printf("Stack size: %d\n", stack_size(s));

  free_stack(s, NULL);
  return 0;
}