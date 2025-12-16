#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define INPUT_FILE "People_in.txt"
#define OUTPUT_FILE "People_out.txt"

struct Person {
	char name[20];
	unsigned int age;
};

void swap(struct Person* a, struct Person* b) {
	struct Person temp = *a;
	*a = *b;
	*b = temp;
}

void selectionSortPersons(struct Person* persons, size_t persons_count) {
	for (size_t i = 0; i < persons_count - 1; ++i) {
		size_t max_ind = i;

		for (size_t j = i; j < persons_count; ++j) {
			if (persons[max_ind].age < persons[j].age) {
				max_ind = j;
			}
		}

		swap(&persons[max_ind], &persons[i]);
	}
}

void insertionSortPersons(struct Person* persons, size_t persons_count) {
	for (size_t i = 1; i < persons_count; ++i) {
		for (size_t j = i; persons[j].age > persons[j - 1].age; --j) {
				swap(&persons[j], &persons[j-1]);        
		}
	}
}

size_t partition(struct Person* persons, int low, int hight) {
	unsigned int pivot = persons[low].age;
	int i = low - 1;
	int j = hight + 1;

	while (1) {
		do {
			i++;
		} while (persons[i].age > pivot);

		do {
			j--;
		} while (persons[j].age < pivot);

		if (i >= j) {
			return j;
		}

		swap(&persons[low], &persons[hight]);
	}
}

void quickSort(struct Person* persons, int low, int hight) {
	srand(time(0));

	if (low < hight) {
		size_t pivot = partition(persons, low, hight);

		quickSort(persons, low, pivot);
		quickSort(persons, pivot + 1, hight);
	}
}

void readPersons(struct Person* persons, size_t* persons_count, char* file_name) {
	FILE* file = fopen(file_name, "r");

	for (size_t i = 0; fscanf(file, "%s %u", persons[i].name, &persons[i].age) != EOF; ++i) {
		*persons_count += 1;
	}

	fclose(file);
}

void writePersons(struct Person* persons, size_t persons_count, char* file_name) {
	FILE* file = fopen(file_name, "w");

	for (size_t i = 0; i < persons_count; ++i) {
		fprintf(file, "%s %u\n", persons[i].name, persons[i].age);
		fprintf(stdout, "%s %u\n", persons[i].name, persons[i].age);
	}

	fclose(file);
}

void clearInput() {
	char ch = '\0';
	while ((ch = getchar()) != '\n' && ch != EOF);
}

unsigned char selectSortType() {
	unsigned char sort_num = 0;

	printf("===[SELECT SORT]===\n");
	printf("1. Quick sort\n");
	printf("2. Selection sort\n");
	printf("3. Insertion sort\n\n");
	printf("Enter sort number: ");
	while (!scanf("%hhu", &sort_num) || sort_num < 1 || sort_num > 3) {
		clearInput();
		printf("Encorrect enter. Enter sort number: ");
	}
	clearInput();

	return sort_num;
}

unsigned char selectIsExit() {
	unsigned char is_exit = 0;

	printf("Select action: \n");
	printf("1. Sort new list (First, edit the People_in.txt)\n");
	printf("2. Exit\n");
	printf("Enter you choose: ");
	while (!scanf("%hhu", &is_exit) || is_exit < 1 || is_exit > 2) {
		clearInput();
		printf("Encorrect enter. Enter you choose: ");
	}
	clearInput();

	return is_exit - 1;
}

void main() {
	unsigned char is_exit = 0;
	struct Person persons[50] = { 0 };
	size_t persons_count = 0;

	readPersons(persons, &persons_count, INPUT_FILE);

	while (!is_exit) {

		clock_t start = 0;
		clock_t end = 0;

		switch (selectSortType()) {
		case 1:
			start = clock();
			quickSort(persons, 0, persons_count - 1);
			end = clock();
			break;
		case 2:
			start = clock();
			selectionSortPersons(persons, persons_count);
			end = clock();
			break;
		case 3:
			start = clock();
			insertionSortPersons(persons, persons_count);
			end = clock();
			break;
		}

		writePersons(persons, persons_count, OUTPUT_FILE);
		printf("\nTime: %lf\n\n", (double)(end - start) / CLOCKS_PER_SEC);
		is_exit = selectIsExit();
	}
}