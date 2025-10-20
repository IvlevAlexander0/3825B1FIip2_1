#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>


void main() {
	printf("Hello, it is a cabinet Weight Calculator \n");
	float h, w, d;
	float const tol_stenki = 0.5f;
	float const tol_bok = 1.5f;
	float const tol_nakl = 1.5f;
	float const tol_dveri = 1.0f;
	float const tol_polk = 0.5f;
	float const plotnost_dsp = 0.55f;
	float const plotnost_dvp = 0.95f;
	float const plotnost_dereva = 0.54f;
	char fl = '0';

	do {
		if (fl == '1') {
			printf("Input error. Try again. \n");
		}

		printf("Enter h (180-220):\n");
		scanf("%f", &h);

		printf("Enter w (80-120):\n");
		scanf("%f", &w);

		printf("Enter d (50-90):\n");
		scanf("%f", &d);
		fl = '1';
	} while (h < 180 || h > 220 || w < 80 || w > 120 || d < 50 || d > 90);

	double mas_zad = plotnost_dvp * h * w * tol_stenki;
	double mas_bok = 2 * plotnost_dsp * d * tol_bok * h;
	double mas_nakl = 2 * plotnost_dsp * w * d * tol_nakl;
	double mas_dveri = plotnost_dereva * h * w * tol_dveri;

	int count_polk = 0;
	float h1 = 0.0f;
	while (h >= h1 + 40.5f) {
		count_polk++;
		h1 += 40.5f;
	}
	double mas_polk = count_polk * plotnost_dsp * tol_polk * w * d;
	double ms = mas_bok + mas_dveri + mas_nakl + mas_polk + mas_zad;
	printf("Finish massa: %lf kg", ms / 1000.0);
}
