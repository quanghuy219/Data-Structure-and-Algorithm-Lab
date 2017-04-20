#define MAX 100

typedef char Eltype;

typedef struct node_s {
  Eltype data;
  struct node_s *prev;
} Node;

typedef struct stack_type {
  Node *top;
} stackType;



stackType *Initialize(stackType *stack){
  // stack = (stackType*)malloc(sizeof(stackType));
  stack -> top = NULL;
  return stack;
}


int empty(stackType *stack) {
  return stack->top == NULL;
}


Node *makeNode(Eltype val) {
  Node *p;
  p = (Node *)malloc(sizeof(Node));
  p->data = val;
  p->prev = NULL;
  return p;
}

Eltype Top(stackType *stack){
  if (!empty(stack))
  return stack -> top -> data;
}

void push(stackType *stack, Eltype val) {
  int i;
  Node *p;
  p = makeNode(val);
  p->prev = stack->top;
  stack->top = p;
}


Eltype pop(stackType *stack) {
  Node *p;
  Eltype val;
  if (empty(stack))
  {
    // printf("Stack overflow\n");
    return 0;
  }
  p = stack->top;
  val = stack->top->data;
  stack->top = stack->top->prev;
  free(p);
  return val;
}


void freeStack(stackType *stack){
  Node *p;

  while ( stack->top != NULL) {
    p = stack->top->prev;
    free(stack->top);
    stack->top = p;
    p = stack->top->prev;
  }
}
