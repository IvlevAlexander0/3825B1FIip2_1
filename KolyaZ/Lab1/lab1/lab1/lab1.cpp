#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>
void main()
{
	setlocale(LC_ALL, "Rus");
	double h, w, d;
	int n;
	double t1 = 0.5;
	double t2 = 1.5;
	double t3 = 1;
	double t4 = 0.5;
	double ds1 = 0.735;
	double ds2 = 1;
	double ds3 = 0.55;
	printf("Введите высоту от 180 см до 220 см, ширину от 80 см до 120 см, глубину от 50 см до 90 см\n");
	scanf("%lf%lf%lf", &h, &w, &d);
	if (h < 180 || h>220 || w < 80 || w > 120 || d < 50 || d > 90) 
	{
		printf("error");
	}
	else
	{
		n = h/(t4+40);
		double v1 = h * w * t1; //объём задней стенки
		double v2 = h * d * t2 * 2; //объём 2 боковин
		double v3 = w * d * t2; //объём 2 крышек
		double v4 = h * w * t3 * 2; //объём 2 дверей
		double v5 = w * d * t4 * n; //объём n полок
		double m1 = v1 * ds2;
		double m2 = v2 * ds1;
		double m3 = v3 * ds1;
		double m4 = v4 * ds3;
		double m5 = v5 * ds1;
		double m = m1 + m2 + m3 + m4 + m5;
		printf("m=%lf грамм", m);
	}
}