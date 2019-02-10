#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "dfa.h"
#include "LinkedList.h"


typedef struct DFA{
    int numStates;
    int **transitionTable;
    LinkedList acceptingStates;
}*DFA;

/**
 * Allocate and return a new DFA containing the given number of states.
 */

DFA new_DFA(int nStates) {
    DFA dfa;
    dfa = (DFA)malloc(sizeof(DFA));
    if (dfa == NULL) {
        return NULL; // Out of memory...
    }
    dfa->numStates = nStates;
    dfa->acceptingStates = new_LinkedList();
    //to allocate transition table
    int** matrix = dfa->transitionTable;
    int *pointer;
    int length = 0;
    length = sizeof(int *) * nStates + sizeof(int) * 128 * nStates;
    matrix = (int **)malloc(length);
    // ptr is now pointing to the first element in of 2D array
    pointer = matrix + nStates;
    // for loop to point rows pointer to appropriate location in 2D array
    for(int i = 0; i < nStates; i++){
        matrix[i] = (pointer + 128 * i);
    }
    dfa->transitionTable = matrix;
    return dfa;
}




/**
 * Free the given DFA.
 */
void DFA_free(DFA dfa) {
    if (&dfa == NULL) {
        return;
    }
    else {
        free(dfa->numStates);
        free(dfa->transitionTable);
        free(dfa->acceptingStates);
        free(dfa);
    }
}

/**
 * Return the number of states in the given DFA.
 */
int DFA_get_size(DFA dfa) {
    return dfa->numStates;
}



/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 */
int DFA_get_transition(DFA dfa, int src, char sym){
    if((src < 0) || (src > dfa->numStates)){
        return 0;
    }
    int charValue = (int)sym; //get ASCII code
    int **matrix = dfa->transitionTable;
    return matrix[src][charValue];
}



/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */

void DFA_set_transition(DFA dfa, int src, char sym, int dst) {
    int charValue = (int)sym; //get ASCII code
    int **matrix = dfa->transitionTable;
    matrix[src][charValue] = dst; //pointer arithmetic to set value in 2d array
    dfa->transitionTable = matrix;
}

/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */

void DFA_set_transition_str(DFA dfa, int src, char *str, int dst) {
    char *strArr[] = { str };
    int **matrix = dfa->transitionTable;
    int length = sizeof(*strArr) / sizeof(strArr[0]); // total number of bytes/ number of bytes in a single char
    for (int i = 0; i < length; i++) {
        char currentChar = *strArr[i];
        int charValue = currentChar;
        matrix[src][currentChar] = dst; //pointer arithmetic to set value in 2d array
    }
}



/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
void DFA_set_transition_all(DFA dfa, int src, int dst) {
    int **matrix = dfa->transitionTable;
    for (int i = 0; i < 128; i++) { //i will be every ASCII code allowed by specs.
        matrix[src][i]= dst; //pointer arithmetic to set value in 2d array
    }
}



/**
 * Set whether the given DFA's state is accepting or not.
 */

void DFA_set_accepting(DFA dfa, int state, bool value) {
    LinkedList list = dfa->acceptingStates;
    if (value) {
        LinkedList_add_at_end(list, state);
    }
    else {
        LinkedList_remove(list, state);
    }
    dfa->acceptingStates = list;
}


/**
 * Return true if the given DFA's state is an accepting state.
 */

bool DFA_get_accepting(DFA dfa, int state) {
    LinkedList list = dfa->acceptingStates;
    return LinkedList_contains(list, state);
}



/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
bool DFA_execute(DFA dfa, char *input) {
    int finalState = 0;
    int n=strlen(input);
    printf("We are checking if the string %s is good\n",input);
    for(int i=0;i<n;i++)
    {
        finalState = DFA_get_transition(dfa, finalState, input[i]);
        }
        return DFA_get_accepting(dfa, finalState);
    }


void DFA_print(DFA dfa) {
    int states = dfa->numStates;
    printf("This Deterministic Finite Automaton has %d total states.", states);
    }