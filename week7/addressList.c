#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char name[20];
  int tel;
  char email[25];
} address;


typedef struct list_el {
  address addr;
  struct list_el *next;
} node_addr;


//typedef struct list_el node_addr;


node_addr *root,*cur,*prev;


node_addr* makeNewNode(address addr){
  node_addr* new = (node_addr*)malloc(sizeof(node_addr));
  new -> addr = addr;
  new -> next = NULL;
  return new;
}

void insertAfterCur(address adr);

void menu1(){
  FILE *fin = fopen("addressList.txt","r");
  if (fin == NULL) {
    printf("Failed to read file phoneDB.txt");
    return;
  }

  char buff[100];
  buff[0] = '\0';
  address adr;
  
  fgets(buff,100,fin);
  sscanf(buff,"%s %d",adr.name,&adr.tel);
  root = makeNewNode(adr);
  cur = root;
  buff[0]='\0';
  while(fgets(buff,100,fin) != NULL){
    sscanf(buff,"%s %d",adr.name,&adr.tel);
   insertAfterCur(adr);
   buff[0] = '\0';
  }
  printf("Build list succesfullly\n\n");
  fclose(fin);
}



void insertAtHead(address adr){
  node_addr* new = makeNewNode(adr);
  new -> next = root;
  root = new;
  cur = root;
}


void insertAfterCur(address adr){
  node_addr* new_item = makeNewNode(adr);
  new_item -> next = cur -> next;
  cur -> next = new_item;
  cur = cur -> next;
}



void insertBeforeCur(address adr){
  node_addr* new_item = makeNewNode(adr);
  node_addr* p = root;
  while (1) {
    if ( p -> next == cur) {
      break;
    }
    if ( root -> next == NULL) {
      break;
    }
    if (root == NULL) {
      new_item = root;
      break;
    }
    p = p -> next;
  }
  new_item -> next = cur;
  p -> next = new_item;
  cur = new_item;
}




void deleteFirstElement(){
  node_addr* del = (node_addr *)malloc(sizeof(node_addr));
  del = root;
  root = del -> next;
  free(del);
}



void deleteCurrentElement(){
  node_addr* p = root;
  while (1) {
    if (p -> next == cur) {
      break;
    }
    p = p -> next;
  }
  p -> next = cur -> next;
  cur = p -> next;
}



address readNode(){
  address new;
  printf("Name: ");
  gets(new.name);
  printf("Phone number: ");
  gets(new.tel);
  return new;
}




void displayNode(node_addr *p){
  printf("%s\t%d\n",p -> addr.name,p -> addr.tel);
}





void traversingList(){
  node_addr *p;
  for (p = root; p != NULL; p=p->next) {
    displayNode(p);
  }
}


void moveCur(){
  int n;
  node_addr *p;
  printf("Enter position: ");
  scanf("%d",&n);
  for (p = root; p!= NULL; p=p->next) {
    if (p -> addr.tel == n) {
      break;
    }
  }
  cur = p;
  displayNode(cur);
}



int main()
{
  int choice;
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
      printf(" 11. Show cur\n");
      printf(" 10. Exit\n");
      printf("Your choice: ");
      scanf("%d",&choice);
      switch (choice)
	{
	case 1:
	  menu1(); 
	  break;
	case 2:
	  //menu2(); 
	  break;
	case 3:
	  traversingList(); 
	  break;
	case 4:{
	  while(getchar() != '\n');
	  printf("Name: ");
	  gets(new.name);
	  printf("Tel: ");
	  scanf("%d",&new.tel);
	  insertAtHead(new); 
	  break;
	}
	case 5:
	  while(getchar() != '\n');
	  printf("Name: ");
	  gets(new.name);
	  printf("Tel: ");
	  scanf("%d",&new.tel);
	  insertBeforeCur(new);
	  break;
	case 6:
	  while(getchar() != '\n');
	  printf("Name: ");
	  gets(new.name);
	  printf("Tel: ");
	  scanf("%d",&new.tel);
	  insertAfterCur(new);
	  break;
	case 7:
	  deleteFirstElement();
	  break;
	case 8:
	  deleteCurrentElement();
	  break;
	case 9:
	  moveCur();
	  break;
	case 11:
	  printf("Cur: %s %d\n", cur -> addr.name, cur -> addr.tel);
	case 10: printf("Exit!!!\n"); return 0;
	default:
	  printf("Invalid input! Your choice must be from 1 to 7\n\n");
	  break;
	}
    }
}
