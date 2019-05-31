// 20/04/2016
//This program takes in a string, and returns a pointer to that string containing that string reversed

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reverse (char *message);

int main (int argc, char* argv[] ) {

    return EXIT_SUCCESS;
}

char *reverse (char *message) {
    // Getting the length of the string
    int length = strlen(message);
    // Allocating memory to store the reversed string + 1 due to EOF
    char *reversed;
    reversed = malloc(length*sizeof(char) + 1);

    //Reversing the string, store the first char of the original string in the last position
    int pos = 0;
    while (pos < length) {
        reversed[length-pos-1] = message [pos];
        pos ++;
    }

    // Null Terminate the String
    reversed[length] = '\0';

    return reversed;
}
