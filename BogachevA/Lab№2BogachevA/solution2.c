#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
	srand(time(NULL));
	unsigned nt = 0;
	int  x = 1000, y = 1, ch;
	char z;
	printf("Select the game mode and type '1' if u wanna guess the number yourself or '2' if u want the computer to guess yours \n");
	unsigned n;
	while ((scanf("%u", &n) != 1 || (n > 2) || (n < 1))) {
		char c;
		while ((c = getchar()) != '\n' && c != EOF) {};
		printf("incorrect enter");
	}

	if (n == 1) {
		printf("start guessing\n");
		x = rand() % 1000 + 1;
		while (y != x) {
			while ((scanf("%d", &y) != 1 || (y > 1000) || (y < 1))) {
				char d;
				while ((d = getchar()) != '\n' && d != EOF) {};
				printf("incorrect enter");
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
				printf("gratz number of attepmts %u\n", nt);
				break;
			}
		}
	}
	if (n == 2) {
		printf("guess the number from 1 to 1000 and use '<>=' to help me!\n");
		do {
			ch = (x + y) / 2;
			nt++;
			printf("U guessed %d, am I right?\n", ch);
			while (getchar() != '\n') {};
			scanf("%c", &z);
			if (z == '>') {
				y = ch+1;
			}
			else if (z == '<') {
				x = ch - 1;
			}
			else if (z == '=') {
				printf("I guessed the number for %u attempts\n", nt);
			}
			else {
				printf("incorrect hint\n");
				nt--;
			}
			if (y > x) {
				printf("incorrect information\n");
				break;
			}
		} while (z != '=');
	}
	return 0;
}