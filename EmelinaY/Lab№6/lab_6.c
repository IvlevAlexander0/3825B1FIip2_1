#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265358979323846
void cleanBuffer() {
    int a;
    while ((a = getchar()) != '\n' && a != EOF);
}
long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}
double ssin(double x, double epsi, int max_terms, int* terms_used) {
    double sum = 0.0;
    double term;
    int n = 0;

    do {
        term = pow(-1, n) * pow(x, 2 * n + 1) / factorial(2 * n + 1);
        sum += term;
        n++;
        if (n >= max_terms) {
            break;
        }
    } while (fabs(term) > epsi); 
    *terms_used = n;
    return sum;
}
double ccos(double x, double epsi, int max_terms, int* terms_used) {
    double sum = 0.0;
    double term;
    int n = 0;

    do {
        term = pow(-1, n) * pow(x, 2 * n) / factorial(2 * n);
        sum += term;
        n++;

        if (n >= max_terms) {
            break;
        }
    } while (fabs(term) > epsi);
    *terms_used = n;
    return sum;
}
double eexp(double x, double epsi, int max_terms, int* terms_used) {
    double sum = 0.0;
    double term;
    int n = 0;

    do {
        term = pow(x, n) / factorial(n);
        sum += term;
        n++;

        if (n >= max_terms) {
            break;
        }
    } while (fabs(term) > epsi);
    *terms_used = n;
    return sum;
}
double aarccos(double x, double epsi, int max_terms, int* terms_used) {
    if (x < -1.0 || x > 1.0) {
        printf("Error: arccos(x) is defined only for x in [-1, 1]\n");
        *terms_used = 0;
        return 0; 
    }
    double sum = PI / 2.0 - x;
    double term;
    int n = 1;
    do {
        double chislitel = 1.0;
        double znamenatel = 1.0;

        for (int i = 1; i <= n; i++) {
            chislitel *= (2 * i - 1);
            znamenatel *= (2 * i);
        }

        double coeff = chislitel / znamenatel;
        term = coeff * pow(x, 2 * n + 1) / (2 * n + 1);
        sum -= term;
        n++;

        if (n >= max_terms) {
            break;
        }
    } while (fabs(term) > epsi);
    *terms_used = n;
    return sum;
}
void one_raschet() {
    int c;
    double x, epsi;
    int max_terms;

    printf("\n=== ONE-TIME PAYMENT ===\n");
    printf("Select a function:\n");
    printf("1. sin(x)\n");
    printf("2. cos(x)\n");
    printf("3. exp(x)\n");
    printf("4. arccos(x)\n");
    printf("Your choice: ");
    while (scanf("%d", &c) != 1 || c < 1 || c > 3) {
        printf("Error. Enter a number from 1 to 4\n");
        cleanBuffer();
    }
    printf("Enter x: ");
    scanf("%lf", &x);
    printf("Enter the accuracy (for example, 0.0001): ");
    while (scanf("%lf", &epsi) != 1 || epsi < 0.000001) {
        printf("Error.\n");
        cleanBuffer();
    }
    printf("Enter the maximum number of terms(1 - 1000) : ");
    while (scanf("%d", &max_terms) != 1 || max_terms < 1 || max_terms > 1000) {
        printf("Error. Enter a number from 1 to 1000\n");
        cleanBuffer();
    }
    int terms_used;
    double my_result, ref_result;

    switch (c) {
    case 1:
        my_result = ssin(x, epsi, max_terms, &terms_used);
        ref_result = sin(x);
        break;
    case 2:
        my_result = ccos(x, epsi, max_terms, &terms_used);
        ref_result = cos(x);
        break;
    case 3:
        my_result = eexp(x, epsi, max_terms, &terms_used);
        ref_result = exp(x);
        break;
    case 4:
        my_result = aarccos(x, epsi, max_terms, &terms_used);
        ref_result = acos(x);
        break;
    default:
        printf("Invalid function choice\n");
        return;
    }

    printf("\n=== RESULTS ===\n");
    printf("Reference value: %.10f\n", ref_result);
    printf("Calculated value: %.10f\n", my_result);
    printf("Difference: %.10f\n", fabs(ref_result - my_result));
    printf("Terms used: %d\n", terms_used);
}

void series_rashet() {
    int c;
    double x;
    int n_max;

    printf("\n SERIES EXPERIMENT ===\n");
    printf("Select a function:\n");
    printf("1. sin(x)\n");
    printf("2. cos(x)\n");
    printf("3. exp(x)\n");
    printf("4. arccos(x)\n");
    printf("Your choice: ");
    while (scanf("%d", &c) != 1 || c < 1 || c > 4) {
        printf("Error. Enter a number from 1 to 4: ");
        cleanBuffer();
    }


    printf("Enter x: ");
    while (scanf("%lf", &x) != 1) {
        printf("Error. Enter a valid number: ");
        cleanBuffer();
    }

    printf("Enter number of experiments (1-25): ");
    while (scanf("%d", &n_max) != 1 || n_max < 1 || n_max > 25) {
        printf("Error. Enter a number from 1 to 25: ");
        cleanBuffer();
    }
    double ref_result;
    switch (c) {
    case 1: ref_result = sin(x); break;
    case 2: ref_result = cos(x); break;
    case 3: ref_result = exp(x); break;
    case 4: ref_result = acos(x); break;
    }

    printf("\nReference value: %.10f\n", ref_result);
    printf("\nResults table:\n");
    printf("┌─────┬──────────────────┬──────────────────┐\n");
    printf("│  N  │    Value         │     Error        │\n");
    printf("├─────┼──────────────────┼──────────────────┤\n");

    for (int n = 1; n <= n_max; n++) {
        int terms_used;
        double my_result;

        double tiny_epsilon = 1e-50;

        switch (c) {
        case 1:
            my_result = ssin(x, tiny_epsilon, n, &terms_used);
            break;
        case 2:
            my_result = ccos(x, tiny_epsilon, n, &terms_used);
            break;
        case 3:
            my_result = eexp(x, tiny_epsilon, n, &terms_used);
            break;
        case 4:
            my_result = aarccos(x, tiny_epsilon, n, &terms_used);
            break;
        }

        double error = fabs(ref_result - my_result);
        printf("│ %3d │ %16.10f │ %16.10f │\n", n, my_result, error);
    }

    printf("└─────┴──────────────────┴──────────────────┘\n");
}
int main() {
    int c;
    printf("=== FUNCTION CALCULATION VIA TAYLOR SERIES ===\n");

    while (1) {
        printf("\nSelect mode:\n");
        printf("1. One-time calculation\n");
        printf("2. Series experiment\n");
        printf("0. Exit\n");
        printf("Your choice: ");
        while (scanf("%d", &c) != 1 || c <0 || c > 2) {
            printf("Error. Enter a valid number: ");
            cleanBuffer();
        }
        switch (c) {
        case 1:
            one_raschet();
            break;
        case 2:
            series_rashet();
            break;
        case 0:
            printf("Exit from program.\n");
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}