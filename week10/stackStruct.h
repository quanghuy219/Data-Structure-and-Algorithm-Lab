#define MAX 50

typedef char Eltype;

typedef struct StackRec {
  Eltype storage[MAX];
  int top;
} stackType;


//typedef struct StackRec stackType;


void Initialize(stackType *stack){
  (*stack).top = 0;
}


int empty(stackType stack){
  return stack.top == 0;
}

int full(stackType stack){
  return stack.top == MAX;
}


void push(stackType *stack, Eltype el){
  if (full(*stack)) {
    printf("Stack overflow\n");
  }
  else (*stack).storage[(*stack).top++] = el;
}


Eltype pop(stackType *stack){
  if (empty(*stack)) {
    printf("stack underflow\n");
  }
  else return (*stack).storage[--(*stack).top];
}

/*
void deleteTop(stackType *stack){
  Eltype p = *stack.top;
  *stack.top = pop(*stack);
  free(p);
}
*/
