#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int unique(int dlina, int chislo) {
    int zifri[10] = { 0 };
    int pervayazifra = chislo;
    for (int i = 1; i < dlina; ++i) {
        pervayazifra /= 10;
    }
    if (pervayazifra == 0) return 0;
    for (int i = 0; i < dlina; ++i) {
        int zifra = chislo % 10;
        if (zifri[zifra]) return 0;
        zifri[zifra] = 1;
        chislo /= 10;
    }
    return 1;
}
int genunique(int dlina) {
    int min = 1, max;
    int sgench;
    for (int i = 1; i < dlina; ++i) {
        min *= 10;
    }
    max = min * 10 - 1;
    do {
        sgench = min + rand() % (max - min + 1);
    } while (!unique(dlina, sgench));
    return sgench;
}
int main() {
    srand(time(NULL));
    int number, guess, hidden[6], user[6], secret, n;
    printf("Now u will play the game 'cows and bulls'. Enter the length of the number >=2 <=5\n");
    while (scanf("%d", &n) == 0 || (n < 2) || (n > 5)) {
        char c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        printf("The length of the number must be more than 1 but less than 6\n");
    }
    number = genunique(n);
    secret = number;
    for (int i = n - 1; i >= 0; --i) {
        hidden[i] = secret % 10;
        secret /= 10;
    }
    printf("Start guessing!\n");
    do {
        int bulls = 0, cows = 0;  
        while (scanf("%d", &guess) == 0 || !unique(n, guess)) {
            char c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("incorrect number\n");
        }
        int usersone = guess;
        for (int i = n - 1; i >= 0; --i) {
            user[i] = usersone % 10;
            usersone /= 10;
        }
        for (int i = 0; i < n; ++i) {
            if (user[i] == hidden[i]) {
                bulls++;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && user[i] == hidden[j]) {
                    cows++;
                }
            }
        }
        if (bulls != n) {
            printf("%d bulls and %d cows, try again!\n", bulls, cows);
        }
        else {
            printf("U have guessed the number gratz!\n");
            break;
        }
    } while (1);
    return 0;
}