#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<stdio.h>

void main() {
	double h, d, w;
	double const pDSP = 0.735;    //в г/см^2
	double const pDVP = 0.8;    //в г/см^2
	double const pderev = 0.6;  //в г/см^2
	double const tol_st = 0.5;  //в см
	double const tol_bok = 1.5;  //в см
	double const tol_cr = 1.5;  //в см
	double const tol_dv = 1;  //в см
	double const tol_pol = 0.5;  //в см


	printf("Cabinet weight counter\n");
	printf("----------------------\n");

	printf("Enter the desired cabinet height h(180-220 cm): ");
	scanf("%lf", &h);

	printf("Enter the desired cabinet width w(80-120 cm): ");
	scanf("%lf", &w);

	printf("Enter the desired cabinet depth d(50-90 cm): ");
	scanf("%lf", &d);

	if (h < 180 || h > 220 || w < 80 || w > 120 || d < 50 || d > 90) {
		printf("The entered parameters do not meet the requirements!\n");
		return 1;
	}

	double mas_st = (h * tol_st * w) * pDVP;
	double mas_bok = 2 * (h * tol_bok * d) * pDSP;
	double mas_cr = 2 * (d * tol_cr * w) * pDSP;
	double mas_dv = (h * tol_dv * w) * pderev;
	double mas_pol = (d * tol_pol * w) * pDSP;   //масса одной полки

	double mas_res = mas_st + mas_bok + mas_cr + mas_dv + floor((h - 2 * tol_cr) / 40.5) * mas_pol;  //на высоту от 180 до 220 см - толщина крышек сверху и снизу деленное на толщину полок и расстояние между ними
	printf("Total weight = %lf", mas_res/1000);  //масса в кг

}
