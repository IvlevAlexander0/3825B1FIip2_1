#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct product {
	char barcode[5];
	char name[21];
	unsigned int price;
	unsigned char discount;
};

void clearInput() {
	char ch = '\0';
	while ((ch = getchar()) != '\n' && ch != EOF);
}

void initProductList(struct product* products, size_t product_count) {
	strcpy(products[0].name, "Apple");
	strcpy(products[1].name, "Tomate");
	strcpy(products[2].name, "Bread");
	strcpy(products[3].name, "Milk");
	strcpy(products[4].name, "Pinapple");

	strcpy(products[0].barcode, "0001");
	strcpy(products[1].barcode, "0002");
	strcpy(products[2].barcode, "0003");
	strcpy(products[3].barcode, "0004");
	strcpy(products[4].barcode, "0005");

	products[0].price = 30;
	products[1].price = 35;
	products[2].price = 45;
	products[3].price = 99;
	products[4].price = 200;

	products[0].discount = 5;
	products[1].discount = 3;
	products[2].discount = 1;
	products[3].discount = 6;
	products[4].discount = 15;
}

void printActionList() {
	printf("===[ACTIONS]===\n");
	printf("1. Add product\n");
	printf("2. Scan product\n");
	printf("3. Scan product and add to cart\n");
	printf("4. Print receipt\n\n");
}

size_t enterAction() {
	size_t action_num = 1;
	printf("Enter action number: ");
	while (!scanf("%zu", &action_num) || action_num < 1 || action_num > 4) {
		clearInput();
		printf("Encorrect enter. Enter action number: ");
	}
	clearInput();

	return action_num;
}

unsigned char isFreeName(char* name, struct product* products, size_t products_count) {
	for (size_t i = 0; i < products_count; ++i) {
		if (!strcmp(products[i].name, name)) return 0;
	}

	return 1;
}

void enterProductName(struct product* products, size_t products_count) {
	printf("Enter product name: ");
	while (!scanf("%20s", products[products_count - 1].name) || !isFreeName(products[products_count - 1].name, products, products_count - 1)) {
		clearInput();
		printf("Encorrect product name. Enter product name: ");
	}
	clearInput();
}

unsigned char isFreeBarcode(char* barcode, struct product* products, size_t products_count) {
	for (size_t i = 0; i < products_count; ++i) {
		if (!strcmp(products[i].barcode, barcode)) return 0;
	}

	return 1;
}

unsigned char isCorrectBarcode(char* barcode) {
	for (size_t i = 0; i < 4; ++i) {
		if (barcode[i] < 48 || barcode[i] > 57) return 0;
	}

	return 1;
}

void enterProductBarcode(struct product* products, size_t products_count) {
	printf("Enter product barcode: ");
	while (!scanf("%4s", products[products_count - 1].barcode) || !isFreeBarcode(products[products_count - 1].barcode, products, products_count - 1) || !isCorrectBarcode(products[products_count - 1].barcode)) {
		clearInput();
		printf("Encorrect product barcode. Enter product barcode: ");
	}
	clearInput();
}

void enterProductPrice(unsigned int* price) {
	int entered_price = 0;
	printf("Enter product price: ");
	while (!scanf("%u", &entered_price) || entered_price <= 0) {
		clearInput();
		printf("Encorrect product price. Enter product price: ");
	}
	clearInput();
	*price = entered_price;
}

void enterProductDiscount(unsigned char* discount) {
	printf("Enter product discount: ");
	while (!scanf("%hhu", discount) || *discount < 1 || *discount > 50) {
		clearInput();
		printf("Encorrect product discount. Enter product discount: ");
	}
	clearInput();
}

