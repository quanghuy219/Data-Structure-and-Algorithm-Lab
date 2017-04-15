#include <stdio.h>
#include <stdlib.h>
#include "nodeStack.h"


int main() {
  stackType *a;
  Initialize(a);
  int n;
  printf("Enter a number: ");
  scanf("%d",&n);
  do {
    push(a,n%2);
    n = n/2;
  } while(n > 0);

  Node *x = a -> top;
  do {
    printf("%d",x -> data);
    x = x -> prev;
  } while(x != NULL);
  printf("\n");
  return 0;
}
