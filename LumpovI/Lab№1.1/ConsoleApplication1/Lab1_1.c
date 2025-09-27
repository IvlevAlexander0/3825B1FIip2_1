#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

const int DSPdensity = 680;
const int DVPdensity = 820;
const int WOODdensity = 740;

const double DVPthickness = 0.005;
const double DSPthickness = 0.015;
const double WOODthickness = 0.001;
const double SHELFthickness = 0.005;

const double maxHeight = 2.2;
const double minHeight = 1.8;
const double maxDepth = 0.9;
const double minDepth = 0.5;
const double maxWidth = 1.2;
const double minWidth = 0.8;


int correctValue(double value, double min, double max) {
    int flag = 0;
    if (value < min || value > max) {
        printf("Inccorect input!!!");
        flag = 1;
        return flag;
    }
    return flag;
}


int main() {
    double h, d, w;
    double mass = 0;

    printf("Enter the height(in metres): ");
    scanf("%lf", &h);
    if (correctValue(h, minHeight, maxHeight) == 1){
        return 1;
    }
    printf("Enter the depth(in metres): ");
    scanf("%lf", &d);
    if (correctValue(d, minDepth, maxDepth)) {
        return 1;
    }
    printf("Enter the width(in metres): ");
    scanf("%lf", &w);
    if (correctValue(w, minWidth, maxWidth)) {
        return 1;
    }

    double sidewallsMass = (h * d * DSPthickness * DSPdensity) * 2;
    double backMass = h * DVPthickness * w * DVPdensity;
    double doorsMass = h * WOODthickness * w * WOODdensity;
    double topLowerMass = (DSPthickness * d * w * DSPdensity) * 2;
    int shelfCount = (h / 0.4) - 1;
    double shelfMass = (d * SHELFthickness * w * DSPdensity) * shelfCount;

    mass += sidewallsMass;
    mass += backMass;
    mass += shelfMass;
    mass += doorsMass;
    mass += topLowerMass;
    printf("Total weight(kg): %.3lf", mass);
}