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
int sumEveryN (list A, int value);
int nodeFromEnd (list A, int value);
list newReverseList (list sourceList);
int orderList (list sourceList);
void deleteEveryNNode (list A, int value);
void zipList (list A, list B, list zip);
void intersection (list A, list B, list C);
void subLink (list A, list B, list C);
void isPalindrome (list A);

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
    append (firstList, 5);
    append (firstList, 6);
    printf ("List A\n");
    showList (firstList);

    // Create second list opposite
    link secNode = malloc (sizeof (node));
    assert (secNode != NULL);
    secNode->value = 5;
    secNode->next = NULL;
    list secondList = malloc (sizeof (list));
    secondList->head = secNode;

    secNode = malloc (sizeof (node));
    assert (secNode != NULL);
    secNode->value = 4;
    secNode->next = NULL;
    secondList->head->next = secNode;
    
    //Insert
    frontInsert (secondList, 6);
    append (secondList, 3);
    append (secondList, 2);
    append (secondList, 1);
    printf ("List B\n");
    showList (secondList);

    link thirdNode = malloc (sizeof (node));
    thirdNode->value = 3;
    thirdNode->next = NULL;
    list thirdList = malloc (sizeof (list));
    thirdList->head = thirdNode;
    frontInsert (thirdList, 2);
    append (thirdList, 1);
    printf ("List C\n");
    showList (thirdList);

    sumEveryN (firstList, 2);
    nodeFromEnd (firstList, 5);
//    printf ("Testing reversing list A\n");
//    newReverseList (firstList);
//    printf ("Testing list A, list B, then list C\n");
//    orderList (firstList);
//    orderList (secondList);
//    orderList (thirdList);
    showList (firstList);
    deleteEveryNNode (firstList, 2);
    showList (firstList);

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

int sumEveryN (list A, int value) {
    link current = A->head;
    link firstValue = NULL;
    int nodeValue = value;
    int secValue = value;
    int sumNumber = 0;
        if (nodeValue == 0) {
            return (-1);
        } else {
            while (current->next != NULL) {
                if (firstValue == NULL) {
                    nodeValue--;
                    firstValue = current;
                    while (nodeValue > 0) {
                        nodeValue--;
                        current = current->next;
                    }
                sumNumber = sumNumber + current->value;
                } else {                
                    while (secValue > 0) {
                        secValue--;
                        current = current->next;
                    }
                    sumNumber = sumNumber + current->value;
                    secValue = value;
                }
            }
            printf ("The sum of every %d nodes is %d\n", value, sumNumber);
        return (sumNumber);
        }           
} 

int nodeFromEnd (list A, int value) {
    link previous = A->head;
    int numberCount = 0;
        while (previous != NULL) {
            numberCount++;
            previous = previous->next;
        }
    int fromLast = numberCount - value;
    link current = A->head;
    int nodeStore = 0;
        while (current->next != NULL) {
            value--;
            if (value == 0) {
                nodeStore = current->value;
            }
            current = current->next;
        }
    printf ("The %d'th node of the end of list is %d\n", fromLast, nodeStore); 
    return (nodeStore);
}

list newReverseList (list sourceList) {
    list newReverseList = malloc (sizeof (list));
    link previous = NULL;
    link current = sourceList->head;
    link after = sourceList->head->next;
        while (current->next != NULL) { 
            after = current->next;
            current->next = previous;
            previous = current;
            current = after; 
        } 
    current->next = previous;
    newReverseList->head = current;
    showList (newReverseList);
    return (newReverseList); 
}

int orderList (list sourceList) {
    link count = sourceList->head;
    int counter = 0;
    int counterTwo = 0;
        while (count->next != NULL) {
            counter++;
            counterTwo++;
            count = count->next;
        }
    link current = sourceList->head;
    link after = sourceList->head->next;
        while (after->next != NULL && after != NULL) {
                if (after->value > current->value) {
                    counter--;
                }  
                if (after->value < current->value) {
                    counterTwo--;
                }
            after = after->next;
            current = current->next;
        }

    if (counter == 0) {
        printf ("The list is ascending\n");
        return (1);
    } else if (counterTwo == 1) {
        printf ("The list is descending\n");
        return (0);
    } else {
        printf ("The list is neither\n");
        return (-1);
    }               
} 

void deleteEveryNNode (list A, int value) {
    link current = A->head;
    link firstValue = NULL;
    int nodeValue = value;
    int secValue = value;
        if (nodeValue == 0) {

        } else {
            while (current->next != NULL) {
                if (firstValue == NULL) {
                    nodeValue--;
                    current->next = current->next->next;
                    firstValue = current;
                    while (nodeValue > 0) {
                        nodeValue--;
                        current = current->next;
                    }
                } else {                
                    while (secValue > 0) {
                        secValue--;
                        current->next = current->next->next;
                    }
                    secValue = value;
                    current = current->next;
                }
            }
            A->head = firstValue;
            printf ("Deleting every %d nodes\n", value);
        }           
} 

void zipList (list A, list B, list zip) {
// Code 
} 

void intersection (list A, list B, list C) {
// Code 
}

void subLink (list A, list B, list C) {
// Code 
}

void isPalindrome (list A) {
// Code 
}
