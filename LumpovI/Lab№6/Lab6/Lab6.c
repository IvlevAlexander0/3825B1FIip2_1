#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi 3.14159265358

typedef double (*MathFunc)(double);

void cleanBuffer() {
    int a;
    while ((a = getchar()) != '\n' && a != EOF);
}

double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

double radians_to_degrees(double radians) {
    return radians * 180.0 / pi;
}

double taylor_sin(double x_rad, int terms, double eps, int* n) {
    double term = x_rad;
    double sum = term;
    int iter = 1;

    while (iter < terms && fabs(term) > eps) {
        term = -term * x_rad * x_rad / ((2 * iter) * (2 * iter + 1));
        sum += term;
        iter++;
    }

    *n = iter;
    return sum;
}

double taylor_cos(double x_rad, int terms, double esp, int* n) {
    double term = 1;
    double sum = term;
    int iter = 1;

    while (iter < terms && fabs(term) > esp) {
        term = -term * x_rad * x_rad / ((2 * iter - 1) * (2 * iter));
        sum += term;
        iter++;
    }

    *n = iter;
    return sum;
}

double taylor_exp(double x, int terms, double eps, int* n) {
    double term = 1;
    double sum = term;
    int iter = 1;

    while (iter < terms && fabs(term) > eps) {
        term = term * x / iter;
        sum += term;
        iter++;
    }

    *n = iter;
    return sum;
}


double taylor_arcctg(double x, int terms, double eps, int* n) {
    double arctg;
    double arcctg;

    if (fabs(x) <= 1) {
        double term = x;
        arctg = term;
        int iter = 1;

        while (iter < terms && fabs(term) > eps) {
            term = -term * x * x * (2 * iter - 1) / (2 * iter + 1);
            arctg += term;
            iter++;
        }
        *n = iter;
    }
    else {
        double inv_x = 1.0 / x;
        double term = inv_x;
        arctg = term;
        int iter = 1;

        while (iter < terms && fabs(term) > eps) {
            term = -term * inv_x * inv_x * (2 * iter - 1) / (2 * iter + 1);
            arctg += term;
            iter++;
        }
        *n = iter;
        arctg = pi / 2 - arctg;
    }

    arcctg = pi / 2 - arctg;
    return arcctg;
}

double get_reference_value(MathFunc func, double x) {
    return func(x);
}

void single_calculation(int fnc, double x_rad, double eps) {
    int terms;

    printf("Input the number of terms (1-1000): ");
    while (scanf("%d", &terms) != 1 || 1 > terms || terms > 1000) {
        printf("Inccorect input: too much ot roo less terms!!!\n");
        cleanBuffer();
    }

    int terms_used = 0;
    double taylor_fnc = 0;
    double ref = 0;
    MathFunc ref_func = NULL;

    switch (fnc) {
    case 1:
        taylor_fnc = taylor_sin(x_rad, terms, eps, &terms_used);
        ref_func = sin;
        break;
    case 2:
        taylor_fnc = taylor_cos(x_rad, terms, eps, &terms_used);
        ref_func = cos;
        break;
    case 3:
        taylor_fnc = taylor_exp(x_rad, terms, eps, &terms_used);
        ref_func = exp;
        break;
    case 4:
        taylor_fnc = taylor_arcctg(x_rad, terms, eps, &terms_used);
        ref = atan(1.0 / x_rad);
        if (x_rad < 0) {
            ref += pi;
        }
        break;
    }

    if (fnc != 4) {
        ref = get_reference_value(ref_func, x_rad);
    }

    printf("\----- Results -----\n");

    printf("Reference value: %.10f\n", ref);
    printf("Taylor value: %.10f\n", taylor_fnc);
    printf("Difference between ref. value and T. value: %.10f\n", fabs(ref - taylor_fnc));
    printf("Quantity of used terms: %d\n", terms_used);
}