unsigned char addToProducts(struct product** products, size_t* products_count) {
	*products_count += 1;

	if (!realloc(*products, *products_count * sizeof(struct product))) return 1;

	enterProductName(*products, *products_count);
	printf("--------------------------\n");
	enterProductBarcode(*products, *products_count);
	printf("--------------------------\n");
	enterProductPrice(&(*products)[*products_count - 1].price);
	printf("--------------------------\n");
	enterProductDiscount(&(*products)[*products_count - 1].discount);
	printf("--------------------------\n");

	return 0;
}

void printProductList(struct product* products, size_t products_count) {
	printf("===[PRODUCTS]===\n");
	for (size_t i = 0; i < products_count; ++i) {
		printf("%zu. %s\n", i + 1, products[i].name);
	}
	printf("\n");
}

size_t selectProduct(size_t products_count) {
	size_t product_num = 1;
	printf("Enter product number: ");
	while (!scanf("%zu", &product_num) || product_num < 1 || product_num > products_count) {
		clearInput();
		printf("Encorrect enter. Enter product number to scan it: ");
	}

	return product_num - 1;
}

void printProductInfo(struct product product_info) {
	printf("%s ---------------- %u RUB | DISC: %hhu%%\n", product_info.name, product_info.price, product_info.discount);
}

void addToCart(int product_num, unsigned int* cart) {
	cart[product_num]++;
}

void printReceipt(unsigned int* cart, struct product* products, size_t products_count) {
	printf("\n===[RECEIPT]===\n");
	size_t number = 1;
	float sum = 0;
	float sum_disc = 0;
	for (size_t i = 0; i < products_count; ++i) {
		if (cart[i] > 0) {
			printf("%zu. %-20s%u X %u RUB | DISC: %hhu%%\n", number, products[i].name, cart[i], products[i].price, products[i].discount);
			printf("TOTAL PRICE: %.0f RUB\n", round(cart[i] * products[i].price * (1 - (float)products[i].discount / 100)));
			sum += cart[i] * products[i].price;
			sum_disc += round(cart[i] * products[i].price * (1 - (float)products[i].discount / 100));
			number++;
		}
	}
	printf("==================\n");
	if (sum > 0) {
		printf("RESULT: %.0f RUB\nTO PAY: %.0f RUB   TOTAL DISC: %.0f%%\n\n", round(sum), round(sum_disc), 100 - round(sum_disc / sum * 100));
	}
	else {
		printf("CART EMPTY :(\n\n");
	}
}

unsigned char selectIsExit() {
	unsigned char is_exit = 0;

	printf("Select action: \n");
	printf("1. Start new receipt\n");
	printf("2. Exit\n");
	printf("Enter you choose: ");
	while (!scanf("%hhu", &is_exit) || is_exit < 1 || is_exit > 2) {
		clearInput();
		printf("Encorrect enter. Enter you choose: ");
	}
	clearInput();

	return is_exit - 1;
}

void main() {
	size_t products_count = 5;
	struct product* products = (struct product*)calloc(products_count, sizeof(struct product));
	unsigned int* cart = (unsigned int*)calloc(products_count, sizeof(unsigned int));

	initProductList(products, products_count);
	unsigned char is_exit = 0;

	while (!is_exit) {
		printActionList();
		size_t now_action = enterAction();
		switch (now_action) {
		case 1:
			is_exit = addToProducts(&products, &products_count);
			cart = (unsigned int*)realloc(cart, products_count * sizeof(unsigned int));
			cart[products_count - 1] = 0;

			if (is_exit) {
				printf("REALLOCATION FAILED");
			}
			break;
		case 2:
			printProductList(products, products_count);
			printProductInfo(products[selectProduct(products_count)]);
			break;
		case 3:
			printProductList(products, products_count);
			addToCart(selectProduct(products_count), cart);
			break;
		case 4:
			printReceipt(cart, products, products_count);
			is_exit = selectIsExit();
			if (!is_exit) {
				for (size_t i = 0; i < products_count; ++i) {
					cart[i] = 0;
				}
			}
			break;
		}
	}

	free(products);
	free(cart);
}