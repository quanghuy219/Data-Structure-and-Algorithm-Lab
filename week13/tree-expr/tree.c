#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "nodeStack.h"
#include "rpn.h"

int i;


typedef struct node_tr{
  char val[MAX];
  struct node_tr* left; //leftChild
  struct node_tr* right; //rightSibling
} Node_tr;

Node_tr* makeNewNode(char i[]){
  Node_tr* p = (Node_tr*)malloc(sizeof(Node));
  strcpy(p->val,i);
  p -> left = NULL;
  p -> right = NULL;
  return p;
}


Node_tr* create(stackType *stack) {
  Node_tr* p;
  int x;

  if( Top(stack) == NULL) return NULL;

  else {
    if ( sscanf(Top(stack),"%d",&x) == 1) {
      p = makeNewNode(pop(stack));
  }

    else if(checkOperator(Top(stack)[0])) {
      p = makeNewNode(pop(stack));
      p -> right = create(stack);
      p -> left = create(stack);
  }

  return p;
  }
}



void preorder(Node_tr* p){
  if (p != NULL) {
    printf("%s   ",p->val);
    preorder(p -> left);
    preorder( p-> right);
  }
}

void postorder(Node_tr* p){
  if (p != NULL) {
    postorder(p -> left);
    postorder(p -> right);
    printf("%s    ",p->val);
  }
}

void inorder(Node_tr* p){
  if (p != NULL) {
    postorder(p -> left);
    printf("%s    ",p->val);
    postorder(p -> right);

  }
}




int count(Node_tr* r){
  int c;
  if (r == NULL) {
    return 0;
  }
  c = 1;
  return 1 + count(r -> left) + count(r -> right);
}


char* eval(Node_tr* r){
  char x[MAX],y[MAX];
  int a,b;

  if(r != NULL){

  if ( checkOperator(r->val[0]) ) {
    strcpy(x,eval(r->left));
    strcpy(y,eval(r->right));

    if ( sscanf(x,"%d",&a) == 1 && sscanf(y,"%d",&b) == 1 ) {
      if (r -> val[0] == '*') sprintf(r->val,"%d",a*b);
      if (r -> val[0] == '/') sprintf(r->val,"%d",a/b);
      if (r -> val[0] == '+') sprintf(r->val,"%d",a+b);
      if (r -> val[0] == '-') sprintf(r->val,"%d",a-b);
    }
  }
}

  return r->val;
}


int main() {

  char ex[MAX];
  stackType post,post1;
  printf("Enter expression: ");
  scanf("%s",ex);

  post = postfix(ex);
  post1 = postfix(ex);
  Node_tr *root,*root1;
  root = create(&post);

  printf("postorder: \n");

  postorder(root);
  printf("\n");
  printf("Post = \n");
  Traverse(post1);
  printf("Result: %s\n",eval(root));
  return 0;
}
