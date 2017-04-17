#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodeStack.h"


void processConfig(stackType a){
  Node *x = a.top;

  while (x != NULL){
    printf("%d",x -> data);
    x = x -> prev;
  }
  printf("\n");
}



void Sum(stackType s1, stackType s2, stackType *result){
  int tmp1,tmp2,tmp;
  int mem = 0;

  while ( empty(&s1) != 1 || empty(&s2) != 1) {
    tmp1 = pop(&s1);
    tmp2 = pop(&s2);
    tmp = tmp1 + tmp2;
    push(result,(tmp + mem) % 10);
    if ( tmp >= 10) {
      mem = 1;
    }
    else mem = 0;

  }

  if (mem == 1) {
    push(result,1);
  }

}



void Subtract(stackType s1, stackType s2, stackType *result){
  int tmp1, tmp2, tmp;
  int mem = 0;

  while (empty(&s1) != 1 || empty(&s2) != 1) {
    tmp1 = pop(&s1);
    tmp2 = pop(&s2);
    tmp = tmp1 - tmp2;
    push(result, (tmp + mem)%10);
    if (tmp < 0) {
      mem = -1;
    }
    else mem = 0;
  }
}




int main() {
  char num1[MAX];
  char num2[MAX];
  int choice,i;
  stackType stack1, stack2, result;

  Initialize(&stack1);
  Initialize(&stack2);
  Initialize(&result);

  printf("1. Sum\n");
  printf("2. Subtract\n");
  printf("Choose: ");
  scanf("%d",&choice);
  while(getchar() != '\n');

  printf("a = ");
  scanf("%s%*c",num1);
  printf("b = ");
  scanf("%s%*c",num2);



  for (i = 0; i < strlen(num1); i++) {
    push(&stack1, num1[i]-'0');
  }
  for (i = 0; i < strlen(num2); i++) {
    push(&stack2, num2[i]-'0');
  }

  switch (choice) {
    case 1:
      printf("a + b = ");
      Sum(stack1,stack2,&result);
      processConfig(result);
      break;

    case 2:
    printf("a - b = ");
    if (strcmp(num1,num2) > 0) {
      Subtract(stack1,stack2,&result);
      processConfig(result);
    }
    else if(strcmp(num1,num2) < 0){
      Subtract(stack2,stack1,&result);
      printf("-");
      processConfig(result);
    }
    else {
    Subtract(stack1,stack2,&result);
    processConfig(result);
    }
    break;

    default: printf("Choose 1 or 2 only\n"); break;
  }



  return 0;
}
