#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define max_prod 20
#define max_items 20
#define len_name 20
#define len_kod 4

char product_names[max_prod][20];
char product_kods[max_prod][5];
int product_costs[max_prod];
int product_sales[max_prod];
int name_len[max_prod];
int product_count = 5;

char receipt_kods[max_items][5];
int count[max_items];
int receipt_count = 0;

void read_tovar(char name[], int size, char kod[4], int stoim, int skidka, int c, int k) {
    printf("Name: ");
    for (int i = 0; i < size && name[i] != '\0'; i++) {
        printf("%c", name[i]);
    }
    printf("\nCode: ");
    for (int i = 0; i < 4; i++) {
        printf("%c", kod[i]);
    }
    printf("\nCost: %d", stoim);
    if (k) {
        printf("\nCount: %d", c);
    }
    printf("\nSale: %d%%", skidka);
    printf("\n");
}

int compare_kod(char kod1[4], char kod2[4]) {
    for (int i = 0; i < 4; i++) {
        if (kod1[i] != kod2[i]) return 0;
    }
    return 1;
}

int digit(char c) {
    return (c >= '0' && c <= '9');
}

int alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}


int find(char kod[len_kod]) {
    for (int i = 0; i < product_count; i++) {
        if (compare_kod(kod, product_kods[i])) {
            return i;
        }
    }
    return -1;
}

int find_rec(char kod[len_kod]) {
    for (int i = 0; i < receipt_count; i++) {
        if (compare_kod(kod, receipt_kods[i])) {
            return i;
        }
    }
    return -1;
}


void copy_name(char dest[len_name], char src[len_name], int max_len) {
    int i;
    for (i = 0; i < max_len && i < len_name; i++) {
        dest[i] = src[i];
    }
}

void copy_kod(char dest[len_kod], char src[len_kod]) {
    for (int i = 0; i < len_kod; i++) {
        dest[i] = src[i];
    }
}

