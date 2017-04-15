#define MAX 50

typedef int Eltype;

typedef Eltype stackType[MAX];

int top;


void Initialize(stackType stack){
  top = 0;
}


int empty(stackType stack){
  return top == 0;
}

int full(stackType stack){
  return top == MAX;
}


void push(Eltype el, stackType stack){
  if (full(*stack)) {
    printf("Stack overflow\n", );
  }
  else stack[top++] = el;
}


Eltype pop(stackType stack){
  if (empty(stack)) {
    printf("stack underflow\n");
  }
  else return stack[--top];
}
