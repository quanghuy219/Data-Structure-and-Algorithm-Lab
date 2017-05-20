#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

clock_t start_clock, end_clock;

void start(){
	start_clock = clock();
}

void end(){
	end_clock = clock();
	float seconds = (float)(end_clock - start_clock)/CLOCKS_PER_SEC;
	printf("\nExcuted time: %f\n", seconds);
}

#define MAX 1000000

int a[MAX];

void menu(){
	printf("*****MENU*****\n");
	printf("1, Generate an array.\n");
	printf("2, Read an array from file.\n");
	printf("3, Selection sort.\n");
	printf("4, Bubble sort.\n");
	printf("5, Insertion sort.\n");
	printf("6, Shell sort.\n");
	printf("7, Quick sort.\n");
	printf("8, Heap sort.\n");
	printf("9, Counting sort.\n");
	printf("10, Radix sort.\n");
	printf("11, Merge sort.\n");
	printf("15, Exit.\n");
}

void generate(){
	int n, x;
	char *fn = "array.txt";
	FILE *fptr;
	fptr = fopen(fn, "w");
	printf("How many number you want to generate.\n"); scanf("%d", &n);
	fseek(fptr, 0, SEEK_SET);
	fprintf(fptr, "%d\n", n);
	for(int i=0; i<n; i++){
		x = rand()%1000;
		fprintf(fptr, "%d ", x);
	}
	fclose(fptr);
}

void readData(int *n){
	FILE *fptr;
	char *fn = "array.txt";
	fptr = fopen(fn, "r");
	fseek(fptr, 0, SEEK_SET);
	fscanf(fptr, "%d", n);
	for(int i=0; i<*n; i++){
		fscanf(fptr, "%d", &a[i]);
	}
	fclose(fptr);
}

void printAll(int n){
	for(int i=0; i<n; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
}

void swap(int *n, int *m){
	int tmp;
	tmp = *n;
	*n = *m;
	*m = tmp;
}

void selectionSort(int n){
	int i, j, jmin;
	for(i=0; i<n; i++){
		jmin = i;
		for(j=i+1; j<n; j++){
			if(a[j] < a[jmin]) jmin = j;
		}
		if(jmin != i) swap(&a[i], &a[jmin]);
	}
}

void bubbleSort(int n){
	int i,j;
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			if(a[i] > a[j])	swap(&a[i], &a[j]);
		}
	}
}

void insertionSort(int n){
	int i, j, tmp;
	for(i=1 ; i<n; i++){
		tmp = a[i];
		j = i-1;
		while( j>=0 && tmp<a[j] ){
			a[j+1] = a[j];
			j=j-1;
		}
		a[j+1] = tmp;
	}
}

void shellSort(int n){
	int h, i, j, k, tmp;
	h = n/2;
	while(h != 0){
		for(i=h; i<n; i++){
			//insertionSort for element a[i-h] a[i] a[i+h]...
			for(k=i; k<n; k+=h){
				tmp = a[k];
				j = k-h;
				while(j>=0 && tmp<a[j] ){
					a[j+h] = a[j];
					j = j-h;
				}
				a[j+h] = tmp;
			}
		}
		h = h/2;
	}
}

int partition(int L, int R, int indexPivot){
	int pivot = a[indexPivot];
	swap(&a[indexPivot], &a[R]);
	int storeIndex = L;
	for(int i=L; i<=R-1; i++){
		if(a[i] < pivot){
			swap(&a[storeIndex], &a[i]);
			storeIndex++;
		}
	}
	swap(&a[storeIndex], &a[R]);

	return storeIndex; //position of pivot
}

void quickSort(int L, int R){
	if(L<R){
		int index = (L+R)/2;
		index = partition(L, R, index);
		if(L<index){
			quickSort(L, index-1);
		}
		if(R>index){
			quickSort(index+1, R);
		}
	}
}

