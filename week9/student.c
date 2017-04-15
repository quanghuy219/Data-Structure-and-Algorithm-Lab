#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define value_t STUDENT

#define ID_LENGTH 10
#define NAME_LENGTH 30

typedef struct {
	char id[ID_LENGTH];
	char name[NAME_LENGTH];
	int grade;
} STUDENT;

typedef struct node {
  value_t val;
  struct node_t *next;
  struct node_t *prev;
} node_t;


node_t *head;
node_t *cur;
node_t *tail;
int len;



node_ph* makeNewNode(value_t val){
  node_ph* new = (node_t*)malloc(sizeof(node_t));
  new -> val = val;
  new -> next = NULL;
  new -> prev = NULL;
  return new;
}


