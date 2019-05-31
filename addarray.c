

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_ELEMENTS 5

double calculate (int array[], int numElements);

int main (int argc, char * argv[]){
    int n = NUM_ELEMENTS;
    int array[5] = {1, 2, 3, 4, 5};
    calculate (array, n);

    return EXIT_SUCCESS;
}

double calculate (int array[], int numElements) {
    int counter = 0;
    double add = 0;
    double mean;

    while (counter < numElements) {
        add += array[counter];
        counter++;
    }
    add += array[counter];
    printf ("%lf and %d\n", add, counter);
    mean = add / counter;
    return (mean);
}
            
