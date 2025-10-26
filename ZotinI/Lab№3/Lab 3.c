#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void main() {
	int n;
	srand(time(NULL));
	while (1) {
		printf("Enter n (2-5): \n");
		if (scanf("%d", &n) == 1 && n > 1 && n < 6) {
			int cled = getchar();
			if (cled == '\n') {
				break;
			}
			else {
				printf("The number must be an integer.\n");
				while (getchar() != '\n');
			}
		}
		else {
			printf("Input error. Try again!\n"); 
			while (getchar() != '\n');
		}
	}
	int right = pow(10, n);
	int left = pow(10, n - 1);
	int prog_num;
	int mas_prog[5];
	int fl = 1;
	short count = 0;

	while (fl) {
		prog_num = rand() % (right - left) + left;
		for (int j = n - 1; j >= 0; j--) {
			mas_prog[j] = prog_num % 10;
			prog_num /= 10;
		}
		int un = 1;
		for (int i = 0; i < n - 1 && un; i++) {
			for (int j = i + 1; j < n; j++) {
				if (mas_prog[i] == mas_prog[j]) {
					un = 0;
					break;
				}
			}
		}

		if (un) {
			fl = 0;
		}
	}



	int pol;
	int mas_pol[5];
	int buk;
	int kor;

	do {
		printf("Enter number length %d: \n", n);
		while (1) {
			if (scanf("%d", &pol) == 1) {
				int cled = getchar();
				if (cled == '\n') {
					if (pol >= left && pol < right) {
						int save_pol = pol;
						int valid = 1;

						for (int j = n - 1; j >= 0; j--) {
							mas_pol[j] = save_pol % 10;
							save_pol /= 10;
						}

						int un = 1;
						for (int i = 0; i < n - 1 && un; i++) {
							for (int j = i + 1; j < n; j++) {
								if (mas_pol[i] == mas_pol[j]) {
									un = 0;
									break;
								}
							}
						}

						if (un) {
							break;
						}
						else {
							printf("The number must contain non-repeating elements. Try again!\n");
						}
					}
					else {
						printf("Number must have exactly %d digits. Try again!\n", n);
					}
				}
				else {
					printf("The number must be an integer.\n");
					while (getchar() != '\n');
				}
			}
			else {
				printf("Input error. Try again!\n");
				while (getchar() != '\n');
			}
		}


		buk = 0;
		kor = 0;
		for (int l = 0; l < n; l++) {
			for (int k = 0; k < n; k++) {
				if (mas_pol[l] == mas_prog[k]) {
					if (k == l) {
						buk += 1;
					}
					else {
						kor += 1;
					}
				}
			}
		}

		printf("Bulls  = %d \n", buk);
		printf("Cows = %d \n", kor);
	} while (buk != n);
	printf("You guessed the number \n");

}