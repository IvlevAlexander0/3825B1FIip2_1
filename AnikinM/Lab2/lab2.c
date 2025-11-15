#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void main() {
	int gamemode;
	int num = 0;
	int guess = 0;
	int att = 1;
	char c;
	printf("Choose the game mode: (1) if you want to guess the number/ (2) if you want the program to guess your number.\n");
	scanf("%d", &gamemode);
	while (gamemode != 1 && gamemode != 2) {
		printf("Choose between 1 and 2\n");
		while ((c = getchar()) != '\n' && c != EOF) {};
		scanf("%d", &gamemode);
	}
	switch (gamemode) {
	case 1:
		srand(time(NULL));
		num = rand() % 1000 + 1;
		for (att; num != guess; att++) {
			printf("Guess the number from 1 to 1000\n");
			while (scanf("%d", &guess) != 1) {
				printf("Error,try again\n");
				while ((c = getchar()) != '\n' && c != EOF) {};
			}
			if (guess > num) {
				printf("Your number is bigger than hidden number\n");
			}
			if (guess < num) {
				printf("Your number is smaller than hidden number\n");
			}
			if (guess == num) {
				printf("You guessed the number. Attempts: %d\n",att);
			}
		}
		break;
	case 2:
		int a = 1;
		int b = 1000;
		printf("Come up with the number from 1 to 1000. Enter to continue.\n");
		while ((c = getchar()) != '\n' && c != EOF) {};
		srand(time(NULL));
		for (att;; att++) {
			if (a > b || a == b) {
				printf("Error, no numbers left in range");
			}
			guess = (a + b) / 2;
			printf("It is %d? Give me a clue: >/=/<\t", guess);
			while ((c = getchar()) != '<' && c != '>' && c!= '=') {
				if (c != '\n') {
					printf("Enter only declared data (>/=/<):\t");
				}
			}
			if (c == '<') {
				b = guess - 1;
			}
			else if (c == '>') {
				a = guess + 1;
			}
			else if (c == '=') {
				printf("I guessed your number! Attempts: %d\n", att);
				break;
			}
		}
		break;
	}
}