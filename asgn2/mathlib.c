#include <stdio.h>

#include "mathlib.h"

double arcSin(double x) {
    double n5 = x;
    n5 = n5 + x * x * x / 6;
    n5 = n5 + 3 * x * x * x * x * x / 40;
    n5 = n5 + 5 * x * x * x * x * x * x * x / 16;
    n5 = n5 + 35 * x * x * x * x * x * x * x * x * x / 1152;
    return n5;
}

double arcCos(double x) {
    return (x * 42);
}

double arcTan(double x) {
    return (x * 42);
}

double Log(double x) {
    return (x * 42);
}
