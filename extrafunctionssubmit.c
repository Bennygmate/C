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
