#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define P 3.14159265358979323846
#define maxiter 1000
#define maxexp 25
#define min_pogreshnost 0.000001
typedef double (*TaylorFunc)(double, int, double, int*);
typedef double (*RefFunc)(double);
typedef struct {
    TaylorFunc taylor_func;
    RefFunc ref_func;
} FunctionData;
void cleanbuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
double radiants(double degrees) {
    return degrees * P / 180.0;
}
double taylor_sin(double x, int iters, double pogreshnost, int* iters1) {
    double iter = x;
    double result = iter;
    *iters1 = 1;
    x = fmod(x, 2 * P);
    for (int i = 1; i < iters && fabs(iter) > pogreshnost; i++) {
        iter = -iter * x * x / ((2 * i) * (2 * i + 1));
        result += iter;
        (*iters1)++;
    }
    return result;
}
double taylor_cos(double x, int iters, double pogreshnost, int* iters1) {
    double iter = 1.0;
    double result = iter;
    *iters1 = 1;
    x = fmod(x, 2 * P);
    for (int i = 1; i < iters && fabs(iter) > pogreshnost; i++) {
        iter = -iter * x * x / ((2 * i - 1) * (2 * i));
        result += iter;
        (*iters1)++;
    }
    return result;
}
double taylor_exp(double x, int iters, double pogreshnost, int* iters1) {
    double iter = 1.0;
    double result = iter;
    *iters1 = 1;
    for (int i = 1; i < iters && fabs(iter) > pogreshnost; i++) {
        iter = iter * x / i;
        result += iter;
        (*iters1)++;
    }
    return result;
}
double taylor_arcctg(double x, int iters, double pogreshnost, int* iters1) {
    double arctg;
    *iters1 = 0;
    if (fabs(x) <= 1.0) {
        double iter = x;
        arctg = iter;
        *iters1 = 1;
        for (int i = 1; i < iters && fabs(iter) > pogreshnost; i++) {
            iter = -iter * x * x * (2 * i - 1) / (2 * i + 1);
            arctg += iter;
            (*iters1)++;
        }
    }
    else {
        double x1 = 1.0 / x;
        double iter = x1;
        arctg = iter;
        *iters1 = 1;

        for (int i = 1; i < iters && fabs(iter) > pogreshnost; i++) {
            iter = -iter * x1 * x1 * (2 * i - 1) / (2 * i + 1);
            arctg += iter;
            (*iters1)++;
        }
        arctg = P / 2 - arctg;
    }
    return P / 2 - arctg;
}
double ref_sin(double x) {
    return sin(x);
}
double ref_cos(double x) {
    return cos(x);
}
double ref_exp(double x) {
    return exp(x);
}
double ref_arcctg(double x) {
    if (x > 0) {
        return P / 2 - atan(x);
    }
    else {
        return 3 * P / 2 - atan(x);
    }
}
FunctionData functions[] = { {taylor_sin, ref_sin},{taylor_cos, ref_cos},{taylor_exp, ref_exp},{taylor_arcctg, ref_arcctg} };
double get_reference_value(int funchoice, double x) {
    RefFunc ref_func = functions[funchoice - 1].ref_func;
    return ref_func(x);
}
void single_calculation(int funchoice, double x, double pogreshnost) {
    int iters;
    printf("\nEnter amount of operations 1-1000\n");
    while (scanf("%d", &iters) != 1 || iters < 1 || iters > maxiter) {
        printf("Incorrect input 1-1000\n");
        cleanbuffer();
    }
    int iters1 = 0;
    double taylor_result = 0.0;
    TaylorFunc taylor_func = functions[funchoice - 1].taylor_func;
    taylor_result = taylor_func(x, iters, pogreshnost, &iters1);
    RefFunc ref_func = functions[funchoice - 1].ref_func;
    double reference = ref_func(x);
    double difference = fabs(reference - taylor_result);
    printf("\nResults\n");
    printf("Reference value: %.10f\n", reference);
    printf("Taylor value: %.10f\n", taylor_result);
    printf("Absolute eps: %.10f\n", difference);
    printf("Amount of iters: %d of %d\n", iters1, iters);
}
void seriesofexperements(int funchoice, double x, double pogreshnost) {
    int experiments;
    printf("\nEnter the number of experiments 1-25\n");
    while (scanf("%d", &experiments) != 1 || experiments < 1 || experiments > maxexp) {
        printf("Incorrect input 1-25\n");
        cleanbuffer();
    }
    RefFunc ref_func = functions[funchoice - 1].ref_func;
    double reference = ref_func(x);
    printf("\nReference value: %.10f\n", reference);
    printf("\n┌───────┬────────────────────┬────────────────────┐\n");
    printf("│ Iters │      Taylor       │        Eps         │\n");  //s rablizoy pomogla neyronka chtob bilo krasivo
    printf("├───────┼────────────────────┼────────────────────┤\n");
    TaylorFunc taylor_func = functions[funchoice - 1].taylor_func;
    for (int i = 1; i <= experiments; i++) {
        int iters1 = 0;
        double taylor_result = taylor_func(x, i, pogreshnost, &iters1);
        double reference_against_teylor = fabs(reference - taylor_result);
        printf("│ %5d │ %18.10f │ %18.10f │\n", i, taylor_result, reference_against_teylor);
    }
    printf("└───────┴────────────────────┴────────────────────┘\n");
}
int main() {
    int mode, funchoice;
    double x, x1, eps;
    printf("Choose '1' for single experiment or '2' for multi-experiment or '3' for exit\n");
    while (1) {
        if (scanf("%d", &mode) != 1 || mode < 1 || mode > 3) {
            printf("Incorrect input 1-3\n");
            cleanbuffer();
            continue;
        }
        break;
    }
    if (mode == 3) {
        printf("Exit\n");
        return 0;
    }
    printf("Choose the function '1' - sin '2' - cos '3'-exp '4'-arcctg\n");
    while (1) {
        if (scanf("%d", &funchoice) != 1 || funchoice < 1 || funchoice > 4) {
            printf("Incorrect input 1-4\n");
            cleanbuffer();
            continue;
        }
        break;
    }
    if (funchoice == 1 || funchoice == 2) {
        printf("Enter the point in degrees\n");
        while (scanf("%lf", &x) != 1) {
            printf("Incorrect input\n");
            cleanbuffer();
        }
        x1 = radiants(x);
    }
    else {
        printf("Enter the point: ");
        while (scanf("%lf", &x) != 1) {
            printf("Incorrect input\n");
            cleanbuffer();
        }
        x1 = x;
    }
    printf("Enter eps >=0.000001\n");
    while (scanf("%lf", &eps) != 1 || eps < min_pogreshnost) {
        printf("Incorrect input >= 0.000001\n");
        cleanbuffer();
    }
    switch (mode) {
    case 1:
        single_calculation(funchoice, x1, eps);
        break;
    case 2:
        seriesofexperements(funchoice, x1, eps);
        break;
    }
    return 0;
}