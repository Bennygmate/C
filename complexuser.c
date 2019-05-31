#include <stdio.h>
#include <stdlib.h>
#include "complex.h"

Complex multiply (Complex a, Complex b);
Complex add (Complex a, Complex b);

int main (int argc, char *argv[]) {
    Complex a, b, c;
    a.real = 0.5;
    a.img = 0.5;
    b.real = 0.5;
    b.img = 0.5;
    c.real = 0.1;
    c.img = 0.9;
    Complex d = multiply (a, b);
    Complex e = add (d, c);

    if (e.img >= 0 ){
      printf("Sum of two complex numbers = %lf + %lfi\n", e.real, e.img);
    } else {
      printf("Sum of two complex numbers = %lf %lfi\n", e.real, e.img); 
    }

    return EXIT_SUCCESS;
}
