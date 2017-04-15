#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef phone_addr element_type;
typedef struct Node Node ;
typedef struct Node {
	element_type element;
	Node *prev;
	Node *next;
} Node;

typedef struct dlist$ {
	Node *root;
	Node *cur;
	Node *last;
} dlist;

Node *makeNode(element_type val) {
	Node *p;
	p = (Node *)malloc(sizeof(Node));
	p->next = NULL;
	p->prev = NULL;
	p->element = val;
	return p;
}

dlist *iniList(dlist *list) {
	list = (dlist *)malloc(sizeof(dlist));
	if (list == NULL) {
		fprintf(stderr, "ERROR : Allocated memory failed !!\n");
		exit(1);
	}
	list->root = NULL;
	list->cur = NULL;
	list->last = NULL;
	return list;
}

//find the length of a list
int listLength(dlist *list) {
	Node *p;
	int i = 0;
	p = list->root;
	while (p != NULL) {
		i++;
		p = p->next;
	}
	return i;
}

//display a node
void display(Node *p) {
	printf("%-30s\t%-15s\t%-30s\n", p->element.name, p->element.tel, p->element.email);
}

void insertEnd(element_type val, dlist *list) {
	Node *p;
	p = makeNode(val);
	if (list->root == NULL) {
		list->root = p;
		list->cur = p;
		list->last = p;
	}
	else
	{
		(list->last)->next = p;
		p->prev = list->last;
		list->last = p;
		list->cur = p;
	}
}

//find a node with a value
Node *findNode(element_type val, dlist *list) {
	Node *p = list->root;
	if (list->root == NULL)
		return NULL;
	while (p != NULL) {
		if (strcmp(p->element.name, val.name) == 0 && strcmp(p->element.tel, val.tel) == 0 && strcmp(p->element.email, val.email) == 0)
		{
			list->cur = p;
			return p;
		}
		p = p->next;
	}
	printf("Not found!!\n");
	return NULL;
}

//locate n-th Node in a list
Node *locateNode(int n, dlist *list) {
	int i = 0;
	Node *p = list->root;
	if (n > listLength(list))
	{
		printf("Not found!!\n");
		return NULL;
	}
	if (list->root == NULL)
		return NULL;
	for (i = 0; i < n; ++i) {
		list->cur = p;
		p = p->next;
	}
	return list->cur;
}

void delNode(Node *p, dlist *list) {
	if (list->root == NULL)
		return;
	if (p == NULL)
		return;
	if (p == list->root) {
		list->root = p->next;
		p->next->prev = NULL; //careful , maybe core dump
		free(p);
	}
	else if (p == list->last) {
		list->last = p->prev;
		p->prev->next = NULL;
		free(p);
	}
	else
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
		list->cur = p->prev;
		free(p);
	}
}

// insert Node before Node p
void insertBefore(Node *p, element_type val, dlist *list) {
	Node *q = makeNode(val);
	list->cur = q;
	if (list->root == NULL) {
		printf("Node haven't create !!");
		return;
	} else if (list->root == p) {
		list->root = q;
		q->next = p;
	} else {
		q->next = p;
		q->prev = p->prev;
		p->prev->next = q;
	}
}

// insert Node after Node p
void insertAfter(Node *p, element_type val, dlist *list) {
	Node *q = makeNode(val);
	list->cur = q;
	if (list->root == NULL) {
		printf("Node haven't create !!");
		return;
	} else {
		if (list->last == p) {
			insertEnd(val, list);
			free(q);
		}  else  {
			q->next = p->next;
			q->prev = p;
			p->next = q;
		}
	}
}

//display a list
void traverse(dlist *list) {
	Node *p;
	p = list->root;
	while ( p != NULL ) {
		display(p);
		p = p->next;
	}
}

//split a list from startPosition to the end with the length of numSplit
void splitList(int startPosition, int numSplit, dlist *list, dlist *list2, dlist *list3) {
	Node *p;
	int i;
	int check[numSplit];
	printf("The length of the list is %d\n", listLength(list));
	for (i = 1; i <= listLength(list); ++i)
	{
		p = locateNode(i, list);
		if (i >= startPosition && i < startPosition + numSplit)
			insertEnd(p->element, list2);
		else
			insertEnd(p->element, list3);
	}
	printf("Split list success\n");
}

//save the content of list to a data file
void savetoFile(FILE *fptr, dlist *list) {
	Node *p;
	p = list->root;
	while ( p != NULL ) {
		// fwrite(&p->element, sizeof(element_type), 1, fptr);
		fprintf(fptr, "%-30s\t%-15s\t%-15s\n", p->element.name, p->element.tel, p->element.email);
		list->cur = p;
		p = p->next;
	}
}

void checkList(dlist *list, char fileName[20]) {
	FILE *fptr;
	Node *p = list->root;
	if ((fptr = fopen(fileName, "w + t")) == NULL)
	{
		printf("Can't open file %s\n", fileName);
		exit(1);
	}
	// while (p != NULL) {
	//   fprintf(fptr, "%-30s\t%-3d\t%-2.1f\t%-9d\n", p->element.model, p->element.storage, p->element.screensize, p->element.price);
	//   p = p->next;
	// }
	savetoFile(fptr, list);
}

// void reverseList(dlist *list) {
// 	Node *p;
// 	Node *q = list->last;
// 	while(list->root->next != q)
// 	{
// 		list->last->next = list->root;
// 		// list->root->prev = list->last;
// 		list->root = list->root->next;
// 		list->last = list->last->next;
// 	}
// }

void reverseList(dlist *list) {
	Node *z, *p;
	list->last = list->root;


	p = list->root;

	list->root = list->root->next;

	z = list->root;
	list->root = list->root->next;
	z->next = p;


	while (list->root != NULL) {
		p = z;
		z = list->root;
		list->root = list->root->next;
		z->next = p ;
	}

	list->root = z;
	list->last->next = NULL;
	list->cur = list->root;
}
//count the identical phone number elements and extract them
dlist *countsameNum(dlist *list, dlist *list2) {
	int max = 0;
	Node *p, *q;
	int i = 0;
	int j;
	int length = listLength(list);
	int check[length];
	int count[length];
	for (i = 0; i < length; ++i)
		count[i] = 0;

	for (i = 0, p = locateNode(i + 1, list); i < length - 1; ++i)
		for (q = p; q != NULL; q = q->next)
			if (strcmp(p->element.tel, q->element.tel) == 0)
				count[i] = count[i] + 1;

	for (i = 0; i < length; ++i) {
		if (max < count[i])
		{
			max = count[i];
			j = i;
		}
		// printf("Count[%d] = %d\n", i + 1, count[i]);
	}
	if (max > 0)
		printf("The maximum number of identical phone numbers is %d\n", max);

	printf("The nodes that have maximum identical phone numbers are: \n");

	if (max != 0) {
		p = locateNode(j + 1, list);
		for (q = p; q != NULL; q = q->next)
			if (strcmp(q->element.tel, p->element.tel) == 0)
			{
				printf("Node with phone number: %s, address: %p\n", q->element.tel, q);
				insertEnd(q->element, list2);
			}
	}
	return list2;
}
void freeList(dlist * list) {
	if (list->root == NULL)
		return;
	Node *to_free = list->root;
	while (to_free != NULL) {
		list->root = (list->root)->next;
		free(to_free); // free node
		to_free = list->root;
	}
}

