#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void clearBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

typedef struct {
	char barcode[5];
	char name[30];
	int price;
	int discount;
} Product;    //Структура продукта

typedef struct {
	Product product;
	int quantity;
	int total_price;
} ChequeItem; //Структура позиции в чеке

typedef struct {
	ChequeItem items[50];
	int item_count;
	int total_cost;
	int total_discount;
	int final_total; 
} Cheque;     //Структура чека


Product products[50];
int product_count = 5;
Cheque current_cheque;


void BaseProducts() {

	strcpy(products[0].barcode, "1111");
	strcpy(products[0].name, "Milk 'Severnaya Dolina'");
	products[0].price = 80;
	products[0].discount = 5;

	strcpy(products[1].barcode, "2222");
	strcpy(products[1].name, "Cheese 'Brest-Litovsk'");
	products[1].price = 150;
	products[1].discount = 20;

	strcpy(products[2].barcode, "3333");
	strcpy(products[2].name, "Bread 'Sormovsky'");
	products[2].price = 50;
	products[2].discount = 10;

	strcpy(products[3].barcode, "4444");
	strcpy(products[3].name, "Eggs 'Okskoye'");
	products[3].price = 190;
	products[3].discount = 25;

	strcpy(products[4].barcode, "5555");
	strcpy(products[4].name, "Oil 'Gorodetskoye'");
	products[4].price = 350;
	products[4].discount = 40;
}

int validBarcode(const char* barcode) {

	if (strlen(barcode) != 4) {
		printf("Error. Barcode has only 4 digits\n");
		return 0;
	}

	for (int i = 0; i < 4; i++) {
		if (barcode[i] < '0' || barcode[i] > '9') {
			printf("Error. Barcode has only digits\n");
			return 0;
		}
	}
	return 1;
}

int findProduct(const char* barcode) {
	for (int i = 0; i < product_count; i++) {
		if (strcmp(products[i].barcode, barcode) == 0) {
			return i;
		}
	}
	return -1; 
}

void getBarcode(char* barcode) {
	int valid = 0;
	while (!valid) {
		printf("Enter a barcode (4 digits): ");
		scanf("%4s", barcode);
		clearBuffer();

		if (validBarcode(barcode)) {
			valid = 1;
		}
	}
}

void addProduct() {
	if (product_count >= 50) {
		printf("Error. Max quantity of products\n");
		return;
	}

	Product new_product;
	getBarcode(new_product.barcode);
	if (findProduct(new_product.barcode) != -1) {
		printf("Error. This barcode is already there\n");
		return;
	}

	printf("Enter the name of product: ");
	scanf("%29s", new_product.name);
	clearBuffer();

	printf("Enter the price of product: ");
	while (scanf("%d", &new_product.price) != 1 || new_product.price <= 0) {
		printf("Error. Enter the price again: ");
		clearBuffer();
	}
	clearBuffer();

	printf("Enter the discount (1-50%%): ");
	while (scanf("%d", &new_product.discount) != 1 || new_product.discount < 1 || new_product.discount > 50) {
		printf("Error. Enter the price again (1-50%%)");
		clearBuffer();
	}
	clearBuffer();

	products[product_count] = new_product;
	product_count++;
	printf("Product '%s' is successfully added.\n", new_product.name);
}

void scanProduct() {
	char barcode[5];
	getBarcode(barcode);

	int index = findProduct(barcode);
	if (index != -1) {
		printf("\n---- INFO ----\n");
		printf("Barcode: %s\n", products[index].barcode);
		printf("Name: %s\n", products[index].name);
		printf("Price: %d rubles.\n", products[index].price);
		printf("Discount: %d%%\n", products[index].discount);
		printf("--------------------------\n\n");
	}
	else {
		printf("Product with barcode '%s' not found\n", barcode);
	}
}

