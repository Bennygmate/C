/*
 *  Written by James Treloar and Benjamin Cheung
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"
#include "mechanicalTurk.h"

#define NUM_TYPES 6

int *getRes (Game g);
int canMakeSpinoff (int res[]);
int canMakeGO8 (int res[]);
int canMakeARC (int res[]);
int canMakeCampus (int res[]);

action decideAction (Game g) {

    int currentPlayer = getWhoseTurn (g);

    action nextAction;
    nextAction.actionCode = PASS;

    int res[] = getRes (g);

    int exchRate[NUM_TYPES][NUM_TYPES];
    int i = 0;
    int j = 0;
    while (i < NUM_TYPES) {
        while (j < NUM_TYPES) {
            exchRate[i][j] = getExchangeRate (g, currentPlayer, i, j);
            j++;
        }
        i++;
    }

    // Check if we can make a spinoff
    if (canMakeSpinoff (res)) {
        nextAction.actionCode = START_SPINOFF;
    } 

    exchRate[0][0]++;

    return nextAction;
}

int *getRes (Game g) {
    // Get the current resources
    int currTHD = getStudents (g, currentPlayer, STUDENT_THD);
    int currBPS = getStudents (g, currentPlayer, STUDENT_BPS);
    int currBQN = getStudents (g, currentPlayer, STUDENT_BQN);
    int currMJ = getStudents (g, currentPlayer, STUDENT_MJ);
    int currMTV = getStudents (g, currentPlayer, STUDENT_MTV);
    int currMMONEY = getStudents (g, currentPlayer, STUDENT_MMONEY);
    
    int res[] = {currTHD, currBPS, currBQN, currMJ, currMTV, currMMONEY};
    return res;
}

int canMakeSpinoff (int res[]) {
    int can = 0;
    if (res[STUDENT_MJ] == 1 && res[STUDENT_MTV] == 1 && res[STUDENT_MMONEY] == 1) {
        can = 1;
    }
    return can;
}


