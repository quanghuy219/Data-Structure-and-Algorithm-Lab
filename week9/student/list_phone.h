typedef struct phone_t{
	char model[30];
	int memory;
	float screensize;
	int price;
}phone;


typedef phone elementtype;

struct node_t{
  elementtype info;
  struct node_t *prev;
  struct node_t *next;  
};
typedef struct node_t node;

node *head, *tail, *cur;


//Display a node/element
void displayNode(node* a){
	if(a == NULL){
		printf("This is a NULL element!\n");
		return;
	}
	printf("%-20s%-15d%-25.1f%d\n", a->info.model, a->info.memory, a->info.screensize, a->info.price); 	
}

//Display the list all the elements
void displayList(node* head){
	node* p;
	int i = 0;
	printf("%-5s%-20s%-15s%-25s%s\n\n", "STT", "MODEL", "MEMORY (GB)", "SCREEN SIZE (INCHES)", "PRICE (VND)");		
	for(p = head; p != NULL; p = p->next){
		printf("%-5d", i++);
		displayNode(p);
	}
}

//Display list in reverse direction
void displayReverseList(node* tail){
	node* p;
	int i = 0;
	printf("%-5s%-20s%-15s%-25s%s\n\n", "STT", "MODEL", "MEMORY (GB)", "SCREEN SIZE (INCHES)", "PRICE (VND)");		
	for(p = tail; p != NULL; p = p->prev){
		printf("%-5d", i++);
		displayNode(p);
	}
}



//make a new node
node* makeNewNode(elementtype a){
  node* new = (node*)malloc(sizeof(node));
  new->info = a;
  new->next = NULL;
  new->prev = NULL;

  return new; 
}

//free the list
void freeList(node** head, node** tail, node** cur){
  node* p = *head;
  while(p != NULL){
    *head = (*head)->next;
    free(p);
    p = *head;
  }

  *head = NULL;
  *tail = NULL;
  *cur = NULL; 
}

//insert an element at the head of the list
void insertAtHead(node** head, node** tail, node** cur, elementtype a){
  node* new = makeNewNode(a);

  if(*head == NULL){
    *head = new;
    *tail = new;
    *cur = new;

    return;
  }

  new->next = *head;
  (*head)->prev = new;
  *head = new;
  *cur = new; 
}

//insert an element at the end of the list
void insertAtEnd(node** head, node** tail, node** cur, elementtype a){
  node* new = makeNewNode(a);
  
  if(*head == NULL){
    *head = new;
    *tail = new;
    *cur = new;
    
    return;
  }

  (*tail)->next = new;
  new->prev = *tail;

  *tail = new;
  *cur = *tail;  
}

//insert an element before current
void insertBeforeCur(node** head, node** tail, node** cur, elementtype a){
  if(*head == NULL){
    printf("Error: Empty list!\n");
    return;
  }

  if(*cur == NULL){
    printf("Error: Current element is NULL!\n");
    return;
  }

  //check if cur = head
  if((*cur)->prev == NULL){
    insertAtHead(head, tail, cur, a);
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

//insert an element before current
void insertAfterCur(node** head, node** tail, node** cur, elementtype a){
  if(*head == NULL){
    printf("Error: Empty list!\n");
    return;
  }

  if(*cur == NULL){
    printf("Error: Current element is NULL!\n");
    return;
  }

  //check if cur = tail
  if((*cur)->next == NULL){
    insertAtEnd(head, tail, cur, a);
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

//detete current element
void deleteNode(node** head, node** tail, node** cur){
	if(*cur == NULL){
		printf("Error: NULL element!\n");
		return;
	}

//if cur = head
  if(*cur == *head){
    *head = (*head)->next;
    (*head)->prev = NULL;
    free(*cur);
    *cur = *head;

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
 
//insert an element at a position
void insertAtPosition(node** head, node** tail, node** cur, elementtype a, int n){
  if(n < 0){
    printf("Error: Invalid value of position!\n");
    return;
  }

  if(*head == NULL){
    printf("Error: Empty list!\n");
    return;
  }

  int num = 0;
  node* p = *head;
  
  while(p != NULL){
    if(num == n)
      break;
    p = p->next;
    num++;
  }
  *cur = p;
  
  if(p != NULL)
    insertBeforeCur(head, tail, cur, a);
  else
    insertAtEnd(head, tail, cur, a); 
}

//delete an element at a position
void deleteAtPosition(node** head, node** tail, node** cur, int n){
  if(n < 0){
    printf("Error: Invalid value of position!\n");
    return;
  }

  if(*head == NULL){
    printf("Error: Empty list!\n");
    return;
  }

  int num = 0;
  node* p = *head;
  
  while(p != NULL){
    if(num == n)
      break;
    p = p->next;
    num++;
  }
  *cur = p;
  
  if(p != NULL)
    deleteNode(head, tail, cur); 
}

void reverseList(node** head, node** tail, node** cur){
	if(*head == NULL || (*head)->next == NULL){
		return;
	}
	
	node* p;
	node* p_next;
	/*prev point to the next element in the original list
	  after this step, prev and next will have same direction
	 */
	for(p = *head; p != NULL; p = p->next){
		p->prev = p->next;
	}

	//next point to the pre element in the original list
	for(p = *head; p->prev != NULL; p = p->prev){
	    
		p_next = p->prev;
		p_next->next = p;
	}
	
	(*head)->next = NULL; //head becomes tail

	p = *head;
	*head = *tail;
	*tail = p;	
	*cur = *head;
}

/*split the original list into 2 halve
  n1 is the index of the begining element of list 1
  n2 is the number of element in list 1
 */

void split(node* head, node** head1, node** tail1, node** cur1, node** head2, node** tail2, node** cur2, int n1, int n2){
	if(*head1 != NULL)
		freeList(head1, tail1, cur1);
	if(*head2 != NULL)
		freeList(head2, cur2, cur2);
	
	if(head == NULL)
		return;
	//check validity of n1 and n2
	if(n1 < 0 || n2 <= 0)
		return;

	//copy original list to list 2
	node* cur = head;
	while(cur != NULL){
		insertAtEnd(head2, tail2, cur2, cur->info);
		cur = cur->next;
	}

	//find the 1st element of list 2 in list 1
	int num = 0;	
	cur = *head2;
	while(cur != NULL){		
		if(num == n1)
			break;
		cur = cur -> next;
		num ++;
	}
	
	node* p = cur->next; //p always point to element after cur (used incase cur is removed)
	insertAtEnd(head1, tail1, cur1, cur->info);    
	deleteNode(head2, tail2, &cur);
	*cur2 = cur;
    		
	num = 2;
    while(num <= n2 && p != NULL){
		cur = p;
		p = p->next;
		
		if(cur != NULL){
			insertAtEnd(head1, tail1, cur1, cur->info);
			deleteNode(head2, tail2, &cur);
			*cur2 = cur;
		}
		num++;
	}
}
