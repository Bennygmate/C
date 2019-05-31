// cross.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "cross.h"

// you can assume size is an odd positive value
// this function is to print on the screen a cross 
// made of asterisks which fits inside a square of
// side length "size"

/* 
compile and test your code as follows

$ gcc -Wall -Werror -std=c99 -O -o partP1 cross.c testCross.c

examples

$ ./partP1 3
* *
 *
* *

$ ./partP1 5
*   *
 * *
  *
 * *
*   *

$ ./partP1 7
*     *
 *   *
  * *
   *
  * *
 *   *
*     *

$ ./partP1 1
*

submit with this command
$ submit partP1 cross.c
*/

void drawCross (int size) {
    int position = 1;
    int leftDiagonal = 1;
    int rightDiagonal = size;
    int middlePosition = ((size * size) + 1) / 2;
    while (position < ((size * size) + 1)) {
        if (position == middlePosition) {
            printf ("*");
            leftDiagonal += size + 1; 
            rightDiagonal += size - 1;
        } else if (position == leftDiagonal) {
            printf ("*");
            leftDiagonal += size + 1;    
        } else if (position == rightDiagonal) {
            printf ("*");
            rightDiagonal += size - 1;
        } else {
            printf (" ");
        }
        
        if (position % size == 0) {
            printf ("\n");
        }

    position++;
    }

}



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



