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



PHONE *allPhone;
int numPhone;




void correct(char *s)
{
  for (int i=0; i<strlen(s); i++)
    if (s[i] == '_')
      s[i] = ' ';
}




PHONE *getInput(int start, int end){
  FILE *f = fopen("phoneDB.dat","rb");
  int count;
  PHONE *phone;
  if (f == NULL) {
    printf("Failed to open phoneDB.dat!!!\n");
    return NULL;
  }
  fseek(f,0,SEEK_END);
  numPhone = ftell(f) / sizeof(PHONE);
  fseek(f,0,SEEK_SET);
  if (end == -1) {
    end = numPhone;
  }

  fseek(f, (start-1) * sizeof(PHONE),SEEK_SET);

  count = end - start + 1;
  phone = (PHONE *)malloc(count * sizeof(PHONE));

 
  fread(phone,sizeof(PHONE),count,f);
  fclose(f);
  free(phone);
  return phone;
}



void getAllPhone(){
  FILE *fin = fopen("phoneDB.dat","rb");
  if(fin == NULL){
     printf("Failed to open phoneDB.dat!!!\n");
    return;
  }
  allPhone = getInput(1,-1);
}




void menu1()
{
  FILE *fi = fopen("phoneDB.txt","r");
  if (fi == NULL)
    {
      printf("Error opening PhoneDB.txt\n");
      return;
    }
  FILE *fo = fopen("phoneDB.dat","wb");
  PHONE phone;
  while (ftell(fi) != SEEK_END)
    {
      phone.model[0] = '\0';
      fscanf(fi,"%s%s%s%d",phone.model,phone.memory,phone.screenSize,&phone.price);
      if (strlen(phone.model) == 0) break;
      correct(phone.model);
      correct(phone.memory);
      correct(phone.screenSize);
      fwrite(&phone,sizeof(PHONE),1,fo);
    }
  fclose(fi);
  fclose(fo);
  printf("Import data from text successfully!\n\n");
}







void menu2(){
  int choice=0;
  int num,i;
  int start,end;
  PHONE *phone;
  printf("\n1.Read from beginning\n");
  printf("2.Read from end\n");
  while(choice != 1 && choice != 2){
  printf("Choose: ");
  scanf("%d",&choice);
  switch (choice) {
  case 1: {
    printf("Number of phones: ");
    scanf("%d",&num);
    while(num < 0){
      printf("Input >= 0");
      printf("Number of phones: ");
      scanf("%d",&num);
    }
    if (num >= numPhone) {
      phone = getInput(1,-1);
    }
    else {
      phone = getInput(1,num);
    }

    for (i = 0; i < num; i++) {
       printf("%-5d%-30s%-10s%-10s%d\n",i+1,allPhone[i].model,allPhone[i].memory,allPhone[i].screenSize,allPhone[i].price);
    }
    break;
  }

  case 2: {
    printf("Number of phones: ");
    scanf("%d",&num);
    while(num < 0){
      printf("Input >= 0");
      printf("Number of phones: ");
      scanf("%d",&num);
    }
    if (num >= numPhone){
      phone = getInput(1,-1);
    }
    else {
      start = numPhone - num + 1;
      phone = getInput(start,-1);
    }
   
    for (i = 0; i < num; i++) {
       printf("%-5d%-30s%-10s%-10s%d\n",i+1,allPhone[i].model,allPhone[i].memory,allPhone[i].screenSize,allPhone[i].price);
    }
    break;
  }
  default: printf("Input must be 1 or 2!!!\n");
    break; 
  }
  }
  printf("\n\n");
}







void menu3(){
  for (int i = 0; i < numPhone; i++) {
    if(i % 20 == 0){
      printf("\nPage %d:\n",i/20+1);
    }
    printf("%-5d%-30s%-10s%-10s%d\n",i+1,allPhone[i].model,allPhone[i].memory,allPhone[i].screenSize,allPhone[i].price);
  }
  printf("\n\n");
 
}









void menu4(){
  char search[MAX_STRING_MODEL];
  char model[MAX_STRING_MODEL];
  int i,j, flag = 0;

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

  for (i = 0; i < numPhone; i++) {
    model[0] = '\0';
    for (j = 0; j <= strlen(allPhone[i].model); j++) {
      model[j] = tolower(allPhone[i].model[j]);
    }

    if(strcmp(model,search) == 0){
       printf("%-30s%-10s%-10s%d\n\n\n",allPhone[i].model,allPhone[i].memory,allPhone[i].screenSize,allPhone[i].price);
       flag = 1;
    }
  }

  if (flag == 0) {
    printf("No result found!!!\n\n");
  }
 
}



int main()
{
  int choice;
  getAllPhone();
  while (1)
    {
      printf(" 1. Convert to DB from text\n");
      printf(" 2. Read data from beginning and end\n");
      printf(" 3. Print all database\n");
      printf(" 4. Find model\n");
      printf(" 5. Exit\n");
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
	  menu3();
	  break;
	case 4:
	  menu4();
	  break;
	case 5:
	  printf("Exit!\n");
	  return 0;
	default:
	  printf("Invalid input! Your choice must be from 1 to 5\n\n");
	  break;
	}
    }
}
