typedef struct phone_t{
	char model[30];
	int memory;
	float screensize;
	int price;
}phone;

typedef phone ElementType;

struct phone_list{
	ElementType info;
	struct phone_list *next;	
};
typedef struct phone_list node;

// create a new element/node
node* makeNewNode(ElementType a){
	node* new = (node*)malloc(sizeof(node));
	new->info = a;
	new->next = NULL;
	return new;
}


//Display a node/element
void displayNode(node* a){
	if(a == NULL){
		printf("This is a NULL element!\n");
		return;
	}
	printf("%-20s%-15d%-25.1f%d\n", a->info.model, a->info.memory, a->info.screensize, a->info.price); 	
}

//Display the list/ all the elements
void displayList(node* root){
	node* p;
	printf("%-20s%-15s%-25s%s\n\n", "MODEL", "MEMORY (GB)", "SCREEN SIZE (INCHES)", "PRICE (VND)");		
	for(p = root; p != NULL; p = p->next)
		displayNode(p);
}

//free the list
node* freeNode(node* root, node** cur){
	node *ptr = root;
	while(ptr != NULL){
		root = root->next;
		free(ptr);
		ptr = root;
	}
	*cur = root;
	return root;	
}

//insert a element at the end of the list
node* insertAtEnd(node* root, node** cur, ElementType a){
	node* new = makeNewNode(a);
	if(root == NULL){ //check if the list is empty
		*cur = new;
		return new;
	}
	node* ptr = root;
	while(ptr != NULL){
		if(ptr->next == NULL) //find the last element of the list
			break;
		ptr = ptr->next;
	}
	ptr->next = new; //link the last element to the new element
	new->next = NULL;
	*cur = new;
	return root;
}


node* insertAtHead(node* root, node** cur, ElementType a){
	node* new = makeNewNode(a);
	if(root == NULL){ //check if the list is empty
		*cur = new;
		return new;
	}
	new->next = root; //link the element to the 1st element of the list
	*cur = new;
	return new;
}


node* insertBeforeCur(node* root, node** cur, ElementType a){
	//check if the list is empty
	if(root == NULL){
		printf("Error: Empty list!\n");
		return root;
	}

	node* subcur = *cur;
// check if cur point to NULL
	if(subcur == NULL){
		printf("Error: NULL element!\n");
		return root;
	}

	//cur point to 1st element
	if(subcur == root)
		return insertAtHead(root, &(*cur), a);

//insert
	node* new = makeNewNode(a);
	node* p = root;
	
	while (p != NULL) {
		if(p->next == subcur) //find the element before cur
			break;
		p = p->next;		
	}
	
	new->next = subcur; //link the new element to cur
	p->next = new; //link the element before cur to new element
	*cur = new;
	return root;	
}


node* insertAfterCur(node* root, node** cur, ElementType a){
//check if the list is empty
	if(root == NULL){
		printf("Error: Empty list!\n");
		return root;
	}

	node* subcur = *cur;
	// check if cur point to NULL
	if(subcur == NULL){
		printf("Error: NULL element!\n");
		return root;
	}
    
//insert
	node* new = makeNewNode(a);
    new->next = subcur->next; //link new element to the element after cur
	subcur->next = new; //link cur to new element
	*cur = new;
	return root;	
}

node* deleteNode(node* root, node** cur){
//check if the list is empty
	if(root == NULL){
		printf("Error: Empty list!\n");
		return root;
	}
     
	node* subcur = *cur;
	// check if cur point to NULL
	if(subcur == NULL){
		printf("Error: NULL element!\n");
		return root;
	}

	//check if cur point to 1st element
	if(subcur == root){
		root = root->next;
		free(subcur);
		*cur = root;
		return root;
	}

	//delete
	node* ptr = root;
	while(ptr != NULL){
		if(ptr->next == subcur) //find the element before cur 
			break;
		ptr = ptr->next;
	}

	ptr->next = subcur->next; //delete cur
	free(subcur);

	*cur = ptr->next;
	return root;	
}


node* insertAtPosition(node* root, node** cur, ElementType a, int n){
	if(root == NULL)
		return NULL;

	if(n < 0)
		return root;

	int num = 0;
	node* ptr = root;
	while(ptr != NULL){
		if(num == n)
			break;
		ptr = ptr->next;
		num++;
	}
	*cur = ptr;
	if(ptr != NULL)
		return root = insertBeforeCur(root, &(*cur), a);
	else
		return root = insertAtEnd(root, &(*cur), a);	
}

node* deleteAtPosition(node* root, node** cur, int n){
		if(root == NULL)
			return NULL;

		if(n < 0)
			return root;
		
		int num = 0;

		node* ptr = root;
		while(ptr != NULL){
			if(num == n)
				break;
			ptr = ptr->next;
			num++;
		}
		*cur = ptr;
		if(ptr == NULL)
			return root;
		else
			return root = deleteNode(root, &(*cur));		
}

node* reverseList(node* root, node** cur){
	if(root == NULL)
		return NULL;
	if(root->next == NULL){
		*cur = root;
		return root;
	}
	node* p1 = root;
	node* p2 = p1->next;
	node* p3 = p2->next;
	root->next = NULL;
	

	while(p2 != NULL){
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		if(p3 != NULL)
			p3 = p3->next;
	}
	*cur = p1;
	return p1;
}
