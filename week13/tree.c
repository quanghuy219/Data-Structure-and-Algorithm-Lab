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

Node* create() {
  Node* p;
  int x;
  printf("Enter data: ");
  scanf("%d",&x);

  if (x == -1) {
    return NULL;
  }

  //if(tmp != -1){
  p = makeNewNode(x);
  printf("Enter left child of %d\n",x);
  //scanf("%d",&x);
  p -> left = create();

  printf("Enter right sibling of %d\n",x);
  //scanf("%d",&x);
  p -> right = create();


  return p;
}


void insertNode(int x, Node **root){
  if (*root == NULL) {
    (*root) = makeNewNode(x);
  }

  else if( x < (*root)->key) insertNode(x,&(*root) -> left);

  else if( x > (*root) -> key) insertNode(x,&(*root)->right);
}


Node* search(int x, Node* root){
  if (root == NULL) {
    return NULL;
  }

  else if (root -> key == x) {
    return root;
  }
  else if(root -> key > x) {
    return search(x,root->left);
  }
  else return search(x,root->right);
}


int deleteMin(Node **root){
  int k;
  if ((*root) -> left == NULL) {
    k = (*root) -> key;
    *root = (*root) -> right;
    return k;
  }
  else return deleteMin(&(*root) -> left);
}



void deleteNode(int k, Node** root) {
  if (*root != NULL) {
    if (k < (*root)->key) deleteNode(k,&(*root)->left);

    else if ((*root)->left == NULL && (*root)->right == NULL) *root = NULL;

    else if ((*root)->left == NULL) *root = (*root)->right;
    else if ((*root)->right == NULL) *root = (*root)->left;
    else (*root) -> key = deleteMin(&(*root)->right);

  }
}


void preorder(Node* p){
  if (p != NULL) {
    printf("%d    ",p->key);
    preorder(p -> left);
    preorder( p-> right);
  }
}

void postorder(Node* p){
  if (p != NULL) {
    postorder(p -> left);
    postorder(p -> right);
    printf("%d    ",p->key);
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
  Node* root,*p;
  root = create();
  postorder(root);
  printf("\n");
  p = search(7,root);
  if (p == NULL) {
    printf("Not found!!!\n");
  }
  else printf("Found\n");

  //insertNode(1234,&root);
  deleteNode(99,&root);
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
