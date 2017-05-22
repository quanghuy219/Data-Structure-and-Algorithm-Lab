
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
} Node;


typedef struct {
  Node *root;
  Node *cur;
  Node *tail;
} db_list;

Node *root,*cur,*tail;


PHONE readData();
void displayNode(Node *p);



void Initialize(db_list *list){
  list -> root = (Node*)malloc(sizeof(Node));
  list -> root = NULL;
  list -> cur = (Node*)malloc(sizeof(Node));
  list -> cur = NULL;
  list -> tail = (Node*)malloc(sizeof(Node));
  list -> tail = NULL;
}

Node* makeNewNode(PHONE ph){
  Node* new = (Node*)malloc(sizeof(Node));
  new -> Phone = ph;
  new -> next = NULL;
  new -> prev = NULL;
  return new;
}


void moveCur(db_list *list, int pos){
  int i = 1;
  if (pos <= 1) {
    list -> cur = list -> root;
  }
  else if (pos >= len) {
    list -> cur = list -> tail;
  }
  else{
    list -> cur = list -> root;
    while( i != pos){
      list -> cur = list -> cur -> next;
      i++;
    }
  }
}



void insertAfterLast(db_list *list, PHONE ph){
  Node* new = makeNewNode(ph);
  len++;
  if ( list -> tail == NULL) {
    list -> tail = new;
    return;
  }
  list -> tail -> next = new;
  new -> prev = list -> tail;
  list -> tail = new;
}



void insertAtHead(db_list *list ,PHONE ph){
  Node* new = makeNewNode(ph);
  len++;
  if ( list -> root == NULL) {
    list -> root = new;
    return;
  }
  list -> root -> prev = new;
  new -> next = list -> root;
  list -> root = new;
}




void insertAfterCur(db_list *list ,PHONE ph){
  len++;
  Node* new = makeNewNode(ph);
  if ( list -> cur == list ->  tail) {
    insertAfterLast(list,ph);
    return;
  }
  new -> prev = list -> cur;
  new -> next = list -> cur -> next;
  new -> next -> prev = new;
  list -> cur -> next = new;
  list -> cur = list -> cur -> next;
}


void insertBeforeCur(db_list *list ,PHONE ph){
  Node* new = makeNewNode(ph);
  len++;
  if ( list -> cur == list -> root) {
    insertAtHead(list,ph);
    return;
  }
  new -> prev = list -> cur -> prev;
  new -> next = list -> cur;
  list -> cur -> prev = new;
  new -> prev -> next = new;
  list -> cur = list -> cur -> prev;
}


void traverseForward(db_list *list){
  Node *p;
  int i = 1;
  for (p = list -> root; p != NULL; p=p->next) {
    printf("%d\t",i);
    displayNode(p);
    i++;
  }
}




void traverseBackward(db_list *list){
  int i = 1;
  Node *p;
  for (p = list -> tail; p != NULL; p=p->prev) {
    printf("%d\t",i);
    displayNode(p);
    i++;
  }
}




void deleteHead(db_list *list){
  Node* p;
  p = list -> root;
  list -> root = list -> root -> next;
  free(p);
  len--;
}


void deleteTail(db_list *list){
  Node* p;
  p = list -> tail -> prev;
  p -> next = NULL;
  free(list -> tail);
  list -> tail = p;
  len--;
}


void deleteCurrent(db_list *list){
  Node* p;
  len--;
  p = list -> cur -> prev;
  list -> cur -> prev -> next = list -> cur -> next;
  list -> cur -> next -> prev = list -> cur -> prev;
  free( list -> cur);
  list -> cur = p;
}


void Reverse(db_list *list){
  Node *p = NULL;
  list -> cur = list -> root;
  //swap prev and next
  while( list -> cur != NULL) {
    p = list -> cur -> prev;
    list -> cur -> prev = list -> cur -> next;
    list -> cur -> next = p;
    list -> cur = list -> cur -> prev;
  }
  if (p != NULL) list -> root = p -> prev;
}
