#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "db_list.h"

# define MAX_STRING_MODEL 30
# define MAX_STRING_MEMORY 10
# define MAX_STRING_SCREENSIZE 10
# define MAX_PAGE 34

int len;

PHONE readData(){
  PHONE new;
  while(getchar() != '\n');
  printf("Model: ");
  gets(new.model);

  printf("Memory: ");
  gets(new.memory);

  printf("Screen size: ");
  gets(new.screenSize);

  printf("Price: ");
  scanf("%d",&new.price);
  return new;
}



void displayNode(node_ph *p){
  printf("%-30s%-10s%-10s%-10d%d\n",p -> Phone.model,p -> Phone.memory,p -> Phone.screenSize,p -> Phone.price,p->count);
}


void buildList(){
  FILE *fin = fopen("phoneDB.dat","rb");
  if (fin == NULL) {
    printf("Cannot open file phoneDB.dat\n");
    return;
  }

  PHONE ph;
  node_ph* new;
  fread(&ph,sizeof(PHONE),1,fin);
  root = makeNewNode(ph);
  tail = root;
  cur = root;
  //displayNode(root);
  //printf("len = %d\n\n",len);
  while (fread(&ph,sizeof(PHONE),1,fin) == 1) {
    insertAfterCur(&root,&tail,&cur,ph);
  }
  //printf("len = %d\n",len);
   printf("Build list succesfullly\n\n");
  fclose(fin);
}


void travereForward(node_ph* r){
  node_ph *p;
  int i = 1;
  for (p = r; p != NULL; p=p->next) {
    printf("%d\t",i);
    displayNode(p);
    i++;
  }
}


void travereBackward(){
  int i = 1;
  node_ph *p;
  for (p = tail; p != NULL; p=p->prev) {
    printf("%d\t",i);
    displayNode(p);
    i++;
  }
}


void printData(){
  int i;
  while(1){
  printf("1. Print Forward\n");
  printf("2. Print Backward\n");
  printf("0. Exit\n");
  printf("Choose: ");
  scanf("%d",&i);
  switch (i) {
  case 1: {
    travereForward(root);
    printf("\n\n\n");
    break;
  }
  case 2:
    travereBackward();
    printf("\n\n\n");
    break;
  case 0:
    printf("\n\n\n");
    return;
  default: printf("Invalid!!! Choose 1 or 2\n");
    break;
  }
  }
}



void moveCur(node* root, node* cur, int pos){
  int i = 1;
  if (pos <= 1) {
    cur = root;
  }
  else if (pos >= len) {
    cur = tail;
  }
  else{
    cur = root;
    while( i != pos){
      cur = cur -> next;
      i++;
    }
  }
}


void Insert(){
  int choice,pos;
  PHONE new;
  while(1){
    printf("1. Insert at head\n");
    printf("2. Insert at last\n");
    printf("3. Insert at middle\n");
    printf("0. Exit!!\n");
    printf("Choose: ");
    scanf("%d",&choice);
    switch (choice) {
    case 1: {
      new = readData();
      insertAtHead(&root,&tail,&cur,new);
      break;
    }
    case 2:
      new = readData();
      insertAtEnd(&root,&tail,&cur,new);
      break;
    case 3:
      new = readData();
      printf("Position: ");
      scanf("%d",&pos);
      insertAtPosition(&root,&tail,&cur,new,pos-1);
      break;
    case 0: printf("\n\n\n"); return;
    default: printf("Invalid!!!\n");
      break;
    }
  }
}



void searchTranspose(){
  node_ph *p;
  p = cur -> prev;
  (p -> prev) -> next = cur;
  cur -> prev = p -> prev;
  cur -> next -> prev = p;
  p -> next = cur -> next;
  cur -> next = p;
  p -> prev = cur;
}


void moveToFront(){
  elementtype a = cur -> Phone;
  deleteNode(&root,&tail,&cur);
  insertAtHead(&root,&tail,&cur,a);
}


