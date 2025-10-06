#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

int main() 
{
	setlocale(LC_ALL, "Russian");
	double x1, y1, r1; // Первая окружность 
	double x2, y2, r2; // Вторая окружность

	printf("\nВведите параметры первой окружности: (x,y,r): ");
	if (scanf("%lf%lf%lf", &x1, &y1, &r1) != 3) 
	{
		printf("Ошибка ввода параметров первой окружности!\n");
		return 1;
	}
	else printf("Ошибка"); return 1;

	printf("\nВведите параметры второй окружности: (x,y,r): ");
	if (scanf("%lf%lf%lf", &x2, &y2, &r2) != 3) 
	{
		printf("Ошибка ввода параметров второй окружности!\n");
		return 1;
	}
	else printf("Ошибка"); return 1;

	//Вычисление расстояний между центрами окружностей
	double dx = x2 - x1;
	double dy = y2 - y1;
	double distanceSqared = dx * dx + dy * dy;

	//Вычисление суммы и разности радиусов в квадрате
	double sum_radii = r1 + r2;
	double sum_radii_squared = sum_radii * sum_radii;

	double diffRadii;
	if (r1 > r2) 
	{
		diffRadii = r1 - r2;
	}
	else 
	{
		diffRadii = r2 - r1;
	}
	double diffSqared = diffRadii * diffRadii;

	//Определяем расположение
	if (distanceSqared == 0) 
	{

		if (r1 == r2) 
		{
			printf("\nОкружности совпадают");
		}
		else 
		{
			printf("\nОкружности одна внутри другой");
		}

	}
	else if (distanceSqared == sum_radii_squared) 
	{
		printf("\nОкружности касаются");
	}
	else if (distanceSqared == diffSqared) 
	{
		printf("\nОкружности пересекаются");
	}
	else if (distanceSqared > sum_radii_squared) 
	{
		printf("\nНе пересекаются");
	}
	else if (distanceSqared < diffSqared) 
	{
		printf("\nОдна окружность лежит внутри другой");
	}
	else 
	{
		printf("\nОкружность пересекается в двух точках");
	}

	return 0;
}