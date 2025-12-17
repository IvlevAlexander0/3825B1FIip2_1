#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

double taysin(double x, int k) {
    double result = 0.0;
    double a = x;
    int f = 1;
    for (int n = 1; n <= k; n++) {
        result += a;
        a = -1 * a * x * x / ((f + 1) * (f + 2));
        f += 2;
    }
    return result;
}

double taycos(double x, int k) {
    double result = 0.0;
    double a = 1.0;
    int f = 0;
    for (int n = 1; n <= k; n++) {
        result += a;
        a = -1 * a * x * x / ((f + 1) * (f + 2));
        f += 2;
    }
    return result;
}

double tayexp(double x, int k) {
    double result = 0.0;
    double a = 1;
    int f = 0;
    for (int n = 1; n <= k; n++) {
        result += a;
        a = a * x / (f + 1);
        ++f;
    }
    return result;
}

double tayarctg(double x, int k) {
    double result = 0.0;
    double a = x;
    int f = 1;
    for (int n = 1; n <= k; n++) {
        result += a;
        a = -1 * a * x * x * f / (f + 2);
        f += 2;
    }
    return result;
}

int checkint(int min, int max) {
    int num = 0;
    while (1) {
        int result = scanf("%d", &num);
        while (getchar() != '\n');
        if (result != 1) {
            printf("Error: Please enter a valid number: ");
            continue;
        }
        if (num < min || num > max) {
            printf("Error: Number must be between %d and %d. Try again: ", min, max);
            continue;
        }
        break;
    }
    return num;
}

double checkdouble(double min) {
    double num = 0;
    while (1) {
        int result = scanf("%lf", &num);
        while (getchar() != '\n');
        if (result != 1) {
            printf("Error: Please enter a valid number: ");
            continue;
        }
        if (num < min) {
            printf("Error: Number must be >= %.6lf. Try again: ", min);
            continue;
        }
        break;
    }
    return num;
}

double checkdouble1(int arct) {
    double num = 0;
    while (1) {
        int result = scanf("%lf", &num);
        while (getchar() != '\n');
        if (result != 1) {
            printf("Error: Please enter a valid number: ");
            continue;
        }
        if (arct == 1 && (num < -1 || num > 1)) {
            printf("Error: For arctg(x) x should be between -1 and 1\n");
            printf("Please enter a new value: ");
            continue;
        }
        
        break;
    }
    return num;
}

void mode1() {
    printf("Choose the function:\n");
    printf("1. sin(x)\n");
    printf("2. cos(x)\n");
    printf("3. exp(x)\n");
    printf("4. arctg(x)\n");
    printf("Your choice: ");
    int choice = checkint(1, 4);
    printf("Enter x: ");
    double x = 0.0;
    if (choice == 4) {
        x = checkdouble1(1);
    }
    else {
        x = checkdouble1(0);
    }
    printf("Enter precision (>= 0.000001): ");
    double number = checkdouble(0.000001);
    printf("Enter maximum number of terms (1-1000): ");
    int maxt = checkint(1, 1000);
    double (*taylor)(double, int) = NULL;
    double (*func)(double) = NULL;
    switch (choice) {
    case 1:
        taylor = taysin;
        func = sin;
        break;
    case 2:
        taylor = taycos;
        func = cos;
        break;
    case 3:
        taylor = tayexp;
        func = exp;
        break;
    case 4:
        taylor = tayarctg;
        func = atan;
        break;
    }
    double res1 = func(x);
    double res2 = 0;
    double dif = 0;
    int count = 0;
    for (int k = 1; k <= maxt; k++) {
        res2 = taylor(x, k);
        dif = fabs(res2 - res1);
        count = k;
        if (dif < number) {
            break;
        }
    }
    printf("math.h value: %lf\n", res1);
    printf("Calculated value: %lf\n", res2);
    printf("Difference: %lf\n", dif);
    printf("Terms used: %d\n", count);
}

void mode2() {
    printf("Select function:\n");
    printf("1. sin(x)\n");
    printf("2. cos(x)\n");
    printf("3. exp(x)\n");
    printf("4. arctg(x)\n");
    printf("Your choice: ");
    int choice = checkint(1, 4);
    printf("Enter x: ");
    double x = 0.0;
    if (choice == 4) {
        x = checkdouble1(1);
    }
    else {
        x = checkdouble1(0);
    }
    if (x > 3.1415 && choice != 3) {
        x = fmod(x, 3.1415);
    }
    printf("Enter number of experiments (1-25): ");
    int k = checkint(1, 25);
    double (*taylor)(double, int) = NULL;
    double (*func)(double) = NULL;
    switch (choice) {
    case 1:
        taylor = taysin;
        func = sin;
        break;
    case 2:
        taylor = taycos;
        func = cos;
        break;
    case 3:
        taylor = tayexp;
        func = exp;
        break;
    case 4:
        taylor = tayarctg;
        func = atan;
        break;
    }
    double res1 = func(x);
    printf("Math.h value: %lf\n", res1);
    printf("| Calculated    | Difference         |\n");
    for (int n = 1; n <= k; n++) {
        double res2 = taylor(x, n);
        double dif = fabs(res2 - res1);
        printf("| %13.8lf | %18.10lf |\n", res2, dif);
    }
}

int main() {
    while (1) {
        printf("Select mode:\n");
        printf("1. Single calculation (with precision)\n");
        printf("2. Series experiment\n");
        printf("3. Exit\n");
        printf("Your choice: ");
        int mode = checkint(1, 3);
        switch (mode) {
        case 1:
            mode1();
            break;
        case 2:
            mode2();
            break;
        case 3:
            return 0;
        }
    }
}