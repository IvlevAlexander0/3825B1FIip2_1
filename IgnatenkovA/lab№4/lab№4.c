#define MAX_ITEMS 100
#define MAX_RECEIPT_SIZE 100
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Item {
    int cost;
    int discount;
    char name[255];
    char code[5];
};

struct ReceiptEntry {
    char code[5];
    int quantity;
};

struct Item items[MAX_ITEMS];
int item_count = 0;

struct ReceiptEntry receipt[MAX_RECEIPT_SIZE];
int receipt_size = 0;

int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

int ValidCode(const char* code) {
    if (strlen(code) != 4) return 0;
    for (int i = 0; i < 4; i++) {
        if (!is_digit(code[i])) return 0;
    }
    return 1;
}
int inputInt(const char* s, int min, int max) {
    int value;
    printf("%s", s);
    while (1) {
        if (scanf("%d", &value) != 1) {
            printf("Incorrect type ");
            while (getchar() != '\n');
        }
        else if (value < min || value > max) {
            printf("Incorrect value range ", min, max);
            while (getchar() != '\n');
        }
        else {
            while (getchar() != '\n');
            return value;
        }
    }
}

void inputString(char* buffer, int max_len, const char* s, int empty) {
    char temp[300];
    printf("%s", s);
    while (1) {
        if (fgets(temp, sizeof(temp), stdin) == NULL) {
            printf("Incorrect input ");
            continue;
        }
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') {
            temp[len - 1] = '\0';
            len--;
        }
        else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("input is too long ");
            continue;
        }
        if (!empty && len == 0) {
            printf("Incorrect input ");
            continue;
        }
        if ((int)len >= max_len) {
            printf("value is too long ");
            continue;
        }
        strcpy(buffer, temp);
        break;
    }
}
void addMainItems() {
    struct Item Main[] = {
        {100, 5, "bread", "1111"},
        {50, 10, "milk", "2222"},
        {200, 15, "cheese", "3333"},
        {30, 1, "apple", "4444"},
        {150, 20, "coffee", "5555"}
    };
    for (int i = 0; i < 5; i++) {
        items[item_count++] = Main[i];
    }
}
void addItem() {
    if (item_count >= MAX_ITEMS) {
        printf("limit on the number of products \n");
        return;
    }
    char code[5];
    while (1) {
        inputString(code, sizeof(code), "enter the code ", 0);
        if (!ValidCode(code)) {
            printf("code must keep 4 digits \n");
            continue;
        }
        int exists = 0;
        for (int i = 0; i < item_count; i++) {
            if (strcmp(items[i].code, code) == 0) {
                exists = 1;
                break;
            }
        }
        if (exists) {
            printf("product with this code already exists \n");
            continue;
        }
        break;
    }
    char name[255];
    inputString(name, sizeof(name), "enter name ", 0);

    int cost = inputInt("enter cost: ", 1, 1000000);
    int discount = inputInt("enter discount: ", 1, 50);

    strcpy(items[item_count].code, code);
    strcpy(items[item_count].name, name);
    items[item_count].cost = cost;
    items[item_count].discount = discount;
    item_count++;
    printf("Product added \n");
}
struct Item* checkItemByCode(const char* code) {
    for (int i = 0; i < item_count; i++) {
        if (strcmp(items[i].code, code) == 0) {
            return &items[i];
        }
    }
    return NULL;
}
void scanAndShow() {
    char code[5];
    inputString(code, sizeof(code), "enter code ", 0);
    if (!ValidCode(code)) {
        printf("incorrect input \n");
        return;
    }
    struct Item* item = checkItemByCode(code);
    if (item == NULL) {
        printf("product not found \n");
        return;
    }
    printf("Name: %s\n", item->name);
    printf("Cost: %d Rub\n", item->cost);
    printf("Discount: %d\n", item->discount);
}
void scanAndAddToReceipt() {
    char code[5];
    inputString(code, sizeof(code), "Enter the product code to add to the receipt: ", 0);
    if (!ValidCode(code)) {
        printf("incorrect input \n");
        return;
    }
    struct Item* item = checkItemByCode(code);
    if (item == NULL) {
        printf("product not found \n");
        return;
    }
    int found = 0;
    for (int i = 0; i < receipt_size; i++) {
        if (strcmp(receipt[i].code, code) == 0) {
            receipt[i].quantity++;
            found = 1;
            break;
        }
    }
    if (!found) {
        if (receipt_size >= MAX_RECEIPT_SIZE) {
            printf("receipt is full \n");
            return;
        }
        strcpy(receipt[receipt_size].code, code);
        receipt[receipt_size].quantity = 1;
        receipt_size++;
    }
    printf("product was added to receipt\n");
}
void printReceipt() {
    if (receipt_size == 0) {
        printf("receipt is empty \n");
        return;
    }
    int total_original = 0;
    int total_discount = 0;
    int total_to_pay = 0;

    printf("\nreceipt\n");
    printf("%s %s %s %s %s\n", "Name", "Cost", "Quantity", "Discount", "Total");

    for (int i = 0; i < receipt_size; i++) {
        struct Item* item = checkItemByCode(receipt[i].code);
        if (!item) continue;
        int q = receipt[i].quantity;
        int c = item->cost;
        int d = item->discount;

        int original_line = c * q;
        int discounted_price_per_c = c * (100 - d) / 100;
        int total_line = discounted_price_per_c * q;
        int discount_line = original_line - total_line;
        printf("%s %d %d %d %d\n", item->name, c, q, d, total_line);
        total_original += original_line;
        total_discount += discount_line;
        total_to_pay += total_line;
    }
    printf("\n");
    printf("Total: %d rub\n", total_original);
    printf("Discount: %d rub\n", total_discount);
    printf("To pay: %d rub\n", total_to_pay);
    printf("\n");
}
void clearReceipt() {
    receipt_size = 0;
}
void Menu() {
    printf("\n Electronic sales register \n");
    printf("1. Add product\n");
    printf("2. Scan and show product\n");
    printf("3. Scan and add to receipt\n");
    printf("4. Show receipt\n");
    printf("5. Generate a final receipt and complete \n");
    printf("Select action: ");
}
int main() {
    addMainItems();
    while (1) {
        Menu();
        int choice = inputInt("", 1, 5);
        switch (choice) {
        case 1:
            addItem();
            break;
        case 2:
            scanAndShow();
            break;
        case 3:
            scanAndAddToReceipt();
            break;
        case 4:
            printReceipt();
            break;
        case 5:
            if (receipt_size == 0) {
                printf("receipt is empty \n");
                break;
            }
            printReceipt();

            printf("new start (1 - yes, 0 - close): ");
            int new_start = inputInt("", 0, 1);
            if (new_start == 1) {
                clearReceipt();
                printf("new receipt has been started \n");
            }
            else {
                printf("\n");
                return 0;
            }
            break;
        }
    }
    return 0;
}