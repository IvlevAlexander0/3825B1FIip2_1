#define _CRT_SECURE_NO_WARNINGS
#define ITEM_AMOUNT 5
#define BARCODE_LENGTH 4
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void mmain() {
	int i; char str[20];
	for (i = 0; (str[i] = getchar()) != '\n'; i++);
	str[i] = '\0';

	printf("\n%s\n", str);

}