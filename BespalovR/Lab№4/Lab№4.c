#define _CRT_SECURE_NO_WARNINGS
#define DESCRIPTION_LENGTH 128
#define BARCODE_LENGTH 4
#define ITEM_AMOUNT 5
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void options_menu() {
    printf("-------------------------------------------\n");
    printf("\nSelect option:\n\n");
    printf("1.Add description to the item.\n");
    printf("2.Scan an item and output it's description.\n");
    printf("3.Scan an item and add it to the receipt.\n");
    printf("4.See receipt.\n");
    printf("5.Get receipt.\n\n");
} 
void item_menu() {
    printf("-------------------------------------------\n");
    printf("\nSelect an item:\n\n");
    printf("1.Apple.\n");
    printf("2.Banana.\n");
    printf("3.Cherry.\n");
    printf("4.Doughnut.\n");
    printf("5.Eggplant.\n\n");
}
int input_5(int input) {
    while (scanf("%d", &input) == 0 || input > 5 || input < 1) {
        printf("Incorrect input. Please try again.\n");
        char c;
        while ((c = getchar()) != '\n') {}
    }
    return input;
}
int main() {
    srand(time(NULL));
    int cart[ITEM_AMOUNT] = { 0 };
    int price[ITEM_AMOUNT];
    float discount[ITEM_AMOUNT];
    int barcode[ITEM_AMOUNT][BARCODE_LENGTH] ;
    char description[ITEM_AMOUNT][DESCRIPTION_LENGTH] = { 0 };
    for ( int i = 0; i < ITEM_AMOUNT; ++i) {
        discount[i] = rand() % 51 / 100.;
        price[i] = 1 + rand() % 1000;
        for (int j = 0; j < BARCODE_LENGTH; ++j) {
            barcode[i][j] = rand() % 10;
        }
    }
    int option = 0;
    int toggle = 0;
    char c;
    int t1 = 0;
    float t2 = 0;
    int t22 = 1;
    int t3 = 0;
    int i; 
    for (;;) {
        if (toggle == 2 ) {
            break;
        }
        else if (toggle == 1) {
            cart[0] = cart[1] = cart[2] = cart[3] = cart[4] = 0;
        }
        options_menu();
        option = input_5(option);

        switch (option) {

        case 1:

            item_menu();
            option = input_5(option) - 1;
            printf("Input item's description.\n");
            while ((c = getchar()) != '\n') {}
            for (i = 0; (description[option][i] = getchar()) != '\n'; ++i);
            description[option][i] = '\0';
            break;

        case 2:
            item_menu();
            option = input_5(option) - 1;
            printf("-------------------------------------------\n");
            printf("\nPrice: %d\n", price[option]);
            printf("Discount: %.2f\n", discount[option]);
            printf("Barcode: %d%d%d%d\n", barcode[option][0], barcode[option][1], barcode[option][2], barcode[option][3]);
            printf("Amount in the cart: %d\n", cart[option]);
            printf("Description: %s\n", description[option]);
            break;

        case 3:
            item_menu();
            option = input_5(option) - 1;
            cart[option] += 1;
            break;

        case 4:
            printf("-------------------------------------------\n");
            printf("Receipt:\n");
            printf("\nApples:\nPrice %d | Amount X%d | Discount %.2f | Total %d\n", price[0], cart[0], discount[0], (int)(price[0] * cart[0] * discount[0]));
            printf("\nBananas:\nPrice %d | Amount X%d | Discount %.2f | Total %d\n", price[1], cart[1], discount[1], (int)(price[1] * cart[1] * discount[1]));
            printf("\nCherries:\nPrice %d | Amount X%d | Discount %.2f | Total %d\n", price[2], cart[2], discount[2], (int)(price[2] * cart[2] * discount[2]));
            printf("\nDoughnuts:\nPrice %d | Amount X%d | Discount %.2f | Total %d\n", price[3], cart[3], discount[3], (int)(price[3] * cart[3] * discount[3]));
            printf("\nEggplants:\nPrice %d | Amount X%d | Discount %.2f | Total %d\n", price[4], cart[4], discount[4], (int)(price[4] * cart[4] * discount[4]));
            for (i = 0; i < ITEM_AMOUNT; ++i) {
                t1 += price[i] * cart[i];
                t2 += discount[i] * cart[i];
                t22 += cart[i];
                t3 += (int)(price[i] * cart[i] * discount[i]);
            }
            printf("\nTotal cost without discount : %d | Total disount: %.2f | Total cost with discount %d\n", t1, (t2 / t22) , t3);
            t1 = t2 = t22 = t3 = 0;
            break;

        case 5:
            printf("-------------------------------------------\n");
            printf("Receipt:\n");
            printf("\nApples:\nPrice %d | Amount X%d | Discount %.2f | Total %d\n", price[0], cart[0], discount[0], (int)(price[0] * cart[0] * discount[0]));
            printf("\nBananas:\nPrice %d | Amount X%d | Discount %.2f | Total %d\n", price[1], cart[1], discount[1], (int)(price[1] * cart[1] * discount[1]));
            printf("\nCherries:\nPrice %d | Amount X%d | Discount %.2f | Total %d\n", price[2], cart[2], discount[2], (int)(price[2] * cart[2] * discount[2]));
            printf("\nDoughnuts:\nPrice %d | Amount X%d | Discount %.2f | Total %d\n", price[3], cart[3], discount[3], (int)(price[3] * cart[3] * discount[3]));
            printf("\nEggplants:\nPrice %d | Amount X%d | Discount %.2f | Total %d\n", price[4], cart[4], discount[4], (int)(price[4] * cart[4] * discount[4]));
            for (i = 0; i < ITEM_AMOUNT; ++i) {
                t1 += price[i] * cart[i];
                t2 += discount[i] * cart[i];
                t22 += cart[i];
                t3 += (int)(price[i] * cart[i] * discount[i]);
            }
            printf("\nTotal cost without discount : %d | Total disount: %.2f | Total cost with discount %d\n", t1, (t2 / t22), t3);
            t1 = t2 = t3 = 0;
            printf("Would you like to start a new receipt?( 1 - Yes / 2 - No )\n");
            while (scanf("%d", &toggle) == 0 || toggle > 2 || toggle < 1) {
                printf("Incorrect input. Please try again.\n");
                char c;
                while ((c = getchar()) != '\n') {}
            }
            break;
        }
    }
}