void sortByCount(){
  node_ph *p,*p1;
  elementtype tmp;
  int tmp1;
  for ( p = root; p != NULL; p = p -> next) {
    for (p1 = p; p1 != NULL; p1 = p1 -> next) {
      if ( p -> count < p1 -> count) {
        tmp = p -> Phone;
        p -> Phone = p1 -> Phone;
        p1 -> Phone = tmp;

        tmp1 = p -> count;
        p -> count = p1 -> count;
        p1 -> count = tmp1;
      }
    }
  }
}



void Search_Update(){
  char search[MAX_STRING_MODEL];
  char model[MAX_STRING_MODEL];
  int i,j, flag = 0;
  int choice;
  node_ph *p;

  while(getchar() != '\n');
  printf("Model: ");
  fgets(search,MAX_STRING_MODEL,stdin);


  if (search[strlen(search)-1] == '\n') {
    search[strlen(search)-1] = '\0';
  }
  printf("search: %s\n\n",search);

  for (i = 0; i < strlen(search); i++) {
    search[i] = tolower(search[i]);
  }
  search[i+1] = '\0';

  for (p = root; p != NULL; p=p->next) {
    model[0] = '\0';
    for (j = 0; j <= strlen(p->Phone.model); j++) {
      model[j] = tolower(p -> Phone.model[j]);
    }

    if(strcmp(model,search) == 0){
       printf("%-30s%-10s%-10s%d\n\n\n",p -> Phone.model,p -> Phone.memory,p -> Phone.screenSize,p -> Phone.price);
       flag = 1;
       cur = p;
       (cur -> count)++;
    }

  }



  //moveToFront();




  if (flag == 0) {
    printf("No result found!!!\n\n");
  }
  else{
    printf("1. Move to front\n");
    printf("2. Transpose\n");
    printf("3. Sort by count\n");
    printf("Choose: ");
    scanf("%d",&choice);
    switch (choice) {
      case 1: moveToFront();
        break;
      case 2:
        if (cur != root) searchTranspose();
        break;
      case 3:
        sortByCount();
        break;
    }
  }
}




void Delete(){
  int n;
  printf("Delete element: ");
  scanf("%d",&n);
  deleteAtPosition(&root,&tail,&cur,n-1);
}

node *root1, *root2, *tail1, *tail2, *cur1, *cur2;


void Divide(){
  int n1,n2;
  do{
    printf("STARTING POINT: ");
    scanf("%d", &n1);

    printf("NUMBER OF ELEMENT(S): ");
    scanf("%d", &n2);
    while(getchar() != '\n');
    if(n1 < 0 || n2 <= 0)
      printf("Invalid value!\nPlease re-enter!\n\n");
  }while(n1 < 0 || n2 <= 0);

  split(root, &root1, &tail1, &cur1, &root2, &tail2, &cur2, n1, n2);


  printf("First list: \n");
  travereForward(root1);
  printf("\n\n\nSecond list: \n");
  travereForward(root2);

}





int main()
{
  len = 0;
  PHONE new;
  int choice;
  while (1)
    {
      printf(" 1. Build list from file dat\n");
      printf(" 2. Print all database\n");
      printf(" 3. Insert at position\n");
      printf(" 4. Delete at position\n");
      printf(" 5. Search and update\n");
      printf(" 6. Divide and Extract\n");
      printf(" 7. Reverse List\n");
      printf(" 8. Save to file\n");
      printf(" 0. Quit\n");
      printf("Your choice: ");
      scanf("%d",&choice);
      switch (choice)
	{
	case 1:
	  buildList();
	  break;
	case 2:
	  printData();
	  break;
	case 3:
	  Insert();
	  break;
	case 4:
	  Delete();
	  break;
	case 5:
	  Search_Update();

	  break;

	case 6:
  Divide();
	  break;
	case 7:
	  reverseList(&root,&tail,&cur);
	  break;
	case 0: printf("Exit!!!\n"); return 0;
	default:
	  printf("Invalid input! Your choice must be from 1 to 7\n\n");
	  break;
	}
    }
}
