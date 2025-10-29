#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void cleanBuffer() {
    int a;
    while ((a = getchar()) != '\n' && a != EOF);
}
int n_start() {
    int n;
    printf("Start a new game!\n Enter the length of the number you've guessed.\n");
    while (scanf("%d", &n) != 1 || n < 2 || n > 5) {
        printf("Error. Enter a number from 2 to 5\n");
        cleanBuffer();
    }
    return n;
}
int  main() {
    srand(time(NULL));
    int n = n_start();
    int radnum[5];
    for (int i = 0; i < n; i++) {
        radnum[i] = -1;
    }
    radnum[0] = rand() % 9 + 1;
    for (int i = 1; i < n; i++) {
        int x;
        int uniqueness;

        do {
            x = rand() % 10;
            uniqueness = 1;
            for (int j = 0; j < i; j++) {
                if (radnum[j] == x) {
                    uniqueness = 0;
                    break;
                }
            }
        } while (uniqueness == 0);
        radnum[i] = x;
    }
    //printf("Generated number: ");
    //for (int i = 0; i < n; i++) {
    //    printf("%d", radnum[i]);
   // }
   // printf("\n");

    int number;
    int num[5];
    int bul;
    do {
        int flag = 0;
        do {
            printf("enter a number: ");
            if (scanf("%d", &number) != 1) {
                printf("error. Please enter a valid number.\n");
                cleanBuffer();
                continue;
            }
            if (number < 0) {
                number = -number;
            }
            if (number > pow(10, n) - 1 || number < pow(10, n - 1)) {
                printf("eror. enter the number of the long n = %d\n", n);
                continue;
            }

            int temp = number;
            for (int i = n - 1; i >= 0; i--) {
                num[i] = temp % 10;
                temp /= 10;
            }
            int flag2 = 1;
            for (int i = 0; i < n - 1; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (num[i] == num[j]) {
                        flag2 = 0;
                        break;
                    }
                }
                if (flag2 == 0) break;
            }

            if (flag2 == 0) {
                printf("error. enter a number with non-repeating digits\n");
                continue;
            }

            flag = 1;
        } while (flag == 0);


        //for (int i = 0; i < n; i++) {
       //      printf("%d", num[i]);
        // }
       //  printf("\n");
        int cow = 0;
        int bull = 0;
        for (int i = 0; i < n; i++) {
            int sim = num[i];
            if (sim == radnum[i]) {
                bull++;
               
            }
            else {
                for (int j = 0; j < n; j++) {
                    if (sim == radnum[j]) {
                        cow++;
                        break;
                    }
                }
            }
        }
        printf("the number of cows (numbers that are part of a number but are not in their place) =%d\n", cow);
        printf("the number of bulls (the numbers that are in place)=%d\n", bull);
        bul = bull;
        if (bul != n) {
            printf("It didn't work this time, so try again\n");
        }
    } while (bul != n);
    printf("You win!!\n");
    return 0;
}