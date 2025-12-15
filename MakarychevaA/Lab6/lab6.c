#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define pi 3.1415926535 

void clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

typedef double (*taylorFunc)(double, int, double, int*);

double taylorSin(double x, int maxMembers, double epsilon, int* actualMember) {
	double result = 0.0;
	int n = 0;
	while (x > pi) {
		x = x - 2 * pi;
	}
	while (x < -pi) {
		x = x + 2 * pi;
	}
	double member = x;
	result = member;
	for (n = 1; n < maxMembers; n++) {
		member = member * (-x * x / ((2 * n) * (2 * n + 1)));
		result += member;
		if (fabs(member) < epsilon) {
			break;
		}
	}
	*actualMember = n + 1;
	return result;
}

double taylorCos(double x, int maxMembers, double epsilon, int* actualMember) {
	double result = 0.0;
	int n = 0;
	while (x > pi) {
		x = x - 2 * pi;
	}
	while (x < -pi) {
		x = x + 2 * pi;
	}
	double member = 1.0;
	result = member;
	for (n = 1; n < maxMembers; n++) {
		member = member * (- x * x / ((2 * n - 1) * (2 * n)));
		result += member;
		if (fabs(member) < epsilon) {
			break;
		}
	}
	*actualMember = n + 1;
	return result;
}

double taylorExp(double x, int maxMembers, double epsilon, int* actualMembers) {
	double result = 0.0;
	int n = 0;
	while (x > pi) {
		x = x - 2 * pi;
	}
	while (x < -pi) {
		x = x + 2 * pi;
	}
	double member = 1.0;
	result = member;
	for (n = 1; n < maxMembers; n++) {
		member = member * (x / n);
		result += member;
		if (fabs(member) < epsilon) {
			break;
		}
	}
	*actualMembers = n + 1;
	return result;
}

double taylorLn(double x, int maxMembers, double epsilon, int* actualMembers) {
	double result = 0.0;
	int n = 0;
	double member = x;
	result = member;
	for (n = 1; n < maxMembers; n++) {
		member = member * (-x * (double)n / (double)(n + 1));
		result += member;
		if (fabs(member) < epsilon) {
			break;
		}
	}
	*actualMembers = n + 1;
	return result;
}

void functionMenu() {
	printf("Function\n");
	printf("1. sin(x)\n");
	printf("2. cos(x)\n");
	printf("3. exp(x)\n");
	printf("4. ln(1+x)\n");
}

void modeMenu() {
	printf("Mode\n");
	printf("1. Single calculation of a function at a given point\n");
	printf("2. Serial experiment\n");
	printf("3. Exit\n");
}

void singleCalculation() {
	int choice;
	int maxMembers;
	int actualMembers = 0;
	double x;
	double epsilon;
	double taylorResult;
	double exactResult = 0.0;
	int scanfSymCount = 0;
	taylorFunc taylor = NULL;

	functionMenu();
	scanfSymCount = scanf("%d", &choice);
	while (scanfSymCount != 1 || choice < 1 || choice > 4) {
		printf("Error. Enter choice (1-4)\n");
		clearInputBuffer();
		scanfSymCount = scanf("%d", &choice);
	}

	printf("Enter x\n");
	scanfSymCount = scanf("%lf", &x);

	while (scanfSymCount != 1 || ( choice == 4 && (x <= -1.0 || x > 1.0))) {
			printf("The Taylor series for ln(1+x) converges only for -1 < x <= 1. Enter value (-1 - 1)\n");
		clearInputBuffer();
		scanfSymCount = scanf("%lf", &x);
	}

	switch (choice) {
	case 1: {
		taylor = taylorSin;
		exactResult = sin(x);
		break;
	}
	case 2: {
		taylor = taylorCos;
		exactResult = cos(x);
		break;
	}
	case 3: {
		taylor = taylorExp;
		exactResult = exp(x);
		break;
	}
	case 4: {
		taylor = taylorLn;
		exactResult = log(1.0 + x);
		break;
	}
	default:
		return;
	}

	printf("Enter epsilon (>=0.000001)\n");
	scanfSymCount = scanf("%lf", &epsilon);
	while (scanfSymCount != 1 || epsilon < 0.000001) {
		printf("Error. Enter epsilon (>=0.000001)\n");
		clearInputBuffer();
		scanfSymCount = scanf("%lf", &epsilon);
	}

	printf("Enter the maximum number of terms(1-1000)\n");
	scanfSymCount = scanf("%d", &maxMembers);
	while (scanfSymCount != 1 || maxMembers < 1 || maxMembers > 1000) {
		printf("Error. Enter the maximum number of terms(1-1000)\n");
		clearInputBuffer();
		scanfSymCount = scanf("%d", &maxMembers);
	}

	taylorResult = taylor(x, maxMembers, epsilon, &actualMembers);

	printf("Exact result %lf\n", exactResult);
	printf("Taylor result %lf\n", taylorResult);
	printf("Difference %lf\n", fabs(taylorResult - exactResult));
	printf("Actual members %d\n", actualMembers);
}

