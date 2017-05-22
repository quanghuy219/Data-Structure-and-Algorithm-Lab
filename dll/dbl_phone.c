#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

# define MAX_STRING_MODEL 30
# define MAX_STRING_MEMORY 10
# define MAX_STRING_SCREENSIZE 10
# define MAX_PAGE 34

int len;

#include "list.h"


void correct(char *s)
{
  for (int i=0; i<strlen(s); i++)
    if (s[i] == '_')
      s[i] = ' ';
}


PHONE readData(){
  PHONE new;
  //while(getchar() != '\n');

  while(strlen(new.model) == 0){
    printf("Model: ");
    gets(new.model);
  }
  while(strlen(new.memory) == 0){
    printf("Memory: ");
    gets(new.memory);
  }
  while(strlen(new.screenSize) == 0){
    printf("Screen size: ");
    gets(new.screenSize);
  }

  printf("Price: ");
  scanf("%d",&new.price);
  return new;
}



void displayNode(Node *p){
  printf("%-30s%-10s%-10s%d\n",p -> Phone.model,p -> Phone.memory,p -> Phone.screenSize,p -> Phone.price);
}


void buildList(db_list *list){
  FILE *fin = fopen("phoneDB.dat","rb");
  if (fin == NULL) {
    printf("Cannot open file phoneDB.dat\n");
    return;
  }

  PHONE ph;
  Node* new;
  fread(&ph,sizeof(PHONE),1,fin);
  list -> root = makeNewNode(ph);
  list -> tail = list -> root;
  list -> cur = list -> root;
  //displayNode(root);
  printf("len = %d\n\n",len);
  while (fread(&ph,sizeof(PHONE),1,fin) == 1) {
    insertAfterCur(list,ph);
  }
  printf("len = %d\n",len);
   printf("Build list succesfullly\n\n");
  fclose(fin);
}



void Search_Update(){
  char search[MAX_STRING_MODEL];
  char model[MAX_STRING_MODEL];
  int i,j, flag = 0;
  int choice;
  Node *p;

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

void insertAtMiddle(db_list *list){
  int pos;
  PHONE new;
  new  = readData();
  printf("Position: ");
  scanf("%d",&pos);
  if(pos > len) insertAfterLast(list,new);
  else if (pos <= 0) insertAtHead(list,new);
  else {
    moveCur(list,pos);
    insertBeforeCur(list,new);
  }
}




void splitList(Node* r, Node** r1, Node** r2, int start, int num){
  if (start <= 1) {
    start = 1;
    cur = r;
  }

  else if (start >= len) {
    start = len;
    cur = tail;
  }

  if (num >= 0){

  }
}


void Divide(){
  int start;
  int num;
  Node* r1,r2;
  printf("Initial position: ");
  scanf("%d",&start);
  printf("Enter num > 0 to split forwark\n num < 0 to split backward\n");
  printf("Enter number of nodes: ");
  scanf("%d",&num);

}





int main()
{
  int pos;
  len = 0;
  PHONE new;
  db_list list;
  Initialize(&list);
  int choice;
  while (1)
    {
      printf(" 1. Build list from file dat\n");
      printf(" 2. Traverse forward\n");
      printf(" 3. Traverse backward\n");
      printf(" 4. Insert at head\n");
      printf(" 5. Insert at last\n");
      printf(" 6. Insert at middle\n");
      printf(" 7. Delete head\n");
      printf(" 8. Delete last\n");
      printf(" 9. Delete current\n");
      printf(" 10. Search and update\n");
      printf(" 11. Divide and Extract\n");
      printf(" 12. Reverse List\n");
      printf(" 13. Save to file\n");
      printf(" 0. Quit\n");
      printf("Your choice: ");
      scanf("%d",&choice);
      switch (choice)
	{
	case 1:
	  buildList(&list);
	  break;
	case 2:
	  traverseForward(&list);
	  break;
  case 3:
    traverseBackward(&list);
    break;
	case 4:
    new = readData();
	  insertAtHead(&list,new);
	  break;
	case 5:
    new = readData();
	  insertAfterLast(&list ,new);
	  break;
  case 6:
    insertAtMiddle(&list);
    break;
  case 7:
    deleteHead(&list);
    break;
  case 8:
    deleteTail(&list);
    break;
  case 9:
    printf("Position: ");
    scanf("%d",&pos);
    moveCur(&list,pos);
    deleteCurrent(&list);
    break;
	case 10:
	  Search_Update();
	  break;
  case 12:
    Reverse(&list);
    break;

	case 0: printf("Exit!!!\n"); return 0;
	default:
	  printf("Invalid input! Your choice must be from 1 to 7\n\n");
	  break;
	}
    }
}
