#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"

typedef struct {
  char value[MAX];
} Player;

int num_player,i;

void buildList(FILE *fin, Player *p){
  char buff[MAX];
  int i = 0;

  while ( fgets(buff,MAX,fin) != NULL) {
    if (buff[strlen(buff)-1] == '\n') {
      buff[strlen(buff)-1] = '\0';
    }
    strcpy(p[i].value,buff);
    i++;
  }
  num_player = i;
}

void Traverse(Player p[], FILE *fin){

  for(int i = 0; i < num_player; i++){
    printf("%s\n", p[i].value);
    fprintf(fin,"%s\n",p[i].value);
  }
}


void buildTree(Node_tr** root, int l, int r,Player p[]) {
  srand(time(NULL));
  if (l == r ) {
    *root = makeNewNode(p[l].value);
    return;
  }
   *root = (Node_tr*)malloc(sizeof(Node_tr));
   buildTree( &( (*root) -> left ), l , (l+r)/2, p );
  buildTree( &( (*root) -> right ), (l+r)/2+1, r, p );


    i = rand() % 2;
    if( i == 0) strcpy( (*root)->val, (*root)->left->val );
    if (i == 1) strcpy( (*root)->val, (*root)->right->val );
}


void print(Node_tr *p, FILE *fin){
  if (p -> left != NULL && p->right != NULL) {
    print(p -> left,fin);
    print(p -> right,fin);
    printf("Winner of %s and %s is %s\n", p -> left -> val, p -> right -> val, p -> val);
    fprintf(fin,"Winner of %s and %s is %s\n", p -> left -> val, p -> right -> val, p -> val);
  }
}


int main() {
  FILE *fin = fopen("USopen.txt","r");
  if (fin == NULL) {
    printf("Failed to read file\n");
    return 0;
  }

  FILE *fp2 = fopen("treegame.txt","w+");
  if (fp2 == NULL) {
    printf("Failed to open file treegame");
    return 0;
  }

  Player *player = (Player*)malloc(MAX * sizeof(Player));
  Node_tr *root;
  root = (Node_tr*)malloc(sizeof(Node_tr));
  buildList(fin,player);
  Traverse(player,fp2);

  buildTree(&root,0,num_player-1,player);
  print(root,fp2);
  fclose(fin);
  fclose(fp2);
}
