#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
int main() {
    double r1=0, r2=0, x1=0, x2=0, y1=0, y2 = 0;
    scanf("%lf%lf%lf%lf%lf%lf", &r1, &r2, &x1, &x2, &y1, &y2);
    double xx = (x1-x2)*(x1 - x2);
    double yy = (y1-y2)*(y1 - y2);
    double rast = sqrt(xx + yy);
    if (r1 < 0 || r2 < 0) {
        printf("Eror");
    }
    if ( rast > r1 + r2) {
        printf("the circles not intersect");
    }
    else if (r1 == r2 && x1 == x2 && y1 == y2) {
        printf("The circles coincide");
    } else if (rast < r1 + r2) {
        printf("the circles intersect");
    }else if (rast == r1+r2) {
        printf("the circles touch the outside");
    }
    else if (fabs(r1 - r2) < rast < r1 + r2) {
        printf("the circles intersect at two points");
    }
    else if (rast == fabs(r1 - r2)) {
        printf("the circles touch the inside");
    } 
    else {
        printf("the circle is inside the other one");
    }

}