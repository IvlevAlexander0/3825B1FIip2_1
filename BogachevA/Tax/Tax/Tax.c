#include <stdio.h>
#include <math.h>
void main() {
	double a, b, c, Tax, p, S, Nalog;
	scanf_s("%d,%d,%d", &a, &b, &c);
	Tax = 10.5f;
	p = (a + b + c) / 2;
	S = sqrt(p * (p - a) * (p - b) * (p - c));
	Nalog = S * Tax;
	printf("%f", Nalog);
}