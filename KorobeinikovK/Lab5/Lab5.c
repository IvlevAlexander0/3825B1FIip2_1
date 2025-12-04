#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PEOPLE 50
#define MAX_NAME_LEN 30

struct per {
	char name[MAX_NAME_LEN];
	int age;
};
int partition(struct per arr[], int l, int r) {
	struct per a = arr[r];
	int i = l - 1;
	for (int j = l; j < r; j++) {
		if (arr[j].age >= a.age) {
			i++;
			struct per temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	struct per temp = arr[i + 1];
	arr[i + 1] = arr[r];
	arr[r] = temp;
	return i + 1;
}
void bubble_sort(struct per arr[], int sz) {
	for (int i = 0; i < sz - 1; ++i) {
		int flag = 1;
		for (int j = sz - 1; (j > i); --j) {
			if (arr[j - 1].age < arr[j].age) {
				struct per temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
				flag = 0;
			}
			
		}
		if (flag) {
			break;
		}
	}
}
void qsort(struct per arr[], int l, int r) {
	if (l < r) {
		int q = partition(arr, l, r);
		qsort(arr, l, q - 1);
		qsort(arr, q + 1, r);
	}
}
void ins_sort(struct per arr[], int s) {
	for (int i = 0; i < s; ++i) {
		for (int j = i; (j > 0) && (arr[j - 1].age < arr[j].age); --j) {
			struct per temp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = temp;
		}
	}
}
int read_file(const char* fname, struct per people[]) {
	FILE* fl = fopen(fname, "r");
	if (fl == NULL) {
		printf("Error: Failed to open file %s\n", fname);
		return -1;
	}
	int count = 0;
	while (fscanf(fl, "%29s %d", people[count].name, &people[count].age) == 2) {  // ИСПРАВЛЕНО: убрал & перед name
		count++;
		if (count >= MAX_PEOPLE) {
			break;
		}
	}
	fclose(fl);
	return count;
}
void write_file(const char* fname, struct per people[], int count) {
	FILE* fl = fopen(fname, "w");
	if (fl == NULL) {
		printf("Error: Failed to create file %s\n", fname);
		return;
	}
	for (int i = 0; i < count; i++) {
		fprintf(fl, "%s %d\n", people[i].name, people[i].age);
	}
	fclose(fl);
	printf("The result is written to a file %s\n", fname);
}
void print_people(struct per people[], int count) {
	printf("Sorted list (age descending):\n");
	printf("----------------------------\n");
	for (int i = 0; i < count; i++) {
		printf("%s %d\n", people[i].name, people[i].age);
	}
	printf("----------------------------\n");
}
void menu() {
	printf("\nSorting selection menu:\n");
	printf("1.Bubble sorting\n");
	printf("2.Insertion sorting\n");
	printf("3.Quick sorting (Hoare)\n");
	printf("0.Exit\n");
	printf("Select sorting:");
}
int main() {
	char in[] = "People_in.txt";
	char out[] = "People_out.txt";
	struct per people[MAX_PEOPLE];
	struct per orig_people[MAX_PEOPLE];
	int count = 0;
	int c = 0;
	count = read_file(in, people);
	if (count <= 0) {
		printf("Could not read data from file or file is empty\n");
		return 1;
	}
	memcpy(orig_people, people, sizeof(struct per) * count);
	printf("People data sorting program\n");
	printf("===========================\n");
	printf("Read %d records from file %s\n", count, in);
	printf("Sorting direction:\n");
	do {
		menu();
		if (scanf("%d", &c) != 1) {
			printf("Invalid input!\n");
			while (getchar() != '\n');
			continue;
		}
		while (getchar() != '\n');
		if (c == 0) {
			printf("The end!\n");
			break;
		}
		if (c < 1 || c > 3) {
			printf("Incorrect operation selection!\n");
			continue;
		}
		memcpy(people, orig_people, sizeof(struct per) * count);
		clock_t start, end;
		double sort_time;
		start = clock();
		switch (c) {
		case 1:
			bubble_sort(people, count);
			printf("Bubble sort applied\n");
			break;
		case 2:
			ins_sort(people, count);
			printf("Insertion sort applied\n");
			break;
		case 3:
			qsort(people, 0, count - 1);
			printf("Quick sort applied\n");
			break;
		}
		end = clock();
		sort_time = ((double)(end - start)) / CLOCKS_PER_SEC;
		print_people(people, count);
		printf("Sorting time: %.6f seconds\n", sort_time);
		write_file(out, people, count);
	} while (c != 0);
	return 0;
}
