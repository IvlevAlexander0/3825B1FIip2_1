﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
void main() 
{
	printf("enter the size for the desired number. the correct values are from 2 to 5\n");
	char n1;
	while (1)
	{
		scanf("%c", &n1);
		if (((int)n1 >= 50) && ((int)n1 <= 53))
		{
			break;
		}
		printf("incorrect\n");
		while (getchar() != '\n');
	}
	int n = (int)n1 - 48;

	srand(time(NULL));
	int q[5];
	for (int i = 0; i < n; ++i)
	{
		int candidate, unique;
		do {
			candidate = rand() % 10;
			unique = 1;
			for (int j = 0; j < i; j++) {
				if (q[j] == candidate) {
					unique = 0;
					break;
				}
			}
		} while (!unique);
		q[i] = candidate;
	}

	printf("enter the answer\n");
	do
	{
		int an;
		scanf("%d", &an);
		int k = 0;
		int t = n;
		int ant = an;
		int an1[5];
		for (int i = 0; i < n; ++i)
		{
			an1[i] = ant / (int)pow(10.0, (double)(t - 1));
			ant = ant % (int)pow(10.0, (double)(t - 1));
			t = t - 1;
		}
		t = n;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (an1[i] > an1[j])
				{
					int temp = an1[j];
					an1[j] = an1[i];
					an1[i] = temp;
				}
			}
		}
		for (int i = 0; i < n; ++i)
		{
			if (an1[i] == an1[i + 1])
			{
				k++;
			}
		}
		if (!((an >= 10) && (an <= 99999) && (an / pow(10, n - 1) >= 1) && (an / pow(10, n - 1) <= 10) && (k == 0)))
		{
			printf("incorrect\n");
			continue;
		}
		k = 0;
		while (getchar() != '\n');
		int c = n;
		int a[5];
		for (int i = 0; i < n; ++i)
		{
			a[i] = an / (int)pow(10.0, (double)(c - 1));
			an = an % (int)pow(10.0, (double)(c - 1));
			c = c - 1;
		}
		c = n;

		int bull = 0;
		for (int i = 0; i < n; ++i)
		{
			if (a[i] == q[i])
			{
				bull++;
			}
		}
		int cow = 0;
		for (int i = 0; i < n; ++i)
		{
			if (a[i] != q[i])
			{
				for (int j = 0; j < n; ++j)
				{
					if (a[i] == q[j])
					{
						cow++;
						break;
					}
				}
			}
		}
		printf("cow = %d\n", cow);
		printf("bull = %d\n", bull);
		if (bull == n)
		{
			printf("You have found the answer.");
			break;
		}
	} while (1);
}
