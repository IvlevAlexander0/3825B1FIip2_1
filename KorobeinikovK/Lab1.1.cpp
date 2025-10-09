#include <cstdio>
#include <locale.h>

void main() {
	setlocale(LC_ALL, "rus");
	float h, w, d, m;
	float dsp = 750, dvp = 400, wood = 690;
	float dsp_t = 1.5, dvp_t = 0.5, wood_t = 1;
	float pol_c = 0, r_pol = 40;
	dvp = dvp / 1000000;//мягкая плита в кг/см^3
	dsp = dsp / 1000000;//средней плотности в кг/см^3
	wood = wood / 1000000;//средняя плотность дуба в кг/см^3
	printf("Введите высоту задней стенки (от 180 до 220 см):");
	scanf_s("%f", &h);
	printf("Введите ширину задней стенки (от 80 до 120 см):");
	scanf_s("%f", &w);
	printf("Введите глубину шкафа (от 50 до 90 см):");
	scanf_s("%f", &d);
	if ((h < 180) || (h > 220)) {
		printf("Некорректно введена высота шкафа ");
	}
	else if ((w < 80) || (w > 120)) {
		printf("Некорректно введена ширина шкафа ");
	}
	else if ((d < 50) || (d > 90)) {
		printf("Некорректно введена глубина шкафа ");
	}
	else {
		while ((r_pol + 1.5) <= h)
		{
			pol_c = pol_c + 1;
			r_pol = r_pol + 41.5;
		}
		m = (h * w * dvp_t * dvp) + (2 * h * d * dsp * dsp_t) + (2 * h * w * wood * wood_t) + (2 * d * w * dsp * dsp_t) + (pol_c * w * d * dsp * dsp_t);
		printf("Maccа шкафа: %.3f кг", m);
	}
}