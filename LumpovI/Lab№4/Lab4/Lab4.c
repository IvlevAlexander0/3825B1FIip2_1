#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cleanBuffer() {
    int a;
    while ((a = getchar()) != '\n' && a != EOF);
}
typedef struct {
    char barcode[5];
    char name[100];
    double price;
    double discount;
} product;

typedef struct {
    char name[100];
    double price;
    int quantity;
    double discount;
} cheque;

product products[100];
cheque cheques[100];
int operation() {
    int op;
    printf("Select an operation: \n");
    printf("1. Adding a product info;\n");
    printf("2. Displaying a product info;\n");
    printf("3. Adding a prodect to check;\n");
    printf("4.Total information about check;\n");
    printf("5.Exit from system or create a new check;\n");
    while (scanf("%d", &op) != 1 || op < 1 || op > 5) {
        printf("Error: inccorect input!!!\n");
        cleanBuffer();
    }
    return op;
}
int main() {
    strcpy(products[0].barcode, "1111");
    strcpy(products[0].name, "bread");
    products[0].price = 80.00;
    products[0].discount = 5.0;

    strcpy(products[1].barcode, "2222");
    strcpy(products[1].name, "egg");
    products[1].price = 100.00;
    products[1].discount = 20.0;

    strcpy(products[2].barcode, "3333");
    strcpy(products[2].name, "pasta");
    products[2].price = 200.0;
    products[2].discount = 15.0;

    strcpy(products[3].barcode, "4444");
    strcpy(products[3].name, "waffle");
    products[3].price = 170.0;
    products[3].discount = 10.0;

    strcpy(products[4].barcode, "5555");
    strcpy(products[4].name, "apple");
    products[4].price = 120.0;
    products[4].discount = 35.0;
    printf("-------- Supermarket 24/7 --------\n");
    int op = operation();
    int cur_prod_count = 5;
    int cur_check_count = 0;
    int flag = 0;
    do {
        switch (op) {
        case 1:
        {
            int fl = 0;
            do {
                printf("Enter the barcode(4 digits): ");
                scanf("%s", products[cur_prod_count].barcode);
                if (strlen(products[cur_prod_count].barcode) != 4) {
                    printf("Error: the barcode must contain only 4 digits!\n");
                    cleanBuffer();
                    continue;
                }

                int digits = 1;
                for (int i = 0; i < 4; i++) {
                    char p = products[cur_prod_count].barcode[i];
                    if ((p < '0' || p > '9')) {
                        digits = 0;
                        break;
                    }
                }
                if (digits == 0) {
                    printf("Error: the barcode must contain only digits!\n");
                    cleanBuffer();
                    continue;
                }
                int u = 0;
                for (int i = 0; i < cur_prod_count; i++) {
                    if (strcmp(products[i].barcode, products[cur_prod_count].barcode) == 0) {
                        printf("error: this code is occupied with another product.\n");
                        u = 1;
                        break;
                    }
                }
                if (u == 1) {
                    continue;
                }
                fl++;
            } while (fl != 1);
            printf("Enter the name: ");
            scanf("%s", products[cur_prod_count].name);
            while (strlen(products[cur_prod_count].name) > 99) {
                printf("Error: The name must contain exactly 99 characters!\n");
                cleanBuffer();
                scanf("%s", products[cur_prod_count].name);
            }

            printf("Enter the price: ");
            while (scanf("%lf", &products[cur_prod_count].price) != 1) {
                printf("Error:. inccorect price input!!!\n");
                cleanBuffer();

            }

            printf("Enter a discount (0-50): ");
            while (scanf("%lf", &products[cur_prod_count].discount) != 1 || products[cur_prod_count].discount > 50 || products[cur_prod_count].discount < 0) {
                printf("error. enter the correct discount from 0 to 50 percent\n");
                cleanBuffer();
            }

            cur_prod_count++;
            printf("The product has been added!\n");
            op = operation();
            continue;
            break;
        }

        case 2:
        {
            int fl2 = 0;
            char scan_kod[5];
            do {
                printf("Enter the product code for scanning (4 digits): ");
                scanf("%s", scan_kod);
                if (strlen(scan_kod) != 4) {
                    printf("Error: the barcode must contain only 4 digits!\n");
                    cleanBuffer();
                    continue;
                }

                int v = 1;
                for (int i = 0; i < 4; i++) {
                    char p = scan_kod[i];
                    if ((p < '0' || p > '9')) {
                        v = 0;
                        break;
                    }
                }
                if (v == 0) {
                    printf("Error: The barcode must contain only digits!\n");
                    cleanBuffer();
                    continue;
                }
                fl2++;
            } while (fl2 != 1);
            int srav = 0;
            for (int i = 0; i <= cur_prod_count; i++) {
                if (strcmp(products[i].barcode, scan_kod) == 0) {
                    printf("name: %s", products[i].name);
                    printf("\nprice: %.2lf", products[i].price);
                    printf("\ndiscount: %.2lf\n", products[i].discount);
                    srav = 1;

                }
            }
            if (srav == 0) {
                printf("The product was not found!\n");
            }
            op = operation();
            continue;
            break;
        }

        case 3:
        {
            int fl3 = 0;
            char cheque_kod[5];
            int quantity;
            do {
                printf("Enter the code to scan and add the product to the receipt (4 digits): ");
                scanf("%s", cheque_kod);
                if (strlen(cheque_kod) != 4) {
                    printf("Error: The barcode must contain only 4 digits!\n");
                    cleanBuffer();
                    continue;
                }

                int t = 1;
                for (int i = 0; i < 4; i++) {
                    char p = cheque_kod[i];
                    if ((p < '0' || p > '9')) {
                        t = 0;
                        break;
                    }
                }
                if (t == 0) {
                    printf("Error: The barcode must contain only digits!\n");
                    cleanBuffer();
                    continue;
                }
                fl3++;
            } while (fl3 != 1);
            printf("Enter the quantity: ");
            scanf("%d", &quantity);
            int found = 0;
            for (int i = 0; i < cur_prod_count; i++) {
                if (strcmp(products[i].barcode, cheque_kod) == 0) {
                    found = 1;
                    int incheque = 0;
                    for (int j = 0; j < cur_check_count; j++) {
                        if (strcmp(cheques[j].name, products[i].name) == 0) {
                            cheques[j].quantity += quantity;
                            printf("Added %d pcs. The product %s\n", quantity, products[i].name);
                            incheque = 1;
                            break;
                        }
                    }
                    if (incheque == 0) {
                        strcpy(cheques[cur_check_count].name, products[i].name);
                        cheques[cur_check_count].price = products[i].price;
                        cheques[cur_check_count].quantity = quantity;
                        cheques[cur_check_count].discount = products[i].discount;
                        cur_check_count++;

                        printf("Product %s added to receipt\n", products[i].name);
                    }
                    break;


                }
            }
            if (found == 0) {
                printf("The product has not been found!\n");
            }
            op = operation();
            continue;
            break;
        }

        case 4:
        {
            if (cur_check_count == 0) {
                printf("The check is empty!\n");
                op = operation();
                continue;
            }
            printf("\n----- TOTAL CHECK -----\n");
            double total_sum = 0;
            double total_discount = 0;
            for (int i = 0; i < cur_check_count; i++) {
                double onesum = cheques[i].price * cheques[i].quantity;
                double prosdiscount = onesum * (cheques[i].discount / 100);
                double finalsum = onesum - prosdiscount;
                printf(" %s - %.2lf rub; Quantity: %d ; Discount: %.2lf  --> %.2lf rub\n", cheques[i].name, cheques[i].price, cheques[i].quantity, cheques[i].discount, finalsum);
                total_sum += onesum;
                total_discount += prosdiscount;
            }
            printf("------------------------\n");
            printf("Total cost(without discount): %.2lf rub.\n", total_sum);
            printf("Discount: %.2lf rub.\n", total_discount);
            printf("Total: %.2lf rub.\n", total_sum - total_discount);
            printf("------------------------\n");
            op = operation();
            continue;
            break;
        }

        case 5:
        {
            printf("Input 1 - complete the work, or 2 - start creating a new receipt");
            int x;
            scanf("%d", &x);
            if (x != 1 && x != 2) {
                printf("Please input only 1 or 2\n");
                scanf("%d", &x);
            }
            if (x == 1) {
                printf("Thanks for the purchase!\n");
                flag++;
            }
            else {
                cur_check_count = 0;
                printf("A new check was created!\n");
                op = operation();
                continue;
                break;
            }
        }
        }
    } while (flag != 1);
}