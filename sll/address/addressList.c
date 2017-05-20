#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
  char name[MAX];
  char email[MAX];
  char tel[MAX];
} address;


#include "address.h"


typedef struct {
  node_addr *root;
  node_addr *cur;
} s_list;


//node_addr *root,*cur,*prev;









void menu1(s_list *list){
  FILE *fin = fopen("addressList.txt","r");
  if (fin == NULL) {
    printf("Failed to read file phoneDB.txt");
    return;
  }

  char buff[100];
  buff[0] = '\0';
  address adr;

  fgets(buff,100,fin);
  sscanf(buff,"%s %s %s",adr.name,adr.email,adr.tel);
  list -> root = makeNewNode(adr);
  list -> cur = list -> root;
  buff[0]='\0';
  while(fgets(buff,100,fin) != NULL){
    sscanf(buff,"%s %s %s",adr.name,adr.email,adr.tel);
   insertAfterCur(adr,list);
   buff[0] = '\0';
  }
  printf("Build list succesfullly\n\n");
  fclose(fin);
}

address readNode(){
  address new;
  while(getchar() != '\n');
  printf("Name: ");
  gets(new.name);
  printf("Email: ");
  gets(new.email);
  printf("Phone number: ");
  gets(new.tel);
  return new;
}




void displayNode(node_addr *p){
  printf("%-20s%-20s%s\n",p -> addr.name,p -> addr.email,p->addr.tel);
}





void traversingList(s_list *list){
  node_addr *p;
  for (p = list -> root; p != NULL; p=p->next) {
    displayNode(p);
  }
}


void moveCur(int n, s_list *list){
  node_addr *p;
  int count;
  count = 0;
  for(p = list -> root; p != NULL; p = p->next){
    count += 1;
  }
  if (n > count || n < 0) {
    printf("Element not exist!!!\n");
  }
  else if (n == 1) {
    list -> cur = list -> root;
  }
  else {
    p = list -> root;
  for (int i = 0; i < n-1; i++) {
    p = p -> next;
  }
  list -> cur = p;
  }
  displayNode(list -> cur);
}



void insertAtPosition(int n, s_list *list){
  node_addr *p;
  address new;
  int count,i;
  
  new = readNode();

  for(p=list -> root; p != NULL; p = p->next){
    count++;
  }
  if (n > count || n < 0) {
    printf("Element not exist!!!\n");
    return;
  }

  else if( n==1){
    insertAtHead(new,list);
  }
  else {
    i = 0;
    for (p = list -> root; p != NULL; p = p->next) {
      i++;
      if (i == n-1) {
	list -> cur = p;
	break;
      }
    }
    insertAfterCur(new, list);
  }
}


void deleteAtPosition(int n, s_list *list){
  if (n == 1) {
    deleteFirstElement(list);
  }
  else{
  moveCur(n,list);
  deleteCurrentElement(list);
  }
}



//
// void list_reverse(){
//   node_addr *prev;
//   cur = prev = NULL;
//   while (root != NULL) {
//     cur = root;
//     root = root -> next;
//     cur -> next = prev;
//     prev = cur;
//   }
// }



int main()
{
  s_list list;
  Initialize(&list);
  int choice, n;
  address new;
  while (1)
    {
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
	  printf("Name: ");
	  gets(new.name);
    printf("Email: ");
    gets(new.email);
	  printf("Tel: ");
	  scanf("%s",new.tel);
	  insertAtHead(new,&list);
	  break;
	}
	case 5:
	  while(getchar() != '\n');
	  printf("Name: ");
	  gets(new.name);
    printf("Email: ");
    gets(new.email);
	  printf("Tel: ");
	  scanf("%s",new.tel);
	  insertBeforeCur(new,&list);
	  break;
	case 6:
	  while(getchar() != '\n');
	  printf("Name: ");
	  gets(new.name);
    printf("Email: ");
    gets(new.email);
	  printf("Tel: ");
	  scanf("%s",new.tel);
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
	  insertAtPosition(n,&list);
	  break;
	case 12:
	  printf("nth element: ");
	  scanf("%d",&n);
	  deleteAtPosition(n,&list);
	  break;
	case 13:
	  //list_reverse();
	  break;
	case 0: printf("Exit!!!\n"); return 0;
	default:
	  printf("Invalid input! Your choice must be from 1 to 7\n\n");
	  break;
	}
    }
}
