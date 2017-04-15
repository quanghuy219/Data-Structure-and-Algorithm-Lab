#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element_type;

typedef struct Node {
  element_type element;
  struct Node *link;
} Node;

typedef struct stack_type$ {
  Node *top;
} stack_type;

//initialize a stack
stack_type *iniStack(stack_type *stack) {
  stack = (stack_type *)malloc(sizeof(stack_type));
  stack->top = NULL;
  return stack;
}

int empty(stack_type *stack) {
  return stack->top == NULL;
}

Node *makeNode(element_type val) {
  Node *p;
  p = (Node *)malloc(sizeof(Node));
  p->element = val;
  p->link = NULL;
  return p;
}

void push(element_type val, stack_type *stack) {
  int i;
  Node *p;
  p = makeNode(val);
  p->link = stack->top;
  stack->top = p;
}

char pop(stack_type *stack) {
  Node *p;
  element_type val;
  if (empty(stack))
  {
    printf("Stack overflow\n");
    exit(0);
  }
  val = stack->top->element;
  p = stack->top;
  stack->top = stack->top->link;
  free(p);
  return val;
}
