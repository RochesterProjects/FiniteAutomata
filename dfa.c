#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
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
    matrix = malloc(nStates * 129 * sizeof(**matrix));
    // for loop to point rows pointer to appropriate location in 2D array
   /* for(int i = 0; i < nStates; i++){
	for(int j = 0; j <128; j++){
          *((int*)matrix + i * 128 + j);
	}
    }*/
    dfa->transitionTable = matrix;
    return dfa;
}




/**
 * Free the given DFA.
 */
void DFA_free(DFA dfa) {
    if (dfa == NULL) {
        return;
    }
    else {
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
    return *((int*)matrix + src * 128 + charValue);
}



/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */

void DFA_set_transition(DFA dfa, int src, char sym, int dst) {
    int charValue = (int)sym; //get ASCII code
    int **matrix = dfa->transitionTable;
    *((int*)matrix + src * 128 + charValue) = dst; //pointer arithmetic to set value in 2d array
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
        *((int*)matrix + src * 128 + charValue) = dst; //pointer arithmetic to set value in 2d array
    }
	dfa->transitionTable = matrix;
}



/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
void DFA_set_transition_all(DFA dfa, int src, int dst) {
    int **matrix = dfa->transitionTable;
    for (int i = 0; i < 128; i++) { //i will be every ASCII code allowed by specs.
        *((int*)matrix + src * 128 + i) = dst; //pointer arithmetic to set value in 2d array
    }
	dfa->transitionTable = matrix;
}



/**
 * Set whether the given DFA's state is accepting or not.
 */

void DFA_set_accepting(DFA dfa, int state, bool value) {
    LinkedList list = dfa->acceptingStates;
   // int* pointer = &state;
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
   //int* pointer = &state;
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
DFA DFA_csc173()

{

    printf("Testing DFA that recognizes exactly \"csc173\". \n");

    DFA d1 = new_DFA(7);

    DFA_set_transition(d1, 0, 'c', 1);

    DFA_set_transition(d1, 1, 's', 2);

    DFA_set_transition(d1, 2, 'c', 3);

    DFA_set_transition(d1, 3, '1', 4);

    DFA_set_transition(d1, 4, '7', 5);

    DFA_set_transition(d1, 5, '3', 6);

    DFA_set_accepting(d1, 6, true);

    return d1;

}


DFA DFA_cat()

{

    printf("Testing DFA that recognizes any string that starts with \"cat\". \n");

    DFA d1 = new_DFA(4);

    DFA_set_transition(d1, 0, 'c', 1);

    DFA_set_transition(d1, 1, 'a', 2);

    DFA_set_transition(d1, 2, 't', 3);

    DFA_set_transition_all(d1, 3 , 3);

    DFA_set_accepting(d1, 3, true);

    return d1;

}


DFA DFA_even0s()

{

    printf("Testing DFA that recognizes a binary input with an even number of 0s. \n");

    DFA d1 = new_DFA(3);

    DFA_set_transition(d1, 0, '0', 1);

    DFA_set_transition(d1, 0, '1', 0);

    DFA_set_transition(d1, 1, '1', 1);

    DFA_set_transition(d1, 1, '0', 2);

    DFA_set_transition(d1, 2, '0', 1);

    DFA_set_transition(d1, 2, '1', 2);

    DFA_set_accepting(d1, 2, true);

    return d1;

}


DFA DFA_even0s_and1s()

{

    printf("Testing DFA that recognizes a binary input with an even number of 0s and 1s. \n");

    DFA d1 = new_DFA(4);

    DFA_set_transition(d1, 0, '0', 1);

    DFA_set_transition(d1, 1, '0', 0);

    

    DFA_set_transition(d1, 1, '1', 2);

    DFA_set_transition(d1, 2, '1', 1);

    

    DFA_set_transition(d1, 2, '0', 3);

    DFA_set_transition(d1, 3, '0', 2);

    

    DFA_set_transition(d1, 3, '1', 0);

    DFA_set_transition(d1, 0, '1', 3);

    

    DFA_set_accepting(d1, 0, true);

    return d1;

}


DFA DFA_miller_or_shoham()

{

    printf("Testing DFA that recognizes either \"miller\" or \"shoham\". \n");

    DFA d1 = new_DFA(13);

    DFA_set_transition(d1, 0, 'm', 1);

    DFA_set_transition(d1, 1, 'i', 2);

    DFA_set_transition(d1, 2, 'l', 3);

    DFA_set_transition(d1, 3, 'l', 4);

    DFA_set_transition(d1, 4, 'e', 5);

    DFA_set_transition(d1, 5, 'r', 6);

    DFA_set_accepting(d1, 6, true);

    

    DFA_set_transition(d1, 0, 's', 7);

    DFA_set_transition(d1, 7, 'h', 8);

    DFA_set_transition(d1, 8, 'o', 9);

    DFA_set_transition(d1, 9, 'h', 10);

    DFA_set_transition(d1, 10, 'a', 11);

    DFA_set_transition(d1, 11, 'm', 12);

    DFA_set_accepting(d1, 12, true);

    

    return d1;

}


void DFA_REPL(DFA dfa)

{

    bool quit = false;

    char* input = (char*) malloc(20*sizeof(char));

    while(!quit)

    {

        printf("Enter an input (\"quit\" to quit): \n");

        

        scanf("%s", input);

        if(strncmp(input, "quit", 4) == 0)

        {

            quit = true;

        }

        else{

            int didAccept = DFA_execute(dfa, input);

            int checkEmpty = strncmp(input, "", 4);

            if (checkEmpty != 0 && didAccept == 1) {

                printf("Result for input \"%s\": true \n", input);

            }

            else {

                printf("Result for input \"%s\": false \n", input);

            }

        }

    }

    free(input);

    DFA_free(dfa);

}
