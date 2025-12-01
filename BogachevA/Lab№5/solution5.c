#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define namelen 30
#define max1 50
typedef struct {
	char name[namelen];
	int age;
} person;
int readfile(const char* filename, person people[]) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) { printf("File is empty\n"); return -1; }
	char line[100];
	int count = 0;
	while (fgets(line, sizeof(line), file) != NULL && count < max1) {
		int len = 0;
		while (line[len] != '\0' && line[len] != '\n') { // esli ne ubrat' \n ne perevidutsya atoi 
			len++;
		}
		line[len] = '\0';
		int space = -1;
		for (int i = len - 1; i >= 0; i--) {
			if (line[i] == ' ') {
				space = i;
				break;
			}
		}
		int namelength = space;
		if (namelength >= namelen) {
			namelength = namelen - 1; // esli imya slishkom dlinoe pridetsya urezet'
		}
		for (int i = 0; i < namelength; i++) {
			people[count].name[i] = line[i];
		}
		people[count].name[namelength] = '\0';
		char agestr[4];
		int agefigue = 0;
		for (int i = space + 1; i <= len && agefigue < 3; i++) {
			if (line[i] != '\0') {
				agestr[agefigue++] = line[i];
			}
		}
		agestr[agefigue] = '\0';
		people[count].age = atoi(agestr);
		count++;
	}
	fclose(file);
	return count;
}
void merge(person arr[], int left, int mid, int right) {
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;
	person* leftarr = (person*)malloc(n1 * sizeof(person));
	person* rightarr = (person*)malloc(n2 * sizeof(person));
	for (i = 0; i < n1; i++)
		leftarr[i] = arr[left + i];
	for (j = 0; j < n2; j++)
		rightarr[j] = arr[mid + 1 + j];
	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2) {
		if (leftarr[i].age <= rightarr[j].age) {
			arr[k] = leftarr[i];
			i++;
		}
		else {
			arr[k] = rightarr[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		arr[k] = leftarr[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = rightarr[j];
		j++;
		k++;
	}
	free(leftarr);
	free(rightarr);
}
void merge_sort(person arr[], int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}
void call_merge_sort(person arr[], int n) {
	merge_sort(arr, 0, n - 1);
}
void bubble_sort(person arr[], int n) {
	int i, j;
	person temp;
	for (i = 0; i < n - 1; i++) {
		int flag = 0;
		for (j = 0; j < n - i - 1; j++) {
			if (arr[j].age > arr[j + 1].age) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				flag = 1;
			}
		}
		if (!flag) {
			break;
		}
	}
}
void comb_sort(person arr[], int n) {
	double factor = 1.2474404;
	int step = n - 1;
	person temp;
	while (step >= 1) {
		for (int i = 0; i + step < n; i++) {
			if (arr[i].age > arr[i + step].age) {
				temp = arr[i];
				arr[i] = arr[i + step];
				arr[i + step] = temp;
			}
		}
		step = (int)(step / factor);
	}
}
void writedown(const char* filename, person people[], int n) {
	FILE* file = fopen(filename, "w");
	for (int i = 0; i < n; i++) {
		fprintf(file, "%s %d\n", people[i].name, people[i].age);
	}
	fclose(file);
}
void print_array(person arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%s %d\n", arr[i].name, arr[i].age);
	}
}
void copy_array(person dest[], person src[], int count) {
	for (int i = 0; i < count; i++) {
		dest[i] = src[i];
	}
}
void sorting(person people[], int n, int choice) {
	clock_t start, end;
	double sortingtime;
	person arr[max1];
	copy_array(arr, people, n);
	switch (choice) {
	case 1:
		start = clock();
		bubble_sort(arr, n);
		end = clock();
		break;
	case 2:
		start = clock();
		comb_sort(arr, n);
		end = clock();
		break;
	case 3:
		start = clock();
		call_merge_sort(arr, n);
		end = clock();
		break;
	default:
		return;
	}
	sortingtime = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Sorted list\n");
	print_array(arr, n);
	printf("Sorting time %lf\n", sortingtime);
	writedown("People_out.txt", arr, n);
	printf("Data was written to People_out.txt\n");
}
int main() {
	int choice;
	person people[max1];
	person refresh[max1];
	int count = readfile("People_in.txt", people);
	copy_array(refresh, people, count);
	do {
		printf("Choose the method of sorting\n");
		printf("'1' - bubble sort\n");
		printf("'2' - comb sort\n");
		printf("'3' - merge sort\n");
		printf("'0' - if u want to exit\n");
		if (scanf("%d", &choice) != 1) {
			printf("Incorrect input\n");
			int c;
			while ((c = getchar()) != '\n' && c != EOF) {};
			continue;
		}
		if (choice >= 1 && choice <= 3) {
			copy_array(people, refresh, count);
			sorting(people, count, choice);
		}
		else if (choice == 0) {
			printf("Exit.\n");
		}
		else {
			printf("Incorrect choice.\n");
		}

	} while (choice != 0);
	return 0;
}