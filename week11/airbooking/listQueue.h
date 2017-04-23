#define MAX 100


typedef struct {
  int row;
  char pos;
} seatType;


typedef struct {
  int id;
  char flight[MAX];
  char name[MAX];
  char *date;
  int quantity;
  seatType seat[MAX];
} elementtype;


typedef struct list {
  elementtype data;
  struct list *next;
  struct list *prev;
} Node;

typedef struct {
  Node *front;
  Node *rear;
} Queue;


void Initialize(Queue *q){
  q -> front = NULL;
  q -> rear = NULL;
}


Node* makeNewNode(elementtype val){
  Node* new = (Node*)malloc(sizeof(Node));
  new -> data = val;
  new -> next = NULL;
  new -> prev = NULL;
  return new;
}


int isEmpty(Queue *q) {
  if (q -> front == NULL) {
    return 1;
  }
  return 0;
}



void enQueue(Queue *q, elementtype a){
  Node* new = makeNewNode(a);

  if (isEmpty(q) == 1) {
    q -> front = new;
    q -> rear = new;
  }

  else {
    new -> next = q -> rear;
    q -> rear -> prev = new;
    q -> rear = new;
  }
}


elementtype deQueue(Queue *q) {
  Node* new = q -> front;
  elementtype temp;

  if (isEmpty(q)) {
    printf("Queue empty. Dequeue failed!!!");
    exit(0);
  }

  temp = new -> data;
  q -> front = q -> front -> prev;
  free(new);
  return temp;
}


elementtype checkFront(Queue *q) {
  if (isEmpty(q)) {
    exit(0);
  }
  return q -> front -> data;
}


int findProgram(Queue *a, int id, Node **cur) {
  Node *tmp = a -> front;
  int flag = 0;


  while (tmp != NULL) {
    if ( (tmp -> data.id) == id) {
      *cur = tmp;
      flag = 1;
      break;
    }
    tmp = tmp -> prev;
  }

  return flag;
}



void deleteNode(Queue *q, int id, Node **cur){

  int x;
  x = findProgram(q,id,cur);

  if (x == 0) {
    return;
  }

//if cur = head
else{
  if(*cur == q -> front){
    deQueue(q);
    return;
  }

  //if cur = rear
  else if(*cur == q -> rear){
    q -> rear = (q -> rear)->prev;
    (q -> rear)->next = NULL;
    free(*cur);
    *cur = q -> rear;

    return;
  }

  //if cur is at the middle
  else {
  (*cur)->prev->next = (*cur)->next;
  (*cur)->next->prev = (*cur)->prev;
  Node* p = (*cur)->next;
  free(*cur);
  *cur = p;
  }
}
}
