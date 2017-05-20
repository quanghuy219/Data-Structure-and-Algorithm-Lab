#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
  char name[MAX];
  char email[MAX];
  char tel[MAX];
} address;

typedef address elementType;

int total;


#include "sll.h"



void menu1(s_list *list){
  FILE *fin = fopen("addressList.txt","r");
  if (fin == NULL) {
    printf("Failed to read file phoneDB.txt");
    return;
  }

  char buff[100];
  buff[0] = '\0';
  elementType adr;

  fgets(buff,100,fin);
  sscanf(buff,"%s %s %s",adr.name,adr.email,adr.tel);
  list -> root = makeNewNode(adr);
  list -> cur = list -> root;
  buff[0]='\0';
  total++;
  while(fgets(buff,100,fin) != NULL){
    sscanf(buff,"%s %s %s",adr.name,adr.email,adr.tel);
   insertAfterCur(adr,list);
   buff[0] = '\0';
   total++;
  }
  printf("Build list succesfullly\n\n");
  fclose(fin);
}


void countTotal(s_list *list){
  Node *p;
  total = 0;
  for( p = list -> root; p != NULL; p = p->next){
    if(p != NULL) total ++;
  }
}


elementType readNode(){
  elementType new;
  while(getchar() != '\n');
  printf("Name: ");
  fgets(new.name,MAX,stdin);
  if (new.name[strlen(new.name)-1] == '\n') new.name[strlen(new.name)-1] = '\0';
  printf("Email: ");
  fgets(new.email,MAX,stdin);
  if (new.email[strlen(new.email)-1] == '\n') new.email[strlen(new.email)-1] = '\0';
  printf("Phone number: ");
  fgets(new.tel,MAX,stdin);
  if (new.tel[strlen(new.tel)-1] == '\n') new.tel[strlen(new.tel)-1] = '\0';
  return new;
}




void displayNode(Node *p){
  if(p != NULL)
  printf("%-20s%-20s%s\n",p -> addr.name,p -> addr.email,p->addr.tel);
}





void traversingList(s_list *list){
  Node *p;
  int i=0;
  for (p = list -> root; p != NULL; p=p->next) {
    printf("%-5d",i+1);
    displayNode(p);
    i++;
  }
}

void traverse(Node* root){
  Node* p;
  for( p = root; p != NULL; p = p->next){
    displayNode(p);
  }
}


int main()
{
  s_list list;
  total = 0;
  Initialize(&list);
  int choice, n;
  elementType new;
  while (1)
    {
      countTotal(&list);
      printf("total = %d\n", total);
      printf(" 1. Build list\n");
      printf(" 2. read node\n");
      printf(" 3. display\n");
      printf(" 4. Insert at head\n");
      printf(" 5. Insert before cur\n");
      printf(" 6. Insert after cur\n");
      printf(" 7. Delete first element\n");
      printf(" 8. Delete cur element\n");
      printf(" 9. Move cur to position\n");
      printf(" 10. Show cur\n");
      printf(" 11. Insert at position\n");
      printf(" 12. Delete at position\n");
      printf(" 13. Reverse list\n");
      printf(" 14. Insert at last\n");
      printf(" 15. Delete last\n");
      printf(" 0. Exit\n");
      printf("Your choice: ");
      scanf("%d",&choice);
      switch (choice)
	{
	case 1:
	  menu1(&list);
	  break;
	case 2:
	  //menu2();
	  break;
	case 3:
	  traversingList(&list);
	  break;
	case 4:{
    while(getchar() != '\n');
	  new = readNode();
	  insertAtHead(new,&list);
	  break;
	}
	case 5:
	  while(getchar() != '\n');
    new = readNode();
	  insertBeforeCur(new,&list);
	  break;
	case 6:
	  while(getchar() != '\n');
	   new = readNode();
	  insertAfterCur(new,&list);
	  break;
	case 7:
	  deleteFirstElement(&list);
	  break;
	case 8:
	  deleteCurrentElement(&list);
	  break;
	case 9:
	  printf("nth element: ");
	  scanf("%d",&n);
	  moveCur(n,&list);
	  break;
	case 10:
	  printf("Cur: %-20s%-20s%s\n", list.cur -> addr.name, list.cur->addr.email , list.cur -> addr.tel);
	  break;
	case 11:
	  printf("nth element: ");
	  scanf("%d",&n);
    elementType new = readNode();
	  insertAtPosition(n,&list,new);
	  break;
	case 12:
	  printf("nth element: ");
	  scanf("%d",&n);
	  deleteAtPosition(n,&list);
	  break;
	case 13:
	  list_reverse(&list);
	  break;
  case 14:
    new = readNode();
    insertAtLast(new,&list);
    break;
  case 15:
    deleteLast(&list);
    break;
	case 0: printf("Exit!!!\n"); return 0;
	default:
	  printf("Invalid input!\n\n");
	  break;
	}
    }
}
