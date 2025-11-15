#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void main() {
	int  h, d, w;
	double answer = 0.0;
	double p1, p2, p3;
	printf("enter the density of chipboard, particleboard, and wood\n");
	scanf("%lf", &p1);
	scanf("%lf", &p2);
	scanf("%lf", &p3);
	printf("enter the height, width, and depth\n ");
	scanf("%d", &h);
	scanf("%d", &w);
	scanf("%d", &d);
	if (h >= 180 && h <= 220 && w >= 80 && w <= 120 && d >= 50 && d <= 90) {
		int k = (h - 40) / 40 + 1;
		answer = (h * w * 0.05f * p2) + (h * d * 0.015f * p1 * 2) + (w * d * 0.015f * 2 * p2) + (h * w * 0.01f * p3 * 2) + (k * 0.4f * p1);
		printf("cabinet weight is %lf", answer);
	}

	else {
		printf("incorrectly entered data\n");
	}
}