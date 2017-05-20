

typedef struct list_el {
  elementType addr;
  struct list_el *next;
} node_addr;

typedef struct {
  node_addr *root;
  node_addr *cur;
} s_list;



void Initialize(s_list *list){
  list -> root = (node_addr*)malloc(sizeof(node_addr));
  list -> root = NULL;
  list -> cur = (node_addr*)malloc(sizeof(node_addr));
  list -> cur = NULL;
}




node_addr* makeNewNode(elementType addr){
  node_addr* new = (node_addr*)malloc(sizeof(node_addr));
  new -> addr = addr;
  new -> next = NULL;
  return new;
}


void displayNode(node_addr *p);


void moveCur(int n, s_list *list){
  node_addr *p;
  int count;
  count = 0;
  for(p = list -> root; p != NULL; p = p->next){
    count += 1;
    list -> cur = p;
  }

  if (n <= 1) {
    list -> cur = list -> root;
  }
  else if (n >= 2 && n <= count) {
    p = list -> root;
  for (int i = 0; i < n-1; i++) {
    p = p -> next;
  }
  list -> cur = p;
  }
  displayNode(list -> cur);
}


void insertAtHead(elementType adr, s_list *list){
  node_addr* new = makeNewNode(adr);
  new -> next = list -> root;
  list -> root = new;
  list -> cur = list -> root;
}



void insertAtLast(elementType adr, s_list *list){
  node_addr* new = makeNewNode(adr);
  node_addr* p;
  int count = 0;
  //list -> cur = list -> root;
  for (p = list -> root; p != NULL; p = p->next) {
    list -> cur = p;
  }
  list -> cur -> next = new;
  list -> cur = list -> cur -> next;
}


void insertAfterCur(elementType adr, s_list *list){
  node_addr* new_item = makeNewNode(adr);
  new_item -> next = list -> cur -> next;
  list -> cur -> next = new_item;
  list -> cur = list -> cur -> next;
}



void insertBeforeCur(elementType adr, s_list *list){
  node_addr* new_item = makeNewNode(adr);
  node_addr* p = list -> root;
  while (1) {
    if ( p -> next == list -> cur) {
      break;
    }
    if ( list -> root -> next == NULL) {
      break;
    }
    if (list -> root == NULL) {
      new_item = list -> root;
      break;
    }
    p = p -> next;
  }
  new_item -> next = list -> cur;
  p -> next = new_item;
  list -> cur = new_item;
}



void insertAtPosition(int n, s_list *list, elementType new){
  node_addr *p;

  int count,i;

  for(p=list -> root; p != NULL; p = p->next){
    count++;
  }


  if( n <=1){
    insertAtHead(new,list);
  }

  if ( n >= count) {
    insertAtLast(new,list);
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




void deleteFirstElement(s_list *list){
  node_addr* del = (node_addr *)malloc(sizeof(node_addr));
  del = list -> root;
  if( list -> cur == list -> root ) list -> cur = list -> root -> next;
  list -> root = del -> next;
  free(del);
}




void deleteCurrentElement(s_list *list){
  node_addr* p;
  if (list -> cur == list -> root) {
    deleteFirstElement(list);
  }
  else{
    p = list -> root;
  while (1) {
    if (p -> next == list -> cur) {
      break;
    }
    p = p -> next;
  }
  p -> next = list -> cur -> next;
  free(list->cur);
  list -> cur = p -> next;
  }
}


void deleteLast(s_list *list){
  node_addr *p;
  for ( p = list -> root; p -> next != NULL; p = p -> next){
    list -> cur = p;
  }
  displayNode(list->cur);
  p = list -> cur -> next;
  list -> cur -> next = NULL;
  free(p);
}


void deleteAtPosition(int n, s_list *list){
  if (n == 1) {
    deleteFirstElement(list);
  }
  else if( n < 1 || n > total){
    printf("Element doesnot exist\n");
  }
  else {
  moveCur(n,list);
  deleteCurrentElement(list);
  }
}




void list_reverse(s_list *list){
  node_addr *prev,*next;
  next = prev = NULL;
  if(list -> root != NULL) {
  while (list -> root -> next != NULL) {
    next = list -> root -> next;
    list -> root -> next = prev;
    prev = list -> root;
    list -> root = next;
  }
  list -> root -> next = prev;
  list -> cur = list -> root;
  }
}
