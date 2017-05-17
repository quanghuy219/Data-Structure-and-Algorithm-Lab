#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define COUNT 10

typedef struct {
  char name[MAX];
  char email[MAX];
  char phone[MAX];
} Contact;


void readFile(FILE *fin, Contact *person,int num){
  for(int i=0; i < num; i++){
    fread(&person[i],sizeof(Contact),1,fin);
  }
}


void sort(Contact *person,int num){
  Contact *sort_person = (Contact*)malloc(sizeof(Contact)*num);
  Contact temp;
  for (int i = 0; i < num; i++) {
    for(int j = i+1; j < num; j++){
      if ( strcmp(person[i].email,person[j].email) > 0) {
        temp = person[i];
        person[i] = person[j];
        person[j] = temp;
      }
    }
  }
}



Node_tr *buildBST(Contact *person, int l, int r){

  if (l > r) {
    return NULL;
  }

  int mid = (l+r)/2;
  Node_tr* root = makeNewNode(person[mid].email);

  root -> left = buildBST(person,l,mid-1);
  root -> right = buildBST(person,mid+1,r);

  return root;
}



int main() {
  FILE *fp1 = fopen("book.dat","rb");
  if (fp1 == NULL) {
    printf("Cannot read file\n");
    return 0;
  }

  fseek(fp1,0,SEEK_END);
  int num_contact = ftell(fp1) / sizeof(Contact);
  Contact *person = (Contact*)malloc(num_contact*sizeof(Contact));
  fseek(fp1,0,SEEK_SET);
  readFile(fp1,person,num_contact);
  fclose(fp1);

  sort(person,num_contact);

  Node_tr *root = buildBST(person,0,num_contact-1);
  inorder(root);

  return 0;
}
