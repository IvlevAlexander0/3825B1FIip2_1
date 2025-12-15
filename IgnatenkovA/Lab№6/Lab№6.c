#define _CRT_SECURE_NO_WARNINGS
#define PI 3.14159265358979323846
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*FuncPtr)(double);

void clean_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

double taylor_sin(double x, int max_terms, double eps, int* used_terms) {
    if (x == 0.0) {
        *used_terms = 1;
        return 0.0;
    }
    double sum = x;
    double term = x;
    *used_terms = 1;
    for (int n = 1; n < max_terms; n++) {
        term *= -x * x / ((2 * n) * (2 * n + 1));
        sum += term;
        (*used_terms)++;
        if (fabs(term) < eps && eps > 0) break;
    }
    return sum;
}
double taylor_cos(double x, int max_terms, double eps, int* used_terms) {
    double sum = 1.0;
    double term = 1.0;
    *used_terms = 1;
    for (int n = 1; n < max_terms; n++) {
        term *= -x * x / ((2 * n - 1) * (2 * n));
        sum += term;
        (*used_terms)++;
        if (fabs(term) < eps && eps > 0) break;
    }
    return sum;
}
double taylor_exp(double x, int max_terms, double eps, int* used_terms) {
    double sum = 1.0;
    double term = 1.0;
    *used_terms = 1;
    for (int n = 1; n < max_terms; n++) {
        term *= x / n;
        sum += term;
        (*used_terms)++;
        if (fabs(term) < eps && eps > 0) break;
    }
    return sum;
}
double taylor_arcsin(double x, int max_terms, double eps, int* used_terms) {
    if (fabs(x) > 1.0) {
        *used_terms = 0;
        return 0.0;
    }
    if (x == 0.0) {
        *used_terms = 1;
        return 0.0;
    }
    double sum = x;
    double term = x;
    *used_terms = 1;
    for (int n = 1; n < max_terms; n++) {
        double factor = (2.0 * n - 1.0) / (2.0 * n);
        term *= factor * factor * x * x * (2.0 * n - 1.0) / (2.0 * n + 1.0);
        sum += term;
        (*used_terms)++;
        if (fabs(term) < eps && eps > 0) break;
    }
    return sum;
}
void mode1() {
    int func_id;
    double x, eps;
    int N;

    printf("Select function:\n");
    printf("1. sin(x)\n2. cos(x)\n3. exp(x)\n4. arccos(x)\n");
    printf("Your choice: ");
    if (scanf("%d", &func_id) != 1 || func_id < 1 || func_id > 4) {
        printf("Incorrect selection.\n");
        clean_input_buffer();
        return;
    }
    printf("Enter the x point: ");
    if (scanf("%lf", &x) != 1) {
        printf("Error entering x.\n");
        clean_input_buffer();
        return;
    }
    if (func_id == 4 && (x < -1.0 || x > 1.0)) {
        printf("arccos(x) is defined only for x in [-1, 1].\n");
        return;
    }
    printf("Enter the accuracy (>= 0.000001): ");
    if (scanf("%lf", &eps) != 1 || eps < 1e-6) {
        printf("The accuracy should be >= 0.000001.\n");
        clean_input_buffer();
        return;
    }
    printf("Enter the maximum number of terms (1..1000): ");
    if (scanf("%d", &N) != 1 || N < 1 || N > 1000) {
        printf("N must be between 1 and 1000.\n");
        clean_input_buffer();
        return;
    }
    int used_terms = 0;
    double approx, reference;
    FuncPtr ref_func = NULL;

    if (func_id == 1) {
        approx = taylor_sin(x, N, eps, &used_terms);
        ref_func = sin;
    }
    else if (func_id == 2) {
        approx = taylor_cos(x, N, eps, &used_terms);
        ref_func = cos;
    }
    else if (func_id == 3) {
        approx = taylor_exp(x, N, eps, &used_terms);
        ref_func = exp;
    }
    else {
        double arcsin_val = taylor_arcsin(x, N, eps, &used_terms);
        approx = PI / 2.0 - arcsin_val;
        reference = acos(x);
    }
    if (func_id != 4) {
        reference = ref_func(x);
    }
    double diff = fabs(approx - reference);

    printf("\nResults\n");
    printf("Function: %s\n", (func_id == 1) ? "sin(x)" :
        (func_id == 2) ? "cos(x)" :
        (func_id == 3) ? "exp(x)" : "arccos(x)");
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
    printf("Select function:\n");
    printf("1. sin(x)\n2. cos(x)\n3. exp(x)\n4. arccos(x)\n");
    printf("Your choice: ");
    if (scanf("%d", &func_id) != 1 || func_id < 1 || func_id > 4) {
        printf("Incorrect selection.\n");
        clean_input_buffer();
        return;
    }
    printf("Enter the x point: ");
    if (scanf("%lf", &x) != 1) {
        printf("Error entering x.\n");
        clean_input_buffer();
        return;
    }
    if (func_id == 4 && (x < -1.0 || x > 1.0)) {
        printf("arccos(x) is defined only for x in [-1, 1].\n");
        return;
    }
    printf("Enter a number of experiments (1..25): ");
    if (scanf("%d", &NMax) != 1 || NMax < 1 || NMax > 25) {
        printf("NMax should be between 1 and 25.\n");
        clean_input_buffer();
        return;
    }
    double reference;
    FuncPtr ref_func = NULL;
    if (func_id == 1) {
        ref_func = sin;
        reference = ref_func(x);
    }
    else if (func_id == 2) {
        ref_func = cos;
        reference = ref_func(x);
    }
    else if (func_id == 3) {
        ref_func = exp;
        reference = ref_func(x);
    }
    else {
        reference = acos(x);
    }
    printf("\nSerial experiment\n");
    printf("Function: %s\n", (func_id == 1) ? "sin(x)" :
        (func_id == 2) ? "cos(x)" :
        (func_id == 3) ? "exp(x)" : "arccos(x)");
    printf("Point x: %g\n", x);
    printf("Reference value: %.12f\n", reference);
    printf("\n%-12s %-20s %-15s\n", "Terms", "Estimate", "Difference");
    printf("\n");
    for (int n = 1; n <= NMax; n++) {
        double approx;
        int temp;
        if (func_id == 1) {
            approx = taylor_sin(x, n, 0.0, &temp);
        }
        else if (func_id == 2) {
            approx = taylor_cos(x, n, 0.0, &temp);
        }
        else if (func_id == 3) {
            approx = taylor_exp(x, n, 0.0, &temp);
        }
        else {
            double arcsin_val = taylor_arcsin(x, n, 0.0, &temp);
            approx = PI / 2.0 - arcsin_val;
        }
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
            clean_input_buffer();
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
            printf("Incorrect mode.\n");
            clean_input_buffer();
        }
    } while (1);
}