#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	printf("Welcome to the most wondefull game \"BULLS AND COWS\"\n ");
	srand(time(0));
	int length = 0;
	
	do {
		printf("Enter the length of a number: ");
		scanf("%d", &length);
		if (length < 2 || length > 5)
			printf("The number should be between 2 and 5. Try again\n");
		else 
			break;
	} while (length < 2 || length > 5);

	int arr[5] = { 0 };
	int sovp[10] = { 0 };
	int x = rand() % 9 + 1;
	arr[0] = x;
	sovp[x] = 1;

	for (int i = 1; i < length; i++) {
		int check = 0;
		while (check == 0) {
			int a = rand() % 10;
			if (sovp[a] == 0) {
				arr[i] = a;
				sovp[a] = 1;
				check = 1;
			}
			else
				continue;
		}

	}
	int guess[5] = { 0 };
	int cow = 0;
	int bull = 0;
	int check = 0;

	do {
		cow = 0;
		bull = 0;
		printf("Try to guess the number. Enter your guess: ");
		for (int i = 0; i < length; i++) {
			scanf("%1d", &guess[i]);
		}
		for (int i = 0; i < length; i++) {
			if (guess[i] == arr[i])
				bull++;
		}
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j++) {
				if (arr[i] == guess[j] && i != j)
					cow++;
			}
		}
		printf("%d bulls, %d cows\n", bull, cow);
		if (bull == length) {
			printf("SUCCESS!!! You have guessed the number!");
			check = 1;
		}
	} while (check == 0);

}
