#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int max(float a, float b) {
    if (a > b) return a;
    else return b;
}

int min(float a, float b) {
    if (a < b) return a;
    else return b;
}

int main() {

    float x1, y1, r1, x2, y2, r2, distance;

    do {

        printf("Input centre coordinates and two circles' radiuses");

        scanf("%f%f%f%f%f%f", &x1, &y1, &r1, &x2, &y2, &r2);

        if ((r1 == 0) || (r2 == 0)) printf("\033[41mRadius can't equal zero\033[49m\n");
        else if ((r1 < 0) || (r2 < 0)) printf("\033[41mRadius can't subceed zero\033[49m\n");
        printf("\n");

    } while ((r1 <= 0) || (r2 <= 0));

    distance = sqrt(pow(fmax(x1, x2) - fmin(x1, x2), 2) + pow(fmax(y1, y2) - fmin(y1, y2), 2));

    if (distance == 0.0f) {

        if (r1 == r2) printf("The circles are equal"); // 7
        else if (r2 > r1) printf("The first circle is within the second one"); // 4
        else printf("The second circle is within the first one"); // 4

        printf("\nThe circles share a centre");

    }
    else {

        if ((r1 + r2) == distance) printf("The circles contact each other");
        else if (distance + fmin(r1, r2) == fmax(r1, r2)) fprintf("The circles contact each other\nOne circle is within the other one");
        else if (distance + fmin(r1, r2) < fmax(r1, r2)) fprintf("One circle is within the other one");
        else if (distance < (r1 + r2)) printf("The circles cross");
        else printf("The circles don't contact each other");

    }

    printf("\r");

    return 0;
}

