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
    scanf("%d", &n);
    while (n < 2 || n > 5) {
        printf("Error. Enter a number from 2 to 5\n");
        cleanBuffer();
        scanf("%d", &n);
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
    printf("enter a number: ");
    scanf("%d", &number);

    if (number < 0) {
        number = -number;
    }
    if (number > pow(10, n) - 1 || number < pow(10, n - 1)) {
        printf("EROR.enter the number of the long n =%d", n);
        printf("\n");
        cleanBuffer();
        scanf("%d", &number);
    }
    int temp = number;
    int nn = n-1;
    int p = pow(10, nn);
    for (int i = 0; i < n; i++) {
        if (temp < 10) {
            num[n - 1] = temp;
        }
        num[i] = temp / p;
        temp = temp % p;
        nn--;
        p = pow(10, nn);
    }
   // for (int i = 0; i < n; i++) {
  //      printf("%d", num[i]);
   // }
  //  printf("\n");
    int bul;
    do {
        int cow = 0;
        int bull = 0;
        for (int i = 0; i < n; i++) {
            int sim = num[i];
            if (sim == radnum[i]) {
                bull++;
                cow--;
            }
            for (int j = 0; j < n; j++) {
                if (sim == radnum[j]) {
                    cow++;
                }
            }
        }
        printf("the number of cows (numbers that are part of a number but are not in their place) =%d\n", cow);
        printf("the number of bulls (the numbers that are in place)=%d\n", bull);
        bul = bull;
        if (bul != n) {
            printf("It didn't work this time, so try again\n");
            printf("enter a number: ");
            int numbers;
            scanf("%d", &numbers);
            if (numbers < 0) {
                numbers = -numbers;
            }
            if (numbers > pow(10, n) - 1 || numbers < pow(10, n - 1)) {
                printf("EROR.enter the number of the long n =%d", n);
                printf("\n");
                cleanBuffer();
                scanf("%d", &numbers);
            }
            int temps = numbers;
            int nns = n - 1;
            int ps = pow(10, nns);
            for (int i = 0; i < n; i++) {
                if (temps < 10) {
                    num[n - 1] = temps;
                }
                num[i] = temps / ps;
                temps = temps % ps;
                nns--;
                ps = pow(10, nns);
            }
        }
    } while (bul != n);
    printf("You win!!");
    return 0;
}
