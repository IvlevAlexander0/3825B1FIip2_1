#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int num_length() {
    int n;
    printf("Start a new game!\n");
    printf("Enter the length of the number to guess (from 2 to 5): ");
    while (scanf("%d", &n) != 1 || n < 2 || n > 5) {
        printf("Error. Enter a number from 2 to 5: ");
        clear_buffer();
    }
    return n;
}

void secret_num (int secret[], int n) {
    for (int i = 0; i < n; i++) {
        secret[i] = -1;
    }
    secret[0] = rand() % 9 + 1;
    for (int i = 1; i < n; i++) {
        int digit;
        int unique;
        do {
            digit = rand() % 10;
            unique = 1;
            for (int j = 0; j < i; j++) {
                if (secret[j] == digit) {
                    unique = 0;
                    break;
                }
            }
        } while (unique == 0);
        secret[i] = digit;
    }
}

int check_input (int number, int n, int user_num[]) {
    if (number < 0) {
        number = -number;
    }
    if (number > pow(10, n) - 1 || number < pow(10, n - 1)) {
        printf("Error. Enter a %d-digit number\n", n);
        return 0;
    }
    int temp = number;
    for (int i = n - 1; i >= 0; i--) {
        user_num[i] = temp % 10;
        temp /= 10;
    }
    int unique_digits = 1;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (user_num[i] == user_num[j]) {
                unique_digits = 0;
                break;
            }
        }
        if (unique_digits == 0) break;
    }
    if (unique_digits == 0) {
        printf("Error. Enter a number with non-repeating digits\n");
        return 0;
    }
    return 1;
}

int guess (int n, int user_num[]) {
    int number;
    int valid = 0;
    do {
        printf("Enter your guess: ");
        if (scanf("%d", &number) != 1) {
            printf("Error. Please enter a valid number.\n");
            clear_buffer();
            continue;
        }
        if (check_input(number, n, user_num)) {
            valid = 1;
        }
    } while (valid == 0);
    return number;
}

void count_bull_cows (int secret[], int user_num[], int n, int *bulls, int *cows) {
    *bulls = 0;
    *cows = 0;
    for (int i = 0; i < n; i++) {
        int current_digit = user_num[i];
        if (current_digit == secret[i]) {
            (*bulls)++;
        }
        else {
            for (int j = 0; j < n; j++) {
                if (current_digit == secret[j]) {
                    (*cows)++;
                    break;
                }
            }
        }
    }
}

int main() {
    srand(time(NULL));
    
    int n = num_length();
    int secret[5];     
    int user_num[5];    
    int bulls, cows;
    int attempts = 0;
    
    printf("\nComputer has generated a %d-digit number.\n", n);
    secret_num(secret, n);
    
    do {
        attempts++;
        guess(n, user_num);
        count_bull_cows(secret, user_num, n, &bulls, &cows);
        
        printf("Cows (correct digits in wrong positions) = %d\n", cows);
        printf("Bulls (correct digits in correct positions) = %d\n", bulls);
    
        if (bulls != n) {
            printf("Not quite right, try again!\n\n");
        }
        
    } while (bulls != n);
    
    printf("\nCongratulations! You won!\n");
    printf("It took you %d attempts.\n", attempts);
    
    return 0;
}
