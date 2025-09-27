#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

void main() {
	printf("input height, width and deepth (in santimeters)");
	double h, w, d;
	scanf("%lf%lf%lf", &h, &w, &d);
	if ((h > 220) || (h < 180) || (w < 80) || (w > 120) || (d < 50) || (d > 90)) {
		printf("Error: one of the imputed variables does not lie within the set range ");
	}
	else {
		double ρDVP = 1000, ρDSP = 900, ρDr = 1300;
		double m = ((h * w * 0.5 * ρDVP) + 2 * (d * h * ρDSP * 1.5) + 2 * (w * d * 1.5 * ρDSP) + 2 * (h * w) + (0.5 * ρDSP * ((h)/40)));
		printf("m = ");
		printf("%lf", m / 100);
	}
}