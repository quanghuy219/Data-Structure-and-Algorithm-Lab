#define MAX 100

typedef struct {
  char step[MAX];
  int val;
} Eltype_ch;

typedef struct node_ch {
  Eltype_ch data;
  struct node_ch *prev;
} Node_ch;

typedef struct stack_type_ch {
  Node_ch *top;
} stackType_ch;



stackType_ch *Initialize_ch(stackType_ch *stack){
  // stack = (stackType*)malloc(sizeof(stackType));
  stack -> top = NULL;
  return stack;
}


int empty_ch(stackType_ch *stack) {
  return stack->top == NULL;
}


Node_ch *makeNode_ch(Eltype_ch val) {
  Node_ch *p;
  p = (Node_ch *)malloc(sizeof(Node_ch));
  p->data = val;
  p->prev = NULL;
  return p;
}

void push_ch(stackType_ch *stack, Eltype_ch val) {
  int i;
  Node_ch *p;
  p = makeNode_ch(val);
  p->prev = stack->top;
  stack->top = p;
}


Eltype_ch pop_ch(stackType_ch *stack) {
  Node_ch *p;
  Eltype_ch val;
  if (empty_ch(stack))
  {
    // printf("Stack overflow\n");
    exit(0);
  }
  p = stack->top;
  val = stack->top->data;
  stack->top = stack->top->prev;
  free(p);
  return val;
}


void freeStack_ch(stackType_ch *stack){
  Node_ch *p;

  while ( stack->top != NULL) {
    p = stack->top->prev;
    free(stack->top);
    stack->top = p;
    p = stack->top->prev;
  }
}
