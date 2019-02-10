#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "nfa.h"
#include "LinkedList.h"
#include "Set.h"
#include "IntHashSet.h"

/**
 * The data structure used to represent a nondeterministic finite automaton.
 * @see FOCS Section 10.3
 * @see Comments for DFA in dfa.h
 */
typedef struct NFA{
    int numStates;
    IntHashSet** transitionTable;
    LinkedList acceptingStates;
    
} *NFA;

/**
 * Allocate and return a new NFA containing the given number of states.
 */
NFA new_NFA(int nStates){
    NFA nfa;
    nfa = (NFA)malloc(sizeof(NFA));
    if (nfa == NULL) {
        return NULL; // Out of memory...
    }
    nfa->numStates = nStates;
    nfa->acceptingStates = new_LinkedList();
    
    //to allocate transition table
    IntHashSet matrix[nStates][128];
    for (int i = 0; i < nStates; i++)
    {
        for(int j = 0; j < 128; j++)
        {
            matrix[i][j]= new_IntHashSet(nStates);
        }
    }
    nfa->transitionTable = *matrix;
    return nfa;
}

/**
 * Free the given NFA.
 */
void NFA_free(NFA nfa){
    if (&nfa == NULL) {
        return;
    }
    else {
        free(nfa->numStates);
        free(nfa->transitionTable);
        free(nfa->acceptingStates);
        free(nfa);
    }
}

/**
 * Return the number of states in the given NFA.
 */
int NFA_get_size(NFA nfa){
    return nfa->numStates;
}

/**
 * Return the set of next states specified by the given NFA's transition
 * function from the given state on input symbol sym.
 */
Set NFA_get_transitions(NFA nfa, int state, char sym){
    int charValue = (int)sym; //get ASCII code
    IntHashSet **matrix = nfa->transitionTable;
    return matrix[state][charValue];
}

/**
 * For the given NFA, add the state dst to the set of next states from
 * state src on input symbol sym.
 */
void NFA_add_transition(NFA nfa, int src, char sym, int dst){
    int charValue = (int)sym; //get ASCII code
    IntHashSet **matrix = nfa->transitionTable;
    if(matrix[src][charValue] == 0){
        IntHashSet set = new_IntHashSet(nfa->numStates);
        IntHashSet_insert(set, dst);
        nfa->transitionTable = matrix;
    }else{
        IntHashSet** set = matrix[src][charValue];
        IntHashSet_insert(set, dst);
        matrix[src][charValue] = set;
        nfa->transitionTable = matrix;
    }
    
}

/**
 * Add a transition for the given NFA for each symbol in the given str.
 */
void NFA_add_transition_str(NFA nfa, int src, char *str, int dst){
    int **matrix = nfa->transitionTable;
    
    
    

}

/**
 * Add a transition for the given NFA for each input symbol.
 */
void NFA_add_transition_all(NFA nfa, int src, int dst){
    IntHashSet **matrix = nfa->transitionTable;
    for (int i = 0; i < 128; i++) { //i will be every ASCII code allowed by specs.
        if(matrix[src][i] == 0){
            IntHashSet set = new_IntHashSet(nfa->numStates);
            IntHashSet_insert(set, dst);
            matrix[src][i]= set; //pointer arithmetic to set value in 2d array
            nfa->transitionTable = matrix;
        }else{
            IntHashSet set = matrix[src][i];
            IntHashSet_insert(set, dst);
            matrix[src][i] = set;
            nfa->transitionTable = matrix;
        }
    }
}

/**
 * Set whether the given NFA's state is accepting or not.
 */
void NFA_set_accepting(NFA nfa, int state, bool value){
    LinkedList list = nfa->acceptingStates;
    if (value) {
        LinkedList_add_at_end(list, state);
    }
    else {
        LinkedList_remove(list, state);
    }
    nfa->acceptingStates = list;
}

/**
 * Return true if the given NFA's state is an accepting state.
 */
bool NFA_get_accepting(NFA nfa, int state){
    LinkedList list = nfa->acceptingStates;
    return LinkedList_contains(list, state);
}

Set execute_helper(NFA nfa,IntHashSet set, int charValue){
    IntHashSet toReturn = new_IntHashSet(nfa->numStates);
    IntHashSetIterator iterator = IntHashSet_iterator(set);
    while(IntHashSetIterator_hasNext(iterator)){
            IntHashSet_union(toReturn, NFA_get_transitions(nfa, IntHashSetIterator_next(iterator), charValue));
        
    }
    free(iterator);
    return toReturn;
}

/**
 * Run the given NFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
bool NFA_execute(NFA nfa, char *input){
    int n=strlen(input);
    printf("We are checking if the string %s is good\n",input);
    IntHashSet statesPassed = new_IntHashSet(nfa->numStates);
    for(int i=0;i<n;i++)
    {
        execute_helper(nfa, statesPassed, input[i]);
    }
    IntHashSetIterator iterator = IntHashSet_iterator(statesPassed);
    while(IntHashSetIterator_hasNext(iterator)){
        if(NFA_get_accepting(nfa,IntHashSetIterator_next(iterator))){
            free(iterator);
            return true;
        }
    }
    free(iterator);
    return false;
}


/**
 * Print the given NFA to System.out.
 */
void NFA_print(NFA nfa){
    int states = nfa->numStates;
    printf("This Non-Deterministic Finite Automaton has %d total states.", states);
}