#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>


void main() {
	srand(time(NULL));
	int gamemode = 0;

	printf("Input gamemode. (1 - User guesses a hidden number. 2 - Program guesses a hidden number.)\n");

	while ((scanf("\n%d", &gamemode) != 1) || ((gamemode != 1) && (gamemode != 2))) {
		printf("Incorrect input. Please try again.\n");
		char c;
		while ((c = getchar()) != '\n') {};
	}

	switch (gamemode) {

	case 1:

		int number = rand() % 1000;
		int guess = -1;
		int guess_amount = 0;

		while (number != guess) {
			printf("\nMake a guess.\n");

			while ((scanf("%d", &guess) != 1)) {
				printf("\nIncorrect input. Please try again.\n");
				char c;
				while ((c = getchar()) != '\n') {};
			}

			if (guess > number) {
				guess_amount += 1;
				printf("\nHidden number is LESS than your guess.\n");
			}

			else if (guess < number) {
				guess_amount += 1;
				printf("\nHidden number is HIGHER than your guess.\n");
			}

			else {
				guess_amount += 1;
				printf("\nYou WON, hidden number is %d. It took %d guesses.\n", number, guess_amount);
			}
		}
		break;

	}
}
	