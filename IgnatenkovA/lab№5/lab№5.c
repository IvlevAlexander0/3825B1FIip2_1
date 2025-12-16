#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct Person {
    char name[50];
    int age;
};

void bubbleSort(struct Person arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].age > arr[j + 1].age) {
                struct Person temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void insertionSort(struct Person arr[], int n) {
    for (int i = 1; i < n; i++) {
        struct Person k = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].age > k.age) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = k;
    }
}
void merge(struct Person arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    struct Person* L = malloc(n1 * sizeof(struct Person));
    struct Person* R = malloc(n2 * sizeof(struct Person));
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].age <= R[j].age) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}
void mergeSort(struct Person arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
void copyPeople(struct Person t[], struct Person f[], int n) {
    for (int i = 0; i < n; i++) {
        t[i] = f[i];
    }
}
void printPeople(struct Person arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", arr[i].name, arr[i].age);
    }
}
void writePeopleToFile(struct Person arr[], int n, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        printf("Couldn't open the file for writing\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(f, "%s %d\n", arr[i].name, arr[i].age);
    }
    fclose(f);
}


int main() {
    FILE* inputFile = fopen("People_in.txt", "r");
    if (inputFile == NULL) {
        printf("Couldn't open the file\n");
        return 1;
    }
    struct Person people[50];
    int count = 0;
    while (count < 50 && fscanf(inputFile, "%49s %d", people[count].name, &people[count].age) == 2) {
        count++;
    }
    fclose(inputFile);
    if (count == 0) {
        printf("file is empty\n");
        return 1;
    }
    struct Person sorted[50];
    int choice;
    clock_t start;
    clock_t end;
    double time;
    do {
        printf("\nMenu\n");
        printf("1. Bubble sorting\n");
        printf("2. insertion sorting\n");
        printf("3. Merge sorting\n");
        printf("0. exit\n");
        printf("Choose a sorting method: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }
        if (choice == 0) {
            break;
        }
        copyPeople(sorted, people, count);
        switch (choice) {
        case 1:
            start = clock();
            bubbleSort(sorted, count);
            end = clock();
            printf("\nBubble sorting:\n");
            break;
        case 2:
            start = clock();
            insertionSort(sorted, count);
            end = clock();
            printf("\nInsertion sorting:\n");
            break;
        case 3:
            start = clock();
            mergeSort(sorted, 0, count - 1);
            end = clock();
            printf("\nMerge sorting:\n");
            break;
        default:
            printf("Wrong choice\n");
            continue;
        }
        time = ((double)(end - start)) / CLOCKS_PER_SEC;
        printPeople(sorted, count);
        writePeopleToFile(sorted, count, "People_out.txt");
        printf("Sorting time: %.6f seconds\n", time);
    } while (1);
}