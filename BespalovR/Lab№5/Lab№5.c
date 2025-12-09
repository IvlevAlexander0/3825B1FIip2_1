#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
struct row {
	//Suggested that names are less than 16 in length.
	char name[16];
	int age;
};

int choose_sort() {
	printf("Choose sorting algorythm:\n");
	printf("1 - Quick sort.\n");
	printf("2 - Selection sort.\n");
	printf("3 - Merge sort.\n");
	int t = 0;
	while (scanf("%d", &t) != 1 || t > 3 || t < 1) {
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
		int t = partition(arr, low, high);
		quick_sort(arr, low, t - 1);
		quick_sort(arr, t + 1, high);
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

void merge(struct row* arr, int left, int mid, int right) {
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;
	//passive debugging of VS gives warnings about leftarr and rightarr
	struct row* left_arr = calloc(n1, sizeof(struct row));
	struct row* right_arr = calloc(n2, sizeof(struct row));
	for (i = 0; i < n1; i++)
		left_arr[i] = arr[left + i];
	for (j = 0; j < n2; j++)
		right_arr[j] = arr[mid + 1 + j];
		i = 0;
		j = 0;
		k = left;
	while (i < n1 && j < n2) {
		if (left_arr[i].age <= right_arr[j].age) {
			arr[k] = left_arr[i++];
		}
		else {
			arr[k] = right_arr[j++];
		}
		k++;
	}
	while (i < n1) {
		arr[k++] = left_arr[i++];
	}
	while (j < n2) {
		arr[k++] = right_arr[j++];
	}
	free(left_arr);
	free(right_arr);
}

void merge_sort(struct row* arr, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

int read_file(struct row* arr) {
	FILE* fptr = fopen("People_in.txt", "r+");
	if (fptr == NULL) {
		return 0;
	}
	int n = 0;
	//Suggested that file is formated the right way of "word number endline".
	while (fscanf(fptr, "%s %d", &arr[n].name, &arr[n].age) == 2) {
		n++;
		if (n > 50) {
			return -1;
		}
	}
	fclose(fptr);
	fptr = NULL;
	return n;
}

void write_file(struct row* arr, int n) {
	FILE* fptr = fopen("People_out.txt", "w+");
	//Suggested that fptr is not NULL and writing goes without errors.
	for (int i = 0; i < n; ++i) {
		fprintf(fptr, "%s\t%d\n", arr[i].name,arr[i].age);
	}
	fclose(fptr);
	fptr = NULL;
}

int main() {
	for (;;) {
		struct row* arr = calloc(51, sizeof(struct row));
		if (arr == NULL) {
			printf("\nCould not allocate memory.\n");
			return -1;
		}

		int n = read_file(arr);
		if (n == 0) {
			printf("\nCould not read file.\n");
			return -1;
		}
		else if (n == -1) {
			printf("Incorrect data format.\n");
			return -1;
		}

		int option = choose_sort();
		clock_t t = clock();
		//Good place for function pointer but switch case will do the thing as well.
		switch (option) {
		case 1:
			quick_sort(arr, 0, n - 1);
			break;
		case 2:
			selection_sort(arr, n);
			break;
		case 3:
			merge_sort(arr, 0, n-1);
			break;
		}
		t = clock() - t;
		double time = ((double)t) / CLOCKS_PER_SEC;

		write_file(arr, n);

		printf("\n");
		for (int i = 0; i < n; ++i) {
			printf("%s\t%d\n", arr[i].name, arr[i].age);
		}

		printf("\nSorted data is stored in People_out.txt.\n");
		printf("Sorting took %lf seconds\n", time);
		//With my limited testing time is always 0 seconds. dunno whether or not it's supposed to be like that.
		printf("\nWould you like to sort again with different sorting algorythm? (y/n)\n");
		char c;
		while ((c = getchar()) != '\n') {}
		while ( scanf("%c", &c ) != 1 || (c != 'n' && c != 'y')) {
			printf("Incorrect input. Please try again.\n");
			while ((c = getchar()) != '\n') {}
		}
		if (c == 'n') {
			break;
		}
		free(arr);
		arr = NULL;
	}
	return 0;
}
