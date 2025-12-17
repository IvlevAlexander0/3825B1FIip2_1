#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Person {
    char name[50];
    int age;
};

int readfile(struct Person** arr, char* fileName) {
    FILE* f = fopen(fileName, "r");
    if (f == NULL) {
        printf("Error of the openning of file\n");
        return 0;
    }
    struct Person temp[50];
    int count = 0;
    while (count < 50) {
        int result = fscanf(f, "%49s %d", temp[count].name, &temp[count].age);
        if (result != 2) {
            break;
        }
        if (temp[count].age < 0 || temp[count].age > 150) {
            printf("Might be incorrect age of %s\n", temp[count].name);
        }
        count++;
    }
    fclose(f);
    if (count < 10) {
        printf("Error: file should contain from 10 to 50 writings\n");
        return 0;
    }
    *arr = (struct Person*)malloc(count * sizeof(struct Person));
    if (*arr == NULL) {
        printf("Error of allocation of memory\n");
        return 0;
    }
    for (int i = 0; i < count; i++) {
        (*arr)[i] = temp[i];
    }
    printf("There are %d records in file \n", count);
    return count;
}

void writefile(struct Person* arr, int count, char* filename) {
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error of creating of file\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s %d\n", arr[i].name, arr[i].age);
    }

    fclose(f);
}

void printdata(struct Person* arr, int count) {
    for (int i = 0; i < count; i++) {
        printf("%s %d\n", arr[i].name, arr[i].age);
    }
}

struct Person* copy(struct Person* arr, int count) {
    struct Person* newarr = (struct Person*)malloc(count * sizeof(struct Person));
    if (newarr == NULL) {
        printf("Error: Cannot allocate memory for copying\n");
        return NULL;
    }
    for (int i = 0; i < count; i++) {
        newarr[i] = arr[i];
    }
    return newarr;
}

int check(int min, int max) {
    int num = 0;
    while (1) {
        int result = scanf("%d", &num);
        while (getchar() != '\n');
        if (result != 1) {
            printf("Error: Please enter a valid number: ");
            continue;
        }
        if (num < min || num > max) {
            printf("Error: Number must be between %d and %d. Try again: ", min, max);
            continue;
        }
        break;
    }
    return num;
}

void separatearr(struct Person* arr, int count, struct Person** arr1, struct Person** arr2, int* count1, int* count2) {
    *count1 = (count + 1) / 2;
    *count2 = count / 2;
    *arr1 = (struct Person*)malloc(*count1 * sizeof(struct Person));
    *arr2 = (struct Person*)malloc(*count2 * sizeof(struct Person));
    if (*arr1 == NULL || *arr2 == NULL) {
        printf("Error: memory allocation failed\n");
        return;
    }
    int index1 = 0;
    int index2 = 0;
    for (int i = 0; i < count; i++) {
        if (i % 2 == 0) {
            (*arr1)[index1] = arr[i];
            index1++;
        }
        else {
            (*arr2)[index2] = arr[i];
            index2++;
        }
    }
}

void mergearr(struct Person* arr, int count, struct Person* arr1, struct Person* arr2, int count1, int count2) {
    int index1 = 0;
    int index2 = 0;
    for (int i = 0; i < count; i++) {
        if (i % 2 == 0) {
            arr[i] = arr1[index1];
            index1++;
        }
        else {
            arr[i] = arr2[index2];
            index2++;
        }
    }
}

void bubblesort1(struct Person* arr, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j].age > arr[j + 1].age) {
                struct Person temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void bubblesort2(struct Person* arr, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j].age < arr[j + 1].age) {
                struct Person temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionsort1(struct Person* arr, int count) {
    for (int i = 1; i < count; i++) {
        struct Person current = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].age > current.age) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = current;
    }
}

void insertionsort2(struct Person* arr, int count) {
    for (int i = 1; i < count; i++) {
        struct Person current = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].age < current.age) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = current;
    }
}

int partition1(struct Person* arr, int low, int high) {
    int pivot = arr[high].age;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].age <= pivot) {
            i++;
            struct Person temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    struct Person temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quicksort1(struct Person* arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition1(arr, low, high);
        quicksort1(arr, low, pivotIndex - 1);
        quicksort1(arr, pivotIndex + 1, high);
    }
}

int partition2(struct Person* arr, int low, int high) {
    int pivot = arr[high].age;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].age >= pivot) {
            i++;
            struct Person temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    struct Person temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quicksort2(struct Person* arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition2(arr, low, high);
        quicksort2(arr, low, pivotIndex - 1);
        quicksort2(arr, pivotIndex + 1, high);
    }
}

double timeofsorting(struct Person* arr, int count, int method) {
    clock_t start = clock();
    struct Person* arr1 = NULL;
    struct Person* arr2 = NULL;
    int count1 = 0;
    int count2 = 0;
    separatearr(arr, count, &arr1, &arr2, &count1, &count2);
    if (method == 1) {
        bubblesort2(arr1, count1);
        bubblesort1(arr2, count2);
    }
    else if (method == 2) {
        insertionsort2(arr1, count1);
        insertionsort1(arr2, count2);
    }
    else if (method == 3) {
        if (count1 > 0) {
            quicksort2(arr1, 0, count1 - 1);
        }
        if (count2 > 0) {
            quicksort1(arr2, 0, count2 - 1);
        }
    }
    mergearr(arr, count, arr1, arr2, count1, count2);
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    free(arr1);
    free(arr2);
    return time;
}

int main() {
    struct Person* arr = NULL;
    int count = 0;
    count = readfile(&arr, "people_in.txt");
    if (count == 0) {
        printf("The wrong file\n");
        return 1;
    }
    do {
        printf("1. Show original data\n");
        printf("2. Choose sorting method and sort\n");
        printf("3. Exit program\n");
        printf("Enter your choice (1-3): ");
        int mode = check(1, 3);
        if (mode == 1) {
            printdata(arr, count);
        }
        else if (mode == 2) {
            int sort = 1;
            do {
                printf("1. Bubble sort\n");
                printf("2. Insertion sort\n");
                printf("3. Quick sort (Hoare)\n");
                printf("4. Return to main menu\n");
                printf("Enter your choice (1-4): ");
                int method = check(1, 4);
                if (method == 4) {
                    sort = 0;
                    break;
                }
                struct Person* copyarray = copy(arr, count);
                if (copyarray == NULL) {
                    printf("Error creating data copy\n");
                    continue;
                }
                double time = timeofsorting(copyarray, count, method);
                printf("Sorting time: %.12f seconds\n", time);
                printdata(copyarray, count);
                writefile(copyarray, count, "people_out.txt");
                free(copyarray);
                printf("Choose the action:\n");
                printf("1. Try another sorting method\n");
                printf("2. Go to main menu\n");
                printf("Enter your choice (1 or 2): ");
                int newchoice = check(1, 2);
                if (newchoice == 2) {
                    sort = 0;
                }

            } while (sort == 1);
        }
        else if (mode == 3) {
           break;
        }
    } while (1);
    free(arr);
    return 0;
}