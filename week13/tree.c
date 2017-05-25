#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
  int key;
  struct node* left; 
  struct node* right; 
} Node;

Node* makeNewNode(int i){
  Node* p = (Node*)malloc(sizeof(Node));
  p -> key = i;
  p -> left = NULL;
  p -> right = NULL;
  return p;
}


Node* insertNode(int x, Node *root){
  if ( root == NULL) {
    root = makeNewNode(x);
    return root;
  }

  else if( x < root->key) root -> left = insertNode(x,  root -> left);

  else if( x > root -> key) root -> right = insertNode(x, root -> right);

  return root;
}


Node* Search(int x, Node* root){
  if (root == NULL) {
    return NULL;
  }

  else if (root -> key == x) {
    return root;
  }
  else if(x < root -> key) {
    return Search(x,root->left);
  }
  else return Search(x,root->right);
}

Node* findLeftMost(Node *root){
  if (root -> left == NULL) return NULL;
  else return findLeftMost(root -> left);
}

Node* findRightMost(Node *root) {
  if (root -> right == NULL) return NULL;
  else return findRightMost(root -> right);
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



Node* deleteNode(int k, Node* root) {
  Node *temp;

  if (root == NULL) return root;

  if (k < root -> key) root -> left = deleteNode(k, root->left);

  else if ( k > root -> key) root -> right = deleteNode(k, root -> right);

  else {
    if (root -> left == NULL){
      temp = root -> right;
      free(root);
      return temp;
    }

    else if (root -> right == NULL) {
      temp = root -> left;
      free(root);
      return temp; 
    }

    temp = findLeftMost(root -> right);
    root -> key = temp -> key;
    root -> right = deleteNode(temp -> key, root -> right);
  }
  return root;
}


void preorder(Node* p){
  if (p != NULL) {
    printf("%d    ",p->key);
    preorder(p -> left);
    preorder( p-> right);
  }
}


void inorder(Node *p){
  if (p != NULL) {
    
    inorder(p->left);
    if(p->left != NULL)
    printf("left of %d : %d\n",p->key, p -> left -> key);

    printf("%d\n",p -> key );
    
    if(p->right!=NULL)
    printf("right of %d : %d\n",p->key, p -> right -> key);
    inorder(p->right);
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
  Node *root,*p;

  root = (Node*)malloc(sizeof(Node));
  root = NULL;
    srand(time(NULL));
  for (int i = 0; i < 5; i++) {
      int a = rand() % 100;
      printf("%d\n",a);
      root = insertNode(a,root);
  }
  printf("\n\n\n");
  inorder(root);
  printf("\n\n\n");
  root = insertNode(15,root);
  inorder(root);

  root = deleteNode(15,root);
  printf("\n\n\n");
  inorder(root);
  return 0;
}
