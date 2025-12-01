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
struct Person {
	char name[50];  
	int age;        
};
int read_people(struct Person people[]) {
    FILE* file = fopen("People_in.txt", "r");
    if (file == NULL) {
        printf("Error! File People_in.txt not found!\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%49s %d", people[count].name, &people[count].age) != EOF && count < 50) {
        count++;
    }

    fclose(file);
    return count; 
}

void write_people(struct Person people[], int count) {
    FILE* file = fopen("People_out.txt", "w");
    if (file == NULL) {
        printf("Error!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", people[i].name, people[i].age);
    }
    fclose(file);
    printf("The result is recorded in a file People_out.txt\n");
}
void print_people(struct Person people[], int count) {
    printf("\nList of people:\n");
    printf("-----------------\n");
    for (int i = 0; i < count; i++) {
        printf("%s - %d age\n", people[i].name, people[i].age);
    }
    printf("-----------------\n");
}
void copy_people(struct Person copy[], struct Person from[], int count) {
    for (int i = 0; i < count; i++) {
        strcpy(copy[i].name, from[i].name);
        copy[i].age = from[i].age;
    }
}
void swap(struct Person* a, struct Person* b) {
    struct Person temp = *a;
    *a = *b;
    *b = temp;
}
void bubble_sort(struct Person people[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int flag = 1;
        for (int j = 0; j < count - i - 1; j++) {
            if (people[j].age < people[j + 1].age) {
                struct Person temp = people[j];
                people[j] = people[j + 1];
                people[j + 1] = temp;
                flag = 0;
            }
        }if (flag == 1) {
            break;
        }
    }
}
void selection_sort(struct Person people[],int count) {
    for (int i = 0; i < count - 1; i++) {
        int max_index = i;
        for (int j = i + 1; j < count; j++) {
            if (people[j].age > people[max_index].age) {
                max_index = j;
            }
        }
        swap(&people[i], &people[max_index]);
    }
}
int partition(struct Person people[], int l, int r) {
    int pivot = people[(l + r) / 2].age;
    int i = l ;
    int j = r ;

    while (i<= j) {
        while (people[i].age > pivot) {
            i++;
        }
        while (people[j].age < pivot) {
            j--;
        }
        if (i <= j) {
            swap(&people[i], &people[j]);
            i++;
            j--;
        }
    }
    return i;
}
void quicksort(struct Person people[], int l, int r) {
    if (l < r) {
        int q = partition(people, l, r);
        quicksort(people, l, q - 1);
        quicksort(people, q+1, r);
    }
}
int main() {
    struct Person people[50];
    struct Person sorted[50];
    int pcount;
    int c;
    int repeat;
    printf("=== A PROGRAM FOR SORTING PEOPLE BY AGE ===\n\n");
    pcount = read_people(people);
    if (pcount == 0) {
        printf("Couldn't read data from the file.\n Create a file People_in.txt with the data!\n");
        return 1;
    }
    do {
        printf("Select an action:\n ");
        printf("1 - bubble sort\n");
        printf("2 - selection sort\n");
        printf("3 - quick sort\n");
        while (scanf("%d", &c) != 1 || c < 1 || c > 3) {
            printf("Error. Enter a number from 1 to 3\n");
            cleanBuffer();
        }
        cleanBuffer();
        copy_people(sorted, people, pcount);

        clock_t start = clock();

        if (c == 1) {
            printf("Bubble sorting is performed...\n");
            bubble_sort(sorted, pcount);
        }
        else if (c == 2) {
            printf("Selection sorting is performed...\n");
            selection_sort(sorted, pcount);
        }
        else if (c == 3) {
            printf("Quick sorting is performed...\n");
            quicksort(sorted, 0, pcount - 1);
        }
        clock_t end = clock();

        double time_sort = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("\nSORTED LIST\n");
        print_people(sorted, pcount);

        printf("Sorting time: %.6f seconds\n", time_sort);
        write_people(sorted, pcount);

        printf("\nDo you want to try another sorting method? if you want to use a different sort, enter 1, if not, enter 0.:\n ");
        scanf("%d", &repeat);
        cleanBuffer();

    } while (repeat == 1);

    printf("\nGoodbye!\n"); 
    return 0;
}
