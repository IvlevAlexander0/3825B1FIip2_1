#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <time.h>


void clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}


typedef struct {
	char name[15];
	int age;
} Person;


void readFile(Person people[], int* count) {
	FILE* file = fopen("People_in.txt", "r");
	if (file == NULL) {
		printf("Error. The file cannot be opened\n");
		return 0;
	}
	*count = 0;
	while (fscanf(file, "%14s %d", people[*count].name, &people[*count].age) == 2) {
		(*count)++;
	}
	fclose(file);
	return 1;
}


void print(Person people[], int count) {
	for (int i = 0; i < count; i++) {
		printf("%s %d\n", people[i].name, people[i].age);
	}
}


void writeFile(Person people[], int count) {
	FILE* file = fopen("People_out.txt", "w");
	if (file == NULL) {
		printf("Error. It is impossible to create a file\n");
		return 0;
	}
	for (int i = 0; i < count; i++) {
		fprintf(file, "%s %d\n", people[i].name, people[i].age);
	}
	fclose(file);
	printf("The result is written to a file\n");
	return 1;
}


void insertionSort(Person people[], int count) {
	for (int i = 1; i < count; i++) {
		int age = people[i].age;
		Person elem = people[i];
		int j = i - 1;
		while (j >= 0 && people[j].age < age) {
			people[j + 1] = people[j];
			j = j - 1;
		}
		people[j + 1] = elem;
	}
}


int partition(Person people[], int left, int right) {
	int pivot = people[right].age;
	int i = left - 1;
	for (int j = left; j < right; j++) {
		if ((people[j].age >= pivot)) {
			i++;
			Person temp = people[i];
			people[i] = people[j];
			people[j] = temp;
		}
	}
	Person temp = people[i + 1];
	people[i + 1] = people[right];
	people[right] = temp;
	return i + 1;
}

void quickSort(Person people[], int left, int right) {
	if (left < right) {
		int pi = partition(people, left, right);
		quickSort(people, left, pi - 1);
		quickSort(people, pi + 1, right);
	}
}

void quickSortWrapper(Person people[], int count) {
	quickSort(people, 0, count - 1);
}


void bubbleSort(Person people[], int count) {
	for (int i = 0; i < count - 1; i++) {
		int flag = 0;
		for (int j = 0; j < count - i - 1; j++) {
			if (people[j].age < people[j + 1].age) {
				Person temp = people[j];
				people[j] = people[j + 1];
				people[j + 1] = temp;
				flag = 1;
			}
		}
		if (!flag) {
			break;
		}
	}
}


void menu() {
	printf("\nChoosing a sorting method\n");
	printf("Sorting method:\n");
	printf("1.Insertion sort\n");
	printf("2.Hoare sort\n");
	printf("3.Bubble sort\n");
	printf("4.Exit the programm\n");
	printf("\n");
}


int main() {
	Person people[50];
	int count = 0;
	int choice = 0;

	readFile(people, &count);
	
	while (1) {
		menu();
		scanf("%d", &choice);
		while (choice < 1 || choice > 4) {
			printf("Error. Select an action (1-4)\n");
			clearInputBuffer();
			scanf("%d", &choice);
		}
		switch (choice) {
		case 1: {
			clock_t start1 = clock(); 
			insertionSort(people, count);
			clock_t end1 = clock();
			double time1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
			printf("%lf\n", time1);
			print(people, count);
			printf("\n");
			writeFile(people, count);
			break;
		}
		case 2: {
			clock_t start2 = clock();
			quickSortWrapper(people, count);
			clock_t end2 = clock();
			double time2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
			printf("%lf\n", time2);
			print(people, count);
			printf("\n");
			writeFile(people, count);
			break;
		}
		case 3: {
			clock_t start3 = clock();
			bubbleSort(people, count);
			clock_t end3 = clock();
			double time3 = (double)(end3 - start3) / CLOCKS_PER_SEC;
			printf("%lf\n", time3);
			print(people, count);
			printf("\n");
			writeFile(people, count);
			break;
		}
		case 4:
			return 0;
		}
	}
}
