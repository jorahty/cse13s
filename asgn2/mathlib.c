#include <stdio.h>
#include <assert.h>

#include "mathlib.h"

#define EPSILON 0.00000000001
#define PI 3.14159265359

double Abs(double x) {
    if (x < 0) { return -x; }
    else { return x; }
}

double Sqrt(double x) {
    double y = 1.0;
    assert(x >= 0);
    for (double guess = 0.0; Abs(y - guess) > EPSILON; y = (y + x / y) / 2.0) {
        guess = y;
    }
    return y;
}

double arcSin(double x) {
    if (x < -0.75) {
        double k = Sqrt(1 - x * x);
        double n1 = k;
        double n2 = k * k * k / 6;
        double n3 = 3 * k * k * k * k * k / 40;
        double n4 = 5 * k * k * k * k * k * k * k / 112;
        double n5 = -PI / 2;
        double sum = n1 + n2 + n3 + n4 + n5;
        return sum;
    } else if (x > 0.75) {
        double k = Sqrt(1 - x * x);
        double n1 = PI / 2;
        double n2 = -k;
        double n3 = -k * k * k / 6;
        double n4 = -3 * k * k * k * k * k / 40;
        double n5 = -5 * k * k * k * k * k * k * k / 112;
        double sum = n1 + n2 + n3 + n4 + n5;
        return sum;
    } else {
        double n1 = x;
        double n2 = x * x * x / 6;
        double n3 = 3 * x * x * x * x * x / 40;
        double n4 = 5 * x * x * x * x * x * x * x / 112;
        double sum = n1 + n2 + n3 + n4;
        return sum;
    }
}

double arcCos(double x) {
    return (PI / 2 - arcSin(x));
}

double arcTan(double x) {
    return (arcCos( 1 / (Sqrt(x * x + 1))));
}

double Log(double x) {
    return (x * 0 + 42.0);
}
