
#define MAX 100

typedef struct {
  char name[MAX];
  char email[MAX];
  char phone[MAX];
} Contact;

typedef struct node_tr{
  Contact val;
  struct node_tr* left; //leftChild
  struct node_tr* right; //rightSibling
} Node_tr;


Node_tr* makeNewNode(Contact person){
  Node_tr* p = (Node_tr*)malloc(sizeof(Node_tr));
  strcpy(p-> val.name, person.name);
  strcpy(p -> val.email, person.email);
  strcpy(p -> val.phone, person.phone);
  p -> left = NULL;
  p -> right = NULL;
  return p;
}

Node_tr* insertNode(Contact x, Node_tr **root){
  if (*root == NULL) {
    (*root) = makeNewNode(x);
  }

  else if( strcmp(x.email, (*root)->val.email ) < 0 ) insertNode(x,&(*root) -> left);

  else if( strcmp(x.email, (*root)->val.email ) > 0) insertNode(x,&(*root)->right);
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
    //printf("left of %s")
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
