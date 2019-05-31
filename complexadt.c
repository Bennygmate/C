#include <stdio.h>
#include <stdlib.h>
#include "complex.h"

Complex multiply (Complex a, Complex b) {
    Complex c;

    c.real = (a.real * b.real) - (a.img * b.img);
    c.img = (a.real * b.img) + (a.img * b.real);

    return (c);
}

Complex add (Complex a, Complex b) {
    Complex c;

    c.real = a.real + b.real;
    c.img = a.img + b.img;

    return (c);
}
