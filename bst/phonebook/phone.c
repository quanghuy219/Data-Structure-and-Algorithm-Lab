#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
  char name[MAX];
  char email[MAX];
  char phone[MAX];
} Contact;

typedef Contact eletype;

#include "tree.h"

#define COUNT 10


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



Node_tr *buildBST(Contact *person, int num){
  Node_tr *root = NULL;

  for (int i = 0; i < num; i++) {
    root = insertNode(person[i],root);
  }

  return root;
}



Node_tr* search(char email[], Node_tr* r) {
  if(r == NULL) return NULL;

  if (strcmp(r->val.email,email) == 0) {
    return r;
  }

  else if (strcmp(r->val.email,email) > 0 ) return search(email,r -> left);

  else return search(email, r -> right);
}


void writeFile(FILE *fin, Node_tr *root){
  if (root != NULL) {
    writeFile(fin,root->left);
    fwrite(&(root->val),sizeof(Contact),1,fin);
    writeFile(fin, root->right);
  }
}


void print(Contact *person, int num_contact) {
  for(int i = 0; i < num_contact; i++){
    printf("%s    %s    %s\n", person[i].name, person[i].email, person[i].phone);
  }
}



int main() {
  FILE *fp1 = fopen("book.dat","rb");
  if (fp1 == NULL) {
    printf("Cannot read file\n");
    return 0;
  }
  FILE *fp2;
  fseek(fp1,0,SEEK_END);
  int num_contact = ftell(fp1) / sizeof(Contact);
  Contact *person = (Contact*)malloc(num_contact*sizeof(Contact));
  fseek(fp1,0,SEEK_SET);
  readFile(fp1,person,num_contact);
  fclose(fp1);

  
  Node_tr *root = buildBST(person,num_contact);
  inorder(root);

  char email[MAX];
  int choice;
  while (1){
    printf("1. Search for email\n");
    printf("2. Write file in ascending order\n");
    printf("0. Exit\n");
    scanf("%d",&choice);

    switch (choice) {
      case 1:
        printf("Search for email: ");
        scanf("%s",email);
        Node_tr *p = search(email,root);
        if (p == NULL) {
        printf("Not found\n");
        }

        else {
          printf("%s\n", p -> val.name);
          printf("%s\n", p -> val.email);
          printf("%s\n", p -> val.phone);
        }
        break;

      case 2:
        fp2 = fopen("sortphone.dat","wb+");
        if (fp2 == NULL) {
          printf("Cannot open file sort phone\n");
          return 0;
        }
        writeFile(fp2,root);
        fseek(fp2,0,SEEK_SET);
        Contact *person1 = (Contact*)malloc(num_contact*sizeof(Contact));
        readFile(fp2,person1,num_contact);
        print(person1,num_contact);
        fclose(fp2);
        break;

      case 0: return 0;
    }
  }

  return 0;
}
