typedef struct list_el {
  address addr;
  struct list_el *next;
} node_addr;



void Initialize(s_list *list){
  list -> root = (node_addr*)malloc(sizeof(node_addr));
  list -> cur = (node_addr*)malloc(sizeof(node_addr));
}




node_addr* makeNewNode(address addr){
  node_addr* new = (node_addr*)malloc(sizeof(node_addr));
  new -> addr = addr;
  new -> next = NULL;
  return new;
}

// void insertAfterCur(address adr, s_list *list);

void insertAtHead(address adr, s_list *list){
  node_addr* new = makeNewNode(adr);
  new -> next = list -> root;
  list -> root = new;
  list -> cur = list -> root;
}


void insertAfterCur(address adr, s_list *list){
  node_addr* new_item = makeNewNode(adr);
  new_item -> next = list -> cur -> next;
  list -> cur -> next = new_item;
  list -> cur = list -> cur -> next;
}



void insertBeforeCur(address adr, s_list *list){
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
