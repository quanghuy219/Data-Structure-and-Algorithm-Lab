#include <stdio.h>
#include <string.h>
#include "stackStruct.h"


int main(){
  char num1[100];
  char num2[100];
  int i;
  stackType stack1, stack2, result;

  Initialize(&stack1);
  Initialize(&stack2);
  Initialize(&result);

  printf("Number 1: ");
  scanf("%s%*c",num1);
  printf("Number2: ");
  scanf("%s%*c",num2);

  for (i = 0; i < strlen(num1); i++) {
    push(&stack1, num1[i]-'0');
  }
  for (i = 0; i < strlen(num2); i++) {
    push(&stack2, num2[i]-'0');
  }

  int tmp, tmp1, tmp2;
  int mem = 0;
  int count = 0;
  do{
    tmp1 = pop(&stack1);
    tmp2 = pop(&stack2);
    tmp = tmp1 + tmp2;
    
    push(&result, (tmp+mem)%10);
    if (tmp >= 10) {
      mem = 1;
    }
    else mem = 0;
    count++;
  } while( empty(stack1) != 1 || empty(stack2) != 1 );

  if (mem == 1) {
    push(&result,1);
    count++;
  }

  for (i = count-1; i >= 0; i--) {
    printf("%d",result.storage[i]);
  }
  printf("\n\n\n");
  return 0;
}
