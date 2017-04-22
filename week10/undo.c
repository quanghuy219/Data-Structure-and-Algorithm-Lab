#include <stdio.h>
#include <stdlib.h>
#include "nodeStack.h"


#define POP 1
#define PUSH 2

void display(stackType s1){
  printf("Top = %d\n",s1.top -> data);
}


int main() {
  int choice, val;
  int tmp;
  stackType s1;
  stackType undo;
  Initialize(&s1);
  Initialize(&undo);

  while (1) {
    printf("1. Push\n");
    printf("2. Display top\n");
    printf("3. Pop\n");
    printf("4. Undo\n");
    printf("0. Exit\n");
    printf("Choose: ");
    scanf("%d",&choice);
    switch (choice) {
      case 1:
        printf("Enter value: ");
        scanf("%d",&val);
        push(&s1,val);
        break;

      case 2:
        display(s1);
        break;

      case 3:
        tmp = pop(&s1);
        break;

      case 4:

      case 0: return 0;
    }
  }



  return 0;
}
