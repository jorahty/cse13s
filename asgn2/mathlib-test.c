#include <stdio.h>
#include <getopt.h>
#include <math.h>

#define OPTIONS "sctea"
#define PI 3.14159265359
#define STEP 0.196349540849
#define EPSILON 0.00000000001

int Sin() {
  
  // Print column titles
  printf("x        Sin             Library         Difference\n");
  printf("-        ---             -------         ----------\n");
  
  // Print rows
  for (double x = -2 * PI; x < 6.3; x = x + STEP) {

    // Plug x into forumula
    double sq = x * x;
    double numer = (sq * (52785432 - 479249 * sq) - 1640635920);
    numer = x * (numer * sq + 11511339840);
    double denom = ((18361 * sq + 3177720) * sq + 277920720) * sq + 11511339840;
    double sinx = numer / denom;

    // Get library value
    double lib = sin(x);

    // Compute difference
    double diff = sinx - lib;
    
    // Print row
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, sinx, lib, diff);

  }

  return 0;
}

int Cos() {

  // Print column titles
  printf("x        Cos             Library         Difference\n");
  printf("-        ---             -------         ----------\n");

  // Print rows
  for (double x = -2 * PI; x < 6.3; x = x + STEP) {

    // Plug x into forumula
    double sq = x * x;
    double numer = (sq * (1075032 - 14615 * sq) - 18471600);
    numer = numer * sq + 39251520;
    double denom = ((127 * sq + 16632) * sq + 1154160) * sq + 39251520;
    double cosx = numer / denom;

    // Get library value
    double lib = cos(x);

    // Compute difference
    double diff = cosx - lib;

    // Print row
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, cosx, lib, diff);

  }

  return 0;
}

int Tan() {

  // Print column titles
  printf("x        Tan             Library         Difference\n");
  printf("-        ---             -------         ----------\n");

  // Print rows
  for (double x = PI / -3; x < 1; x = x + STEP) {

    // Plug x into forumula
    double sq = x * x;
    double numer;
    numer = x * (sq * (sq * (sq * (sq - 990) + 135135) - 4729725) + 34459425);
    double denom;
    denom = 45 * (sq * (sq * (sq * (sq - 308) + 21021) - 360360) + 765765);
    double tanx = numer / denom;

    // Get library value
    double lib = tan(x);

    // Compute difference
    double diff = tanx - lib;

    // Print row
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, tanx, lib, diff);

  }

  return 0;
}

int Exp() {
  
  printf("x        Exp             Library         Difference\n");
  printf("-        ---             -------         ----------\n");

  double x = 0;
  while (x <= 9) {

    // Get library value
    double lib = exp(x);

    double prev = 1.0;
    double sum = 1.0;
    int n = 0;
    while (lib - sum > EPSILON) {
      n++;
      prev = prev * x / n;
      sum = sum + prev;
    }

    // Compute difference
    double diff = lib - sum;

    // Print row
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, sum, lib, diff);

    x = x + 0.1;
  }

  return 0;
}

int main(int argc, char **argv) {
  
  // Get the first 2 options
  int firstopt = getopt(argc, argv, OPTIONS);
  int secondopt = getopt(argc, argv, OPTIONS);
  
  // Check for no options
  if (firstopt == -1) {
    printf("Error: No options!\n");
  
  // Check for mutiple options
  } else if (secondopt != -1) {
    printf("Error: Multiple options!\n");
    
  // Run the the appropriate test
  } else if (firstopt == 's') {
    Sin();
  } else if (firstopt == 'c') {
    Cos();
  } else if (firstopt == 't') {
    Tan();
  } else if (firstopt == 'e') {
    Exp();
  } else if (firstopt == 'a') {
    Sin();
    Cos();
    Tan();
    Exp();
  }
  
  return 0;
}
