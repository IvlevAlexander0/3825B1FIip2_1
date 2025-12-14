#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void cleanBuffer() {
	int a;
	while ((a = getchar()) != '\n' && a != EOF);
}
void user() {
	srand(time(NULL));
	int randomNum = rand() % 1000 + 1;
	int znum, pop = 0;
	printf("You guess the number\n I have thought of a number from 1 to 1000. Try to guess!\n");
	do {
		pop++;
		printf("Enter your guess:\n");
		cleanBuffer();
		scanf("%d", &znum);
		while (znum < 1 || znum > 1000) {
			printf("Error. Enter a number from 1 to 1000\n");
			cleanBuffer();
			scanf("%d", &znum);
		}if (znum < randomNum) {
			printf("The hidden number is higher\n");
		}else if (znum > randomNum) {
			printf("The hidden number is smaller\n");
		}else {
			printf("Congratulations! You guessed the number %d in %d attempts!\n\n", randomNum, pop);
		}
	} while (znum != randomNum);
}
void computer() {
	int left = 1, right = 1000;
	int znum, pop = 0;
	int num = 0;
	char sym = 0;
	printf("The computer guesses the number\n");
	printf("Think of a number from 1 to 1000. I'll try to guess it!\n");
	cleanBuffer();
	scanf("%d", &num);
	while (num < 1 || num > 1000) {
		printf("Error. Enter a number from 1 to 1000\n");
		cleanBuffer();
		scanf("%d", &num);
	}
	printf("Enter:\n");
	printf("'>' - if your number is higher than mine\n");
	printf("'<' - if your number is less than mine\n");
	printf("'=' - If I guessed right\n");
	do {
		pop++;
		znum = left + (right - left) / 2;
		printf("My guess %d\n", znum);
		cleanBuffer();
		scanf("%c", &sym);
		if (sym == '>') {
			left = znum + 1;
		}else if (sym == '<') {
			right = znum - 1;
		}else {
			printf("Hooray! I guessed the number %d in %d attempts!\n\n", znum, pop);
		}
	} while (sym !=  '=');
}
int start() {
	int game = 0;
	printf("Enter the game mode (1 or 2)\n 1 - the program guesses a number\n 2 - the user guesses a number\n other sym - for exit\n");
	scanf("%d", &game);
	return game;
}
int main() {
	int mode = start();
	if (mode != 1 && mode != 2) {
		return 0;
	}
	while (mode == 1 || mode == 2) {
		if (mode == 1) {
			user();
		}else if (mode == 2) {
			computer();
		}
		cleanBuffer();
		mode = start();
	}
	return 0;
}