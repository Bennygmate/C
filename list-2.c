// linked list code
// #2 improve the type with indirection
// so we can modify which node is the first in the list

// secondly a better type


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define FILE_DESCRIPTION "list-2: list definition using indirection"

typedef struct _node *link;    // a link points to a node

typedef struct _node {
	int value;
	link next;
} node;

// a list is just represented by a pointer to a link to the first node in it
typedef link *list;     

// now lets modify the definition and refactor the existing functions
// first check that the modifications work before addding new functions

// print out a list - useful function to write first for debugging help
void showList (list listToPrint);

void frontInsert (list l, int item);

// count the number of items in the list
int numItems (list l);

// simple unit tests on the list
void testList (void);

// new function free up memory allocated for the list
void disploseList (list l);


int main (int argc, char *argv[])  {

    testList();
    
    printf ("finished %s!\n",FILE_DESCRIPTION);
	return EXIT_SUCCESS;
}

void testList (void) {

	// create a list with one node in it
	link ptrHeadOfList = malloc (sizeof (node));
    assert (ptrHeadOfList != NULL);  
    ptrHeadOfList->value = 1;
    ptrHeadOfList->next = NULL;

    //myList points to the link which points to the first node 
    // of the list aka the head
    list myList = &ptrHeadOfList;


    showList (myList);
    assert (numItems (myList) == 1);

    // create a list with two nodes in it
    link ptrToNewNode = malloc (sizeof (node));
    assert (ptrToNewNode != NULL);  

    ptrToNewNode->value = 2;
    ptrToNewNode->next = NULL;

    link head = *myList;
    head->next = ptrToNewNode;

    showList (myList);
    assert (numItems (myList) == 2);

    //insert a node containing 0 at the head i.e. before 1->2->X list
    // to produce 0->1->2->X
    
    frontInsert (myList, 0);
    showList (myList);
    assert (numItems (myList) == 3);


    printf ("All tests passed!  You are awesome\n");
}

void showList (list listToPrint) {
	// start at the first node
	link current = *listToPrint;
    while (current != NULL) {
    	printf ("[%d] -> ", current->value);
    	current = current->next;
    }
    printf ("X\n");
}


void frontInsert (list l, int item) {
    assert ( l != NULL);
    link ptrToNewNode = malloc(sizeof(node));
    assert ( ptrToNewNode != NULL);
    ptrToNewNode->value = item;

    link ptrToHead = *l;
    ptrToNewNode->next = ptrToHead; 
    *l = ptrToNewNode;
}


// count the number of items in the list
int numItems (list l) {
	int count = 0;
	// start at the first node
	link current = *l;   
    while (current != NULL) {
    	count++;
    	current = current->next;
    }
    return (count);
}
//free memory one node at a time
void disposeList (list l){
    
    // start at the first node
    link current = *l;
    link temp;   
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    l = NULL;
}

