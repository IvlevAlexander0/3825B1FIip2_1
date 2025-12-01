#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* strc(const char* buffer) {
    int n = strlen(buffer);
    char* destination = calloc(n + 1, sizeof(char));
    strcpy(destination, buffer);
    return destination;
}

int main() {



    int  amount = 5;
    int* discount = calloc(amount, sizeof(int));
    int* quantity = calloc(amount, sizeof(int));
    int* barcode = calloc(amount, sizeof(int));
    int* price = calloc(amount, sizeof(int));
    char** names = calloc(amount, sizeof(char*));
    names[0] = strc("Apples");
    names[1] = strc("Butter");
    names[2] = strc("Cheese");
    names[3] = strc("Donuts");
    names[4] = strc(" Eggs ");
    for (int i = 0; i < amount; ++i) {
        barcode[i] = 1111 * (i + 1);
        quantity[i] = 0;
        price[i] = rand() % 1000;
        discount[i] = 1 + rand() % 50;
    }
    char c;
    int t;
    int t1;
    int t11;
    int t2;
    int option = 0;
    char* buffer = calloc ( 256, sizeof(char));


    for (;;) {


        if (option == -1) {
            option = 0;
            for (int i = 0; i < amount; ++i) {
                quantity[i] = 0;
            }
        }
        else if (option == -2) {
            break;
        }
        t = t1 = t11 = t2 = 0;
        printf("\nChoose option : \n1.Add new item to the system.\n2.Show item's info.\n3.Add item to the cart.\n4.Show cart.\n5.Get cheque.\n");
        while (scanf("%d", &option) != 1 || option > 5 || option < 1) {
            printf("Incorrect input, please try again.\n");
            while ((c = getchar()) != "\n") {}
        }


        switch (option) {


        case 1:
            printf("Input new item's barcode.(4 digits max. 13 is equal to 0013 barcode)\n");
            while (scanf("%d", &t) != 1 || t > 9999 || t < 0) {
                printf("Incorrect input, please try again.\n");
                while ((c = getchar()) != "\n") {}
            }
            for (int i = 0; i < amount; ++i) {
                if (t == barcode[i]) {
                    t = -1;
                }
            }
            if (t == -1) {
                printf("Incorrect barcode.\n");
                continue;
            }
            ++amount;
            discount = realloc(discount, amount * sizeof(int));
            quantity = realloc(quantity, amount * sizeof(int));
            barcode = realloc(barcode, amount * sizeof(int));
            price = realloc(price, amount * sizeof(int));
            names = realloc(names, amount * sizeof(char*));
            printf("Input new item's name, price and discount%%.\n");
            while (scanf("%s%d%d", buffer, &price[amount - 1], &discount[amount - 1]) != 3 || price[amount - 1] < 1 || discount[amount - 1] > 50 || discount[amount - 1] < 1) {
                printf("Incorrect input, please try again.\n");
                while ((c = getchar()) != "\n") {}
            }
            names[amount - 1] = strc(buffer);
            barcode[amount - 1] = t;
            quantity[amount - 1] = 0;
            break;


        case 2:
            printf("Choose item:\n");
            for (int i = 0; i < amount; ++i) {
                printf("%d - %s\n", i + 1, names[i]);
            }
            while (scanf("%d", &option) != 1 || option > amount || option < 1) {
                printf("Incorrect input, please try again.\n");
                while ((c = getchar()) != "\n") {}
            }
            printf("\n Name  - price - quantity - discount - barcode\n%s\t%d\t%d\t%d%%\t%.4d\n", names[option - 1], price[option - 1], quantity[option - 1], discount[option - 1], barcode[option - 1]);
            break;


        case 3:
            printf("Choose item:\n");
            for (int i = 0; i < amount; ++i) {
                printf("%d - %s\n", i + 1, names[i]);
            }
            while (scanf("%d", &option) != 1 || option > amount || option < 1) {
                printf("Incorrect input, please try again.\n");
                while ((c = getchar()) != "\n") {}
            }
            ++quantity[option];
            break;


        case 4:
            printf("\n Name  - price - quantity - discount - total\n");
            for (int i = 0; i < amount; ++i) {
                if (quantity[i] > 0) {
                    t += price[i] * quantity[i];
                    t1 += discount[i] * quantity[i];
                    t11 += quantity[i];
                    t2 += price[i] * quantity[i] * (100 - discount[i]) / 100;
                    printf("%s -  %d  -     %d    -   %d%%    -   %d\n", names[i], price[i], quantity[i], discount[i], price[i] * quantity[i] * (100 - discount[i]) / 100);
                }
            }
            if (t11 != 0) {
                printf("\nTo pay without discount: %d\nAverage discount: %d%%\nTo pay: %d\n", t, t1 / t11, t2);
            }
            else {
                printf("\nTo pay without discount: %d\nAverage discount: %d%%\nTo pay: %d\n", t, t1 / (t1 + 1), t2);
            }
            break;


        case 5:
            printf("\n Name  - price - quantity - discount - total\n");
            for (int i = 0; i < amount; ++i) {
                if (quantity[i] > 0) {
                    t += price[i] * quantity[i];
                    t1 += discount[i] * quantity[i];
                    t11 += quantity[i];
                    t2 += price[i] * quantity[i] * (100 - discount[i]) / 100;
                    printf("%s -  %d  -     %d    -   %d%%    -   %d\n", names[i], price[i], quantity[i], discount[i], price[i] * quantity[i] * (100 - discount[i]) / 100);
                }
            }
            if (t11 != 0) {
                printf("\nTo pay without discount: %d\nAverage discount: %d%%\nTo pay: %d\n", t, t1 / t11, t2);
            }
            else {
                printf("\nTo pay without discount: %d\nAverage discount: %d%%\nTo pay: %d\n", t, t1 / (t1 + 1), t2);
            }
            printf("\nWould you like to create a new cart?\n-2 - No.\n-1 - Yes.\n");
            while (scanf("%d", &option) != 1 || option > -1 || option < -2) {
                printf("Incorrect input, please try again.\n");
                while ((c = getchar()) != "\n") {}
            }
            break;
        }
    }
}
