#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pi 3.14159265358979323846


typedef double (*teylorfunc)(double, int, int*, double);
typedef double (*refencefunc)(double);

double tsin(double x, int n, int* count, double pog) {
    x = fmod(x, 2 * pi);
    if (x > pi) {
        x -= 2 * pi;
    }
    if (x < -pi) {
        x += 2 * pi;
    }

    long double term = x;
    long double res = x;
    int k = 1;
    *count = 1;

    do {
        term *= -x * x / ((2 * k) * (2 * k + 1));
        res += term;
        k++;
        (*count)++;  
    } while (k <= n && fabsl(term) > pog);

    if (fabsl(term) <= pog) {
        (*count)--;
        res -= term;
    }
    return res;
}

double tcos(double x, int n, int* count, double pog) {
    x = fmod(x, 2 * pi);
    if (x > pi) {
        x -= 2 * pi;
    }
    if (x < -pi) {
        x += 2 * pi;
    }

    long double term = 1.0;
    long double res = 1.0;
    int k = 1;
    *count = 1;

    do {
        term *= -x * x / ((2 * k - 1) * (2 * k));
        res += term;
        k++;
        (*count)++;
    } while (k <= n && fabsl(term) > pog);

    if (fabsl(term) <= pog) {
        (*count)--;
        res -= term;
    }
    return res;
}

double telexp(double x, int n, int* count, double pog) {
    int p = 0;
    long double origx = x;

    if (fabsl(x) > 1.0) {
        p = (int)fabsl(x) + 1;
        x /= p;
    }

    long double term = 1.0;
    long double res = 1.0;
    int k = 1;
    *count = 1;

    do {
        term *= x / k;
        res += term;
        k++;
        (*count)++;
    } while (k <= n && fabsl(term) > pog);

    if (fabsl(term) <= pog) {
        (*count)--;
        res -= term;
    }

    if (p > 0) {
        long double st = 1.0;
        for (int i = 0; i < p; i++) {
            st *= res;  
        }
        res = st;

        if (origx < 0) {
            res = 1.0 / res;
        }
    }

    return res;
}

double tarcsin(double x, int n, int* count, double pog) {
        if (fabsl(x) == 1.0) {
            *count = 1;
            return (x > 0) ? (pi / 2) : (-pi / 2);
        }

        double sign;
        if (x >= 0) {
            sign = 1.0;
        }
        else {
            sign = -1.0;
        }
        x = fabsl(x);

        if (x > 0.5) {
            double reduced_x = sqrtl((1.0 - x) / 2.0);
            int c = 0;
            double result = (pi / 2) - 2.0 * tarcsin(reduced_x, n, &c, pog);
            *count = c;
            return sign * result;
        }

        long double term = x;
        long double res = x;
        long double x_squared = x * x;
        int k = 1;
        *count = 1;

        do {
            term *= x_squared * (2 * k - 1) * (2 * k - 1) / ((2 * k) * (2 * k + 1));
            res += term;
            k++;
            (*count)++;
        } while (k <= n && fabsl(term) > pog);

        if (fabsl(term) <= pog) {
            (*count)--;
            res -= term;
        }

        return sign * res;
    }


teylorfunc rdT(char f) {
    if (f == '1') {
        return tsin;
    }
    else if (f == '2') {
        return tcos;
    }
    else if (f == '3') {
        return telexp;
    }
    else {
        return tarcsin;
    }
}

refencefunc standart(char f) {
    if (f == '1') {
        return sin;
    }
    else if (f == '2') {
        return cos;
    }
    else if (f == '3') {
        return exp;
    }
    else {
        return asin;
    }
}


int main() {
    char mode, func;
    double x, pog;

    printf("Select a mode: \n1. A single calculation of the function at a given point.\n2. Serial experiment.\n");
    while (1) {
        mode = getchar();
        if (mode != '1' && mode != '2') {
            printf("Input error. Try again!\n");
        }
        else {
            char cled = getchar();
            if (cled != '\n') {
                printf("Input error. Try again!\n");
            }
            else {
                break;
            }
        }
        while (getchar() != '\n');
    }

    printf("Select a function: \n1. sin x \n2. cos x \n3. exp x \n4. arcsin x\n");
    while (1) {
        func = getchar();
        if (func != '1' && func != '2' && func != '3' && func != '4') {
            printf("Input error. Try again!\n");
        }
        else {
            char cled = getchar();
            if (cled != '\n') {
                printf("The number must be since 1 to 4\n");
            }
            else {
                break;
            }
        }
        while (getchar() != '\n');
    }

    printf("Enter the point where you want to calculate the value: \n");
    while (1) {
        if (scanf("%lf", &x) == 1) {
            double cled = getchar();
            if (cled == '\n') {
                if (func == '4' && x >= -1.00 && x <= 1.00) {
                    break;
                }
                else if (func == '4') {
                    printf("The number must be since -1 to 1.\n");
                }
                else {
                    break;
                }
            }
            else {
                printf("Input error. Try again!\n");
                while (getchar() != '\n');
            }
        }
        else {
            printf("Input error. Try again!\n");
            while (getchar() != '\n');
        };
    }

    teylorfunc taylor = rdT(func);
    refencefunc std = standart(func);

    if (mode == '1') {
        int n;
        int count = 0;
        printf("Enter the accuracy of the calculation (from 0.000001 or more): \n");
        while (1) {
            if (scanf("%lf", &pog) == 1 && pog > 0.000001) {
                double cled = getchar();
                if (cled == '\n') {
                    break;
                }
                else {
                    printf("Input error. Try again!\n");
                    while (getchar() != '\n');
                }
            }
            else {
                printf("Input error. Try again!\n");
                while (getchar() != '\n');
            }
        }

        printf("Enter the maximum number of row elements to perform the calculation (N - from 1 to 1000): \n");
        while (1) {
            if (scanf("%d", &n) == 1 && (n > 1 && n < 1000)) {
                int cled = getchar();
                if (cled == '\n') {
                    break;
                }
                else {
                    printf("The number must be an integer\n");
                    while (getchar() != '\n');
                }
            }
            else {
                printf("Input error. Try again!\n");
                while (getchar() != '\n');
            }
        }


        if (taylor == NULL || std == NULL) {
            printf("Error: function not found\n");
            return 1;
        }

        double res1 = std(x);
        double res2 = taylor(x, n, &count, pog);
        printf("The reference value: %.10f\n", res1);
        printf("Evaluation of the function value: %.10f\n", res2);
        printf("The difference between the estepimate and the reference value: %.10f\n", fabs(res2 - res1));
        printf("Number of terms: %d\n", count);
    }
    else {
        int nmax;
        printf("Enter number of experiments (1 - 25): \n");
        while (1) {
            if (scanf("%d", &nmax) == 1 && (nmax > 0 && nmax < 26)) {
                int cled = getchar();
                if (cled == '\n') {
                    break;
                }
                else {
                    printf("The number must be an integer\n");
                    while (getchar() != '\n');
                }
            }
            else {
                printf("Input error. Try again!\n");
                while (getchar() != '\n');
            }
        }

        double et = std(x);
        printf("The reference value: %.10f\n\n", et);
        printf(" --------------------------------------------------------\n");
        printf("| Count |         Taylor        |       Difference       |\n");
        printf(" --------------------------------------------------------\n");

        for (int i = 1; i <= nmax; i++) {
            int count = 0;
            double tlor = taylor(x, i, &count, 1e-20);
            printf("|  %3d  | %21.10f | %21.10f  |\n", i, tlor, fabs(et - tlor));
        }
        printf("---------------------------------------------------------\n\n");
    }
    return 0;
}