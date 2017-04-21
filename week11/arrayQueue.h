#define MAX 100

typedef int Eltype;

typedef struct {
  Eltype element[MAX];
  int front, rear;
} Queue;


void Initialize(Queue *Q){
  *Q.front = -1;
  *Q.rear = -1;
}

int Empty_Queue(Queue Q){
  return Q.Front==-1;
}

int Full_Queue(Queue Q){
  return (Q.Rear-Q.Front+1)==MaxLength;
}
