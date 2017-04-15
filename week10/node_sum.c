#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodeStack.h"


// void processConfig(stackType *s){
//   Node *x = s -> top;
//   while (x != NULL) {
//     printf("%d",x->data);
//     x = x -> prev;
//   }
// }


void Sum(stackType *s1, stackType *s2, stackType **result){
  int tmp1,tmp2,tmp;
  int mem = 0;

  tmp1 = s1 -> top -> data;
  tmp2 = s1 -> top -> data;

  push(*result,(tmp1+tmp2+mem)%10);

  if (tmp1 + tmp2 >= 10) {
    mem = 1;
  }

  while ( empty(s1) != 1 || empty(s2) != 1 ) {
    tmp1 = pop(s1);
    tmp2 = pop(s2);
    push(*result,(tmp1+tmp2+mem)%10);
    if (tmp1 + tmp2 >= 10) {
      mem = 1;
    }
    else mem = 0;
  }

  if (mem == 1) {
    push(*result,1);
  }

}




int main() {
  char num1[MAX];
  char num2[MAX];
  int i;
  stackType *stack1, *stack2, *result;

  Initialize(stack1);
  Initialize(stack2);
  Initialize(result);


  printf("Number 1: ");
  scanf("%s%*c",num1);
  printf("Number2: ");
  scanf("%s%*c",num2);


  for (i = 0; i < strlen(num1); i++) {
    push(stack1, num1[i]-'0');
  }
  for (i = 0; i < strlen(num2); i++) {
    push(stack2, num2[i]-'0');
  }


  Sum(stack1,stack2,&result);

  Node *x = result -> top;

  while (x != NULL) {
    printf("%d",x -> data);
    x = x -> prev;
  }
  printf("\n");

  return 0;
}
