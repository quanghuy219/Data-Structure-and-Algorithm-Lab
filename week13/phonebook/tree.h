
#define MAX 100

typedef struct node_tr{
  char val[MAX];
  struct node_tr* left; //leftChild
  struct node_tr* right; //rightSibling
} Node_tr;


Node_tr* makeNewNode(char i[]){
  Node_tr* p = (Node_tr*)malloc(sizeof(Node_tr));
  strcpy(p->val,i);
  p -> left = NULL;
  p -> right = NULL;
  return p;
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
    //printf("left of %s")
    postorder(p -> left);
    postorder(p -> right);
    printf("%s\n",p->val);
  }
}

void inorder(Node_tr* p){
  if (p != NULL) {
    inorder(p -> left);
    printf("%s\n",p->val);
    inorder(p -> right);

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
