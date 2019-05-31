#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    int x;
    printf ("Please enter a number\n");
    scanf ("%d", &x);
    int powerOfTwo = 1;
    while (powerOfTwo < x && powerOfTwo < 1073741824) {
        powerOfTwo = powerOfTwo * 2;
    } 
    printf ("%d\n", powerOfTwo);

    return EXIT_SUCCESS;
}
    