void main() {
    char prog = '1';
    printf("Welcome to the electronic sales register \n");
    printf("----------------------------------------\n");
    char milk_name[] = "milk";
    char milk_kod[] = "1429";
    copy_name(product_names[0], milk_name, 4);
    copy_kod(product_kods[0], milk_kod);
    product_costs[0] = 78;
    product_sales[0] = 25;
    name_len[0] = 4;

    char bread_name[] = "bread";
    char bread_kod[] = "1234";
    copy_name(product_names[1], bread_name, 5);
    copy_kod(product_kods[1], bread_kod);
    product_costs[1] = 30;
    product_sales[1] = 2;
    name_len[1] = 5;

    char water_name[] = "water";
    char water_kod[] = "5678";
    copy_name(product_names[2], water_name, 5);
    copy_kod(product_kods[2], water_kod);
    product_costs[2] = 37;
    product_sales[2] = 2;
    name_len[2] = 5;

    char apple_name[] = "apple";
    char apple_kod[] = "9012";
    copy_name(product_names[3], apple_name, 5);
    copy_kod(product_kods[3], apple_kod);
    product_costs[3] = 15;
    product_sales[3] = 10;
    name_len[3] = 5;

    char meat_name[] = "meat";
    char meat_kod[] = "3456";
    copy_name(product_names[4], meat_name, 4);
    copy_kod(product_kods[4], meat_kod);
    product_costs[4] = 220;
    product_sales[4] = 15;
    name_len[4] = 4;

    printf("Available products: \n");
    printf("1429 - Milk\n1234 - Bread\n5678 - Water\n9012 - Apple\n3456 - Meat\n");
    printf("----------------------------------------\n");
    do {
        printf("\nSelect an action: \n");
        printf("1. Add product description\n");
        printf("2. Scan product and show info\n");
        printf("3. Scan product and add to receipt\n");
        printf("4. Show receipt\n");
        printf("5. Finalize receipt\n");
        printf("0. Exit\n");
        printf("Your choice: ");

        char choice;

        do {
            if (scanf(" %c", &choice) != 1) {
                printf("Input error! Please enter a single character: ");
                while (getchar() != '\n');
            }
            else {
                char next = getchar();
                if (next != '\n') {
                    printf("Input error! Please enter only ONE character: ");
                    while (getchar() != '\n'); 
                }
                else {
                    break; 
                }
            }
        } while (1);

        switch (choice) {
        case '1': {
            if (product_count >= max_prod) {
                printf("Cannot add more products.\n");
                break;
            }

            char kod_product[len_kod];
            printf("Enter product code (4 digits): ");

            int error_kod = 0;
            while (!error_kod) {
                error_kod = 1;
                for (int i = 0; i < 4; i++) {
                    if (scanf(" %c", &kod_product[i]) != 1 || !digit(kod_product[i])) {
                        printf("Input error! Please enter exactly 4 digits: ");
                        while (getchar() != '\n');
                        error_kod = 0;
                        break;
                    }
                }

                if (error_kod) {
                    char next;
                    if (scanf("%c", &next) == 1 && next != '\n') {
                        printf("Input error! Please enter exactly 4 digits (no extra characters): ");
                        while (getchar() != '\n');
                        error_kod = 0;
                        continue;
                    }

                    if (find(kod_product) != -1) {
                        printf("Product with this code already exists! Use different code: ");
                        error_kod = 0;
                    }
                }
            }
            char name_product[20];
            printf("Enter product name: ");

            int i = 0;
            int error_name = 0;
            while (!error_name) {
                i = 0;
                char c;
                scanf(" %c", &c);
                if (c != '\n') {
                    if (!alpha(c)) {
                        printf("Input error! Use only letters: ");
                        while (getchar() != '\n');
                        continue;
                    }
                    name_product[i] = c;
                    i++;

                    while (i < len_name) {
                        c = getchar();
                        if (c == '\n') {
                            break;
                        }

                        if (!alpha(c) && c != ' ') {
                            printf("Input error! Use only letters: ");

                            while (getchar() != '\n');
                            i = 0;
                            break;
                        }
                        name_product[i] = c;
                        i++;
                    }
                }
                if (i > 0) {
                    error_name = 1;
                }
                else {
                    printf("Name cannot be empty! Enter product name: ");
                }
            }

            int cost_product;
            printf("Enter cost: ");
            while (scanf("%d", &cost_product) != 1 || cost_product <= 0) {
                printf("Enter positive number: ");
                while (getchar() != '\n');
            }

            int sale_product;
            printf("Enter sale (0-50): ");
            while (scanf("%d", &sale_product) != 1 || sale_product < 0 || sale_product > 50) {
                printf("Enter number between 0-50: ");
                while (getchar() != '\n');
            }

            copy_name(product_names[product_count], name_product, 20);
            copy_kod(product_kods[product_count], kod_product);
            product_costs[product_count] = cost_product;
            product_sales[product_count] = sale_product;
            name_len[product_count] = i;
            product_count++;

            printf("Product added successfully!\n");
            break;
        }

        case '2': {
            char kod[len_kod];
            printf("Enter product code: ");

            int error_kod = 0;
            while (!error_kod) {
                error_kod = 1;
                for (int i = 0; i < len_kod; i++) {
                    if (scanf(" %c", &kod[i]) != 1 || !digit(kod[i])) {
                        printf("Enter 4 digits: ");
                        while (getchar() != '\n');
                        error_kod = 0;
                        break;
                    }
                }
            }

            int product_index = find(kod);
            if (product_index != -1) {
                printf("\n");
                read_tovar(product_names[product_index], name_len[product_index], product_kods[product_index], product_costs[product_index], product_sales[product_index], 0, 0);
            }
            else {
                printf("Product not found!\n");
            }
            break;
        }

        case '3': {
            char kod[len_kod];
            printf("Enter product code to add to receipt: ");

            int error_kod = 0;
            while (!error_kod) {
                error_kod = 1;
                for (int i = 0; i < len_kod; i++) {
                    if (scanf(" %c", &kod[i]) != 1 || !digit(kod[i])) {
                        printf("Enter 4 digits: ");
                        while (getchar() != '\n');
                        error_kod = 0;
                        break;
                    }
                }
            }

            int product_index = find(kod);
            if (product_index != -1) {
                if (receipt_count >= max_items) {
                    printf("Cannot add more products.\n");
                }
                else {
                    int receipt_index = find_rec(kod);
                    if (receipt_index != -1) {
                        count[receipt_index]++;
                        printf("Product '");
                        for (int j = 0; j < name_len[product_index]; j++) {
                            printf("%c", product_names[product_index][j]);
                        }
                        printf("' quantity increased to %d\n", count[receipt_index]);
                    }
                    else {
                        copy_kod(receipt_kods[receipt_count], kod);
                        count[receipt_count] = 1;
                        receipt_count++;
                        printf("Product '");
                        for (int j = 0; j < name_len[product_index]; j++) {
                            printf("%c", product_names[product_index][j]);
                        }
                        printf("' added to receipt!\n");
                    }
                }
            }
            else {
                printf("Product not found! Cannot add to receipt.\n");
            }
            break;
        }

        case '4': {
            if (receipt_count == 0) {
                printf("Receipt is empty!\n");
            }
            else {
                printf("\n--- CURRENT RECEIPT ---\n");
                printf("-------------------------\n");

                float total_cost = 0;
                float total_discount = 0;
                float total_savings = 0;

                for (int i = 0; i < receipt_count; i++) {
                    int product_index = find(receipt_kods[i]);
                    if (product_index != -1) {
                        int price = product_costs[product_index];
                        int c = count[i];
                        int sale = product_sales[product_index];
                        int total_orig = c * price;
                        float total_dis = c * total_orig * (100 - sale)/100.0;
                        float total = c * price * (sale / 100.0);
                        read_tovar(product_names[product_index], name_len[product_index], product_kods[product_index], product_costs[product_index], product_sales[product_index], c, 1);

                        total_cost += total_orig;
                        total_discount += total_dis;
                        total_savings += total;
                        printf("-------------------------\n");
                    }
                }

                printf("Total cost: %.2f\n", total_cost);
                printf("Total savings: %.2f\n", total_savings);
                printf("Final amount: %.2f\n", total_discount);
            }
            break;
        }

        case '5': {
            if (receipt_count == 0) {
                printf("Cannot finalize empty receipt!\n");
            }
            else {
                printf("\n=== FINAL RECEIPT ===\n");
                printf("-------------------------\n");
                float total_cost = 0;
                float total_discount = 0;
                float total_savings = 0;

                for (int i = 0; i < receipt_count; i++) {
                    int product_index = find(receipt_kods[i]);
                    if (product_index != -1) {
                        int price = product_costs[product_index];
                        int c = count[i];
                        int sale = product_sales[product_index];
                        int total_orig = c * price;
                        float total_dis = c * total_orig * (100 - sale) / 100.0;
                        float total = c * price * (sale / 100.0);
                        read_tovar(product_names[product_index], name_len[product_index], product_kods[product_index], product_costs[product_index], product_sales[product_index], c, 1);

                        total_cost += total_orig;
                        total_discount += total_dis;
                        total_savings += total;
                        printf("-------------------------\n");
                    }
                }

                printf("TOTAL COST: %.2f\n", total_cost);
                printf("TOTAL SAVINGS: %.2f\n", total_savings);
                printf("FINAL AMOUNT TO PAY: %.2f\n", total_discount);
                printf("Thank you for your purchase!\n");

                printf("Clear receipt and start new? (y/n): ");
                char confirm;
                scanf(" %c", &confirm);
                if (confirm == 'y' || confirm == 'Y') {
                    receipt_count = 0;
                    printf("Receipt cleared. Ready for new purchase.\n");
                }
            }
            break;
        }

        case '0':
            prog = '0';
            break;

        default:
            printf("Input error! Please select 0-5.\n");
        }
        printf("----------------------------------------\n");

    } while (prog == '1');
}
