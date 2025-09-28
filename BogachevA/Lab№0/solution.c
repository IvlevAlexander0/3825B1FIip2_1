#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>
int main() {
	setlocale(LC_ALL, "Rus");
	double x1, x2, y1, y2, r1, r2;
	double distance;
	scanf("%lf%lf%lf%lf%lf%lf\n", &x1, &x2, &y1, &y2, &r1, &r2);
	if (r1 != 0 && r2 != 0) {
		distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
		if (distance > r1 + r2) {
			printf("окружности не пересекаются");
		}
		else if (distance < r1 + r2) {
			printf("окружности пересекаются");
		}
		else if (distance == r1 + r2) {
			printf("окружности касаются");
		}
		else if (distance == 0) {
			printf("окружности лежат друг в друге");
		}
	}
	else {
		printf("радиусы не должны равняться нулю");
		}
		return 0;
	}