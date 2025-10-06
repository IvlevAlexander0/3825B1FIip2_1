#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void userGuess() {
	srand(time(NULL));
	int randomNumber = rand() % 1000 + 1;
	int guess, attempts = 0;
	
	printf("MODE 1: You guess the number\n I have thought of a number from 1 to 1000. Try to guess!\n");
	
	do {
		attempts++;
		printf("Enter your guess:\n");
		clearInputBuffer();
		scanf("%d", &guess);
		while (guess < 1 || guess > 1000) {
			printf("Error. Enter a number from 1 to 1000\n");
			clearInputBuffer();
			scanf("%d", &guess);
		}
		if (guess < randomNumber) {
			printf("The hidden number is higher\n");
		}
		else if (guess > randomNumber) {
			printf("The hidden number is smaller\n");
		}
		else {
			printf("Congratulations! You guessed the number %d in %d attempts!\n\n", randomNumber, attempts);
		}
	} while (guess != randomNumber);
}


void computerGuess() {
	int left = 1, right = 1000;
	int guess, attempts = 0;
	int number = 0;
	char sym = 0;

	printf("MODE 2: The computer guesses the number\n");
	printf("Think of a number from 1 to 1000. I'll try to guess it!\n");
	clearInputBuffer();
	scanf("%d", &number);
	while (number < 1 || number > 1000) {
		printf("Error. Enter a number from 1 to 1000\n");
		clearInputBuffer();
		scanf("%d", &number);
	}
	printf("Enter:\n");
	printf("'>' - if your number is HIGHER than mine\n");
	printf("'<' - if your number is LESS than mine\n");
	printf("'=' - If I guessed right\n");

	do {
		attempts++;
		guess = left + (right - left) / 2;
		printf("My guess %d\n", guess);
		clearInputBuffer();
		scanf("%c", &sym);
		if (sym == '>') {
			left = guess + 1;
		}
		else if (sym == '<') {
			right = guess - 1;
		}
		else {
			printf("Hooray! I guessed the number %d in %d attempts!\n\n", guess, attempts);
		}
	} while (sym !=  '=');
}


int getGameMode() {
	int mode = 0;
	printf("Enter the game mode (1 or 2)\n 1 - the program guesses a number\n 2 - the user guesses a number\n other sym - for exit\n");
	scanf("%d", &mode);
	return mode;
}

int main() {
	int mode = getGameMode();
	if (mode != 1 && mode != 2) {
		return 0;
	}

	while (mode == 1 || mode == 2) {
		if (mode == 1) {
			userGuess();
		}
		else if (mode == 2) {
			computerGuess();
		}
		clearInputBuffer();
		mode = getGameMode();
	}
	return 0;
}
