﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main() {
    // плотность будем считать как г/сm^3
    double const  tolst = 0.5;
    double const  tolbok = 1.5;
    double const  tolkr = 1.5;
    double const  toldver = 1.0;
    double const  tolpolk = 0.5;
    double const  plDSP = 0.75;
    double const  plDVP = 0.85;
    double const  plderevo = 0.6;
    double h, d, w;
    printf("calculation of cabinet weight\n");
    printf("==================\n");
    printf("Enter the height of the cabinet h (180-220 cm): ");
    scanf("%lf", &h);
    printf("Enter the cabinet depth d (50-90 cm): ");
    scanf("%lf", &d);
    printf("Enter the cabinet width w(80 - 120 cm) : ");
    scanf("%lf", &w);
    if (h < 180 || h > 220 || d < 50 || d > 90 || w < 80 || w > 120) {
        printf("Error: the parameters are outside the allowed ranges!\n");
        return 1;
    }
    double masst = h * w * tolst * plDVP;
    double masbok = 2 * h * d * tolbok * plDSP;
    double maskr = 2 * w * d * tolkr * plDSP;
    double masdver = h * w * toldver * plderevo;
    double poslpolka = 0;
    int countpolk = 0;
    while (poslpolka <= h - 40.5) {
        countpolk += 1;
        poslpolka += 40.5;
    }
    double maspolk = countpolk * (w * tolpolk * d) * plDSP;
    double sum_mas = (masst + masbok + maskr + masdver + maspolk) / 1000.0;
    printf("\nCalculation results:\n");
    printf("Cabinet height: %.1f cm\n", h);
    printf("cabinet depth: %.1f cm\n", d);
    printf("cabinet width: %.1f cm\n", w);
    printf("cabinet weight : %.2f kg\n", sum_mas);
}