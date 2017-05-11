#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "rpn.h"

int i;
int a;
int b;

typedef struct node_tr{
  char val;
  struct node_tr* left; //leftChild
  struct node_tr* right; //rightSibling
} Node_tr;

Node_tr* makeNewNode(char i){
  Node_tr* p = (Node_tr*)malloc(sizeof(Node));
  p -> val = i;
  p -> left = NULL;
  p -> right = NULL;
  return p;
}

Node_tr* create(char post[]) {
  Node_tr* p;

  if ( isdigit(post[i]) ) {
    p = makeNewNode(post[i]);
  }

  if(checkOperator(post[i])) {
  p = makeNewNode(post[i]);
  i = i - 1;
  p -> right = create(post);
  i = i - 1;
  p -> left = create(post);
  }

  return p;
}


void preorder(Node_tr* p){
  if (p != NULL) {
    printf("%c",p->val);
    preorder(p -> left);
    preorder( p-> right);
  }
}

void postorder(Node_tr* p){
  if (p != NULL) {
    postorder(p -> left);
    postorder(p -> right);
    printf("%c",p->val);
  }
}


Node_tr* find(Node_tr* r, int v){
  if (r == NULL) return NULL;
  if (r -> val == v) return r;
  Node_tr* p = r -> left;
  while (p != NULL) {
    Node_tr* pv = find(p,v);
    if (pv != NULL) {
      return pv;
    }
    p = p -> right;
  }
  return NULL;
}

int count(Node_tr* r){
  int c;
  if (r == NULL) {
    return 0;
  }
  c = 1;
  return 1 + count(r -> left) + count(r -> right);
}


void addLeftMost(Node_tr* r){
  int x;
  printf("Enter data: ");
  scanf("%d",&x);
  Node_tr* new = makeNewNode(x);
  if(r == NULL) r = new;
  else {
    Node_tr* pv = r ;
    while (pv -> left != NULL) {
      pv = pv -> left;
    }
    pv -> left = new;
  }
  preorder(r);
}


void addRightMost(Node_tr* r){
  int x;
  printf("Enter data: ");
  scanf("%d",&x);
  Node_tr*new = makeNewNode(x);
  if(r == NULL) r = new;
  else {
    Node_tr*pv = r;
    while(pv -> right != NULL) pv = pv -> right;
    pv -> right = new;
  }
  preorder(r);
}

char eval(Node_tr* r){
  char x,y;
  if(r != NULL){

  if ( checkOperator(r->val) ) {
    x = eval(r->left);
    y = eval(r -> right);
    if ( isdigit(x) && isdigit(y) ) {
      a = x - '0';
      b = y - '0';
    }

    if (r -> val == '*') r -> val = '0' + a*b;
    if (r -> val == '/') r -> val = '0' + a/b;
    if (r -> val == '+') r -> val = '0' + a+b;
    if (r -> val == '-') r -> val = '0' + a-b;

  }
}

  return r->val;
}


int main() {

  char ex[MAX];
  char post[MAX];
  printf("Enter expression: ");
  scanf("%s",ex);
  strcpy(post,postfix(ex));
  printf("%s",post);
  printf("\n");
  Node_tr *root,*root1;
  i = strlen(post)-1;
  root = create(post);
  i = strlen(post)-1;
  root1 = create(post);
  //preorder(root);
  printf("\n");
  //postorder(root);
  printf("\n");
  char result;
  printf("Result: %c\n",eval(root1));
  return 0;
}
