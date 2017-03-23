#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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



typedef struct list_phone {
  PHONE Phone;
  struct list_phone *next;
} node_ph;



node_ph *root,*cur;



PHONE *allPhone;
int numPhone;



void correct(char *s)
{
  for (int i=0; i<strlen(s); i++)
    if (s[i] == '_')
      s[i] = ' ';
}




node_ph* makeNewNode(PHONE ph){
  node_ph* new = (node_ph*)malloc(sizeof(node_ph));
  new -> Phone = ph;
  new -> next = NULL;
  return new;
}



void insertAfterCur(PHONE ph){
  node_ph* new = makeNewNode(ph);
  new -> next = cur -> next;
  cur -> next = new;
  cur = cur -> next;
}





void displayNode(node_ph *p){
  printf("%-30s%-10s%-10s%d\n",p -> Phone.model,p -> Phone.memory,p -> Phone.screenSize,p -> Phone.price);
}




void traversingList(){
  node_ph *p;
  for (p = root; p != NULL; p=p->next) {
    displayNode(p);
  }
}





void menu1(){
  FILE *fin = fopen("phoneDB.txt","r");
  if (fin == NULL) {
    printf("Failed to read file phoneDB.txt");
    return;
  }

  char buff[100];
  buff[0] = '\0';
  PHONE ph;
  
  fgets(buff,100,fin);
  sscanf(buff,"%s %s %s %d",ph.model,ph.memory,ph.screenSize,&ph.price);
  correct(ph.model);
  root = makeNewNode(ph);
  cur = root;
  buff[0]='\0';
  while(fgets(buff,100,fin) != NULL){
   sscanf(buff,"%s %s %s %d",ph.model,ph.memory,ph.screenSize,&ph.price);
   correct(ph.model);
   insertAfterCur(ph);
   buff[0] = '\0';
  }
  traversingList();
  fclose(fin);
}



void menu2(){
  FILE *fin = fopen("phoneDB.dat","rb");
  if (fin == NULL) {
    printf("Cannot open file phoneDB.dat\n");
    return;
  }

  PHONE ph;
  fread(&ph,sizeof(PHONE),1,fin);
  root = makeNewNode(ph);
  cur = root;
 
  while (fread(&ph,sizeof(PHONE),1,fin) == 1) {
    insertAfterCur(ph);
  }
  traversingList();
  fclose(fin);
}





void menu4(){
  char search[MAX_STRING_MODEL];
  char model[MAX_STRING_MODEL];
  int i,j, flag = 0;
  node_ph *p;

  while(getchar() != '\n');
  printf("Model: ");
  fgets(search,MAX_STRING_MODEL,stdin);
  

  if (search[strlen(search)-1] == '\n') {
    search[strlen(search)-1] = '\0';
  }
  printf("search: %s\n\n",search);

  for (i = 0; i < strlen(search); i++) {
    search[i] = tolower(search[i]);
  }
  search[i+1] = '\0';

  for (p = root; p != NULL; p=p->next) {
    model[0] = '\0';
    for (j = 0; j <= strlen(p->Phone.model); j++) {
      model[j] = tolower(p -> Phone.model[j]);
    }

    if(strcmp(model,search) == 0){
       printf("%-30s%-10s%-10s%d\n\n\n",p -> Phone.model,p -> Phone.memory,p -> Phone.screenSize,p -> Phone.price);
       flag = 1;
    }
  }

  if (flag == 0) {
    printf("No result found!!!\n\n");
  }
}




void menu5(){
  node_ph *p;
  int price,flag=0;;
  printf("Enter price: ");
  scanf("%d",&price);
  for (p = root; p != NULL; p = p->next) {
    if (p->Phone.price < price) {
      printf("%-30s%-10s%-10s%d\n",p -> Phone.model,p -> Phone.memory,p -> Phone.screenSize,p -> Phone.price);
	flag = 1;
    }
  }
  if (flag == 0) {
    printf("No result found!!!\n");
  }
  printf("\n\n");
}





void readFile(){
  int numPhone;
  FILE *f = fopen("PhoneDB.dat","rb");
  PHONE *p;
  fseek(f,0,SEEK_END);
  numPhone = ftell(f) / sizeof(PHONE);
  fseek(f,0,SEEK_SET);
  p = (PHONE *)malloc(numPhone * sizeof(PHONE));
  fread(p,sizeof(PHONE),numPhone,f);
  for (int i = 0; i < numPhone; i++) {
    printf("%-30s%-10s%-10s%d\n",p[i].model,p[i].memory,p[i].screenSize,p[i].price);
  }
  fclose(f);
  free(p);
  printf("\n\n\n");
}





void menu6(){
  node_ph *p;
  FILE *f = fopen("PhoneDB.dat","wb");
  if (f == NULL) {
    printf("Cannot open file PhoneDB.dat\n");
    return;
  }
  for (p = root; p != NULL; p=p->next) {
    fwrite(&p->Phone,sizeof(PHONE),1,f);
  }
  fclose(f);
  readFile();
}


int main()
{
  int choice;
  while (1)
    {
      printf(" 1. Build list from file text\n");
      printf(" 2. Build list from file dat\n");
      printf(" 3. Print all database\n");
      printf(" 4. Find model\n");
      printf(" 5. Search by price\n");
      printf(" 6. Export list to PhoneDB.dat\n");
      printf(" 7. Exit\n");
      printf("Your choice: ");
      scanf("%d",&choice);
      switch (choice)
	{
	case 1:
	  menu1(); 
	  break;
	case 2:
	  menu2(); 
	  break;
	case 3:
	  traversingList(); 
	  break;
	case 4:
	  menu4(); 
	  break;
	case 5:
	  menu5();
	  break;
	case 6:
	  menu6();
	  break;
	case 7: printf("Exit!!!\n"); return 0;
	default:
	  printf("Invalid input! Your choice must be from 1 to 7\n\n");
	  break;
	}
    }
}
