#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodeStack.h"
#include "nodeStackChar.h"



void displayTop(stackType s1){
  printf("Top = %d\n",s1.top -> data);
}

void displayStack(stackType s1){
  Node *p = s1.top;

  if (empty(&s1)) {
    printf("Stack empty\n");
    return;
  }

  while( p != NULL){
    printf("%d    ",p->data);
    p = p -> prev;
  }
  printf("\n");
}


void Undo(stackType_ch *undo, stackType *s1){
  Eltype_ch a;
  a = pop_ch(undo);
  if ( strcmp(a.step,"POP") == 0) {
    push(s1,a.val);
  }

  if ( strcmp(a.step,"PUSH") == 0) {
    pop(s1);
  }

}


int main() {
  int choice, val;
  int tmp;
  stackType s1;
  stackType_ch undo;
  Initialize(&s1);
  Initialize_ch(&undo);
  Eltype_ch a;

  while (1) {
    printf("1. Push\n");
    printf("2. Display top\n");
    printf("3. Pop\n");
    printf("4. Undo\n");
    printf("5. Display int stack\n");
    printf("0. Exit\n");
    printf("Choose: ");
    scanf("%d",&choice);
    switch (choice) {
      case 1:
        printf("Enter value: ");
        scanf("%d",&val);
        push(&s1,val);
        strcpy(a.step,"PUSH");
        a.val = val;
        push_ch(&undo,a);
        printf("\nPUSH %d",val);
        break;

      case 2:
        displayTop(s1);
        break;

      case 3:
        tmp = pop(&s1);
        strcpy(a.step,"POP");
        a.val = tmp;
        push_ch(&undo,a);
        printf("\nPOP");
        break;

      case 4:
        Undo(&undo,&s1);
        printf("\nUndo");
        break;

      case 5:
        displayStack(s1);
        break;

      case 0: printf("\n");
      return 0;
      default: printf("\nWrong input!!!"); break;
    }
    printf("\n\n\n");
  }
  printf("\n");
  return 0;
}
