#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void swap1(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void swap2(char** a, char** b) {  
    char* t = *a;                 
    *a = *b;
    *b = t;
}

double bubble_sort(int* mas, char** name, size_t n) {  
    clock_t start, end;
    start = clock();

    for (int i = 0; i < n - 1; ++i) {
        int fl = 0;
        for (int j = 0; j < n - i - 1; ++j) {  
            if (mas[j] < mas[j + 1]) {
                swap1(&mas[j], &mas[j + 1]);
                swap2(&name[j], &name[j + 1]);  
                fl = 1;
            }
        }
        if (!fl) {  
            break;
        }
    }
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

double sel_sort(int* mas, char** name, size_t n) {  
    clock_t start, end;
    start = clock();
    for (size_t i = 0; i < n - 1; ++i) {
        size_t ind = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (mas[ind] > mas[j]) {
                ind = j;
            }
        }
        if (ind != i) {  
            swap1(&mas[i], &mas[ind]);
            swap2(&name[i], &name[ind]);  
        }
    }
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int partition(int* mas, char** name, int l, int r) {  
    int p = mas[r];
    int i = (l - 1);
    for (int j = l; j <= r - 1; j++) {
        if (mas[j] <= p) {
            i++;
            swap1(&mas[i], &mas[j]);
            swap2(&name[i], &name[j]);  
        }
    }
    swap1(&mas[i + 1], &mas[r]);
    swap2(&name[i + 1], &name[r]);  
    return (i + 1);
}

void quicksort(int* mas, char** name, int l, int r) { 
    if (l < r) {
        int q = partition(mas, name, l, r);
        quicksort(mas, name, l, q - 1); 
        quicksort(mas, name, q + 1, r);
    }
}

void writefile(char** name, int* mas, int i) {  
    FILE* ft = fopen("People_out.txt", "w");
    if (ft == NULL) {
        printf("Error opening the file\n");
        return;
    }

    for (int k = 0; k < i; k++) {
        fprintf(ft, "%s %d\n", name[k], mas[k]);
    }

    fclose(ft);
}

int main() {
    int n = 50;
    int* mas = (int*)malloc(sizeof(int) * n);
    char** name = (char**)malloc(sizeof(char*) * n);

    for (int i = 0; i < n; i++) {
        name[i] = (char*)malloc(sizeof(char) * 20);
    }

    FILE* fp = fopen("People_in.txt", "r");
    if (fp == NULL) {
        printf("Error opening the file\n");
        for (int i = 0; i < n; i++) {
            free(name[i]);
        }
        free(name);
        free(mas);
        return 1;
    }
    char c = fgetc(fp);
    int k = 0;

    while (c != EOF && k < n) {  
        char im[20];
        int j = 0;

        while (c != ' ' && c != EOF && c != '\n' && j < 19) {
            im[j] = c;
            j++;
            c = fgetc(fp);
        }
        im[j] = '\0';

        strcpy(name[k], im);

        while (c == ' ') {
            c = fgetc(fp);
        }

        char ch[10];
        j = 0;

        while (c != '\n' && c != EOF && c != ' ' && j < 9) {
            ch[j] = c;
            j++;
            c = fgetc(fp);
        }
        ch[j] = '\0';

        mas[k] = atoi(ch);

        while (c != '\n' && c != EOF) {
            c = fgetc(fp);
        }

        while (c == '\n') {
            c = fgetc(fp);
        }

        k++;
    }
    fclose(fp);
    n = k;
    char choice;
    int should_continue = 1;  

    int* orig = (int*)malloc(sizeof(int) * n);
    char** origname = (char**)malloc(sizeof(char*) * n);
    for (int i = 0; i < n; i++) {
        orig[i] = mas[i];
        origname[i] = (char*)malloc(sizeof(char) * 20);
        strcpy(origname[i], name[i]);
    }

    do {
        printf("\nSelect the sorting method: \n1. Bubble sort \n2. Selection sort \n3. Quicksort \n0. Exit \n");
        printf("Your choice: ");
        scanf(" %c", &choice);
        for (int i = 0; i < n; i++) {
            mas[i] = orig[i];
            strcpy(name[i], origname[i]);
        }

        double res;
        switch (choice) {
        case '1':
            printf("Bubble sorting time: %f seconds\n", bubble_sort(mas, name, n));
            writefile(name, mas, n);
            break;
        case '2':
            printf("Selection sorting time: %f seconds\n", sel_sort(mas, name, n));
            writefile(name, mas, n);
            break;
        case '3':
        {
            clock_t start, end;
            start = clock();
            quicksort(mas, name, 0, n - 1);  
            end = clock();
            res = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Hoare Quicksort execution time: %f seconds\n", res);
            writefile(name, mas, n);
        }
        break;
        case '0':
            should_continue = 0;
            break;
        default:
            printf("Input error! Try again!\n");
            break;
        }

        if (choice >= '1' && choice <= '3') {
            printf("\nSorted data:\n");
            for (int i = 0; i < n; i++) {
                printf("%s %d\n", name[i], mas[i]);
            }
        }

    } while (should_continue);

    printf("Goodbye!\n");

    for (int i = 0; i < n; i++) {
        free(origname[i]);
    }
    free(origname);
    free(orig);

    for (int i = 0; i < n; i++) {
        free(name[i]);
    }
    free(name);
    free(mas);

    return 0;
}