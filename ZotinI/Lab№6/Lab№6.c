#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*teylorfunc)(double, int, int*, double);
typedef double (*refencefunc)(double);

double factorial(int n) {
    double res = 1.0;
    for (int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

double tsin(double x, int n, int* count, double pog) {
    double res = 0.0;
    double term;
    double prev;
    if (count) {
        *count = 0;
    }

    for (int k = 0; k < n; k++) {
        int step = 2 * k + 1;
        term = pow(x, step) / factorial(step);

        if (k % 2 == 1) {
            term = -term;
        }

        res += term;
        if (count) {
            (*count)++;
        }

        if (k > 0 && fabs(term) < pog) {
            break;
        }
    }

    return res;
}


double tcos(double x, int n, int* count, double pog) {
    double res = 0.0;
    double term;
    if (count) {
        *count = 0;
    }

    for (int k = 0; k < n; k++) {
        int step = 2 * k;
        term = pow(x, step) / factorial(step);

        if (k % 2 == 1) {
            term = -term;
        }

        res += term;
        if (count) {
            (*count)++;
        }
        if (k > 0 && fabs(term) < pog) {
            break;
        }
    }

    return res;
}

double telexp(double x, int n, int* count, double pog) {
    double res = 0.0;
    double term;
    if (count) {
        *count = 0;
    }

    for (int k = 0; k < n; k++) {
        term = pow(x, k) / factorial(k);
        res += term;
        if (count) {
            (*count)++;
        }

        if (k > 0 && fabs(term) < pog) {
            break;
        }
    }

    return res;
}

double tarcsin(double x, int n, int* count, double pog) {
    double res = 0.0;
    double term;
    if (count) {
        *count = 0;
    }

    for (int k = 0; k < n; k++) {
        double coeff = 1.0;
        for (int i = 1; i <= k; i++) {
            coeff *= (2.0 * i - 1.0) / (2.0 * i);
        }

        int step = 2 * k + 1;
        term = coeff * pow(x, step) / step;

        res += term;
        if (count) {
            (*count)++;
        }

        if (k > 0 && fabs(term) < pog) {
            break;
        }
    }

    return res;
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
	while (scanf(" %c", &mode) != 1 || (mode != '1' && mode != '2')) {
		printf("Input error. Try again!\n");
	}
	while (getchar() != '\n');

	printf("Select a function: \n1. sin x \n2. cos x \n3. exp x \n4. arcsin x\n");
	while (scanf(" %c", &func) != 1 || (func != '1' && func != '2' && func != '3' && func != '4')) {
		printf("Input error. Try again!\n");
	}
	while (getchar() != '\n');

	printf("Enter the point where you want to calculate the value: \n");
	while (scanf("%lf", &x) != 1 || (func == '4' && (x < -1.0 || x > 1.0))) {
		printf("Input error. Try again!\n");
	}
	while (getchar() != '\n');

	if (mode == '1') {
		int n;
        int count = 0;
		printf("Enter the accuracy of the calculation (from 0.000001 or more): \n");
		while (scanf("%lf", &pog) != 1) {
			printf("Input error. Try again!\n");
		}
		while (getchar() != '\n');

		printf("Enter the maximum number of row elements to perform the calculation (N - from 1 to 1000): \n");
		while (scanf("%d", &n) != 1 || (n < 1 || n > 1000)) {
			printf("Input error. Try again!\n");
		}
		while (getchar() != '\n');

        teylorfunc taylor = rdT(func);
        refencefunc std = standart(func);

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
        while (scanf("%d", &nmax) != 1 || nmax < 1 || nmax > 25) {
            printf("Input error. Try again!\n");
        }
        while (getchar() != '\n');

        refencefunc std = standart(func);
        teylorfunc taylor = rdT(func);
        double et = std(x);
        printf("The reference value: %.10f\n\n", et);
        printf(" --------------------------------------------------------\n");
        printf("| Count |         Taylor        |       Difference       |\n");
        printf(" --------------------------------------------------------\n");
        double tlor;
        int pr = -1;
        for (int i = 1; i <= nmax; i++) {
            int count = 0;
            double tlor = taylor(x, i, &count, 1e-20);
            if (count != pr) {
                printf("|  %3d  | %21.10f | %21.10f  |\n", count, tlor, et - tlor);
            }
            pr = count;
        }
        printf("---------------------------------------------------------\n\n");
	}
	return 0;
}