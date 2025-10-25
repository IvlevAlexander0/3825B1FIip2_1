#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void clearInput() {
	char ch = '\0';
	while ((ch = getchar()) != '\n' && ch != EOF);
}

unsigned short enterLength() {
	unsigned short length = 1;

	printf("Enter number length (2 - 5): ");
	while (scanf("%hd", &length) != 1 || length < 2 || length > 5) {
		printf("Encorrect enter\n");
		clearInput();
		printf("Enter number length (2 - 5): ");
	}
	clearInput();

	return length;
}

char isCorrectNumber(unsigned char number[], unsigned short length) {
	unsigned char digits_count[10] = { 0 };

	for (size_t i = 0; i < length; ++i) {
		char digit = number[i] - '0';
		if (digit >= 0) {
			if (digits_count != 1) {
				digits_count[digit] = 1;
			}
			else {
				return 0;
			}
		}
	}

	unsigned char num_lenght = 0;
	for (size_t i = 0; i < 10; ++i) {
		num_lenght += digits_count[i];
	}
	if (num_lenght != length) {
		return 0;
	}
	return 1;
}

void enterNumber(unsigned char number[6], unsigned short length) {
	printf("Enter you guess: ");
	while (scanf("%5s", number) != 1 || !isCorrectNumber(number, length)) {
		printf("Encorrect enter\n");
		clearInput();
		printf("Enter you guess: ");
	}
	clearInput();
}

unsigned char generateNumber(unsigned char guessing_number[6], unsigned short length) {
	unsigned char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

	for (size_t i = 10; i > 10 - length; --i) {
		size_t digit_index = 0;
		if (i == 10) {
			digit_index = 1 + rand() % (i - 1);
		}
		else {
			digit_index = rand() % i;
		} 
		unsigned char temp = digits[digit_index];
		digits[digit_index] = digits[i - 1];
		digits[i - 1] = temp;

		guessing_number[10 - i] = temp;
	}

	return guessing_number;
}

unsigned char getCowCount(unsigned char user_answer[], unsigned char guessing_number[]) {
	unsigned char cow_count = 0;
	unsigned char digits_count[10] = { 0 };

	for (size_t i = 0; guessing_number[i] != '\0'; ++i) {
		if (user_answer[i] != guessing_number[i]) {
			digits_count[user_answer[i] - '0']++;
			digits_count[guessing_number[i] - '0']++;
		}
	}
	
	for (size_t i = 0; i < 10; ++i) {
		cow_count += digits_count[i] == 2;
	}

	return cow_count;
}

unsigned char getBullCount(unsigned char user_answer[], unsigned char guessing_number[]) {
	unsigned char bull_count = 0;

	for (size_t i = 0; guessing_number[i] != '\0'; ++i) {
		bull_count += user_answer[i] == guessing_number[i];
	}

	return bull_count;
}

unsigned char isStringEqual(unsigned char str_1[], unsigned char str_2[]) {
	for (size_t i = 0; str_1[i] != '\0'; ++i) {
		if (str_1[i] != str_2[i]) return 0;
	}
	return 1;
}

//FIX IT:
//user_ans_format : "123  ";
//generate_num_format: "  123"


void main() {
	srand(time(0));

	unsigned char guessing_number[6] = { 0 };
	unsigned char user_answer[6] = { 0 };
	unsigned short length = enterLength();

	generateNumber(guessing_number, length);

	do 
	{
		enterNumber(user_answer, length);
		printf("Cows: %d | Bulls: %d\n", getCowCount(user_answer, guessing_number), getBullCount(user_answer, guessing_number));
	} while (!isStringEqual(user_answer, guessing_number));
	printf("You're damn right");
}