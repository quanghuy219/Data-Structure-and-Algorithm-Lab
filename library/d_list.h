
typedef struct {
  char model[MAX_STRING_MODEL];
  char memory[MAX_STRING_MEMORY];
  char screenSize[MAX_STRING_SCREENSIZE];
  int price;
} PHONE;

typedef PHONE elementtype;


typedef struct list_phone {
  elementtype Phone;
  struct list_phone *next;
  struct list_phone *prev;
} Node;


typedef struct {
  Node *root;
  Node *cur;
  Node *tail;
} db_list;

Node *root,*cur,*tail;


elementtype readData();
void displayNode(Node *p);



void Initialize(db_list *list){
  list -> root = (Node*)malloc(sizeof(Node));
  list -> root = NULL;
  list -> cur = (Node*)malloc(sizeof(Node));
  list -> cur = NULL;
  list -> tail = (Node*)malloc(sizeof(Node));
  list -> tail = NULL;
}

Node* makeNewNode(elementtype ph){
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



void insertAtLast(db_list *list, elementtype ph){
  Node* new = makeNewNode(ph);
  len++;


  if ( list -> root == NULL) {
    list -> tail = new;
    list -> root = new;
    list -> cur = list -> root;
    return;
  }

  list -> tail -> next = new;
  new -> prev = list -> tail;
  list -> tail = new;
  list -> cur = list -> tail;
}



void insertAtHead(db_list *list ,elementtype ph){
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




void insertAfterCur(db_list *list ,elementtype ph){
  len++;
  Node* new = makeNewNode(ph);
  if ( list -> cur == list ->  tail) {
    insertAtLast(list,ph);
    return;
  }
  new -> prev = list -> cur;
  new -> next = list -> cur -> next;
  new -> next -> prev = new;
  list -> cur -> next = new;
  list -> cur = list -> cur -> next;
}


void insertBeforeCur(db_list *list ,elementtype ph){
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




elementtype deleteHead(db_list *list){
  Node* p;
  elementtype tmp;
  if (list -> root != NULL) {

  p = list -> root;
  tmp = p -> Phone;
  list -> root = list -> root -> next;
  free(p);
  list -> cur = list -> root;
  return tmp;
}
}


elementtype deleteTail(db_list *list){
  Node* p;
  elementtype tmp;
  tmp = list -> tail -> Phone;
  p = list -> tail -> prev;
  p -> next = NULL;
  free(list -> tail);
  list -> tail = p;
  return tmp;
}


elementtype deleteCurrent(db_list *list){
  Node* p;
  elementtype tmp;

  if (list -> cur == list -> root) return deleteHead(list);

  else if (list -> cur == list -> tail) return deleteTail(list);

  tmp = list -> cur -> Phone;
  p = list -> cur -> next;
  list -> cur -> prev -> next = list -> cur -> next;
  list -> cur -> next -> prev = list -> cur -> prev;
  free( list -> cur);
  list -> cur = p;
  return tmp;
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


void freeList(db_list *list){
  Node *p = list -> root;
  while( p != NULL){
    list -> root = list -> root -> next;
    free(p);
    p = list -> root;
  }
  list -> root = NULL;
  list -> cur = NULL;
  list -> tail = NULL;
}



int count(db_list *list){
  Node *p;
  int tmp = 0;
  for( p = list -> root; p != NULL; p = p -> next) tmp++;
  return tmp;
}
