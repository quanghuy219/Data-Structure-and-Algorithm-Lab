#include <stdio.h>
#include <stdlib.h>
#include "listQueue.h"

void print(Queue *q) {
  int i;
  node *x = q -> front;
  
  while (x != NULL) {
    printf("%d    ", x -> data);
    x = x -> prev;
  }
}

int main() {
  Queue q;
  int choice,a;
  Initialize(&q);

  while (1) {
    printf("1. EnQueue\n");
    printf("2. DeQueue\n");
    printf("3. Print\n");
    printf("0. Exit\n");
    scanf("%d",&choice);

    switch (choice) {

      case 1:
        printf("Enter a num: ");
        scanf("%d",&a);
        enQueue(&q,a);
        break;
      case 2: deQueue(&q);
        break;
      case 3: print(&q);
      printf("\n\n");
          break;
      case 0: return 0;
    }
    printf("\n\n");
  }



  return 0;
}
