#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 1000
#define NMAX 25
#define PI 3.14159265358979323846
#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef long double (*tayf)(long double, int, int*);
typedef long double (*reff)(long double);
typedef struct {
	int id;
	const char* name;
	tayf tay_f;
	reff ref_f;
}func_info;

void f_menu() {
	printf("Function selection menu:\n");
	printf("1.sin(x)\n");
	printf("2.cos(x)\n");
	printf("3.exp(x)\n");
	printf("4.arctg(x)\n");
	printf("Your choice:");
}
void m_menu() {
	printf("Selecting a mode:\n");
	printf("1.Single calculation\n");
	printf("2.Serial experiment\n");
	printf("0.Exit\n");
	printf("Your choice:");
}
//Riad Taylora
long double t_sin(long double x, int n, int* comp_elem) {
	long double res = 0.0;
	long double elem0 = x;
	int elem_num = 1;
	*comp_elem = 0;
	while (x > PI) x -= 2 * PI;
	while (x < -PI) x += 2 * PI;
	for (int i = 0; i < n; ++i) {
		res += elem0;
		elem_num += 2;
		elem0 = -elem0 * x * x / ((elem_num - 1) * elem_num);
		(*comp_elem)++;
	}
	return res;
}
long double t_cos(long double x, int n, int* comp_elem) {
	long double res = 0.0;
	long double elem0 = 1.0;
	int elem_num = 0;
	*comp_elem = 0;
	while (x > PI) x -= 2 * PI;
	while (x < -PI) x += 2 * PI;
	for (int i = 0; i < n; ++i) {
		res += elem0;
		elem_num += 2;
		elem0 = -elem0 * x * x / ((elem_num - 1) * elem_num);
		(*comp_elem)++;
	}
	return res;
}
long double t_exp(long double x, int n, int* comp_elem) {
	long double res = 1.0;
	long double elem0 = 1.0;
	int elem_num = 1;
	*comp_elem = 1;
	for (int i = 1; i < n; ++i) {
		elem0 *= x / elem_num;
		res += elem0;
		elem_num++;
		(*comp_elem)++;
	}
	return res;
}
long double t_arctg(long double x, int n, int* comp_elem) {
	if (x < -1 || x > 1) {
		printf("Error:arctg converges only when -1 <= х <= 1!\n");
		*comp_elem = 0;
		return NAN;
	}
	long double res = 0.0;
	long double elem0 = x;
	int elem_num = 1;	
	*comp_elem = 0;
	for (int i = 0; i < n; ++i) {
		res += elem0;
		elem_num += 2;
		elem0 = -elem0 * x * x * (elem_num - 2) / elem_num;
		(*comp_elem)++;
	}
	return res;
}
//Osnv
void calculate(func_info* func, long double x, long double eps, long double n) {
	long double ref_val = func->ref_f(x);
	long double res = 0.0;
	long double elem0 = 1.0;
	int comp_elem = 0;
	switch (func->id) {
	case 1://sin	
		res = 0.0;
		elem0 = x;
		comp_elem = 0;
		break;
	case 2://cos
		res = 0.0;
		elem0 = 1.0;
		comp_elem = 0;
		break;
	case 3://exp
		res = 1.0;
		elem0 = 1.0;
		comp_elem = 1;
		break;
	case 4://atg
		if (x < -1 || x > 1) {
			printf("Error:x must be between -1 and 1!\n");
			return;
		}
		res = 0.0;
		elem0 = x;
		comp_elem = 0;
		break;
	}
	while (comp_elem < n) {
		if (!(func->id == 3 && comp_elem == 0)) {
			res += elem0;
		}
		comp_elem++;
		if (ABS(elem0) < eps) {
			break;
		}
		switch (func->id) {
		case 1: // sin(x)
			elem0 = -elem0 * x * x / ((2 * comp_elem) * (2 * comp_elem + 1));
			break;
		case 2: // cos(x)
			elem0 = -elem0 * x * x / ((2 * comp_elem - 1) * (2 * comp_elem));
			break;
		case 3: // exp(x)
			elem0 *= x / (comp_elem + 1);
			break;
		case 4: // arctg(x)
			elem0 = -elem0 * x * x * (2 * comp_elem - 1) / (2 * comp_elem + 1);
			break;
		}
	}
	printf("=== Calculation results ===\n");
	printf("Function: %s\n", func->name);
	printf("Reference value: %Lf\n", ref_val);
	printf("Calculated estimate: %Lf\n", res);
	printf("Difference: %Lf\n", ABS(res - ref_val));
	printf("Number of terms: %d\n", comp_elem);
}
//1
void sin_calc(func_info func[], int count) {
	int f_c = 0, n = 0;
	long double x = 0.0, eps = 0.0;
	f_menu();
	if (scanf("%d", &f_c) != 1 || f_c <1 || f_c> count) {
		printf("Incorrect function selection!\n");
		while (getchar() != '\n');
		return;
	}
	func_info* sel_func = &func[f_c - 1];
	printf("Enter point x:");
	if (scanf("%Lf", &x) != 1) {
		printf("x entered incorrectly!");
		while (getchar() != '\n');
		return;
	}
	printf("Enter the calculation precision(from 0.000001 and higher):");
	if (scanf("%Lf", &eps) != 1 || eps < 0.000001) {
		printf("The accuracy must be at least 0.000001!\n");
		while (getchar() != '\n');
		return;
	}
	printf("Enter the maximum number of elements in the series (1-1000):");
	if (scanf("%d", &n) != 1 || n < 1 || n > N) {
		printf("The number of elements must be from 1 to 1000!\n");
		while (getchar() != '\n');
		return;
	}
	calculate(sel_func,x,eps,n);
}

