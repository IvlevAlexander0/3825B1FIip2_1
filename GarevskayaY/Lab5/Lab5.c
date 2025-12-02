#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



#define MAX_NAME_LEN 50
#define MAX_PEOPLE 50

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

typedef struct {
    char* name;
    int age;
} Person;

void swap(Person* a, Person* b) {
    Person temp = *a;
    *a = *b;
    *b = temp;
}

//Сортировки по возрастанию (номер в списке 6, четный)

// Сортировка выбором
void insertion_sort(Person arr[], int n) {
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0; --j) {
            if (arr[j - 1].age > arr[j].age) {
                swap(&arr[j - 1], &arr[j]);
            }
            else {
                break;
            }
        }
    }
}

// Сортировка слиянием
void merge(Person arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    Person *L = (Person*)malloc(n1 * sizeof(Person));
    Person *R = (Person*)malloc(n2 * sizeof(Person));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;

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

void mergesort(Person arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Сортировка пузырьком (по выбору)
void bubble_sort(Person arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = n - 2; j >= i; --j) {
            if (arr[j].age > arr[j + 1].age) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}
int read_file(const char* filename, Person people[]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }

    int count = 0;
    while (count < MAX_PEOPLE && fscanf(file, "%s %d", people[count].name, &people[count].age) == 2) {
        count++;
    }

    fclose(file);
    return count;
}

void write_file(const char* filename, Person people[], int count) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Cannot create file %s\n", filename);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", people[i].name, people[i].age);
    }

    fclose(file);
}

void print_people(Person people[], int count) {
    printf("\nSorted list of people:\n");
    for (int i = 0; i < count; i++) {
        printf("%s %d\n", people[i].name, people[i].age);
    }
}

void copy_people(Person dest[], Person src[], int count) {
    for (int i = 0; i < count; i++) {
        dest[i] = src[i];
    }
}


int main() {

    Person people[MAX_PEOPLE];
    Person temp_people[MAX_PEOPLE];
    int count = 0;
    int choice;
    int sort_again = 1;

    count = read_file("People_in.txt", people);
    if (count == 0) {
        printf("Error of reading file. Make sure file 'People_in.txt' in format: Name1 Age1\n");
        return 1;
    }

    printf("Successfully read people from file.\n");

    while (sort_again) {
        printf("1. Bubble sort\n");
        printf("2. Insertion sort\n");
        printf("3. Merge sort\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        clearInputBuffer();

        if (choice == 0) {
            break;
        }

        if (choice < 1 || choice > 3) {
            printf("Error. Please enter 0-3.\n");
            continue;
        }

        copy_people(temp_people, people, count);

        clock_t start_time, end_time;
        double sorting_time;
        start_time = clock();

        switch (choice) {
        case 1:
            printf("\nSorting with bubble sort\n");
            bubble_sort(temp_people, count);
            break;

        case 2: 
            printf("\nSorting with insertion sort\n");
            insertion_sort(temp_people, count);
            break;

        case 3:
            printf("\nSorting with merge sort\n");
            mergesort(temp_people, 0, count - 1);
            break;
        }

        end_time = clock();
        sorting_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        print_people(temp_people, count);

        write_file("People_out.txt", temp_people, count);
        printf("Results saved to 'People_out.txt'\n");
        printf("Time: %.8f seconds\n", sorting_time);

        printf("\nIf you want to sort again, enter 1, else enter 0.");
        scanf("%d", &sort_again);
        clearInputBuffer();
    }

    printf("\nGoodbye.");
    return 0;
}



