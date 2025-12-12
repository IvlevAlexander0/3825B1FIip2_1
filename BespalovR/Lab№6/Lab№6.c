#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

long double lf_sin(long double eps, size_t n, long double x, size_t *i_count) {
    long double res = 0;
    long double term = x; 
    long double x_squared = x * x;
    short int sign = 1;
    *i_count = 0;
    for (size_t i = 0; i < n; ++i) {
        res += sign * term;
        *i_count++;
        if (fabsl(term) < eps) {
            break;
        }
        term *= x_squared;
        term /= (2 * i + 2);
        term /= (2 * i + 3);
        sign *= -1;
    }
    return res;
}
long double lf_cos(long double eps, size_t n, long double x, size_t *i_count) {
    long double res = 0;
    long double term = 1;
    long double x_squared = x * x;
    short int sign = 1;
    *i_count = 0;
    for (size_t i = 0; i < n; ++i) {
        res += sign * term;
        *i_count++;
        if (fabsl(term) < eps) {
            break;
        }
        term *= x_squared;
        term /= (2 * i + 1);
        term /= (2 * i + 2);
        sign *= -1;
    }
    return res;
}
long double lf_exp(long double eps, size_t n, long double x, size_t *i_count) {
    long double res = 0;
    long double term = 1;
    *i_count = 0;
    for (size_t i = 0; i < n; ++i) {
        res += term;
        *i_count++;
        if (fabsl(term) < eps) {
            break;
        }
        term *= x;
        term /= ( i + 1);
    }
    return res;
}
long double lf_arccos(long double eps, size_t n, long double x, size_t *i_count) {
    if (x < -1 || x > 1) {
        printf("Incorrect input. x must be in [-1;1].\n");
        return EOF;
    }
    long double res = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989/2;
    long double term = x;
    long double x_squared = x * x;
    *i_count = 0;
    for (size_t i = 0; i < n; ++i) {
        res -= term;
        *i_count++;
        if (fabsl(term) < eps) {
            break;
        }
        term *= x_squared;
        term *= (2 * i + 1);
        term *= (2 * i + 1);
        term /= (2 * i + 2);
        term /= (2 * i + 3);
    }
    return res;
}
long double (*lf_func(int choice))(long double, size_t, long double, size_t*) {
    switch (choice) {
    case 1: 
        return lf_sin;
        break;
    case 2: 
        return lf_cos;
        break;
    case 3: 
        return lf_exp;
        break;
    case 4: 
        return lf_arccos;
        break;
    }
}
long double (*standard_func(int choice))( long double ) {
    switch (choice) {
    case 1: 
        return sinl;
        break;
    case 2: 
        return cosl;
        break;
    case 3: 
        return expl;
        break;
    case 4: 
        return acosl;
        break;
    }
}
int select_mode() {
    printf("Select the program mode:\n1 - Singular calculation.\n2 - Serial calculation.\n");
    int choice;
    while (scanf("%d", &choice) != 1 || choice > 2 || choice < 1) {
        printf("Incorrect input. Please try again.\n");
        char c;
        while ((c = getchar()) != '\n') {}
    }
    return choice;
}
int select_function() {
    printf("Select function:\n1 - Sin.\n2 - Cos.\n3 - Exp.\n4 - Arccos.\n");
    int choice;
    while (scanf("%d", &choice) != 1 || choice > 4 || choice < 1) {
        printf("Incorrect input. Please try again.\n");
        while (getchar() != '\n');
    }
    return choice;
}

int main() {

    int mode = select_mode();
    int choice = select_function();
    size_t i;
    size_t* i_count = &i;
    long double(*fnc)(long double) = standard_func(choice);
    long double(*lf_fnc)(long double, size_t, long double, size_t*) = lf_func(choice);
    switch (mode) {
    case 1: {


        printf("Input x.\n");
        long double x;
        while (scanf("%Lf", &x) != 1) {
            printf("Incorrect input. Please try again.\n");
            char c;
            while ((c = getchar()) != '\n') {}
        }


        printf("Input EPS.\n");
        long double eps;
        while (scanf("%Lf", &eps) != 1 || eps < 0.000001) {
            printf("Incorrect input. Please try again.\n");
            char c;
            while ((c = getchar()) != '\n') {}
        }


        printf("Input n.\n");
        size_t n;
        while (scanf("%zu", &n) != 1 ||  n < 1) {
            printf("Incorrect input. Please try again.\n");
            char c;
            while ((c = getchar()) != '\n') {}
        }


        printf("%Lf\n", fnc(x));
        printf("%Lf\n", lf_fnc(eps, n, x, i_count));
        printf("%Lf\n", fabsl(lf_fnc(eps, n, x, i_count) - fnc(x)));
        printf("%zu\n", i);
        break;
    }


    case 2: {


        printf("Input x.\n");
        long double x;
        while (scanf("%Lf", &x) != 1) {
            printf("Incorrect input. Please try again.\n");
            char c;
            while ((c = getchar()) != '\n') {}
        }


        printf("Input n.\n");
        size_t nmax;
        while (scanf("%zu", &nmax) != 1 || nmax < 1) {
            printf("Incorrect input. Please try again.\n");
            char c;
            while ((c = getchar()) != '\n') {}
        }

        for (size_t n = 1; n < nmax + 1; ++n) {
            printf("%zu\t%Lf\t%Lf\n", n, lf_fnc(0, n, x, i_count), fabsl(lf_fnc(0, n, x, i_count) - fnc(x)));
        }
        break;
    }
    }
}