void series_experiment(int fnc, double x_rad) {
    int exp_count;

    printf("Input the number of experiments (1-25): ");
    while (scanf("%d", &exp_count) != 1 || exp_count < 1 || exp_count > 25) {
        printf("Inccorect input: too much ot too less quantity of experiments!!!\n");
        cleanBuffer();
    }

    double reference = 0;
    MathFunc ref_func = NULL;

    switch (fnc) {
    case 1:
        ref_func = sin;
        reference = get_reference_value(ref_func, x_rad);
        break;
    case 2:
        ref_func = cos;
        reference = get_reference_value(ref_func, x_rad);
        break;
    case 3:
        ref_func = exp;
        reference = get_reference_value(ref_func, x_rad);
        break;
    case 4:
        reference = atan(1.0 / x_rad);
        if (x_rad < 0) reference += pi;
        break;
    }

    printf("------ Results ------\n");
    printf("Reference value: %.10f \n\n", reference);

    printf(" --------------------------------------------------------\n");
    printf("| Count |         Taylor        |       Difference       |\n");
    printf(" --------------------------------------------------------\n");

    for (int i = 1; i <= exp_count; i++) {
        int terms_used = 0;
        double taylor_func = 0;
            double eps = 1e-15;

        switch (fnc) {
        case 1:
            taylor_func = taylor_sin(x_rad, i, eps, &terms_used);
            break;
        case 2:
            taylor_func = taylor_cos(x_rad, i, eps, &terms_used);
            break;
        case 3:
            taylor_func = taylor_exp(x_rad, i, eps, &terms_used);
            break;
        case 4:
            taylor_func = taylor_arcctg(x_rad, i, eps, &terms_used);
            break;
        }

        double difference = fabs(reference - taylor_func);
        printf("|    %5d| %18.10f | %18.10f |\n", i, taylor_func, difference);
    }

    printf("---------------------------------------------------------\n\n");
}


int main() {
    int op;
    int fnc;
    double x_input, x_rad, eps;

    printf("Taylor calculator\n");
    printf("---------------------------------\n");
    printf("Choose a mode: \n");
    printf("1. Single calculate\n");
    printf("2. Serial experiment\n");
    printf("3. Exit\n");

    while (scanf("%d", &op) != 1 || op > 3 || op < 1) {
        printf("Error: please input only 1-3\n");
        cleanBuffer();
    }

    printf("Choose a function:\n");
    printf("1. sin(x)\n");
    printf("2. cos(x)\n");
    printf("3. exp(x)\n");
    printf("4. arcctg(x)\n");

    while (scanf("%d", &fnc) != 1 || fnc > 4 || fnc < 1) {
        printf("Inccorect input: plese input only 1-4\n");
        cleanBuffer();
    }

    if (fnc == 1 || fnc == 2) {
        int user_units;
        printf("In what units of measurement will you write x?: \n");
        printf("1. Degrees\n");
        printf("2. Radians\n");
        while (scanf("%d", &user_units) != 1 || user_units < 1 || user_units > 2) {
            printf("Inccorect input: plese input only 1-2\n");
            cleanBuffer();
        }

        printf("Input x: ");
        while (scanf("%lf", &x_input) != 1) {
            printf("Too much values!!!\n");
            cleanBuffer();
        }

        if (user_units == 1) {
            x_rad = degrees_to_radians(x_input);
        }
        else {
            x_rad = x_input;
        }

    }
    else {
        printf("Input x: ");
        while (scanf("%lf", &x_input) != 1) {
            printf("Too much values!!!\n");
            cleanBuffer();
        }
        x_rad = x_input;
    }

    printf("Input epsilon (>= 0.000001): ");
    while (scanf("%lf", &eps) != 1 || eps < 0.000001) {
        printf("Inccorect input: epsilon too minor\n");
        cleanBuffer();
    }

    switch (op) {
    case 1:
        single_calculation(fnc, x_rad, eps);
        break;
    case 2:
        series_experiment(fnc, x_rad);
        break;
    case 3:
        printf("GL HF!!!\n");
        return;
    }

    return 0;
}