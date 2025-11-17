#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

void main() {
	printf("Input game mode (1 - User guess a number; 2 - Program guess a number): ");
	int gamemode = 0;
	char c;
	while (scanf("%d", &gamemode) != 1 || (gamemode != 1 && gamemode != 2)) {
		printf("Incorrect input!!! Try again\n");
		while ((c = getchar()) != '\n') {};
	}

	int ans = -1;
	int guess = -1;
	switch (gamemode) {
	case 1:
		ans = rand() % 1000;
		guess = -1;
		for (int guess_amount = 1; ans != guess; guess_amount++) {
			printf("Guess a number (0-1000)\n");
			while (scanf("%d", &guess) != 1) {
				printf("Incorrect input!!! Try again\n");
				while ((c = getchar()) != '\n') {};
			}
			if (guess > ans) {
				printf("Hidden number is less.\n");
			}
			else if (guess < ans) {
				printf("Hidden number is higher.\n");
			}
			else {
				printf("Correct!! It took %d attempts.\n", guess_amount);
			}
		}
		break;
	case 2:
		printf("I'll try to guess your number. If I'll wrong input '<' or '>' else '='.\n");
		printf("Input a number (0-1000)\n");
		while (scanf("%d", &ans) != 1 || ans < 0 || ans >= 1000) {
			printf("Incorrect input!!! Try again.\n");
			while ((c = getchar()) != '\n') {};
		}
		int min_value = 0;
		int max_value = 1000;
		for (int guess_amount = 1; ans != guess; guess_amount++) {
			if (min_value >= max_value) {
				printf("Error");
				break;
			}
			guess = (min_value + max_value)/2;
			printf("My number is %d, your number is...  ", guess);
			c = getchar();
			c = getchar();
			if (c == '<' && guess < max_value) {
				max_value = guess - 1;
			}
			else if (c == '>' && guess > min_value) {
				min_value = guess + 1;
			}
			else if (c == '=' && guess == ans) {
				printf("Your number is %d. It took %d attempts for me to guess it.\n", guess, guess_amount);
				break;
			}
			else { printf("Incorrect input. Please try again.\n"); }
		}
		break;
	}
}
