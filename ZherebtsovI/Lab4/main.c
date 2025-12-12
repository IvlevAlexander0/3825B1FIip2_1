#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Вопросы:
/*
Прочитал про такую штуку, как  интернирование строк. Там строковый литерал пихается в read-only data, а указатель получает адрес начала этого литерала.
Из этого вопросы:
1.  char* str = "Old str"; 
	str = "New Str"; //Память утекла?
2. Можем ли мы подобные вещи делать с массивами. Можем ли мы вообще изменятб указатель массива, который указывает на первый элемент?
*/

struct product {
	char barcode[5];
	char name[21];
};

struct product_info {
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
}

void initProductInfoList(struct product_info* products_info, struct product* products, size_t product_count) {
	for (size_t i = 0; i < product_count; ++i) {
		strcpy(products_info[i].barcode, products[i].barcode); //Maybe copy pointers?
		strcpy(products_info[i].name, products[i].name);
	}
	
	products_info[0].price = 30;
	products_info[1].price = 35;
	products_info[2].price = 45;
	products_info[3].price = 99;
	products_info[4].price = 200;

	products_info[0].discount = 5;
	products_info[1].discount = 3;
	products_info[2].discount = 1;
	products_info[3].discount = 6;
	products_info[4].discount = 15;
}

void printActionList() {
	printf("===[ACTIONS]===\n");
	printf("1. Add product\n");
	printf("2. Scan product\n\n");
}

size_t selectAction() {
	size_t action_num = 0;
	printf("Enter action number: ");
	while (!scanf("%zu", &action_num) || action_num < 1 || action_num > 2) {
		clearInput();
		printf("Encorrect enter. Enter action number: ");
	}
}

void printProductList(struct product* products, size_t products_count) {
	printf("===[PRODUCTS]===\n");
	for (size_t i = 0; i < products_count; ++i) {
		printf("%zu. %s\n", i + 1, products[i].name);
	}
	printf("\n");
}

size_t selectProduct(struct product products[], size_t products_count) {
	size_t product_num = 0;
	printf("Enter product number to scan it: ");
	while (!scanf("%zu", &product_num) || product_num < 1 || product_num > products_count) {
		clearInput();
		printf("Encorrect enter. Enter product number to scan it: ");
	}
	return product_num;
}

unsigned char isFreeName(char* name, struct product* products, size_t products_count) {
	for (size_t i = 0; i < products_count; ++i) {
		if (!strcmp(products[i].name, name)) return 0;
	}

	return 1;
}

void enterProductName(struct product* products, struct product_info* products_info, size_t products_count) {
	printf("Enter product name: ");
	while (!scanf("%20s", products[products_count - 1].name) || !isFreeName(products[products_count - 1].name, products, products_count - 1)) {
		printf("Encorrect product name.\n");
		clearInput();
		printf("Enter product name: ");
	}
	clearInput();
	strcpy(products_info[products_count - 1].name, products[products_count - 1].name);
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

void enterProductBarcode(struct product* products, struct product_info* products_info, size_t products_count) {
	printf("Enter product barcode: ");
	while (!scanf("%4s", products[products_count - 1].barcode) || !isFreeBarcode(products[products_count - 1].barcode, products, products_count - 1) || !isCorrectBarcode(products[products_count - 1].barcode)) {
		printf("Encorrect product barcode.\n");
		clearInput();
		printf("Enter product barcode: ");
	}
	clearInput();
	strcpy(products_info[products_count - 1].barcode, products[products_count - 1].barcode);
}

void enterProductPrice(unsigned int *price) {
	int entered_price = 0;
	printf("Enter product price: ");
	while (!scanf("%u", &entered_price) || entered_price <= 0) {
		printf("Encorrect product price.\n");
		clearInput();
		printf("Enter product price: ");
	}
	clearInput();
	*price = entered_price;
}

void enterProductDiscount(unsigned char* discount) {
	printf("Enter product discount: ");
	while (!scanf("%hhu", discount) || *discount < 1 || *discount > 50) {
		printf("Encorrect product discount.\n");
		clearInput();
		printf("Enter product discount: ");
	}
	clearInput();
}


void addToProducts(struct product_info* products_info, struct product* products, size_t* products_count) {
	*products_count += 1;

	products = (struct product*)realloc(products, *products_count * sizeof(struct product));
	products_info = (struct product_info*)realloc(products_info, *products_count * sizeof(struct product_info));

	enterProductName(products, products_info, *products_count);
	printf("--------------------------\n");
	enterProductBarcode(products, products_info, *products_count);
	printf("--------------------------\n");
	enterProductPrice(&products_info[*products_count - 1].price);
	printf("--------------------------\n");
	enterProductDiscount(&products_info[*products_count - 1].discount);
	printf("--------------------------\n");
}

void addToCart(int* cart, int product_num) {
	//cart = 
}

void printProductInof(struct product_info* products_info, size_t products_count) {
	printf("===[PRODUCTS]===\n");
	for (size_t i = 0; i < products_count; ++i) {
		printf("%zu. %s--%s-----%u----%hhu\n", i + 1, products_info[i].name, products_info[i].barcode, products_info[i].price, products_info[i].discount);
	}
	printf("\n");
} //deleteMe

void main() {
	size_t products_count = 5;
	struct product* products = (struct product*)malloc(products_count * sizeof(struct product));
	struct product_info* products_info = (struct product_info*)malloc(products_count * sizeof(struct product_info));

	int* cart = (int*)malloc(0 * sizeof(struct product));

	initProductList(products, products_count);
	initProductInfoList(products_info, products, products_count);

	addToProducts(products_info, products, &products_count);
	printProductInof(products_info, products_count);

	free(products);
	free(products_info); //In Debug causes _CrtIsValidHeapPointer(block) visual studio error
	free(cart);
} 