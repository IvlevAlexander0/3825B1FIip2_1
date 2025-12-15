#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

typedef double (*taylorFunc)(double, int, double, int*);

double taylorSin(double x, int maxMembers, double epsilon, int* actualMembers) {
    while (x > PI) x -= 2 * PI;
    while (x < -PI) x += 2 * PI;
    
    double result = x;
    double term = x;
    int n = 1;
    
    while (n < maxMembers) {
        term *= -x * x / ((2 * n) * (2 * n + 1));
        result += term;
        n++;
        if (fabs(term) < epsilon) break;
    }
    *actualMembers = n;
    return result;
}

double taylorCos(double x, int maxMembers, double epsilon, int* actualMembers) {
    while (x > PI) x -= 2 * PI;
    while (x < -PI) x += 2 * PI;
    
    double result = 1.0;
    double term = 1.0;
    int n = 1;
    
    while (n < maxMembers) {
        term *= -x * x / ((2 * n - 1) * (2 * n));
        result += term;
        n++;
        if (fabs(term) < epsilon) break;
    }
    *actualMembers = n;
    return result;
}

double taylorExp(double x, int maxMembers, double epsilon, int* actualMembers) {
    double result = 1.0;
    double term = 1.0;
    int n = 1;
    
    while (n < maxMembers) {
        term *= x / n;
        result += term;
        n++;
        if (fabs(term) < epsilon) break;
    }
    *actualMembers = n;
    return result;
}

double taylorArcsin(double x, int maxMembers, double epsilon, int* actualMembers) {
    if (x < -1.0 || x > 1.0) {
        printf("arcsin(x) requires -1 <= x <= 1\n");
        *actualMembers = 0;
        return NAN;
    }
    
    double result = x;
    double term = x;
    int n = 1;
    
    while (n < maxMembers) {
        term *= x * x * (2 * n - 1) * (2 * n - 1) / ((2 * n) * (2 * n + 1));
        result += term;
        n++;
        if (fabs(term) < epsilon) break;
    }
    *actualMembers = n;
    return result;
}

void functionMenu() {
    printf("Select function:\n");
    printf("1. sin(x)\n");
    printf("2. cos(x)\n");
    printf("3. exp(x)\n");
    printf("4. arcsin(x)\n");
}

void modeMenu() {
    printf("Select mode:\n");
    printf("1. Single calculation\n");
    printf("2. Serial experiment\n");
    printf("3. Exit\n");
}

void singleCalculation() {
    int choice, maxMembers, actualMembers;
    double x, epsilon, taylorResult, exactResult;
    taylorFunc taylor = NULL;
    
    functionMenu();
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        printf("Invalid function choice\n");
        clearInputBuffer();
        return;
    }
    
    printf("Enter x: ");
    if (scanf("%lf", &x) != 1) {
        printf("Invalid x\n");
        clearInputBuffer();
        return;
    }
    
    if (choice == 4 && (x < -1.0 || x > 1.0)) {
        printf("Warning: arcsin(x) converges for -1 <= x <= 1 only\n");
    }
    
    switch (choice) {
        case 1: taylor = taylorSin; exactResult = sin(x); break;
        case 2: taylor = taylorCos; exactResult = cos(x); break;
        case 3: taylor = taylorExp; exactResult = exp(x); break;
        case 4: taylor = taylorArcsin; exactResult = asin(x); break;
        default: return;
    }
    
    printf("Enter epsilon (>= 0.000001): ");
    if (scanf("%lf", &epsilon) != 1 || epsilon < 0.000001) {
        printf("Invalid epsilon\n");
        clearInputBuffer();
        return;
    }
    
    printf("Enter max terms (1-1000): ");
    if (scanf("%d", &maxMembers) != 1 || maxMembers < 1 || maxMembers > 1000) {
        printf("Invalid max terms\n");
        clearInputBuffer();
        return;
    }
    
    taylorResult = taylor(x, maxMembers, epsilon, &actualMembers);
    
    printf("Exact value: %lf\n", exactResult);
    printf("Taylor value: %lf\n", taylorResult);
    printf("Difference: %lf\n", fabs(taylorResult - exactResult));
    printf("Terms used: %d\n", actualMembers);
}

void serialExperiment() {
    int choice, NMax, actualMembers;
    double x, taylorResult, exactResult;
    taylorFunc taylor = NULL;
    
    functionMenu();
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        printf("Invalid function choice\n");
        clearInputBuffer();
        return;
    }
    
    printf("Enter x: ");
    if (scanf("%lf", &x) != 1) {
        printf("Invalid x\n");
        clearInputBuffer();
        return;
    }
    
    if (choice == 4 && (x < -1.0 || x > 1.0)) {
        printf("Warning: arcsin(x) converges for -1 <= x <= 1 only\n");
    }
    
    switch (choice) {
        case 1: taylor = taylorSin; exactResult = sin(x); break;
        case 2: taylor = taylorCos; exactResult = cos(x); break;
        case 3: taylor = taylorExp; exactResult = exp(x); break;
        case 4: taylor = taylorArcsin; exactResult = asin(x); break;
        default: return;
    }
    
    printf("Enter number of experiments (1-25): ");
    if (scanf("%d", &NMax) != 1 || NMax < 1 || NMax > 25) {
        printf("Invalid number of experiments\n");
        clearInputBuffer();
        return;
    }
    
    printf("Exact value: %lf\n", exactResult);
    printf("Terms | Taylor value | Difference\n");
    
    for (int i = 1; i <= NMax; i++) {
        taylorResult = taylor(x, i, 0.0, &actualMembers);
        printf("%5d | %12lf | %12lf\n", i, taylorResult, fabs(taylorResult - exactResult));
    }
}

int main() {
    int modeChoice;
    
    while (1) {
        modeMenu();
        if (scanf("%d", &modeChoice) != 1) {
            clearInputBuffer();
            continue;
        }
        
        switch (modeChoice) {
            case 1: singleCalculation(); break;
            case 2: serialExperiment(); break;
            case 3: return 0;
            default: printf("Invalid mode\n");
        }
    }
}