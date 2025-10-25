#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void main() {


	printf("Input gamemode. (1 - User guesses a hidden number. 2 - Program guesses a hidden number.)\n");
	int gamemode = 0;
	char c;
	while (scanf("\n%d", &gamemode) != 1 || (gamemode != 1 && gamemode != 2)) {
		printf("Incorrect input. Please try again.\n");
		while ((c = getchar()) != '\n') {};
	}


	int number = -1;
	int guess = -1;
	switch (gamemode) {


	case 1:
		srand(time(NULL));
		number = rand() % 1000;
		guess = -1;
		for (int guess_amount = 1; number != guess; guess_amount++) {
			printf("Guess a number between 0 and 1000.\n");

			while (scanf("%d", &guess) != 1) {
				printf("Incorrect input. Please try again.\n");
				while ((c = getchar()) != '\n') {};
			}

			if (guess > number) {
				printf("Hidden number is LESS than your guess.\n");
			}

			else if (guess < number) {
				printf("Hidden number is HIGHER than your guess.\n");
			}

			else {
				printf("You WON, hidden number is %d. It took %d guesses.\n", number, guess_amount);
			}
		}
		break;


	case 2:

		printf("Come up with a number between 0 and 1000.\n");
		while (scanf("%d", &number) != 1 || number < 0 || number >= 1000) {
			printf("Incorrect input. Please try again.\n");
			while ((c = getchar()) != '\n') {};
		}

		int Bottom_Border = 0;
		int Upper_Border = 1000;
		srand(time(NULL));

		for (int guess_amount = 1; number != guess; guess_amount++) {

			if (Bottom_Border >= Upper_Border) {
				printf("Error.");
				break;
			}

			guess = Bottom_Border + rand() % ( Upper_Border - Bottom_Border );

			printf("Is your number %d? Print </=/> if your number is less/equal/higher.\n", guess);

			while ((c = getchar()) != "<" && c != ">" && c != "=") {}

			if ( c == 60 && guess < Upper_Border) {
				Upper_Border = guess;
			}

			else if ( c == 62 && guess > Bottom_Border) {
				Bottom_Border = guess + 1;
			}

			else if ( c == 61 && guess == number) {
				printf("Your number is %d. It took me %d attempts to guess it.\n", guess, guess_amount);
			}

			else { printf("Incorrect input. Please try again.\n"); }
		}
	}
}
	