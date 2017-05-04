# define MAX_STRING_MODEL 30
# define MAX_STRING_MEMORY 10
# define MAX_STRING_SCREENSIZE 10
# define MAX_PAGE 34


typedef struct {
  char model[MAX_STRING_MODEL];
  char memory[MAX_STRING_MEMORY];
  char screenSize[MAX_STRING_SCREENSIZE];
  int price;
} PHONE;

typedef PHONE elementtype;


typedef struct list_phone {
  elementtype Phone;
  int count;
  struct list_phone *next;
  struct list_phone *prev;
}node_ph;


typedef node_ph node;


node *root,*cur,*tail;


node_ph* makeNewNode(elementtype ph){
  node_ph* new = (node_ph*)malloc(sizeof(node_ph));
  new -> Phone = ph;
  new -> next = NULL;
  new -> prev = NULL;
  return new;
}


void freeList(node** root, node** tail, node** cur){
  node* p = *root;
  while(p != NULL){
    *root = (*root)->next;
    free(p);
    p = *root;
  }

  *root = NULL;
  *tail = NULL;
  *cur = NULL;
}



void insertAtHead(node** root, node** tail, node** cur, elementtype a){
  node* new = makeNewNode(a);

  if(*root == NULL){
    *root = new;
    *tail = new;
    *cur = new;

    return;
  }

  new->next = *root;
  (*root)->prev = new;
  *root = new;
  *cur = new;
}


void insertAtEnd(node** root, node** tail, node** cur, elementtype a){
  node* new = makeNewNode(a);

  if(*root == NULL){
    *root = new;
    *tail = new;
    *cur = new;

    return;
  }

  (*tail)->next = new;
  new->prev = *tail;

  *tail = new;
  *cur = *tail;
}



void insertBeforeCur(node** root, node** tail, node** cur, elementtype a){
  if(*root == NULL){
    printf("Error: Empty list!\n");
    return;
  }

  if(*cur == NULL){
    printf("Error: Current element is NULL!\n");
    return;
  }

  //check if cur = head
  if((*cur)->prev == NULL){
    insertAtHead(root, tail, cur, a);
    return;
  }

  //insert in the middle
  node* new = makeNewNode(a);

  (*cur)->prev->next = new;
  new->prev = (*cur)->prev;
  (*cur)->prev = new;
  new->next = *cur;
  *cur = new;
}



void insertAfterCur(node** root, node** tail, node** cur, elementtype a){
  if(*root == NULL){
    printf("Error: Empty list!\n");
    return;
  }

  if(*cur == NULL){
    printf("Error: Current element is NULL!\n");
    return;
  }

  //check if cur = tail
  if((*cur)->next == NULL){
    insertAtEnd(root, tail, cur, a);
    return;
  }

  //insert in the middle
  node* new = makeNewNode(a);

  (*cur)->next->prev = new;
  new->next = (*cur)->next;
  (*cur)->next = new;
  new->prev = *cur;
  *cur = new;
}




void deleteNode(node** root, node** tail, node** cur){
	if(*cur == NULL){
		printf("Error: NULL element!\n");
		return;
	}

//if cur = head
  if(*cur == *root){
    *root = (*root)->next;
    (*root)->prev = NULL;
    free(*cur);
    *cur = *root;

    return;
  }

  //if cur = tail
  if(*cur == *tail){
    *tail = (*tail)->prev;
    (*tail)->next = NULL;
    free(*cur);
    *cur = *tail;

    return;
  }

  //if cur is at the middle

  (*cur)->prev->next = (*cur)->next;
  (*cur)->next->prev = (*cur)->prev;
  node* p = (*cur)->next;
  free(*cur);
  *cur = p;
}



void insertAtPosition(node** root, node** tail, node** cur, elementtype a, int n){
  if(n < 0){
    printf("Error: Invalid value of position!\n");
    return;
  }

  if(*root == NULL){
    printf("Error: Empty list!\n");
    return;
  }

  int num = 0;
  node* p = *root;

  while(p != NULL){
    if(num == n)
      break;
    p = p->next;
    num++;
  }
  *cur = p;

  if(p != NULL)
    insertBeforeCur(root, tail, cur, a);
  else
    insertAtEnd(root, tail, cur, a);
}




void deleteAtPosition(node** root, node** tail, node** cur, int n){
  if(n < 0){
    printf("Error: Invalid value of position!\n");
    return;
  }

  if(*root == NULL){
    printf("Error: Empty list!\n");
    return;
  }

  int num = 0;
  node* p = *root;

  while(p != NULL){
    if(num == n)
      break;
    p = p->next;
    num++;
  }
  *cur = p;

  if(p != NULL)
    deleteNode(root, tail, cur);
}




void reverseList(node** root, node** tail, node** cur){
  node_ph* p;
  *cur = (*root);
  while(*cur != NULL){
    p = (*cur) -> next;
    (*cur) -> next = (*cur) -> prev;
    (*cur) -> prev = p;
    (*root) = (*cur);
    (*cur) = p;
  }
  printf("\n\n\n");
}






void split(node* root, node** root1, node** tail1, node** cur1, node** root2, node** tail2, node** cur2, int n1, int n2){
	if(*root1 != NULL)
		freeList(root1, tail1, cur1);
	if(*root2 != NULL)
		freeList(root2, cur2, cur2);

	if(root == NULL)
		return;
	//check validity of n1 and n2
	if(n1 < 0 || n2 <= 0)
		return;

	//copy original list to list 2
	node* cur = root;
	while(cur != NULL){
		insertAtEnd(root2, tail2, cur2, cur->Phone);
		cur = cur->next;
	}

	//find the 1st element of list 2 in list 1
	int num = 0;
	cur = *root2;
	while(cur != NULL){
		if(num == n1)
			break;
		cur = cur -> next;
		num ++;
	}

	node* p = cur->next; //p always point to element after cur (used incase cur is removed)
	insertAtEnd(root1, tail1, cur1, cur->Phone);
	deleteNode(root2, tail2, &cur);
	*cur2 = cur;

	num = 2;
    while(num <= n2 && p != NULL){
		cur = p;
		p = p->next;

		if(cur != NULL){
			insertAtEnd(root1, tail1, cur1, cur->Phone);
			deleteNode(root2, tail2, &cur);
			*cur2 = cur;
		}
		num++;
	}
}
