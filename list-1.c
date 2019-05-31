// linked list code
// #1 the type

// first a simple type
// it;s not perfect but is ok for some uses

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define FILE_DESCRIPTION "list-1: simple list definition"

typedef struct _node *link;    // a link points ot a node

typedef struct _node {
	int value;
	link next;
} node;

typedef link list;     // a list is just represented by a link to the first node in it

// print out a list - useful function to write first for debugging help
void showList (list listToPrint);

// inset item at the front of the list -can't do this with this type definition  - hmm
void frontInsert (list l, int item);

// count the number of items in the list
int numItems (list l);

// simple unit tests on the list
void testList (void);

int main (int argc, char *argv[])  {

    testList();
    
    printf ("finished %s!\n",FILE_DESCRIPTION);
	return EXIT_SUCCESS;
}

void testList (void) {

	// create a list with one node in it
	link newNode = malloc (sizeof (node));
    assert (newNode != NULL);  
    newNode->value = 1;
    newNode->next = NULL;

    list myList = newNode;

    showList (myList);
    assert (numItems (myList) == 1);

    // create a list with two nodes in it
    newNode = malloc (sizeof (node));
    assert (newNode != NULL);  

    newNode->value = 2;
    newNode->next = NULL;

    myList->next = newNode;

    showList (myList);
    assert (numItems (myList) == 2);

    printf ("All tests passed!  You are awesome");
}

void showList (list listToPrint) {
	// start at the first node
	link current = listToPrint;
    while (current != NULL) {
    	printf ("[%d] -> ", current->value);
    	current = current->next;
    }
    printf ("X\n");
}


void frontInsert (list l, int item) {
    assert ("!Don't call me - i'm not written yet");
}


// count the number of items in the list
int numItems (list l) {
	int count = 0;
	// start at the first node
	link current = l;   // i hate this variable name - hmm need to think of a better one
    while (current != NULL) {
    	count++;
    	current = current->next;
    }
    return (count);
}

