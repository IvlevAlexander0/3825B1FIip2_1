#define _CRT_SECURE_NO_WARNINGS
#define size_of_code 4
#define max 20
#include <stdio.h>
int stop = 0;
struct product {
    char code[size_of_code];
    char name[31];
    int price;
    int discount;
};
struct bill_position {
    struct product position;
    int quantity_of_position;
    int total_price_4_position;
};
struct total_bill {
    struct bill_position products_in_bill[max];
    int total_cost;
    int total_discount;
    int final_total;
    int bill_count;
};
struct product products[max];
int count = 0;
struct total_bill bill;
void copy_code(char arr1[], char arr2[]) {
    for (int i = 0; i < size_of_code; i++) {
        arr1[i] = arr2[i];
    }
}
int compare_codes(char code1[], char code2[]) {
    for (int i = 0; i < size_of_code; i++) {
        if (code1[i] != code2[i]) {
            return 0;
        }
    }
    return 1;
}
void copy_string(char s1[], char s2[]) {
    int i = 0;
    while (s1[i] != '\0' && i < 30) {
        s2[i] = s1[i];
        i++;
    }
    s2[i] = '\0';
}
void base() {
    char code1[size_of_code] = { '1','2','3','4' };
    copy_code(products[0].code, code1);
    copy_string("Tango", products[0].name);
    products[0].price = 90;
    products[0].discount = 10;
    char code2[size_of_code] = { '0','1','2','3' };
    copy_code(products[1].code, code2);
    copy_string("Mango", products[1].name);
    products[1].price = 70;
    products[1].discount = 7;
    char code3[size_of_code] = { '3','1','2','4' };
    copy_code(products[2].code, code3);
    copy_string("cheese", products[2].name);
    products[2].price = 2000;
    products[2].discount = 50;
    char code4[size_of_code] = { '1','2','2','4' };
    copy_code(products[3].code, code4);
    copy_string("healing salve", products[3].name);
    products[3].price = 100;
    products[3].discount = 5;
    char code5[size_of_code] = { '4','3','2','1' };
    copy_code(products[4].code, code5);
    copy_string("iron branch", products[4].name);
    products[4].price = 50;
    products[4].discount = 5;
    count = 5;
}
int find_product(char code1[]) {
    for (int i = 0; i < count; i++) {
        if (compare_codes(products[i].code, code1)) {
            return i;
        }
    }
    return -1;
}
void add_2_base() {
    if (count >= max) {
        printf("The product limit has been reached\n");
        return;
    }
    char input_code[size_of_code + 1];
    printf("Add new product to base\n");
    printf("Enter the code (4 digits 0-9)\n");
    if (scanf("%4s", input_code) != 1) {
        printf("Incorrect input\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    char code1[size_of_code];
    for (int i = 0; i < size_of_code; i++) {
        code1[i] = input_code[i];
    }
    if (find_product(code1) != -1) {
        printf("Product with such code already exists\n");
        return;
    }
    copy_code(products[count].code, code1);
    printf("Enter the name\n");
    if (scanf("%30s", products[count].name) != 1) {
        printf("Incorrect input\n");
        return;
    }
    printf("Enter the price\n");
    if (scanf("%d", &products[count].price) != 1) {
        printf("Incorrect input\n");
        return;
    }
    printf("Enter the discount (1-50%%)\n");
    if (scanf("%d", &products[count].discount) != 1) {
        printf("Incorrect input\n");
        return;
    }
    if (products[count].discount < 1 || products[count].discount > 50) {
        printf("Discount must be from 1 to 50 percent\n");
        products[count].discount = 0;
    }
    count++;
    printf("Product was successfully added\n");
}
void scan_product() {
    char input_code[size_of_code + 1];
    printf("Enter product code");
    if (scanf("%4s", input_code) != 1) {
        printf("Incorrect input\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    char code1[size_of_code];
    for (int i = 0; i < size_of_code; i++) {
        code1[i] = input_code[i];
    }
    int founded = find_product(code1);
    if (founded == -1) {
        printf("No product with such code in base\n");
        return;
    }
    printf("Name: %s\n", products[founded].name);
    printf("Price: %d\n", products[founded].price);
    printf("Discount: %d%%\n", products[founded].discount);
}
void bill_in() {
    bill.total_cost = 0;
    bill.total_discount = 0;
    bill.final_total = 0;
    bill.bill_count = 0;
}
void add_2_bill() {
    char input_code[size_of_code + 1];
    printf("Enter the code of the product\n");
    if (scanf("%4s", input_code) != 1) {
        printf("Incorrect input\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    char code1[size_of_code];
    for (int i = 0; i < size_of_code; i++) {
        code1[i] = input_code[i];
    }
    int index = find_product(code1);
    if (index == -1) {
        printf("No product with such code in base\n");
        return;
    }
    for (int i = 0; i < bill.bill_count; i++) {
        if (compare_codes(bill.products_in_bill[i].position.code, code1)) {
            bill.products_in_bill[i].quantity_of_position++;
            int price_with_discount = bill.products_in_bill[i].position.price *
                (100 - bill.products_in_bill[i].position.discount) / 100;
            bill.products_in_bill[i].total_price_4_position =
                bill.products_in_bill[i].quantity_of_position * price_with_discount;
            printf("Product was successfully added to the bill\n");
            return;
        }
    }
    copy_code(bill.products_in_bill[bill.bill_count].position.code, products[index].code);
    copy_string(products[index].name, bill.products_in_bill[bill.bill_count].position.name);
    bill.products_in_bill[bill.bill_count].position.price = products[index].price;
    bill.products_in_bill[bill.bill_count].position.discount = products[index].discount;
    bill.products_in_bill[bill.bill_count].quantity_of_position = 1;
    int price_with_discount = products[index].price * (100 - products[index].discount) / 100;
    bill.products_in_bill[bill.bill_count].total_price_4_position = price_with_discount;
    bill.bill_count++;
    printf("Product was successfully added to the bill\n");
}
void form_the_bill() {
    if (bill.bill_count == 0) {
        printf("bill is empty!\n");
        return;
    }
    bill.total_cost = 0;
    bill.total_discount = 0;
    bill.final_total = 0;
    printf("\n");
    printf("BILL\n");
    for (int i = 0; i < bill.bill_count; i++) {
        struct bill_position position1 = bill.products_in_bill[i];
        int total_for_1_position = position1.position.price * position1.quantity_of_position;
        int discount_sum = total_for_1_position - position1.total_price_4_position;
        printf("%s - %d rub. x %d - %d%% = %d rub.\n",
            position1.position.name,
            position1.position.price,
            position1.quantity_of_position,
            position1.position.discount,
            position1.total_price_4_position);
        bill.total_cost += total_for_1_position;
        bill.total_discount += discount_sum;
        bill.final_total += position1.total_price_4_position;
    }
    printf("\n");
    printf("Total price for all items: %d rub.\n", bill.total_cost);
    printf("Discount: %d rub.\n", bill.total_discount);
    printf("TOTAL: %d rub.\n", bill.final_total);
}
void finish_purchasing() {
    if (bill.bill_count == 0) {
        printf("bill is empty\n");
        return;
    }
    printf("Would you like to form a new bill? (Y/N)\n");
    char choice;
    scanf("%c", &choice);
    switch (choice) {
    case 'Y':
    case 'y':
        bill_in();
        printf("You have started forming a new bill\n");
        break;
    case 'N':
    case 'n':
        printf("Thanks for purchasing, have a nice day!\n");
        stop = 1;
        break;
    default:
        printf("Incorrect value\n");
    }
}
int main() {
    base();
    bill_in();
    int choice;
    while (!stop) {
        printf("menu\n");
        printf("1 - Add product to base\n");
        printf("2 - Scan the product\n");
        printf("3 - Add product to the bill\n");
        printf("4 - Form the total bill\n");
        printf("5 - Finish the purchasing\n");
        if (scanf("%d", &choice) != 1) {
            printf("Incorrect input\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        switch (choice) {
        case 1:
            add_2_base();
            break;
        case 2:
            scan_product();
            break;
        case 3:
            add_2_bill();
            break;
        case 4:
            form_the_bill();
            break;
        case 5:
            finish_purchasing();
            break;
        default:
            printf("Incorrect value\n");
        }
    }
    return 0;
}