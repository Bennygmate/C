// selectEven.c
// 
     
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
     
#include "list-selectEven.h"
     
// given a list of integers, write a function which 
// finds all even integers and constructs
// a new list containing these even integers 
// The original list should remain unmodified.
// The new list should be returned by the function.
// So if the original list is 1->55->66->4->X, the function
// should return a list 66->4->X. 
// And if the original list is 1->3->7->X, the function
// should return an empty list.
//
// Constraints:
// don't delete any nodes (i.e. do not call free())
// the order of integers in the new list should be the same as the original
// the original list should remain unmodified
//
// A function to determine the length of a list called numItems() 
// is provided. Feel free to use it but do not modify the function.
     
     
list selectEven (list sourceList) {
    list evenList = malloc (sizeof (list));
    if (sourceList->head == NULL) {
        // Do nothing Empty
        return (sourceList);
    } else if (sourceList->head->next == NULL) {
        // One noded 
        if (sourceList->head->value % 2 == 0) {
            return (sourceList);
        } else {
            link current = sourceList->head;
            current->next = current->next;
            evenList->head = NULL;
            return (evenList);
        }
    } else { 
        link evenHead = NULL;
        link current = sourceList->head;
        link previous = sourceList->head;
            while (current != NULL) {
            previous = current;
                if (previous->value % 2 == 0) {
                    if (evenHead == NULL) { //First node 
                        evenList->head = previous;
                        evenHead = previous;
                    }
                } else { // Delete/go over the odds
                    if (evenHead != NULL) {
                    previous->next = previous->next->next;
                    }
                }
            current = current->next;
            }

        // There could be no evens at all 
            if (evenHead == NULL) {
                evenList->head = NULL;
            }
        return (evenList);
    }
}