void addToCheque() {

	char barcode[5];
	getBarcode(barcode);
	int index = findProduct(barcode);
	if (index == -1) {
		printf("Product with barcode '%s' not found\n", barcode);
		return;
	}

	int quantity;
	printf("Enter the quantity: ");
	while (scanf("%d", &quantity) != 1 || quantity <= 0) {
		printf("Error. Enter the quantity again: ");
		clearBuffer();
	}
	clearBuffer();

	int found_in_cheque = -1;
	for (int i = 0; i < current_cheque.item_count; i++) {
		if (strcmp(current_cheque.items[i].product.barcode, barcode) == 0) {
			found_in_cheque = i;
			break;
		}
	}

	if (found_in_cheque != -1) {
		current_cheque.items[found_in_cheque].quantity += quantity;
		printf("Added %d pieces of product '%s' (total: %d pieces.)\n",
			quantity, products[index].name, current_cheque.items[found_in_cheque].quantity);
	}
	else {
		current_cheque.items[current_cheque.item_count].product = products[index];
		current_cheque.items[current_cheque.item_count].quantity = quantity;
		current_cheque.item_count++;
		printf("Product '%s' added to cheque\n", products[index].name);
	}
}

void displayCheque() {
	if (current_cheque.item_count == 0) {
		printf("Cheque is empty\n");
		return;
	}

	printf("\n--- Current cheque ---\n");
	current_cheque.total_cost = 0;
	current_cheque.total_discount = 0;

	for (int i = 0; i < current_cheque.item_count; i++) {
		Product p = current_cheque.items[i].product;
		int quantity = current_cheque.items[i].quantity;

		int cost_without_discount = p.price * quantity;
		int discount_amount = cost_without_discount * p.discount / 100;
		int cost_with_discount = cost_without_discount - discount_amount;

		current_cheque.items[i].total_price = cost_with_discount;

		current_cheque.total_cost += cost_without_discount;
		current_cheque.total_discount += discount_amount;

		printf("%s - %d rubles. × %d pcs. - %d%% = %d rubles.\n",
			p.name, p.price, quantity, p.discount, cost_with_discount);
	}

	current_cheque.final_total = current_cheque.total_cost - current_cheque.total_discount;

	printf("----------------------------\n");
	printf("Total price: %d rubles.\n", current_cheque.total_cost);
	printf("Total discount: %d rubles.\n", current_cheque.total_discount);
	printf("TOTAL: %d rubles.\n", current_cheque.final_total);
	printf("----------------------------\n\n");
}

void finalizeCheque() {
	if (current_cheque.item_count == 0) {
		printf("Cheque is empty\n");
		return;
	}

	displayCheque();
	int choice;
	printf("Choose:\n");
	printf("1 - Complete the work\n");
	printf("2 - Add a new cheque\n");
	while (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
		printf("Error. Enter 1 or 2: ");
		clearBuffer();
	}
	clearBuffer();

	if (choice == 1) {
		printf("Thanks! Goodbye.\n");
		exit(0);
	}
	else {
		current_cheque.item_count = 0;
		printf("New cheque is opened\n");
	}
}

int displayMenu() {
	int choice;
	printf("\n--- Sales register ---\n");
	printf("1. Add a product\n");
	printf("2. Get info about the product\n");
	printf("3. Scan a product (add to cheque)\n");
	printf("4. Display current cheque\n");
	printf("5. Finalize cheque\n");
	printf("0. Exit\n");
	printf("Choose: ");
	while (scanf("%d", &choice) != 1 || choice < 0 || choice > 5) {
		printf("Error. Enter number from 0 to 5: ");
		clearBuffer();
	}
	clearBuffer();

	return choice;
}

int main() {

	BaseProducts();
	current_cheque.item_count = 0;

	printf("Hello. Welcome to the sales register\n");

	while (1) {
		int choice = displayMenu();

		switch (choice) {
		case 0:
			printf("Goodbye.\n");
			return 0;

		case 1:
			addProduct();
			break;

		case 2:
			scanProduct();
			break;

		case 3:
			addToCheque();
			break;

		case 4:
			displayCheque();
			break;

		case 5:
			finalizeCheque();
			break;
		}
	}

	return 0;

}

