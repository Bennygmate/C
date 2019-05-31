#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// print out a list
void showList (list listToPrint) {
	assert (listToPrint != NULL);
	node current;
	current = listToPrint->head;
		while (current != NULL) {
			printf("[%d]->",current->value);
			current = current->next;
		}
	printf("[X]\n");
}
 
// inset item at the front of the list
void frontInsert (list l, int item) {

/*	assert (l != NULL);
	node front = l->head;
*/

	assert (l != NULL);
	link front = malloc(sizeof(node)); //Creates new node
	assert (front != NULL);

	//Inserting
	link oldnode = l->head; //temp node
	front->next = oldnode; //all front values move to the temp node
	l->head = front; //the head should now be 'front'
}
 
// count the number of items in the list
int numItems (list l) {
	assert (l != NULL);
	int counter = 0;
	node current;
	current = l->head;
		while (current != NULL) {
			current = current->next;
			counter++;
		}
		return counter;
}
 
// insert at end of list
void append (list l, int value) {
	assert (l != NULL);
	link toInsert = malloc(sizeof(node));
	toInsert->next = NULL;
	link temp = NULL;
	toInsert->value = value; //stores input value

	if (l->head != NULL) {
		temp = l->head; //Head points to node if list is not empty
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = toInsert;
	} else { //If list is empty
		l->head = toInsert; //basically add to front
	}
	

	/*
	if (l->head != NULL) {
		while (temp != NULL) {
			 = current->next;
		} //Moves along until reaches null
		current->next = temp; //Temp value is added to end
		current = endNode; //Value then points to null
	} else if (l-> == NULL) {
		l->head = toInsert;
	}

	link newNode = malloc(sizeof(node));
	newNode->value = value;
	newNode->next = NULL; //Last node

	node current;
	current = l->head; // current wil be the head
	if (l != 0) {
		while (current != NULL) {
			current = current->next;
		}
		current->next = NULL;
	} else {
		frontInsert(l, value);
	}
	*/
}
 
// find the value stored at position i
// i MUST be a valid position in the list
// dont call this on positions outside the list
int lookup (list l, int position) {
	assert (l != NULL);
	assert (position >= 0);
	//temp will go through linked list
	node temp = l->head; //temp starts at the head
	int pos = 0;
	assert (position <= numItems(l)); //ensures the position given is within the list
		//while position is not position given, move along list
		while (pos != position) {
			temp = temp->next;
			assert (temp->next != NULL);
			pos++;
		}
return temp->value;
}



