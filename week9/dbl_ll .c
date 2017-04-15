#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

# define MAX_STRING_MODEL 30
# define MAX_STRING_MEMORY 10
# define MAX_STRING_SCREENSIZE 10
# define MAX_PAGE 34


typedef struct {
  char model[MAX_STRING_MODEL];
  char memory[MAX_STRING_MEMORY];
  char screenSize[MAX_STRING_SCREENSIZE];
  int price;
} PHONE;


typedef struct list_phone {
  PHONE Phone;
  struct list_phone *next;
  struct list_phone *prev;
} node_ph;

node_ph *root,*cur,*tail;
int len;


void correct(char *s)
{
  for (int i=0; i<strlen(s); i++)
    if (s[i] == '_')
      s[i] = ' ';
}


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


node_ph* makeNewNode(PHONE ph){
  node_ph* new = (node_ph*)malloc(sizeof(node_ph));
  new -> Phone = ph;
  new -> next = NULL;
  new -> prev = NULL;
  return new;
}


void insertAfterLast(PHONE ph){
  node_ph* new = makeNewNode(ph);
  len++;
  if (tail == NULL) {
    tail = new;
    return;
  }
  tail -> next = new;
  new -> prev = tail;
  tail = new;
}



void insertBeforeRoot(PHONE ph, node_ph** r){
  node_ph* new = makeNewNode(ph);
  len++;
  if (r == NULL) {
    *r = new;
    return;
  }
  (*r) -> prev = new;
  new -> next = (*r);
  (*r) = new;
}




void insertAfterCur(PHONE ph){
  len++;
  node_ph* new = makeNewNode(ph);
  if (cur == tail) {
    insertAfterLast(ph);
    return;
  }
  new -> prev = cur;
  new -> next = cur -> next;
  new -> next -> prev = new;
  cur -> next = new;
  cur = cur -> next;
}


void insertBeforeCur(PHONE ph){
  node_ph* new = makeNewNode(ph);
  len++;
  if (cur == root) {
    insertBeforeRoot(ph,root);
    return;
  }
  new -> prev = cur -> prev;
  new -> next = cur;
  cur -> prev = new;
  new -> prev -> next = new;
  cur = cur -> prev;
}


void displayNode(node_ph *p){
  printf("%-30s%-10s%-10s%d\n",p -> Phone.model,p -> Phone.memory,p -> Phone.screenSize,p -> Phone.price);
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
  displayNode(root);
  printf("len = %d\n\n",len);
  while (fread(&ph,sizeof(PHONE),1,fin) == 1) {
    insertAfterCur(ph);
  }
  printf("len = %d\n",len);
   printf("Build list succesfullly\n\n");
  fclose(fin);
}


void travereForward(){
  node_ph *p;
  int i = 1;
  for (p = root; p != NULL; p=p->next) {
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
    travereForward();
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






void moveCur(){
  int pos;
  int i = 1;
  printf("Move to position: ");
  scanf("%d",&pos);
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



void insertAtPosition(){
  int choice;
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
      insertBeforeRoot(new,&root);
      break;
    }
    case 2:
      new = readData();
      insertAfterLast(new);
      break;
    case 3:
      new = readData();
      moveCur();
      insertBeforeCur(new);
      break;
    case 0: printf("\n\n\n"); return;
    default: printf("Invalid!!!\n");
      break;
    }
  }
}



void deleteHead(){
  node_ph* p;
  p = root -> next;
  free(root);
  root = p;
  len--;
}


void deleteTail(){
  node_ph* p;
  p = tail -> prev;
  free(tail);
  tail = p;
  len--;
}


void deleteCurrent(){
  node_ph* p;
  len--;
  p = cur -> prev;
  cur -> prev -> next = cur -> next;
  cur -> next -> prev = cur -> prev;
  free(cur);
  cur = p;
}



void deleteAtPosition(){
  int choice;
  PHONE new;
  while(1){
    printf("1. Delete head\n");
    printf("2. Delate last\n");
    printf("3. Delete current\n");
    printf("0. Exit!!\n");
    printf("Choose: ");
    scanf("%d",&choice);
    switch (choice) {
    case 1: {
      deleteHead();
      break;
    }
    case 2:
      deleteTail();
      break;
    case 3:
      moveCur();
      deleteCurrent();
      break;
    case 0: printf("\n\n\n"); return;
    default: printf("Invalid!!!\n");
      break;
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
    }
  }

  if (flag == 0) {
    printf("No result found!!!\n\n");
  }
  if(flag == 1){
    printf("Do you want to update?");
    printf("1. Yes\n");
    printf("0. No\n");
    scanf("%d",&choice);
    if (choice == 1) {
      PHONE new = readData();
      cur -> Phone = new;
    }
  }
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
	  insertAtPosition();
	  break;
	case 4:
	  deleteAtPosition();
	  break;
	case 5:
	  Search_Update();
	  break;
	  
	  /*
	
	case 4:
	  menu4(); 
	  break;
	case 5:
	  menu5();
	  break;
	case 6:
	  menu6();
	  break;*/
	case 0: printf("Exit!!!\n"); return 0;
	default:
	  printf("Invalid input! Your choice must be from 1 to 7\n\n");
	  break;
	}
    }
}
