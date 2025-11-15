#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void cleanBuffer() {
	int a;
	while ((a = getchar()) != '\n' && a != EOF);
}
struct product {
    char kod[5];
    char name[30];
    int price;
    int discount;
};
struct cheque {
    char name[30];
    int price;
    int quantity;
    int discount;
};

struct product products[20];
struct cheque cheques[30];
int start(){
    int a;
    printf("Select an operation:\n1. Adding a product description\n 2. 'Scanning' a product and displaying its description\n 3. 'Scanning' a product and adding it to a check\n 4. Displaying a purchase check\n 5.finish the job or start a new receip\n");
    while (scanf("%d", &a) != 1 || a < 1 || a > 5) {
        printf("Error. Enter a number from 1 to 4\n");
        cleanBuffer();
    }
    return a;
}
int main() {
    strcpy(products[0].kod, "1111");
    strcpy(products[0].name, "bread");
    products[0].price = 35;
    products[0].discount = 5;

    strcpy(products[1].kod, "2222");
    strcpy(products[1].name, "milk");
    products[1].price = 80;
    products[1].discount = 20;

    strcpy(products[2].kod, "1234");
    strcpy(products[2].name, "cheese");
    products[2].price = 200;
    products[2].discount = 15;

    strcpy(products[3].kod, "5432");
    strcpy(products[3].name, "oil");
    products[3].price = 280;
    products[3].discount = 10;

    strcpy(products[4].kod, "7890");
    strcpy(products[4].name, "meat");
    products[4].price = 350;
    products[4].discount = 35;
    printf("====== electronic sales register ======\n");
    int a = start();
    int numproduct = 5;
    int chequecount = 0;
    int q = 0;
    do {
        if (a == 1) {
            int c = 0;
            do {
                printf("Enter the barcode,4 digits: \n");
                scanf("%s", products[numproduct].kod);
                if (strlen(products[numproduct].kod) != 4) {
                    printf("Error: The barcode must contain exactly 4 digits!\n");
                    cleanBuffer();
                    continue;
                }

                int digits = 1;
                for (int i = 0; i < 4; i++) {
                    char p = products[numproduct].kod[i];
                    if ((p < '0' || p > '9')) {
                        digits = 0;
                        break;
                    }
                }
                if (digits == 0) {
                    printf("Error: The barcode must contain only digits!\n");
                    cleanBuffer();
                    continue;
                }
                c++;
            } while (c != 1);
            printf("Enter the name: ");
            scanf("%s", products[numproduct].name);
            while (strlen(products[numproduct].name) > 29) {
                printf("Error: The name must contain exactly 29 characters!\n");
                cleanBuffer();
                scanf("%s", products[numproduct].name);
            }

            printf("Enter the price: ");
            while (scanf("%d", &products[numproduct].price) != 1) {
                printf("error. Please enter a valid price.\n");
                cleanBuffer();

            }

            printf("Enter a discount (0-50): ");
            while (scanf("%d", &products[numproduct].discount) != 1 || products[numproduct].discount > 50 || products[numproduct].discount < 0) {
                printf("error. enter the correct discount from 0 to 50 percent\n");
                cleanBuffer();
            }

            numproduct++;
            printf("The product has been added!\n");
            a = start();
            continue;
        }
        
        if (a == 2) {
            int d = 0;
            char scan_kod[5];
            do {
                printf("enter the product code for scanning (4 digits)\n");
                scanf("%s", scan_kod);
                if (strlen(scan_kod) != 4) {
                    printf("Error: The barcode must contain exactly 4 digits!\n");
                    cleanBuffer();
                    continue;
                }

                int digi = 1;
                for (int i = 0; i < 4; i++) {
                    char p = scan_kod[i];
                    if ((p < '0' || p > '9')) {
                        digi = 0;
                        break;
                    }
                }
                if (digi == 0) {
                    printf("Error: The barcode must contain only digits!\n");
                    cleanBuffer();
                    continue;
                }
                d++;
            } while (d != 1);
            int srav = 0;
            for (int i = 0; i <= numproduct; i++) {
                if (strcmp(products[i].kod, scan_kod) == 0) {
                    printf("name: %s", products[i].name);
                    printf("\nprice: %d", products[i].price);
                    printf("\ndiscount: %d", products[i].discount);
                    srav = 1;
                    
                }
            }
            if (srav == 0) {
                printf("The product was not found!\n");
            }
            a = start();
            continue;
        }

        if (a == 3) {
            int z = 0;
            char cheque_kod[5];
            int quantity;
            do {
                printf("enter the code to scan and add the product to the receipt. (4 digits)\n");
                scanf("%s", cheque_kod);
                if (strlen(cheque_kod) != 4) {
                    printf("Error: The barcode must contain exactly 4 digits!\n");
                    cleanBuffer();
                    continue;
                }

                int digit = 1;
                for (int i = 0; i < 4; i++) {
                    char p = cheque_kod[i];
                    if ((p < '0' || p > '9')) {
                        digit = 0;
                        break;
                    }
                }
                if (digit == 0) {
                    printf("Error: The barcode must contain only digits!\n");
                    cleanBuffer();
                    continue;
                }
                z++;
            } while (z != 1);
            printf("Enter the quantity: ");
            scanf("%d", &quantity);

            for (int i = 0; i < numproduct; i++) {
                if (strcmp(products[i].kod, cheque_kod) == 0) {
                    for (int j = 0; j < chequecount; j++) {
                        if (strcmp(cheques[j].name, products[i].name) == 0) {
                            cheques[j].quantity += quantity;
                            printf("Added %d pcs. The product %s\n", quantity, products[i].name);
                            a = start();
                            continue;
                        }
                    }
                    strcpy(cheques[chequecount].name, products[i].name);
                    cheques[chequecount].price = products[i].price;
                    cheques[chequecount].quantity = quantity;
                    cheques[chequecount].discount = products[i].discount;
                    chequecount++;

                    printf("Product %s added to receipt\n", products[i].name);
                    a = start();
                    continue;
                   
                   
                }
            }
            printf("The product has not been found!\n");
            a = start();
            continue;
        }
        if (a == 4) {
            if (chequecount == 0) {
                printf("The check is empty!\n");
                a = start();
                continue;
            }
            printf("\n=== CURRENT RECEIPT ===\n");
            int summa = 0, alldiscount = 0;
            for (int i = 0; i < chequecount; i++) {
                int onesum = cheques[i].price * cheques[i].quantity;
                int prosdiscount = onesum * cheques[i].discount / 100;
                int finalsum = onesum - prosdiscount;
                printf(" %s - %d rub.x %d pcs. - %d %  = %d rub\n", cheques[i].name, cheques[i].price, cheques[i].quantity, cheques[i].discount, finalsum);
                summa += onesum;
                alldiscount += prosdiscount;
            }
            printf("------------------------\n");
            printf("Total cost: %d rub.\n", summa);
            printf("Discount: %d rub.\n", alldiscount);
            printf("total: %d rub.\n", summa - alldiscount);
            a = start();
            continue;
        }
        if (a == 5) {
            if (chequecount == 0) {
                printf("The check is empty!\n");
                return;
            }
            printf("\n=== CURRENT RECEIPT ===\n");
            int summa = 0, alldiscount = 0;
            for (int i = 0; i < chequecount; i++) {
                int onesum = cheques[i].price * cheques[i].quantity;
                int prosdiscount = onesum * cheques[i].discount / 100;
                int finalsum = onesum - prosdiscount;
                printf(" %s - %d rub.x %d pcs. - %d %  = %d rub\n", cheques[i].name, cheques[i].price, cheques[i].quantity, cheques[i].discount, finalsum);
                summa += onesum;
                alldiscount += prosdiscount;
            }
            printf("------------------------\n");
            printf("Total cost: %d rub.\n", summa);
            printf("Discount: %d rub.\n", alldiscount);
            printf("total: %d rub.\n", summa - alldiscount);

            printf("make a choice, 1 - complete the work, 2 - start creating a new receipt");
            int x;
            scanf("%d", &x);
            if ( x != 1 || x != 2) {
                printf("mistake.enter your choice with the number 1 or 2\n");
                scanf("%d", &x);
            }
            if (x == 1) {
                printf("Thanks for the purchase!\n");
                q++;
            }
            else {
                chequecount = 0;
                printf("A new receipt has been started!\n");
                a = start();
                continue;
            }
        }
    }while (q != 1);
}



