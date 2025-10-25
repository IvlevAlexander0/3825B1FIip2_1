#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

int main() {
    int mode = 0;
    int count = 0;

    while (mode != 1 && mode != 2) {
        printf("Choose mode:\n");
        printf("1 - You guess computer's number\n");
        printf("2 - Computer guesses number\n");
        scanf("%d", &mode);
        if (mode != 1 && mode != 2) {
            printf("Error: try again to choose the mode.\n");
        }
        else {
            break;
        }
    }

    if (mode == 1) {
        srand(time(0));
        int a = 1, b = 1000;
        int s = rand() % ((b - a) + 1) + a;
        int g = 0;
        printf("Computer guessed a number from 1 to 1000. Try to guess it!\n");
        while (s != g) {
            printf("Enter your number: ");
            scanf("%d", &g);
            count = count + 1;
            if (g == s) {
                printf("SUCCESS! You guessed the number.\n");
            }
            else if (g < s) {
                printf("The number is bigger\n");
            }
            else {
                printf("The number is smaller\n");
            }
        }
    }

    else if (mode == 2) {
        int a = 1, b = 1000;
        int g = 0;
        char answer = ' ';
        printf("Computer guess your number\n");
        while (answer != '=') {
            g = (a + b) / 2;
            count = count + 1;
            printf("Computer's guess: %d\n", g);
            printf("Enter '>' if your number is bigger, '<' if smaller, '=' if correct: ");
            scanf(" %c", &answer);
            if (answer == '=') {
                printf("Computer guessed your number!\n");
                printf("The number is: %d\n", g);
                break;
            }
            else if (answer == '>') {
                a = g + 1;
            }
            else if (answer == '<') {
                b = g - 1;
            }
        }
    }
    printf("Number of attempts: %d\n", count);
}