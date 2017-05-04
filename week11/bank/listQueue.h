#define MAX 100

typedef struct{
  int id;
  int h_in;
  int m_in;
  int wait;
} elementtype;


typedef struct list {
  elementtype data;
  struct list *next;
  struct list *prev;
}node;

typedef struct {
  node *front;
  node *rear;
} Queue;


void Initialize(Queue *q){
  q -> front = NULL;
  q -> rear = NULL;
}


node* makeNewNode(elementtype val){
  node* new = (node*)malloc(sizeof(node));
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
  node* new = makeNewNode(a);

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
  node* new = q -> front;
  elementtype temp;

  if (isEmpty(q)) {
    //printf("Queue empty. Dequeue failed!!!");
    exit(0);
  }

  temp = new -> data;
  q -> front = q -> front -> prev;
  free(new);
  return temp;
}
