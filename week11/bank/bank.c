#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listQueue.h"

int total_client;
float total_wait;
int num_desk;
int h_prev;
int m_prev;


int countQueue(Queue q){
  node *new;
  int count=0;
  if ( isEmpty(&q) == 1) {
    return 0;
  }

  for(new = q.front; new != NULL; new = new->prev){
    count++;
  }
  return count;
}



int min(Queue *queue){
  int min=0;
  int tmp,init;

  init = countQueue(queue[0]);
  for (int i = 0; i < num_desk; i++) {
    tmp = countQueue(queue[i]);
    if (tmp < init) min = i;
  }
  return min;
}



void menu1(Queue *queue){
  int h,i;
  int m;
  int min_queue,count;
  elementtype client;
  int num_client;
  int time_interval;
  node *new;

  while( h<h_prev || (h == h_prev && m < m_prev)){
  printf("Time (hh:mm): ");
  scanf("%d:%d",&h,&m);
  }

  time_interval = (h - h_prev)*60 + (m - m_prev);
  for (i = 0; i < num_desk; i++) {
    if ( !isEmpty(&queue[i])) {
      for (new = queue[i].front; new != NULL; new = new -> prev) {
        new -> data.wait = new -> data.wait - time_interval;
      }
      new = queue[i].front;
      // while(1){
      //   new -> data.wait = new -> data.wait - time_interval;
      //   if (new -> data.wait <= 0) {
      //     deQueue(&queue[i]);
      //     new = queue[i].front;
      //     continue;
      //   }
      //   new = new -> prev;
      // }

      while (1) {
        if (new -> data.wait < 0) {
          deQueue(&queue[i]);
          new = queue[i].front;
        }
        else break;
      }

    }
  }

  h_prev = h;
  m_prev = m;

  printf("Number of clients: ");
  scanf("%d",&num_client);
  for (i = 0; i < num_client; i++) {
    client.id = total_client++;
    client.h_in = h;
    client.m_in = m;

    min_queue = min(queue);
    printf("min = %d\n",min_queue);
    count = countQueue(queue[min_queue]);
    printf("count = %d\n",count);
    if ( count == 0) {
      client.wait = 0;
    }

    //else client.wait = count * 15 + (queue[min_queue].front)->data.wait;
    else client.wait = queue[min_queue].rear->data.wait+15;
    enQueue(&queue[min_queue],client);
    total_wait += client.wait;
    printf("%d\n",client.wait);

  }



}

int main() {
  int i;
  total_wait = 0;
  total_client = 0;
  h_prev = 9;
  m_prev = 0;

  printf("Number of service desks: ");
  scanf("%d",&num_desk);
  Queue desk[num_desk];
  for(i = 0; i < num_desk; i++){
    Initialize(&desk[i]);
  }
  int choice;
  while(1){
  printf("1. Time entering the bank\n");
  printf("2. Total clients\n");
  printf("3. Total waiting time\n");
  printf("4. Average waiting time\n");
  printf("Choose: ");
  scanf("%d",&choice);
  switch (choice) {
    case 1:
    menu1(desk);




  }
  }
  return 0;
}
