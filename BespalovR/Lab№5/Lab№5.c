//по возрастанию 
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
struct row {
	char name[16];
	unsigned short int age;
};

char choose_sort() {
	printf("Choose sorting algorythm.\n");
	printf("1 - Quick sort.\n");
	printf("2 - Selection sort.\n");
	printf("3 - Bubble sort.\n");
	char t;
	while (scanf("%d") != 1 || t > 3 || t < 1) {
		printf("Incorrect input. Please try again.\n");
		char c;
		while ( ( c = getchar()) != '\n' ){}
	}
	return t;
}

int partition(struct row* arr, int low, int high) {
	int pivot = arr[high].age;
	int i = low - 1;
	for (int j = low; j <= high - 1; j++) {
		if (arr[j].age < pivot) {
			i++;
			struct row t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
		}
	}
	struct row t = arr[i+1];
	arr[i+1] = arr[high];
	arr[high] = t;
	return i + 1;
}

void quick_sort(struct row* arr, int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void selection_sort(struct row* arr, int n) {
	for (int i = 0; i < n - 1; i++) {
		int mn = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j].age < arr[mn].age) {
				mn = j;
			}
		}
		struct row t = arr[i];
		arr[i] = arr[mn];
		arr[mn] = t;
	}
}

void bubble_sort(struct row* arr, int n) {
	for (int i = 0; i < n - 1; ++i) {
		char flag = 0;
		for (int j = 0; j < n - i - 1; ++j) {
			if (arr[j].age > arr[j + 1].age) {
				struct row t = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = t;
				flag = 1;
			}
		}
		if (flag == 0) {
			break;
		}
	}
				
}

int read_file(struct row* arr) {
	FILE* fptr = fopen("test.txt", "r+");
	
	fclose(fptr);
}

void write_file(struct row* arr, int n) {
	FILE* fptr = fopen("test.txt", "w+");
	for (int i = 0; i < n; ++i) {
		fprintf(fptr, "%s\t%d\n", arr[i].name,arr[i].age);
	}
	fclose(fptr);
}

void main() {

}