void heapify(int i, int n){
	int L = 2*i+1;
	int R = 2*i+2;
	int max = i;
	if(L<n && a[L]>a[max] ){
		max = L;
	}
	if(R<n && a[R]>a[max]){
		max = R;
	}
	if(max != i){
		swap(&a[i], &a[max]);
		heapify(max, n);
	}
}

void buildHeap(int n){
	for(int i=n/2; i>=0; i--){
		heapify(i, n);
	}
}

void heapSort(int n){
	buildHeap(n);
	for(int i=n-1; i>0; i--){
		swap(&a[0], &a[i]);
		heapify(0, i-1);
	}
}

void countingSort(int n){
	int i;
	int c[n], r[MAX];
	for(i=0; i<MAX; i++) r[i] = 0;
	for(i=0; i<n; i++) r[a[i]]++;
	for(i=1; i<MAX; i++) r[i] = r[i] + r[i-1];
	//sort
	for(i=n-1; i>=0; i--){
		c[r[a[i]]] = a[i];
		r[a[i]]--;
	}
	//copy
	for(i=0; i<n; i++){
		a[i] = c[i];
	}
}

void radixSort10(int n){
	int max = -10000;
	for(int i=0; i<n; i++){
		if(max<a[i]) max = a[i];
	}
	int tmp[MAX];
	int exp = 1;
	while(max/exp > 0){
		int bin_sz[10] = {0};
		int idx[10];
		for(int i=0; i<n; i++){
			int c = (a[i]/exp)%10;
			bin_sz[c]++;
			tmp[i] = a[i];
		}
		idx[0] = 0;
		for(int i=1; i<10; i++){
			idx[i] = idx[i-1] + bin_sz[i-1];
		}
		for(int i=0; i<n; i++){
			int c = (tmp[i]/exp)%10;
			a[idx[c]] = tmp[i];
			idx[c]++;
		}
		exp *= 10;
	}
}

void merge(int L, int M, int R){
	// merge two sorted list a[L..M] and a[M+1..R]
	int i = L;	//first position of list a[L..M]
	int j = M+1;	//second position of list a[M+1..R]
	int tmp[MAX];
	for(int k=L; k<=R; k++){
		if(i>M){	//the first list is all scanned
			tmp[k] = a[j];
			j++;
		} else if(j>R){	//the second list is all scanned
			tmp[k] = a[i];
			i++;
		} else {
			if(a[i] < a[j]){
				tmp[k] = a[i];
				i++;
			} else {
				tmp[k] = a[j];
				j++;
			}
		}
	}
	for(int k=L; k<=R; k++){
		a[k] = tmp[k];
	}
}

void mergeSort(int L, int R){
	if(L<R){
		int M = (L+R)/2;
		mergeSort(L, M);
		mergeSort(M+1, R);
		merge(L, M, R);
	}
}

int main(){
	int choice, n;
	do{
		menu();
		printf("Enter your choice : "); scanf("%d", &choice);
		switch(choice){
			case 1:
				generate();
				break;
			case 2:
				readData(&n);
				// printAll(n);
				break;
			case 3:
				start();
				selectionSort(n);
				end();
				// printAll(n);
				break;
			case 4:
				start();
				bubbleSort(n);
				end();
				// printAll(n);
				break;
			case 5:
				start();
				insertionSort(n);
				end();
				// printAll(n);
				break;
			case 6:
				start();
				shellSort(n);
				end();
				// printAll(n);
				break;
			case 7:
				start();
				quickSort(0, n-1);
				end();
				 printAll(n);
				break;
			case 8:
				start();
				heapSort(n);
				end();
				 printAll(n);
				break;
			case 9:
				start();
				countingSort(n);
				end();
				// printAll(n);
				break;
			case 10:
				start();
				radixSort10(n);
				end();
				// printAll(n);
				break;
			case 11:
				start();
				mergeSort(0, n-1);
				end();
				printAll(n);
				break;
			case 15:
				printf("Thank you.\n");
				break;
			default:
				printf("Syntax Error.\n");
				continue;
		}
	} while(choice != 15);

	return 0;
}