//
//2
void ser_exper(func_info func[], int count) {
	int f_c = 0, ex = 0;
	long double x = 0.0;
	f_menu();
	if (scanf("%d", &f_c) != 1 || f_c <1 || f_c> count) {
		printf("Incorrect function selection!\n");
		while (getchar() != '\n');
		return;
	}
	func_info* sel_func = &func[f_c - 1];
	printf("Enter point x:");
	if (scanf("%Lf", &x) != 1) {
		printf("x entered incorrectly!");
		while (getchar() != '\n');
		return;
	}
	printf("Enter the number of experiments (1-25):");
	if (scanf("%d", &ex) != 1 || ex < 1 || ex > NMAX) {
		printf("The number of experiments should be from 1 to 25!\n");
		while (getchar() != '\n');
		return;
	}
	long double ref_val = sel_func->ref_f(x);
	printf("=== Results of a serial experiment ===\n");
	printf("Function: %s\n", sel_func->name);
	printf("Reference value: %Lf\n", ref_val);
	printf("--------------------------------------------------------\n");
	printf("|   Terms   |      Eval.values     |        Diff        \n");
	printf("|-----------|----------------------|--------------------\n");
	for (int nm = 1; nm <= ex; ++nm) {
		int comp_elem = 0;
		long double res = sel_func->tay_f(x, nm, &comp_elem);
		if (isnan(res)) {
			printf("| %9d |Calculation error|No data\n", comp_elem);
			continue;
		}
		printf("| %9d |  %17.10Lf   | %14.10Lf\n", comp_elem, res, ABS(res-ref_val));
	}
}
//
int main() {
	func_info func[] = { {1,"sin(x)",t_sin,sinl}, {2, "cos(x)", t_cos, cosl},
		{3, "exp(x)", t_exp, expl}, {4, "arctg(x)", t_arctg, atanl} };
	int count = sizeof(func) / sizeof(func[0]);
	int m_c = 0;
	do{
		m_menu();
		if (scanf("%d", &m_c) != 1) {
			printf("Invalid input!\n");
			while (getchar() != '\n');
			continue;
		}
		switch (m_c) {
		case 1:
			sin_calc(func, count);
			break;
		case 2:
			ser_exper(func, count);
			break;
		case 0:
			printf("Exit\n");
			break;
		default:
			printf("Incorrect mode selection!\n");
			break;
		}
		if (m_c != 0) {
			printf("--------------------------------------------------------\n");
			printf("Press Enter to continue");
			while (getchar() != '\n');
		}
	} while (m_c != 0);
	return 0;
}
