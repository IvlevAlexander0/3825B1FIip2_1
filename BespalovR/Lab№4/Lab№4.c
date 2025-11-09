#define _CRT_SECURE_NO_WARNINGS
#define DESCRIPTION_LENGTH 256
#define ITEM_AMOUNT 5
#define BARCODE_LENGTH 4
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
    char barcode[ITEM_AMOUNT][BARCODE_LENGTH] = { 0 };
    int price[ITEM_AMOUNT] = { 0 };
    for (int i = 0; i < ITEM_AMOUNT; ++i) {
        price[i] = 1 + rand() % 1000;
        for (int j = 0; j < BARCODE_LENGTH; ++j) {
            barcode[i][j] = rand() % 10;
        }
    }

    int option = 0;
    int item = 0;
    char c;
    int i;
    char desc[ITEM_AMOUNT][DESCRIPTION_LENGTH];
    for (;;) {

        options_menu();
        option = input_5(option);

        switch (option) {

        case 1:

            item_menu();
            item = input_5(item);
            printf("Input item's description.\n");
            while ((c = getchar()) != '\n') {}
            for (i = 0; (desc[item][i] = getchar()) != '\n'; ++i);
            desc[item][i] = '\0';
            break;

        case 2:
            item_menu();
            item = input_5(item);

            printf("\n%s\n", desc[item]);
            break;

        case 3:
            item_menu();
            item = input_5(item);

            break;

        case 4:
            break;

        case 5:
            break;
        }
    }
}