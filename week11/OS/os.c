#include <stdio.h>
#include <stdlib.h>
#include "listQueue.h"

int process,count;
float mem_capa, mem_used;


void listProgram(Queue *q) {
  Node *tmp = q -> front;
  printf("%-10s%s\n","ID","MEMORY USE");
  while (tmp != NULL) {
    printf("%-10d%f\n",tmp -> data.id,tmp -> data.memory);
    tmp = tmp -> prev;
  }
  printf("\n");
}


void Create(Queue *wait) {
  elementtype program;
  printf("Program ID: ");
  scanf("%d",&program.id);
  printf("Program memory: ");
  scanf("%f",&program.memory);

  enQueue(wait,program);
}



void killProgram(Queue *run, Queue* wait) {
  int id;
  Node *cur;
  Node *cur1,*cur2;

  printf("Program ID: ");
  scanf("%d",&id);
  int a,b;
  a = findProgram(wait,id,&cur);
  cur1 = cur;
  b = findProgram(run,id,&cur);
  cur2 = cur;
  if ( a == 1) {
      deleteNode(wait,id,&cur);
      count--;
      mem_used = mem_used - cur -> data.memory;
      printf("Program #%d killed\n\n",id);
      //printf("Waiting\n");
  }
  else if ( b == 1 ) {
    deleteNode(run,id,&cur);
     count--;
     mem_used = mem_used - cur -> data.memory;
    printf("Program #%d killed\n\n",id);
    //printf("Running\n");
  }
  else printf("Cannot find program!!!\n\n\n");
}


void processRunning(Queue *run, Queue *wait) {
  elementtype temp;
  elementtype tmp;
  if (isEmpty(wait) == 1) {
    return;
  }
  temp = checkFront(wait);
  if (mem_used + temp.memory <= mem_capa && count < process) {
    tmp = deQueue(wait);
    enQueue(run,tmp);
    count++;
    mem_used = mem_used + tmp.memory;
  }
}




int main() {
  printf("Memory capacity(GB): ");
  scanf("%f",&mem_capa);
  printf("Number of parallel program: ");
  scanf("%d",&process);
  mem_used = 0;
  count = 0;


  Queue wait,run;
  int choice,id;
  Node *cur;
  Initialize(&wait);
  Initialize(&run);

  while (1) {
    printf("1. Create new program\n");
    printf("2. Kill program\n");
    printf("3. Check program status\n");
    printf("0. Exit\n");
    printf("Choose: ");
    scanf("%d",&choice);
    //processRunning(&run,&wait);
    switch (choice) {
      case 1:
        Create(&wait);
        break;

      case 2:
      killProgram(&run,&wait);
        break;

      case 3:
      printf("Running:\n");
      listProgram(&run);
      printf("Waiting\n");
      listProgram(&wait);
      break;

      case 0:
        printf("Exit!!!\n\n\n");
        return 0;
    }
    processRunning(&run,&wait);
    printf("\n\n");
  }
  return 0;
}
