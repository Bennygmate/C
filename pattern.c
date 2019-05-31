// pattern.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pattern.h"

// you can assume size is a positive value between 1 and 26 (inclusive)
// this function is to print on the screen a pattern of upper case 
// characters with an empty diamond shape in the center.
// The number of unique characters to be used is equal to "size" and 
// always start from 'A'. The pattern fits inside a square of side
// length "2*size". 
// NOTE: It is hard to describe the pattern in words but the examples 
// below should clarify what is expected.

// match the output shown below

/* 
compile and test your code as follows

$ gcc -O -o partP1 -Wall -Werror -std=c99  pattern.c testPattern.c

examples and how to run it:

$ ./partP1 5
ABCDEEDCBA
ABCD  DCBA
ABC    CBA
AB      BA
A        A
A        A
AB      BA
ABC    CBA
ABCD  DCBA
ABCDEEDCBA

$ ./partP1 8
ABCDEFGHHGFEDCBA
ABCDEFG  GFEDCBA
ABCDEF    FEDCBA
ABCDE      EDCBA
ABCD        DCBA
ABC          CBA
AB            BA
A              A
A              A
AB            BA
ABC          CBA
ABCD        DCBA
ABCDE      EDCBA
ABCDEF    FEDCBA
ABCDEFG  GFEDCBA
ABCDEFGHHGFEDCBA

$ ./partP1 11
ABCDEFGHIJKKJIHGFEDCBA
ABCDEFGHIJ  JIHGFEDCBA
ABCDEFGHI    IHGFEDCBA
ABCDEFGH      HGFEDCBA
ABCDEFG        GFEDCBA
ABCDEF          FEDCBA
ABCDE            EDCBA
ABCD              DCBA
ABC                CBA
AB                  BA
A                    A
A                    A
AB                  BA
ABC                CBA
ABCD              DCBA
ABCDE            EDCBA
ABCDEF          FEDCBA
ABCDEFG        GFEDCBA
ABCDEFGH      HGFEDCBA
ABCDEFGHI    IHGFEDCBA
ABCDEFGHIJ  JIHGFEDCBA
ABCDEFGHIJKKJIHGFEDCBA

$ ./partP1 1
AA
AA

$ ./partP1 2
ABBA
A  A
A  A
ABBA

$ ./partP1 3
ABCCBA
AB  BA
A    A
A    A
AB  BA
ABCCBA

submit with this command
$ submit partP1 pattern.c
*/


void printPattern (int size) {
    int position = 1; 
    char alphabet = 'A';

    int rowPrinterOne = size;
    int rowPrinterTwo = size + 1;
    int endRow = (size * 2);
    while (position < ((size * 2) * (size * 2)) + 1) {
        if (position <= rowPrinterOne) {
            printf ("%c", alphabet);
            alphabet++;
        } else if (position >= rowPrinterTwo && position <= endRow) {
            alphabet--;
            printf ("%c", alphabet);
        } else {
            printf (" ");
        }
        
        if (position == endRow) {
            printf ("\n");
            if (position < (size * size) * 2) {
                rowPrinterOne = rowPrinterOne + ((size * 2) - 1);
                rowPrinterTwo = rowPrinterTwo + ((size * 2) + 1);
                endRow = endRow + (size * 2);
            } else if (position == (size * size) * 2) {
                rowPrinterOne = rowPrinterOne + (size * 2);
                rowPrinterTwo = rowPrinterTwo + (size * 2);
                endRow = endRow + (size * 2);
            } else {
                rowPrinterOne = rowPrinterOne + ((size * 2) + 1);
                rowPrinterTwo = rowPrinterTwo + ((size * 2) - 1);
                endRow = endRow + (size * 2);
            }
        }
    position++;
    }

}





