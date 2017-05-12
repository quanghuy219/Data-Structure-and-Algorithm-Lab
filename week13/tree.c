#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int key;
  struct node* left; //leftChild
  struct node* right; //rightSibling
} Node;

Node* makeNewNode(int i){
  Node* p = (Node*)malloc(sizeof(Node));
  p -> key = i;
  p -> left = NULL;
  p -> right = NULL;
  return p;
}

Node* create(int x) {
  Node* p;
  int tmp = x;
  //tmp = x;
  //printf("Enter data: ");
  //scanf("%d",&x);

  if (x == -1) {
    return NULL;
  }

  if(tmp != -1){
  p = makeNewNode(x);
  printf("Enter left child of %d\n",x);
  scanf("%d",&x);
  p -> left = create(x);

  printf("Enter right sibling of %d\n",x);
  scanf("%d",&x);
  p -> right = create(x);
  }

  return p;
}


void preorder(Node* p){
  if (p != NULL) {
    printf("%d",p->key);
    preorder(p -> left);
    preorder( p-> right);
  }
}

void postorder(Node* p){
  if (p != NULL) {
    postorder(p -> left);
    postorder(p -> right);
    printf("%d",p->key);
  }
}


Node* find(Node *r, int v){
  if (r == NULL) return NULL;
  if (r -> key == v) return r;

  Node *p = r -> left;
  while (p != NULL) {
    Node *pv = find(p,v);
    if (pv != NULL) {
      return pv;
    }
    p = p -> right;
  }
  return NULL;
}

int count(Node *r){
  int c;
  if (r == NULL) {
    return 0;
  }
  c = 1;
  return 1 + count(r -> left) + count(r -> right);
}


void addLeftMost(Node* r){
  int x;
  printf("Enter data: ");
  scanf("%d",&x);
  Node *new = makeNewNode(x);
  if(r == NULL) r = new;
  else {
    Node *pv = r ;
    while (pv -> left != NULL) {
      pv = pv -> left;
    }
    pv -> left = new;
  }
  preorder(r);
}


void addRightMost(Node *r){
  int x;
  printf("Enter data: ");
  scanf("%d",&x);
  Node *new = makeNewNode(x);
  if(r == NULL) r = new;
  else {
    Node *pv = r;
    while(pv -> right != NULL) pv = pv -> right;
    pv -> right = new;
  }
  preorder(r);
}


int main() {
  Node* root;
  root = create(0);
  postorder(root);
  printf("\n");

  // printf("\nPreorder Transersal\n");
  // preorder(root);
  // printf("\n");
  //
  // int i;
  // printf("Find : ");
  // scanf("%d",&i);
  // if ( find(root,i) != NULL) {
  //   printf("Found\n");
  // }
  // else printf("Not found\n");
  //
  // printf("Number of nodes: %d\n",count(root));
  // printf("Add left most\n");
  // addLeftMost(root);
  // printf("\n");
  // printf("Add right most\n");
  // addRightMost(root);
  // printf("\n");
  return 0;
}
