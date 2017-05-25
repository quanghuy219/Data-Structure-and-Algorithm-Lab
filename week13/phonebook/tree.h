

typedef struct node_tr{
  eletype val;
  struct node_tr* left; //leftChild
  struct node_tr* right; //rightSibling
} Node_tr;


Node_tr* makeNewNode(eletype person){
  Node_tr* p = (Node_tr*)malloc(sizeof(Node_tr));
  strcpy(p-> val.name, person.name);
  strcpy(p -> val.email, person.email);
  strcpy(p -> val.phone, person.phone);
  p -> left = NULL;
  p -> right = NULL;
  return p;
}

Node_tr* findLeftMost(Node_tr *root){
  if (root -> left == NULL) return root;
  else return findLeftMost(root -> left);
}

Node_tr* findRightMost(Node_tr *root) {
  if (root -> right == NULL) return root;
  else return findRightMost(root -> right);
}

Node_tr* insertNode(eletype x, Node_tr *root){
  if (root == NULL) {
    root = makeNewNode(x);
    return root;
  }

  else if( strcmp(x.email, root->val.email ) < 0 ) root -> left = insertNode(x, root -> left);

  else if( strcmp(x.email, root->val.email ) > 0) root -> right = insertNode(x, root -> right);

  return root;
}

Node_tr* deleteNode(eletype k, Node_tr *root) {
  Node_tr *temp;

  if (root == NULL) return root;

  if (strcmp(k.email, root->val.email ) < 0) root -> left = deleteNode(k, root->left);

  else if ( strcmp(k.email, root->val.email ) > 0) root -> right = deleteNode(k, root -> right);

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
    root -> val = temp -> val;
    root -> right = deleteNode(temp -> val, root -> right);
  }
  return root;
}



void preorder(Node_tr* p){
  if (p != NULL) {
    printf("%s   ",p->val.email);
    preorder(p -> left);
    preorder( p-> right);
  }
}

void postorder(Node_tr* p){
  if (p != NULL) {
    postorder(p -> left);
    postorder(p -> right);
    printf("%s\n",p->val.email);
  }
}

void inorder(Node_tr* p){
  if (p != NULL) {
    inorder(p -> left);
    printf("%s\n",p->val.email);
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