void serialExperiment() {
	int choice;
	int NMax;
	double x;
	int actualMembers = 0;
	double taylorResult;
	double exactResult = 0.0;
	int scanfSymCount = 0;
	taylorFunc taylor = NULL;

	functionMenu();
	scanfSymCount = scanf("%d", &choice);
	while (scanfSymCount != 1 || choice < 1 || choice > 4) {
		printf("Error. Enter choice (1-4)\n");
		clearInputBuffer();
		scanfSymCount = scanf("%d", &choice);
	}

	printf("Enter x\n");
	scanfSymCount = scanf("%lf", &x);

	while (scanfSymCount != 1 || (choice == 4 && (x <= -1.0 || x > 1.0))) {
		printf("The Taylor series for ln(1+x) converges only for -1 < x <= 1. Enter value (-1 - 1)\n");
		clearInputBuffer();
		scanfSymCount = scanf("%lf", &x);
	}

	switch (choice) {
	case 1: {
		taylor = taylorSin;
		exactResult = sin(x);
		break;
	}
	case 2: {
		taylor = taylorCos;
		exactResult = cos(x);
		break;
	}
	case 3: {
		taylor = taylorExp;
		exactResult = exp(x);
		break;
	}
	case 4: {
		taylor = taylorLn;
		exactResult = log(1.0 + x);
		break;
	}
	default:
		return;
	}

	printf("Enter number of experiments (1-25)\n");
	scanfSymCount = scanf("%d", &NMax);
	while (scanfSymCount != 1 || NMax < 1 || NMax > 25){
		printf("Error. Enter number of experiments (1-25)\n");
		clearInputBuffer();
		scanfSymCount = scanf("%d", &NMax);
	}

	printf("Exact result %lf\n", exactResult);

	printf("| Member |  Meaning   | Difference |\n");
	for (int i = 1; i <= NMax; i++) {
		taylorResult = taylor(x, i, 0.0, &actualMembers);
		printf("| %6d | %10lf | %10lf |\n", i, taylorResult, fabs(taylorResult - exactResult));
	}
}

	int main() {
		int modeChoice = 0;
		int scanfSymCount = 0;
		while (1) {  
			modeMenu(); 
			scanfSymCount = scanf("%d", &modeChoice);
			while (scanfSymCount != 1 || modeChoice < 1 || modeChoice > 3) {
				printf("Error. Enter mode (1-3)\n");
				clearInputBuffer();
				scanfSymCount = scanf("%d", &modeChoice);
			}
			switch (modeChoice) {
			case 1: {
				singleCalculation();
				break;
			}
			case 2: {
				serialExperiment();
				break;
			}
			case 3:{
				printf("Exit\n");
				return 0;
			}
			default:
				printf("Error\n");  
			}
		}
	}
