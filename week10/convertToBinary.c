#include <stdio.h>
#include "structStack.h"


int main() {
  int n;
  stackType stack;
  Initialize(&stack);
  printf("Enter: ");
  scanf("%d",&n);
  do{
    push(&stack, n %2);
    n = n / 2;
  }while(n > 0);
  while (!empty(stack)) {
    printf("%d",pop(&stack));
  }
  printf("\n\n\n");
  return 0;
}
