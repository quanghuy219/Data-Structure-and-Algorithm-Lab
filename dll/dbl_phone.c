#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

# define MAX_STRING_MODEL 30
# define MAX_STRING_MEMORY 10
# define MAX_STRING_SCREENSIZE 10
# define MAX_PAGE 34

int len;

#include "d_list.h"


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
   printf("Build list succesfullly\n\n");
  fclose(fin);
}



void Search_Update(db_list *list){
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

  for (p = list -> root; p != NULL; p=p->next) {
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
    printf("Do you want to update?\n");
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
  if(pos > len) insertAtLast(list,new);
  else if (pos <= 0) insertAtHead(list,new);
  else {
    moveCur(list,pos);
    insertBeforeCur(list,new);
  }
}


void splitList(db_list *list,db_list *list1, db_list *list2, int start, int end){

  Node *p;
  for(p = list -> root; p != NULL; p = p -> next){
    insertAtLast(list1,p -> Phone);
  }
  printf("List1:\n");
  traverseForward(list1);
  len = count(list);
  if (start <= 1) {
    start = 1;
  }

  if(end >= len) end = len;

  if(start > end) {
    printf("Invalid input\n");
    return;
  }

  moveCur(list1,start);
  printf("len = %d\n",len );
  printf("start = %d. end = %d\n",start,end);
  for (int i = start; i <= end; i++) {
    printf("i = %d\n",i);
    insertAtLast(list2,deleteCurrent(list1));
  }
}


int main()
{
  int pos;
  len = 0;
  PHONE new;
  db_list list;
  db_list list1, list2;
  Initialize(&list);
  Initialize(&list1);
  Initialize(&list2);
  int choice;
  while (1)
    {
      len = count(&list);
      printf("len = %d\n",len);
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
      printf(" 14. Free list\n");
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
	  insertAtLast(&list ,new);
	  break;
  case 6:
    insertAtMiddle(&list);
    break;
  case 7:
    new = deleteHead(&list);
    printf("%-30s%-10s%-10s%d\n",new.model,new.memory,new.screenSize,new.price);
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
	  Search_Update(&list);
	  break;
  case 11:
    printf("Enter start and end: ");
    int start,end;
    scanf("%d %d", &start, &end);
    splitList(&list,&list1,&list2,start,end);
    printf("List 1\n\n\n");
    traverseForward(&list1);
    printf("List2\n\n\n");
    traverseForward(&list2);
    break;
  case 12:
    Reverse(&list);
    break;

  case 14:
    freeList(&list);
    break;

	case 0: printf("Exit!!!\n"); return 0;
	default:
	  printf("Invalid input! Your choice must be from 1 to 7\n\n");
	  break;
	}
    }
}
