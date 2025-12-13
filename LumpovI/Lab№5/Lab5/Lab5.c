#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

void cleanBuffer() {
	int a;
	while ((a = getchar()) != '\n' && a != EOF);
}

struct person {
	char name[50];
	int age;
};

int PeopleIn(struct person people[]) {
	FILE* file = fopen("People_in.txt", "r");
	if (file == NULL) { 
		printf("File cannot be read");
		return 1;
	}
	
	int n = 0;
	while (fscanf(file, "%s %d", people[n].name, &people[n].age) != EOF && n < 50) {
		n++;
	}
	fclose(file);
	return n;
}

void PeopleOut(struct person people[], int n) {
	FILE* file = fopen("People_out.txt", "w");
	if (file == NULL) {
		printf("Something went wrong!");
		return;
	}

	for (int i = 0; i < n; i++) {
		fprintf(file, "%s %d\n", people[i].name, people[i].age);
	}
	fclose(file);
	printf("The list was written in file. Check People_out.txt\n");
}

void list_print(struct person people[], int n) {
	printf("Sorted list of people:\n");
	for (int i = 0; i < n; i++) {
		printf("%s %d\n", people[i].name, people[i].age);
	}
}

void copy_ppl(struct person dest[], struct person from[], int count) {
	for (int i = 0; i < count; i++) {
		strcpy(dest[i].name, from[i].name);
		dest[i].age = from[i].age;
	}
}

void swap(struct person* ppl1, struct person* ppl2) {
	struct person c = *ppl1;
	*ppl1 = *ppl2;
	*ppl2 = c;
}

double selection_sort(struct person ppl[], size_t n) {
	clock_t start, end;
	start = clock();
	for (size_t i = 0; i < n - 1; i++) {
		int ind_min = i;
		for (size_t j = i + 1; j < n; j++) {
			if (ppl[ind_min].age > ppl[j].age) {
				ind_min = j;
			}
		}
		swap(&ppl[ind_min], &ppl[i]);
	}
	end = clock();
	return ((double)(end - start)) / CLOCKS_PER_SEC;
}

void merge(struct person ppl[], int lt, int mid, int rt) {
	int n1 = mid - lt + 1;
	int n2 = rt - mid;
	struct person* leftarr = (struct person*)malloc(n1 * sizeof(struct person));
	struct person* rightarr = (struct person*)malloc(n2 * sizeof(struct person));
	for (int i = 0; i < n1; i++) {
		leftarr[i] = ppl[lt + i];
	}
	for (int j = 0; j < n2; j++) {
		rightarr[j] = ppl[mid + 1 + j];
	}
	int a = 0;
	int b = 0;
	int k = lt;
	while (a < n1 && b < n2) {
		if (leftarr[a].age <= rightarr[b].age) {
			ppl[k] = leftarr[a];
			a++;
		}
		else {
			ppl[k] = rightarr[b];
			b++;
		}
		k++;
	}
	while (a < n1) {
		ppl[k] = leftarr[a];
		a++;
		k++;
	}
	while (b < n2) {
		ppl[k] = rightarr[b];
		b++;
		k++;
	}
	free(leftarr);
	free(rightarr);
}

void merge_sort_helper(struct person ppl[], int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		merge_sort_helper(ppl, left, mid);
		merge_sort_helper(ppl, mid + 1, right);
		merge(ppl, left, mid, right);
	}
}

double merge_sort(struct person ppl[], int n) {
	clock_t start, end;
	start = clock();
	merge_sort_helper(ppl, 0, n - 1);
	end = clock();
	return ((double)(end - start)) / CLOCKS_PER_SEC;
}

double bubble_sort(struct person ppl[], size_t n) {
	clock_t start, end;
	start = clock();

	for (int i = 0; i < n - 1; ++i) {
		int flag = 0;
		for (int j = 0; j < n - i - 1; ++j) {
			if (ppl[j].age > ppl[j + 1].age) {
				swap(&ppl[j], &ppl[j + 1]);
				flag = 1;
			}
		}
		if (!flag) {
			break;
		}
	}
	end = clock();
	return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
	struct person ppl[50];
	struct person ppl_srt[50];
	int count;
	int flag;
	int operation;
	printf("------ LIST SORT ------\n");
	count = PeopleIn(ppl);
	if (count == 0) { printf("Something went wrong!!!"); return -1; }	

	do {
		printf("Please select the type of sort:\n");
		printf("1 - selection sort\n");
		printf("2 - merge sort\n");
		printf("3 - bubble sort\n");
		while (scanf("%d", &operation) != 1 || operation < 1 || operation > 3) {
			printf("Error: Inccorect input!!! Please enter only a number from 1 to 3\n");
			cleanBuffer();
		}
		copy_ppl(ppl_srt, ppl, count);
		flag = 0;

		switch (operation) {
		case 1:
			printf("Sorting...\n");
			double sort_time = selection_sort(ppl_srt, count);
			list_print(ppl_srt, count);
			printf("---------------\n");

			PeopleOut(ppl_srt, count);
			printf("Data: time of sort - %.6lf sec.\n", sort_time);

			printf("Do you want to try another sorting method? Input 1 - yes; 0 - shut out system: ");
			scanf("%d", &flag);
			cleanBuffer();
			break;

		case 2:
			printf("Sorting...\n");
			double sort_time2 = merge_sort(ppl_srt, count);
			list_print(ppl_srt, count);
			printf("---------------\n");

			PeopleOut(ppl_srt, count);
			printf("Data: time of sort - %.6lf sec.\n", sort_time2);

			printf("Do you want to try another sorting method? if you want to use a different sort, enter 1, if not, enter 0.: ");
			scanf("%d", &flag);
			cleanBuffer();
			break;

		case 3:
			printf("Sorting...\n");
			double sort_time3 = bubble_sort(ppl_srt, count);
			list_print(ppl_srt, count);
			printf("---------------\n");

			PeopleOut(ppl_srt, count);
			printf("Data: time of sort - %.6lf sec.\n", sort_time3);

			printf("Do you want to try another sorting method? if you want to use a different sort, enter 1, if not, enter 0.: ");
			scanf("%d", &flag);
			cleanBuffer();
			break;
		}

	} while (flag == 1);
	printf("GL HF!!!\n");
	return 0;
}