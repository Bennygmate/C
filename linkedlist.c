// By Benjamin Cheung, z3460693
// Tue-Sitar, Andrew Shellshear
// 26/05/2016
// Linked lists 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list3.h"

void showList (list listToPrint);
static void testList (void); 
void frontInsert (list l, int item);
void append (list l, int value);
int numItems (list l);
int lookup (list l, int position);
void deleteHead (list l);
void deleteLast (list l);
void concatenate (list to, list from);
int count42s (list l);
list reverse (list inputList);
list frontToBack (list list);
void orderedDelete (list l);
void frontBackSplit (list sourceList, list frontList, list backList);
void pairwiseSwap (list l);
void deleteNumber (list sourceList);
void zigZag (list listA, list listB, list zipList);

int main (int argc, char*argv[]) {

    testList ();
    printf("All Tests Passed!\n");

    return EXIT_SUCCESS;
}

static void testList (void) {
    //Create first list
    link ptrNode = malloc (sizeof (node));
    assert (ptrNode != NULL);
    ptrNode->value = 2;
    ptrNode->next = NULL;
    //Create List
    list firstList = malloc (sizeof (list)); 
    firstList->head = ptrNode;
    //Create second node
    ptrNode = malloc (sizeof (node)); 
    assert (ptrNode != NULL);
    ptrNode->value = 3;
    ptrNode->next = NULL;
    //Add to list
    firstList->head->next = ptrNode;
    //front + back insert 
    frontInsert (firstList, 1);
    append (firstList, 4);
    showList (firstList);

    // Create second list 43
    link secNode = malloc (sizeof (node));
    assert (secNode != NULL);
    secNode->value = 6;
    secNode->next = NULL;
    list secondList = malloc (sizeof (list));
    secondList->head = secNode;

    secNode = malloc (sizeof (node));
    assert (secNode != NULL);
    secNode->value = 7;
    secNode->next = NULL;
    secondList->head->next = secNode;
    
    //Insert
    frontInsert (secondList, 5);
    append (secondList, 8);
    showList (secondList);

    //Concatenate
    concatenate (firstList, secondList);
    printf ("Combining Above Two Lists\n");
    showList (firstList);
/*
    count42s (firstList);

    // Reverse 
    reverse (firstList);
    printf ("Reversing the list\n");
    showList (firstList);

    //Front To back
    frontToBack (firstList);
    printf ("Sending first node to last node\n");
    showList (firstList);

    // Ordered Delete
    printf ("Delete if the after is more than the previous undeleted function\n");
    orderedDelete (firstList);
    showList (firstList);
*/    
    // Need two empty lists to test
    list emptyList = malloc (sizeof (list));
    emptyList->head = NULL;
    list emptyListTwo = malloc (sizeof (list));
    emptyListTwo->head = NULL;
    
    //Test frontBackSplits
    printf ("Splitting the list\n");
    frontBackSplit (firstList, emptyList, emptyListTwo);
    showList (emptyList);
    showList (emptyListTwo);


/*    //Test pairwise
    printf ("Testing pairwise\n");
    pairwiseSwap (emptyListTwo);
    showList (emptyListTwo);
*/
    link thirdNode = malloc (sizeof (node));
    thirdNode->value = 10;
    thirdNode->next = NULL;
    list thirdList = malloc (sizeof (list));
    thirdList->head = thirdNode;
    showList (thirdList);
    // Test deleteLast
    printf ("Testing deleteNumber\n");
    deleteNumber (thirdList);
    showList (thirdLIst;
/*
    // Test zigzag
    printf ("Testing ZigZag\n");
    list emptyListThree = malloc (sizeof (list));
    emptyListThree->head = NULL;
    zigZag (emptyList, emptyListTwo, emptyListThree);
    showList (emptyListThree); 
*/
}

void showList (list listToPrint) { 
    //Start at first node 
    link current = listToPrint->head; 
    while (current != NULL) {
        printf ("[%d] -> ", current->value);
        current = current->next;
    }
    printf ("[X]\n");
}

int numItems (list l) {
    int count = 0;
    link current = l->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return (count);
}

void frontInsert (list l, int item) {
    link newNode = malloc (sizeof (node));
    assert (newNode != NULL);
    newNode->value = item;

    link oldHead = l->head;
    newNode->next = oldHead;
    l->head = newNode;
}

void append (list l, int value) {
    assert (l != NULL);
    link backNode = malloc (sizeof (list));
    assert (backNode != NULL);
    backNode->value = value;
    backNode->next = NULL;

    if (l->head == NULL) {
        l->head = backNode;
    } else {
        link current = l->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = backNode;
    }
}

int lookup (list l, int position) {
    link current = l->head;
    int positionCount = 0;
    while (positionCount != position) {
        positionCount++;
        assert (current->next != NULL);
        current = current->next;
    }
    printf ("The value in position %d is %d\n", position, current->value);
    return (current->value);
}

void deleteHead (list l) {
    link oldHead = l->head;
    link newHead = l->head->next;
    free (oldHead);
    l->head = newHead;
}

void deleteLast (list l) {
    link prePointer = l->head;
    link lastPointer = l->head;
    while (lastPointer->next != NULL) {
        prePointer = lastPointer;
        lastPointer = lastPointer->next;
    }
    free (lastPointer);
    prePointer->next = NULL;
}

void concatenate (list to, list from) {
    //First find the last pointer of the first list 
    link current = to->head;
    while (current->next != NULL) {
        current = current->next;
    }
    // Point last pointer to second list 
    current->next = from->head;   
}

int count42s (list l) {
    link current = l->head;
    int numberCount = 0;
    while (current != NULL) {
        if (current->value == 42) {
        numberCount++;
        }
    current = current->next;
    }
    printf ("Number of 42's is %d\n", numberCount);
    return (numberCount);
}

list reverse (list inputList) {
    link current = inputList->head;
    link previous = NULL;
    link after = inputList->head->next;

    while (current->next != NULL) {
        after = current->next; //Always after current 
        current->next = previous; //Now the current points to the end
        previous = current; //The previous is the start 
        current = after; // current is moved forward one to keep it looped
    }
    current->next = previous; // current points to the start of list
    inputList->head = current; // list is now made pointing to current
    return inputList;
} 

list frontToBack (list list) {        
    link current = list->head;
    link oldHead = list->head;
    link newHead = list->head->next;
    //Find Last Pointer
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = oldHead;
    oldHead->next = NULL;
    list->head = newHead; 
    return list;
}

void orderedDelete (list l) {
    if (l->head == NULL) {
    //PENIS
    } else if (l->head->next == NULL) {    
    //PENIS 2
    } else {
    link previous = l->head;
    link current = l->head;
    link after = l->head;
    //Count up to NULL
    while (after != NULL) {
        previous = current;
        current = current->next;
        after = current->next;
        if (current->value < previous->value) {
            previous->next = after;
            current = previous;
        }
    }
    }
}

void frontBackSplit (list sourceList, list frontList, list backList) {
	link currentNode = sourceList->head;
	int lengthList = numItems(sourceList) ;
	//If list is empty
	if(sourceList->head == NULL) {
		backList = sourceList;
		frontList = sourceList;
	}
	//If the list is even
	else if(lengthList%2 == 0) {
		int middle = lengthList/2;
		int counter = 1;
		//finds the number of items in the list
		frontList->head = currentNode;
		while (counter < middle) {
			//Start of new list is first half
			currentNode = currentNode->next; 
			counter++;
		}
		backList->head = currentNode->next; //head of the 2nd half
                currentNode->next = NULL;
                sourceList->head = NULL;
	}
	//If the list is odd
	else if(lengthList%2 != 0) {
		int middle = (lengthList+1)/2;
		int counter = 1;
		//finds the number of items in the list
		frontList->head = currentNode;
		while (counter != middle) {
			//Start of new list is first half
			currentNode = currentNode->next; 
			counter++;
		}
		backList->head = currentNode->next; //head of the 2nd half
                currentNode->next = NULL;
                sourceList->head = NULL;
	}
}

void pairwiseSwap (list l) {
    link current = l->head;
    link after = l->head;
    link previous = NULL;

    if (l->head == NULL) {
    // Empty do nothing 
    } else if (l->head->next == NULL) {
    // One node do nothing 
    } else { 
        while (current != NULL && current->next != NULL) {
            after = current->next;
            current->next = after->next;
            after->next = current;
            if (previous == NULL) { 
                l->head = after;
            } else {
                previous->next = after;
            }
            previous = current;
            current = current->next;
        }
    }
}
/* The tests state that we have to move everything smaller than the
   first node to the front, while keeping the order. 
   Eg. [10]->[16]->[9]->[7]->[4]->[22] becomes
       [9]->[7]->[4]->[10]->[16]->[22]

   2nd option - easier way, logically
   1) traverse through the list
   2) check each number to see if it's smaller than 10.
   3) join them together into a mini/sub-list
   4) join the 2 lists together by putting the sub-list first

   My solution for the 2nd option:
*/

void deleteNumber (list sourceList) {
    if (sourceList->head == NULL) {
        // Empty list 
    } else if (sourceList->head == NULL) {
        // Test one node
    } else { // Two list and beyond
        // We want to delete small from the original list
        // Join Small List to original list
        // Small list will be the head
        // First store first element   
        int firstElement = sourceList->head->value;
        // Then traverse the list, deleting smaller nodes
        link current = sourceList->head; 
        link previous = sourceList->head;
        link origHolder = NULL;
        link smallHolder = NULL;
        // Get ready to make the smalllist
        link smallList = NULL;
            while (current != NULL) {
                if (current->value < firstElement) {
                    if (smallList == NULL) {
                        smallList = current;
                        smallHolder = smallList;
                    } else {
                        smallList->next = current;
                        smallList = smallList->next;
                    }
                } else {
                    if (origHolder == NULL) {
                        origHolder = previous;
                        sourceList->head = previous;
                    } else {                
                        previous->next = current;
                        previous = previous->next;
                    }
                }
            current = current->next;
            }
        // Make sure previous list is null terminated at end
        previous->next = NULL;
        // Now just simply link the smalllist to the original holder
        smallList->next = sourceList->head;
        sourceList->head = smallHolder;
    }
}

// List A first, then B, zipList is empty
void zigZag (list listA, list listB, list zipList) {
    link currentA = listA->head;
    link currentB = listB->head;
    link currentZip = listA->head;
    // Start at listA
    zipList->head = currentZip; 
    currentA = currentA->next;
        while (currentZip->next != NULL) {
            if (currentB != NULL) {
                currentZip->next = currentB;
                currentB = currentB->next;
                currentZip = currentZip->next;
                if (currentA != NULL) {
                    currentZip->next = currentA;
                    currentA = currentA->next;
                    currentZip = currentZip->next;
                }
            } 
            if (currentZip->next == NULL) {
                if (currentA != NULL) {
                    currentZip->next = currentA;
                    currentA = currentA->next;
                    currentZip = currentZip->next;
                }
                if (currentB != NULL) {
                currentZip->next = currentB;
                currentB = currentB->next;
                currentZip = currentZip->next;
                }
            }
            
        }
}















