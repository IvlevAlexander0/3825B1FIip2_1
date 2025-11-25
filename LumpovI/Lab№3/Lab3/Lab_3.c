#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int InputLength(int num, int len) {
	int i = 0;
	while (num != 0) {
		num /= 10;
		i+=1;
	}
	if (i == len) {
		return 1;
	}
	else {
		return 0;
	}
}

int InputDiff(int num, int len) {
	int user_num[5];
	for (int i = len - 1; i >= 0; i--) {
		user_num[i] = num % 10;
		num /= 10;
	}
	for (int i = 0; i < len - 1; i++) {
		int j = i + 1;
		while (j < len) {
			if (user_num[j] == user_num[i]) {
				return 0;
			}
			j++;
		}
	}
	return 1;
}

int Digits(int len) {
	int num;
	int c;
	printf("Try to guess the number the size %d(without repeatings): ", len);
	while (1) {
		while ((c = getchar()) != '\n') {}
		scanf("%d", &num);
		if (num < 0) {
			printf("Incorrect input!!! The number must be positive\n");
		}
		else if (InputLength(num, len) == 0) {
			printf("Incorrect input!!! The length should be the size %d\n", len);
		}
		else if (InputDiff(num, len) == 0) {
			printf("Incorrect input!!! The number must not contain repeated digits.\n");
		}
		else {
			return num;
		}
	}
}

int main() {
	int number; int len;
	int arr[5];
	int bulls = 0; int cows = 0;
	int user_num[5];
	int c;
	printf("Enter the length of the number(2-5): ");
	scanf("%d", &len);
	while (len > 5 || len < 2) {
		printf("Incorrect length input!!! Please try again.\n");
		while ((c = getchar()) != '\n') {}
		scanf("%d", &len);
	}

	char t;
	char i = 0;
	char num[10] = { 0 };
	while (i < len) {
		if (num[t = rand() % 10] == 0 && (t > 0 || i > 0)) {
			num[arr[i++] = t] += 1;
		}
	}
	while (bulls != len) {
		bulls = 0;
		cows = 0;
		number = Digits(len);
		for (int i = len - 1; i >= 0; i--) {
			user_num[i] = number % 10;
			number /= 10;
		}
		for (int i = 0; i < len; i++) {
			if (user_num[i] == arr[i]) {
				bulls++;
			}
			else {
				for (int j = 0; j < len; j++) {
					if (user_num[j] == arr[i]) {
						cows++;
					}
				}
			}
		}
		if (bulls == len) {
			printf("You win!!!\n");
		}
		printf("Number of cows = %d, number of bulls = %d.\n", cows, bulls);
	}
}