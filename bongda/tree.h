

typedef struct node_tr{
  eletype val;
  struct node_tr* left; //leftChild
  struct node_tr* right; //rightSibling
} Node_tr;


Node_tr* makeNewNode(eletype x){
  Node_tr* p = (Node_tr*)malloc(sizeof(Node_tr));
  strcpy(p-> val.team, x.team);
  p -> val.pts = x.pts;
  p -> left = NULL;
  p -> right = NULL;
  return p;
}


int Compare(char s1[], char s2[]){
  if (strcmp(s1,s2) < 0) return -1;

  else if (strcmp(s1,s2) > 0) return 1;

  else return 0;
}

void display(eletype x){
  printf("%-10s\t%-10d\n", x.team,x.pts);
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

  else if( strcmp(x.team, root->val.team ) < 0 ) root -> left = insertNode(x, root -> left);

  else if( strcmp(x.team, root->val.team ) > 0) root -> right = insertNode(x, root -> right);

  return root;
}

Node_tr* deleteNode(eletype k, Node_tr *root) {
  Node_tr *temp;

  if (root == NULL) return root;

  if (strcmp(k.team, root->val.team ) < 0) root -> left = deleteNode(k, root->left);

  else if ( strcmp(k.team, root->val.team ) > 0) root -> right = deleteNode(k, root -> right);

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


Node_tr* Search(eletype x, Node_tr* root){
  if (root == NULL) {
    return NULL;
  }

  else if (Compare(x.team,root->val.team) == 0) {
    return root;
  }
  else if(Compare(x.team,root -> val.team) < 0) {
    return Search(x,root->left);
  }
  else return Search(x,root->right);
}



void preorder(Node_tr* p){
  if (p != NULL) {
    printf("%s   ",p->val.team);
    preorder(p -> left);
    preorder( p-> right);
  }
}

void postorder(Node_tr* p){
  if (p != NULL) {
    postorder(p -> left);
    postorder(p -> right);
    printf("%s\n",p->val.team);
  }
}

void inorder(Node_tr* p){
  if (p != NULL) {
    inorder(p -> left);
    // printf("%s\n",p->val.team);
    display(p->val);
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
