#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main() {
	float h, w, d, m;
	float dsp = 750, dvp = 400, wood = 690;
	float dsp_t = 1.5, dvp_t = 0.5, wood_t = 1;
	float pol_c = 0, r_pol = 40;
	dvp = dvp / 1000000;
	dsp = dsp / 1000000;
	wood = wood / 1000000;
	printf("Enter height (180 - 220 cm):");
	scanf("%f", &h);
	printf("Enter width (80-120 cm):");
	scanf("%f", &w);
	printf("Enter depth (50-90 cm):");
	scanf("%f", &d);
	if ((h < 180) || (h > 220)) {
		printf("Entered incorrectly");
	}
	else if ((w < 80) || (w > 120)) {
		printf("Entered incorrectly");
	}
	else if ((d < 50) || (d > 90)) {
		printf("Entered incorrectly");
	}
	else {
		while ((r_pol + 1.5) <= h)
		{
			pol_c = pol_c + 1;
			r_pol = r_pol + 41.5;
		}
		m = (h * w * dvp_t * dvp) + (2 * h * d * dsp * dsp_t) + (2 * h * w * wood * wood_t) + (2 * d * w * dsp * dsp_t) + (pol_c * w * d * dsp * dsp_t);
		printf("Weight: %.3f kg", m);
	}
}