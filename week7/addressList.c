#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char name[20];
  char tel[11];
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



address readNode(){
  address new;
  printf("Name: ");
  gets(new.name);
  printf("Phone number: ");
  gets(new.tel);
  return new;
}


void traversingList(){
  node_addr *p;
  for (p = root; p != NULL; p=p->next) {
    displayNode(p);
  }
}


void displayNode(node_addr *p){
  printf("Name: %s\n",p -> addr.name);
  printf("Tel: %s\n",p -> addr.tel);
}



int main()
{
  address a = readNode();
  address b;
  root = makeNewNode(a);
  cur = root;
  int flag = 1;
  while(flag != 0){
    while(getchar() != '\n');
    b = readNode();
    insertAfterCur(b);
    printf("Next: ");
    scanf("%d",&flag);
  }
  printf("\n\n\n");
  traversingList();
  //insertAtHead(b);
  
  /*
  int count=0;
  if (root != NULL) {
    count++;
  }
  cur = root;
  
  while (cur -> next != NULL) {
    printf("Name: %s\n",cur -> addr.name);
    printf("Tel: %s\n",cur -> addr.tel);
    count += 1;
    cur = cur -> next;
  }
  
  printf("So phan tu: %d\n",count);
  */

  
  
  return 0;
}
