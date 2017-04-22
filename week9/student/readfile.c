#include <stdio.h>
#include <stdlib.h>

#define ID_LENGTH 9
#define NAME_LENGTH 30

typedef struct Student_t
{
	char id[ID_LENGTH];
	char name[NAME_LENGTH];
	float grade;
}student;

int main(int argc, char *argv[])
{
	if(argc != 2){
		printf("There should be 2 arguments!\n");
		return 0;
	}
	
	char* file = argv[1];
 	FILE* f = fopen(file, "r+b");
	
	student* studentA = (student*)malloc(sizeof(student));
	int n = 0;
    
	while(!feof(f)){
		n++;
		studentA = (student*)realloc(studentA, n * sizeof(student));
		int num = fread(studentA + n - 1, sizeof(student), 1, f);
	}
	n--;
	for(int i = 0; i < n ; i ++){
	    printf("%-5d%-15s%-30s%3.1f\n", i+1, studentA[i].id, studentA[i].name, studentA[i].grade);
	}
	free(studentA);
	fclose (f);

    return 0;
}

