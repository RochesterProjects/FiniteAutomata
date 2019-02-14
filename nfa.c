#include <stdlib.h>

#include <stdio.h>

#include <stdbool.h>

#include <assert.h>
#include <string.h>

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

    IntHashSet** matrix = nfa->transitionTable;

    matrix = malloc(nStates * 129 * sizeof(**matrix));
//create an empty set at each point in the table
    for(int i = 0; i < nStates; i++){
        for(int j = 0; j < 128; j++){
             *((IntHashSet *)matrix + i * 128 + j) = new_IntHashSet(nStates);
        }
    }

    nfa->transitionTable = matrix;

    return nfa;

}


/**

 * Free the given NFA.

 */

void NFA_free(NFA nfa){

    if (nfa == NULL) {

        return;

    }

    else {
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

    return *((IntHashSet *)matrix + state * 128 + charValue);;

}


/**

 * For the given NFA, add the state dst to the set of next states from

 * state src on input symbol sym.

 */

void NFA_add_transition(NFA nfa, int src, char sym, int dst){

    int charValue = (int)sym; //get ASCII code

    IntHashSet **matrix = nfa->transitionTable;

    IntHashSet set = *((IntHashSet *)matrix + src * 128 + charValue);

    IntHashSet_insert(set, dst);

    *((IntHashSet *)matrix + src * 128 + charValue) = set;

    nfa->transitionTable = matrix;

}

    



/**

 * Add a transition for the given NFA for each symbol in the given str.

 */

void NFA_add_transition_str(NFA nfa, int src, char *str, int dst){
	IntHashSet **matrix = nfa->transitionTable;
	 int n= strlen(str);
	for(int i = 0; i < n; i++){
		int currentChar = str[i];
		 IntHashSet set = *((IntHashSet *)matrix + src * 128 + currentChar);

   		 IntHashSet_insert(set, dst);

    		*((IntHashSet *)matrix + src * 128 + currentChar) = set;
		
	
    

    


}


/**

 * Add a transition for the given NFA for each input symbol.

 */

void NFA_add_transition_all(NFA nfa, int src, int dst){

    IntHashSet** matrix = nfa->transitionTable;

    for (int i = 0; i < 128; i++) { //i will be every ASCII code allowed by specs.

        IntHashSet set = *((IntHashSet *)matrix + src * 128 + i);

        IntHashSet_insert(set, dst);

        *((IntHashSet *)matrix + src * 128 + i) = set; //pointer arithmetic to set value in 2d array

        nfa->transitionTable = matrix;

        }

    }




/**

 * Set whether the given NFA's state is accepting or not.

 */

void NFA_set_accepting(NFA nfa, int state, bool value){

    LinkedList list = nfa->acceptingStates;
    //int* pointer = &state;

    if (value) {

        LinkedList_add_at_end(list, state);
	printf("Just set %d as an accepting state!\n", state);

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
    //int* pointer = &state;
    LinkedList list = nfa->acceptingStates;

    return LinkedList_contains(list, state);

}

int getMax(IntHashSet set){
	int max = 0;
	IntHashSetIterator iterator = IntHashSet_iterator(set);
            while(IntHashSetIterator_hasNext(iterator)){
                int nextState = IntHashSetIterator_next(iterator);
                if(nextState> max){
                	max = nextState;
                }
            }
	return max;
}
	

/**

 * Run the given NFA on the given input string, and return true if it accepts

 * the input, otherwise false.

 */

bool NFA_execute(NFA nfa, char *input){

    int n= strlen(input);

    printf("We are checking if the string %s is good\n",input);
    int lastElementReached = 0;
    int state = 0;

    for(int i=0;i<n;i++){ 
        IntHashSet currentSet = NFA_get_transitions(nfa, lastElementReached, input[i]);
        if(IntHashSet_count(currentSet) == 1){
            lastElementReached = getMax(currentSet);
	printf("This is the last element reached now: %d\n", lastElementReached);
		//state = lastElementReached;

            

        }

        else if(IntHashSet_count(currentSet) > 1){

            IntHashSetIterator iterator = IntHashSet_iterator(currentSet);

            while(IntHashSetIterator_hasNext(iterator)){

                int nextState = IntHashSetIterator_next(iterator);
                IntHashSet set = NFA_get_transitions(nfa, nextState, input[i]);
                if(getMax(set) > lastElementReached){
                	lastElementReached = getMax(set);
				printf("This is the last element reached now: %d\n", lastElementReached);
				//state = lastElementReached;
            	}
	}		
			
        }
		if(IntHashSet_count(currentSet) == 0){
			if(i == (n-1)){
		  		return false;
			} 
			lastElementReached = 0;
			printf("This is the last element reached now: %d\n", lastElementReached);
				
	}

        

    }
	printf("This is the last element reached now: %d\n", lastElementReached);

    return NFA_get_accepting(nfa, lastElementReached);

}



/**

 * Print the given NFA to System.out.

 */

void NFA_print(NFA nfa){

    int states = nfa->numStates;

    printf("This Non-Deterministic Finite Automaton has %d total states.", states);
}

NFA NFA_ends_in_code()

{

    printf("Testing NFA that recognizes any string ending in \"code\". \n");

    NFA n1 = new_NFA(5);

    NFA_add_transition_all(n1, 0, 0);

    NFA_add_transition(n1, 0, 'c', 1);

    NFA_add_transition(n1, 1, 'o', 2);

    NFA_add_transition(n1, 2, 'd', 3);

    NFA_add_transition(n1, 3, 'e', 4);

    NFA_set_accepting(n1, 4, true);

    return n1;

}


NFA NFA_contains_code()

{

    printf("Testing NFA that recognizes any string containing \"code\". \n");

    NFA n1 = new_NFA(5);

    NFA_add_transition_all(n1, 0, 0);

    NFA_add_transition(n1, 0, 'c', 1);

    NFA_add_transition(n1, 1, 'o', 2);

    NFA_add_transition(n1, 2, 'd', 3);

    NFA_add_transition(n1, 3, 'e', 4);

    NFA_add_transition_all(n1, 4, 4);

    NFA_set_accepting(n1, 4, true);

    return n1;

}


NFA NFA_washington()

{

    printf("Testing NFA that recognizes a string with more than one a, g, h, i, o, s, t, or w, or more than two n’s. \n");

    NFA n1 = new_NFA(20);

    NFA_add_transition_all(n1,0,0);

    NFA_add_transition(n1, 0, 'a', 1);

    NFA_add_transition_all(n1, 1, 1);

    NFA_add_transition(n1, 1, 'a', 2);

    NFA_set_accepting(n1, 2, true);

    

    NFA_add_transition(n1, 0, 'g', 3);
    NFA_add_transition_all(n1,3,3);

    NFA_add_transition(n1, 3, 'g', 4);

    NFA_set_accepting(n1, 4, true);

    

    NFA_add_transition(n1, 0, 'h', 5);

    NFA_add_transition_all(n1, 5, 5);

    NFA_add_transition(n1, 5, 'h', 6);

    NFA_set_accepting(n1, 6, true);

    

    NFA_add_transition(n1, 0, 'i', 7);

    NFA_add_transition_all(n1, 7, 7);

    NFA_add_transition(n1, 7, 'i', 8);

    NFA_set_accepting(n1, 8, true);

    

    NFA_add_transition(n1, 0, 'n', 9);

    NFA_add_transition_all(n1, 9, 9);

    NFA_add_transition(n1, 9, 'n', 10);

    NFA_add_transition_all(n1, 10, 10);

    NFA_add_transition(n1, 10, 'n', 11);

    NFA_set_accepting(n1, 11, true);

    

    NFA_add_transition(n1, 0, 'o', 12);

    NFA_add_transition_all(n1, 12, 12);

    NFA_add_transition(n1, 12, 'o', 13);

    NFA_set_accepting(n1, 13, true);

    

    NFA_add_transition(n1, 0, 's', 14);

    NFA_add_transition_all(n1, 14, 14);

    NFA_add_transition(n1, 14, 's', 15);

    NFA_set_accepting(n1, 15, true);

    

    NFA_add_transition(n1, 0, 't', 16);

    NFA_add_transition_all(n1, 16, 16);

    NFA_add_transition(n1, 16, 't', 17);

    NFA_set_accepting(n1, 17, true);

    

    NFA_add_transition(n1, 0, 'w', 18);

    NFA_add_transition_all(n1, 18, 18);

    NFA_add_transition(n1, 18, 'w', 19);

    NFA_set_accepting(n1, 19, true);

    

    return n1;

}


//Note:  We did not include "y" as a vowel

NFA NFA_vowels()

{

    printf("Testing NFA that recognizes any string containing any vowels(not including \"y\"). \n");

    NFA n1 = new_NFA(6);

    NFA_add_transition_all(n1, 0, 0);

    NFA_add_transition_all(n1, 1, 1);

    NFA_add_transition_all(n1, 2, 2);

    NFA_add_transition_all(n1, 3, 3);

    NFA_add_transition_all(n1, 4, 4);

    NFA_add_transition_all(n1, 5, 5);

    

    NFA_add_transition(n1, 0, 'a', 1);

    NFA_add_transition(n1, 0, 'e', 2);

    NFA_add_transition(n1, 0, 'i', 3);

    NFA_add_transition(n1, 0, 'o', 4);

    NFA_add_transition(n1, 0, 'u', 5);

    

    NFA_set_accepting(n1, 1, true);

    NFA_set_accepting(n1, 2, true);

    NFA_set_accepting(n1, 3, true);

    NFA_set_accepting(n1, 4, true);

    NFA_set_accepting(n1, 5, true);

    return n1;

}



void NFA_REPL(NFA nfa)

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

            int didAccept = NFA_execute(nfa, input);

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

    NFA_free(nfa);

}


