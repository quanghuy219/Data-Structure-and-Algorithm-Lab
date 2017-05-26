#define MAX 100

typedef struct node_tr{
  eletype val;
  struct node_tr* left; //leftChild
  struct node_tr* right; //rightSibling
} Node_tr;

void display(eletype val);


Node_tr* makeNewNode(eletype person){
  Node_tr* p = (Node_tr*)malloc(sizeof(Node_tr));
  p->val.code = person.code;
  strcpy(p->val.toy,person.toy);
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

  else if( x.code < root ->val.code ) root -> left = insertNode(x, root -> left);

  else if( x.code > root ->val.code ) root -> right = insertNode(x, root -> right);

  return root;
}

Node_tr* deleteNode(eletype k, Node_tr *root) {
  Node_tr *temp;

  if (root == NULL) return root;

  if (k.code < root ->val.code) root -> left = deleteNode(k, root->left);

  else if ( k.code > root ->val.code ) root -> right = deleteNode(k, root -> right);

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


Node_tr* Search(int x, Node_tr* root){
  if (root == NULL) {
    return NULL;
  }

  else if (root -> val.code == x) {
    return root;
  }
  else if(x < root -> val.code) {
    return Search(x,root->left);
  }
  else return Search(x,root->right);
}



void preorder(Node_tr* p){
  if (p != NULL) {
    //printf("%s   ",p->val.email);
    preorder(p -> left);
    preorder( p-> right);
  }
}

void postorder(Node_tr* p){
  if (p != NULL) {
    postorder(p -> left);
    postorder(p -> right);
    //printf("%s\n",p->val.email);
  }
}

void inorder(Node_tr* p){
  if (p != NULL) {
    inorder(p -> left);
    display(p->val);
    inorder(p -> right);
  }
}




int countNode(Node_tr* r){
  int c;
  if (r == NULL) {
    return 0;
  }
  c = 1;
  return 1 + countNode(r -> left) + countNode(r -> right);
}
