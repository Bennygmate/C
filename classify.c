/*
=== Question 17 ===

(7 Marks)

Write a function which implements the prototype
{{{
void classify (int array[], int n);
}}}
which inspects an array of n elements to find which one of the following
cases is true and prints a single letter identifying the case.

a. array contains no zeros.

b. array contains only one zero.

c. the first two zeros in the array are separated by an even number of
non-zeros.

d. the first two zeros in the array are separated by an odd number of
non-zeros.

The function should either print "a", "b", "c", or "d".

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void classify (int array[], int n);

int main (int argc, char * argv[]){
    int n = 5;
    int array[n] = {1, 0, 2, 2, 0};

    classify (array, n);

    return EXIT_SUCCESS;
}

void classify (int array[], int n) {
    int counter = 0;
    int zeroCounter = 0;
    int firstZero = 0;
    int secondZero = 0;

    while (counter < n) {
        if (array[counter] == 0) {
            zeroCounter++;
            if (firstZero == 0) {
                firstZero = counter;
            } else if (secondZero == 0) {
                secondZero = counter;
            }
        }
    counter++;
    }

    firstZero = secondZero - firstZero;
    if (zeroCounter == 0) {
        printf ("a. Array contains no zeros\n");
    } else if (zeroCounter == 1) {
        printf ("b. Array contains one zero\n");
    } else if (firstZero % 2 == 0) {
        printf ("d. The first two zeros are separated by an odd number of non-zeros\n");
    } else if (firstZero %2 != 0) {
        printf ("c. The first two zeros are separated by an even number of non-zeros\n");
    }
}
            
