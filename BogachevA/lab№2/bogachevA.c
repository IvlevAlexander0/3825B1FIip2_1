#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void main() {
	srand(time(NULL));
	unsigned nt = 0;
	int  x = 1000, y = 0, ch;
	char z;
	printf("Select the game mode and type '1' if u wanna guess the number yourself or '2' if u want the computer to guess yours \n");
	unsigned n;
	while ((scanf("%u", &n) != 1 || (n > 2) || (n < 1))) {
		char c;
		while ((c = getchar()) != '\n' || c != EOF) {};
	}

	if (n == 1) {
		printf("start guessing\n");
		x = rand() % 1000 + 1;
		while (y != x) {
			while ((scanf("%d", &y) != 1 || (y > 1000) || (y < 1))) {
				char d;
				while ((d = getchar()) != '\n' || d != EOF) {};
			}
			if (y > x) {
				printf("The hidden number is less\n");
				nt++;
			}

			else if (y < x) {
				printf("The hidden number is greater\n");
				nt++;
			}

			else if (y == x) {
				nt++;
				printf("gratz\tnumber of attepmts %u\n", nt);
				break;
			}
		}
	}
	if (n == 2) {
		printf("Pick the number from 1 to 1000 and use '<>=' 2 help me\n");
		while (y <= x) {
			nt++;
			ch = (x + y) / 2;
			printf("U picked %d right?\n", ch);
			scanf("%c", &z);
			if (z == '=') {
				break;
			}
			else if (z == '<') {
				x = ch - 1;
			}
			else if (z == '>') {
				y = ch + 1;
			}
			else {
				printf("incorrect value of hint");
				//char d;
				//while ((d = getchar()) != '\n' || d != EOF) {};
			}
		}
		if (y > x) {
			printf("incorrect information");
		}
		else {
			printf("I guessed the number for %u attempts", nt);
		}

	}
}