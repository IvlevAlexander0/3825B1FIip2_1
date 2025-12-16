#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
void menu(){
	printf("1 - to add a product\n");
	printf("2 - to scan a product and to check it's description\n");
	printf("3 - to scan a product and to add it into cheque\n");
	printf("4 - to check the cheque\n");
	printf("5 - to check the cheque and to start a new cheque\n");
	printf("6 - to complete the work\n");
}
int checkingcode(char arr[]) {
	if (strlen(arr) != 4) {
		printf("The barcode should contain exactly 4 numbers\n");
		return 0;
	}
	for (int i = 0; i < 4; i++) {
		if (arr[i] < '0' || arr[i] > '9') {
			printf("Incorrect barcode. Try again\n");
			return 0;
		}
	}
	return 1;
}

void copy(char a[], char b[]) {
	int i = 0;
	while (a[i] != '\0') {
		b[i] = a[i];
		++i;
	}
	b[i] = '\0';
}
int compare(char a[], char b[]) {
	int i = 0;
	while (a[i] != '\0' && b[i] != '\0') {
		if (a[i] != b[i]) {
			return 0;
		}
		++i;
	}
	if (a[i] == '\0' && b[i] == '\0') {
		return 1;
	}
	return 0;
}
void addpr(char names[][50], char code[][5], int prices[], int discounts[], int c, int* prt) {
	if (*prt >= 20) {
		printf("Maximum number of products reached\n");
		return;
	}
	printf("Enter barcode of a new product: ");
	
	char temp[5] = { 0 };
	do {
		int proverka = 0;
		scanf("%4s", temp);
		if (checkingcode(temp) == 0) {
			while (getchar() != '\n');
			continue;
		}
		while (getchar() != '\n');
		proverka = 0;
		for (int i = 0; i < *prt; i++) {
			if (compare(code[i], temp) == 1) {
				proverka = 1;
				break;
			}
			
		}
		
		if (proverka == 1) {
			printf("Such product has been added. Enter the another barcode: ");
		}
		else {
			copy(temp, code[*prt]);
			break;
		}
	} while (1);
	printf("Enter the name of the product: ");
	scanf("%49s", names[*prt]);
	while (getchar() != '\n');
	do {
		printf("Enter the price of the product: ");
		int check = scanf("%d", &prices[*prt]);
		if (prices[*prt] < 0 || check != 1) {
			printf("ERROR: the price was entered incorrectly.\n");
			while (getchar() != '\n');
			continue;
		}
		else {
			break;
		}
	} while (1);
	
	do {
		printf("Enter the discount of the product: ");
		int check = scanf("%d", &discounts[*prt]);
		while (getchar() != '\n');
		if (check != 1) {
			printf("ERROR: enter a number\n");
		}
		else if ((discounts[*prt] > 50 || discounts[*prt] < 0)) {
			printf("ERROR: The discount should be between 0 and 50%.\n");
			while (getchar() != '\n');
			continue;
		}
		else {
			break;
		}
	} while (1);
	*prt = *prt + 1;
}
void scandescription(char names[][50], char code[][5], int prices[], int discounts[], int c) {
	char arr[5] = { '0' };
	int check = 0;
	printf("Enter the barcode of the product: ");
	do {
		scanf("%4s", arr);
		while (getchar() != '\n');
		if (checkingcode(arr) == 0) {
			continue;
		}
		else {
			break;
		}

	} while (1);
	
	for (int i = 0; i < c && i < 20; i++) {
		if (compare(arr, code[i]) == 1) {
			printf("The product: %s\n", names[i]);
			printf("The price: %d\n", prices[i]);
			printf("The discount: %d\n", discounts[i]);
			++check;
			break;

		}
	}
	if (check != 1) {
		printf("Such product has not been added. Choose the mode again to enter another barcode \n");		
	}
}
void scancheck(char names[][50], char code[][5], int prices[], int discounts[], int c, char names1[][50], char code1[][5], int prices1[], int discounts1[], int* prt) {
	if (*prt >= 20) {
		printf("Maximum number of products reached\n");
		return;
	}
	char arr[5] = { '0' };
	int poisk = 0;
	printf("Enter the barcode of the product: ");
	do {
		scanf("%4s", arr);
		while (getchar() != '\n');
		if (checkingcode(arr) == 0) {
			continue;
		}
		else {
			break;
		}
	} while (1);
	for (int i = 0; i < c && i < 20; i++) {

		if (compare(arr, code[i]) == 1) {

			copy(names[i], names1[*prt]);
			copy(code[i], code1[*prt]);
			prices1[*prt] = prices[i];
			discounts1[*prt] = discounts[i];
			(*prt)++;
			poisk = 1;
			break;
		}
	}
	if (poisk != 1) {
		printf("Such product has not been added\n");
	}
}
void printcheck(char names[][50], char code[][5], int prices[], int discounts[], int c, int* prt) {
	int k = 1;
	int allprice = 0;
	int itog = 0;
	int alldiscount = 0;
	int prices1[20] = { 0 };
	if (*prt == 0) {
		printf("There are no products in the cheque.\n");
	}
	else {
		for (int i = 0; i < *prt; i++) {
			if (discounts[i] != 0) {
				prices1[i] = prices[i] - prices[i] * discounts[i] / 100;
			}
			else {
				prices1[i] = prices[i];
			}
		}
		for (int i = 0; i < *prt; i++) {
			itog += prices1[i];
			allprice += prices[i];
			alldiscount += prices[i] - prices1[i];
			printf("Product %d: %s\n", k, names[i]);
			printf("Price: %d\n", prices[i]);
			printf("Discount: %d\n", discounts[i]);
			printf("Final price: %d\n", prices1[i]);
			printf("\n");
			++k;
		}
		printf("Final price without discounts: %d\n", allprice);
		printf("Final summ of discount: %d\n", alldiscount);
		printf("Final price: %d\n", itog);
	}
	printf("The number of products in cheque: %d\n", *prt);
}
int main() {
	char names[20][50] = { "Bread", "Milk", "Eggs", "Chockolate", "Butter" };
	char codes[20][5] = { "0123", "1234", "2345", "3456", "4567" };
	int prices[20] = { 30, 80, 150, 80, 200 };
	int discounts[20] = { 0, 10, 50, 20, 30 };

	int count = 5;
	int* c = &count;
	int mode = 0;
	int chequecount = 0;
	int* ch = &chequecount;

	char checkn[20][50] = { '0' };
	char checkc[20][5] = { '0' };
	int checkp[20] = { 0 };
	int checkd[20] = { 0 };

	printf("Welcome to our system! What do you want to do?\n");
	menu();
	int flag = 0;
	do {
		do {
			int z = scanf("%d", &mode);
			if (z != 1) {
				printf("Enter the number instead of another symbols.");
				while (getchar() != '\n');
				continue;
			}
			else if (mode > 6 || mode < 1) {
				printf("Enter another number: ");
				continue;
			}
			else  {
				break;
			}
		} while (1);
		
		switch (mode) {
			case 1:
				addpr(names, codes, prices, discounts, count, c);
				menu();
				break;
			case 2:
				scandescription(names, codes, prices, discounts, count);
				menu();
				break;
			case 3:
				scancheck(names, codes, prices, discounts, count, checkn, checkc, checkp, checkd, ch);
				menu();
				break;
			case 4:
				printcheck(checkn, checkc, checkp, checkd, count, ch);
				menu();
				break;
			case 5:
				printcheck(checkn, checkc, checkp, checkd, count, ch);
				chequecount = 0;
				printf("New cheque started\n");
				menu();
				break;
			case 6:
				++flag;
				break;
			default:
				return 0;
				break;
		}
	} while (flag == 0);
	return 0;
}
