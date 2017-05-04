#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listQueue.h"

char flight_name[MAX];
int position[50][6];
int ID;



void printRequest(elementtype request) {
  //printf("%-5d%-10s%-20s%-30s%\n",request.id,request.flight,request.name,request.date);
  printf("Request ID: %d\n",request.id);
  printf("Flight: %s\n",request.flight);
  printf("Name: %s",request.name);
  printf("Booking Date: %s",request.date);
  printf("Quantity: %-5d",request.quantity);
  for (int i = 0; i < request.quantity; i++) {
    printf("%d%-7c", request.seat[i].row,request.seat[i].pos);
  }
  printf("\n\n\n");
}



void printAll(Queue *q) {
  if ( isEmpty(q) == 1) {
    printf("No data!!!\n\n");
    return;
  }
  Node *tmp = q -> front;
  while (tmp != NULL) {
    printRequest(tmp -> data);
    tmp = tmp -> prev;
  }

}


char *getTime(){
  time_t current_time;
    char* c_time_string;

    /* Obtain current time. */
    current_time = time(NULL);

    c_time_string = ctime(&current_time);

    return c_time_string;
}





elementtype Booking() {
  elementtype request;
  char name[MAX];
  int quatity;
  seatType seat[MAX];
  char buff[MAX];

  request.id = ID;
  strcpy(request.flight,flight_name);
  printf("Name: ");
  fgets(request.name,MAX,stdin);
  request.date = getTime();
  printf("Quantity: ");
  scanf("%d",&request.quantity);
  while(getchar() != '\n');
  for (int i = 0; i < request.quantity; i++) {
    printf("Seat: ");
    fgets(buff,MAX,stdin);
    sscanf(buff,"%d%c",&request.seat[i].row,&request.seat[i].pos);
  }
  //enQueue(wait,request);
  printf("\nWaiting\n\n");
  return request;
}





int convert(char c){
  if (c == 'A' || c == 'a')  return 0;
  else if (c == 'B' || c == 'b')  return 1;
  else if (c == 'C' || c == 'c')  return 2;
  else if (c == 'D' || c == 'd')  return 3;
  else if (c == 'E' || c == 'e')  return 4;
  else if (c == 'F' || c == 'f')  return 5;
}





int checkPlace(seatType a) {
  int col = convert(a.pos);
  if ( position[a.row -1 ][col] == 0 ) {
    return 1;
  }
  else return 0;
}





int processBooking(Queue *accept, elementtype request) {
  int flag = 0;
  for (int i = 0; i < request.quantity; i++) {
    if ( checkPlace(request.seat[i]) == 0) {
      flag = 1;
      printf("Seat %d%c not available!!!\n",request.seat[i].row,request.seat[i].pos);
    }
  }

  if (flag == 0) {
    enQueue(accept,request);
    for (int i = 0; i < request.quantity; i++) {
      position[request.seat[i].row -1 ][convert(request.seat[i].pos)] = 1;
    }
    printRequest(request);
    printf("Request Accepted\n\n\n");
    ID++;
    return 1;
  }
  else printf("Request Refused!!!\n\n\n");
  return 0;
}


int Cancel(Queue *accept, Node **cur, int id) {

  elementtype a;

  if ( findProgram(accept,id,cur) == 1) {
    a = (*cur) -> data;
    deleteNode(accept,id,cur);

    for (int i = 0; i < a.quantity; i++) {
      position[a.seat[i].row-1][convert(a.seat[i].pos) ] = 0;
    }
    return 1;
  }
  else return 0;
}



void Edit(Queue *accept, Node **cur, int id){
  elementtype a;
  int flag;
  while(getchar()!='\n');
  if ( findProgram(accept,id,cur) != 1 ) {
    printf("Cannot find request\n\n\n");
    return;
  }
  a = Booking();
  flag = processBooking(accept,a);
  if (flag == 1) {
    Cancel(accept,cur,id);
  }
}


void printSeat(){
  int i,j;
  printf("   %-4c%-4c%-4c%-4c%-4c%-4c\n",'A','B','C','D','E','F');
  for (i = 0; i < 50; i++) {
    printf("%-3d",i);
    for (j = 0; j < 6; j++) {
      printf("%-4d",position[i][j]);
    }
    printf("\n");
  }
}






int main() {
  printf("Booking for flight: ");
  scanf("%s",flight_name);
  ID = 1;
  Queue accept;
  elementtype request;
  int choice,id;
  Node *cur;


  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 6; j++) {
      position[i][j] = 0;
    }
  }

  Initialize(&accept);

  while (1) {
  printf("1. Book ticket\n");
  printf("2. Cancel request\n");
  printf("3. Modify request\n");
  printf("4. Print all request\n");
  printf("5. Seat status\n");
  printf("0. Exit\n");
  printf("Choose: ");
  scanf("%d",&choice);
  printf("\n");
  while (getchar() != '\n');

  switch (choice) {
    case 1:
      request = Booking();
      processBooking(&accept,request);
      break;

    case 2:
      printf("Request ID: ");
      scanf("%d",&id);
      int x;
      x = Cancel(&accept,&cur,id);
      if (x == 1) printf("Request %d cancelled!!!\n\n\n",id);
      else printf("Cannot find request\n\n\n");

      break;

    case 3:
      printf("Request ID: ");
      scanf("%d",&id);
      Edit(&accept,&cur,id);
      break;

    case 4:
      printAll(&accept);
      break;

    case 5:
      printSeat();
      break;

    case 0: printf("Exit!!!\n\n\n");
      return 0;
  }


  }
  return 0;
}
