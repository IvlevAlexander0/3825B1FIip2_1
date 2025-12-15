#define _CRT_SECURE_NO_WARNINGS
#define PI 3.14159265358979323846
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double term_sin(int n, double x) {
    double sign = (n % 2 == 0) ? 1.0 : -1.0;
    double num = sign * pow(x, 2 * n + 1);
    double den = tgamma(2 * n + 2);
    return num / den;
}
double term_cos(int n, double x) {
    double sign = (n % 2 == 0) ? 1.0 : -1.0;
    double num = sign * pow(x, 2 * n);
    double den = tgamma(2 * n + 1);
    return num / den;
}
double term_exp(int n, double x) {
    double num = pow(x, n);
    double den = tgamma(n + 1);
    return num / den;
}
double term_arcsin(int n, double x) {
    if (fabs(x) > 1.0) return 0.0;
    double coeff = tgamma(2 * n + 1) / (pow(4.0, n) * pow(tgamma(n + 1), 2) * (2 * n + 1));
    return coeff * pow(x, 2 * n + 1);
}
double taylor_sum(double x, double (*term_func)(int, double), int max_terms, double eps, int* used_terms) {
    double sum = 0.0;
    *used_terms = 0;

    for (int n = 0; n < max_terms; n++) {
        double term = term_func(n, x);
        sum += term;
        (*used_terms)++;
        if (fabs(term) < eps && eps > 0) {
            break;
        }
    }
    if (term_func == term_arcsin) {
        sum = PI / 2.0 - sum;
    }
    return sum;
}
void mode1() {
    int func_id;
    double x, eps;
    int N;
    double (*term_func)(int, double) = NULL;
    char* func_name = NULL;
    printf("Select function:\n");
    printf("1. sin(x)\n2. cos(x)\n3. exp(x)\n4. arccos(x)\n");
    printf("Your choice: ");
    if (scanf("%d", &func_id) != 1 || func_id < 1 || func_id > 4) {
        printf("Incorrect selection.\n");
        return;
    }
    switch (func_id) {
    case 1: term_func = term_sin; func_name = "sin(x)"; break;
    case 2: term_func = term_cos; func_name = "cos(x)"; break;
    case 3: term_func = term_exp; func_name = "exp(x)"; break;
    case 4: term_func = term_arcsin; func_name = "arccos(x)"; break;
    }
    printf("Enter the x point: ");
    if (scanf("%lf", &x) != 1) {
        printf("Error entering x.\n");
        return;
    }
    if (func_id == 4 && (x < -1.0 || x > 1.0)) {
        printf("arccos(x) is defined only for x = [-1, 1].\n");
        return;
    }
    printf("Enter the accuracy (>= 0.000001): ");
    if (scanf("%lf", &eps) != 1 || eps < 1e-6) {
        printf("The accuracy should be >= 0.000001.\n");
        return;
    }
    printf("Enter the maximum number of terms (1..1000): ");
    if (scanf("%d", &N) != 1 || N < 1 || N > 1000) {
        printf("N must be between 1 and 1000.\n");
        return;
    }
    int used_terms = 0;
    double approx = taylor_sum(x, term_func, N, eps, &used_terms);
    double reference;
    if (func_id == 1) reference = sin(x);
    else if (func_id == 2) reference = cos(x);
    else if (func_id == 3) reference = exp(x);
    else reference = acos(x);
    double diff = fabs(approx - reference);
    printf("\nResults\n");
    printf("Function: %s\n", func_name);
    printf("Point x: %g\n", x);
    printf("Reference value: %.12f\n", reference);
    printf("Calculated: %.12f\n", approx);
    printf("Difference: %.2e\n", diff);
    printf("Used terms: %d\n", used_terms);
}

void mode2() {
    int func_id;
    double x;
    int NMax;
    double (*term_func)(int, double) = NULL;
    char* func_name = NULL;

    printf("Select function:\n");
    printf("1. sin(x)\n2. cos(x)\n3. exp(x)\n4. arccos(x)\n");
    printf("Your choice: ");
    if (scanf("%d", &func_id) != 1 || func_id < 1 || func_id > 4) {
        printf("Incorrect selection.\n");
        return;
    }
    switch (func_id) {
    case 1: term_func = term_sin; func_name = "sin(x)"; break;
    case 2: term_func = term_cos; func_name = "cos(x)"; break;
    case 3: term_func = term_exp; func_name = "exp(x)"; break;
    case 4: term_func = term_arcsin; func_name = "arccos(x)"; break;
    }
    printf("Enter the x point: ");
    if (scanf("%lf", &x) != 1) {
        printf("Error entering x.\n");
        return;
    }
    if (func_id == 4 && (x < -1.0 || x > 1.0)) {
        printf("arccos(x) is defined only for x = [-1, 1].\n");
        return;
    }
    printf("Enter a number of experiments: ");
    if (scanf("%d", &NMax) != 1 || NMax < 1 || NMax > 25) {
        printf("NMax should be between 1 and 25.\n");
        return;
    }
    double reference;
    if (func_id == 1) reference = sin(x);
    else if (func_id == 2) reference = cos(x);
    else if (func_id == 3) reference = exp(x);
    else reference = acos(x);
    printf("\nSerial experiment\n");
    printf("Function: %s\n", func_name);
    printf("Point x: %g\n", x);
    printf("The reference value: %.12f\n", reference);
    printf("\n%-12s %-20s %-15s\n", "Terms", "Estimate", "Difference");
    printf("\n");
    for (int n = 1; n <= NMax; n++) {
        int temp;
        double approx = taylor_sum(x, term_func, n, 0.0, &temp);
        double diff = fabs(approx - reference);
        printf("%-12d %-20.12f %-15.2e\n", n, approx, diff);
    }
}

int main() {
    int mode;
    do {
        printf("\nTaylor Series Calculator\n");
        printf("1. One-time calculation\n");
        printf("2. Serial experiment\n");
        printf("3. Exit\n");
        printf("Your choice: ");
        if (scanf("%d", &mode) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            mode = -1;
        }
        if (mode == 1) {
            mode1();
        }
        else if (mode == 2) {
            mode2();
        }
        else if (mode == 3) {
            break;
        }
        else {
            printf("Incorrect mode. Please try again.\n");
        }
    } while (1);
}