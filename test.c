
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "dfa.h"
#include "nfa.h"
#include "nfa2dfa.h"
//create DFA that accepts exactly "csc173"
int main()
{

    
   /* NFA n1 = new_NFA(5);
    NFA_add_transition_all(n1, 0, 0);
    NFA_add_transition(n1, 0, 'c', 1);
    //printf("done with second\n");
    NFA_add_transition(n1, 1, 'o', 2);
    NFA_add_transition(n1, 2, 'd', 3);
    NFA_add_transition(n1, 3, 'e', 4);
    //printf("added all the transitions\n");
    NFA_set_accepting(n1, 4, true);
    char *input2 = {"ffffcfffode"};
    int didAccept2 = NFA_execute(n1, input2);
    if ((didAccept2 == 1)){
        printf("Accepted Input\n");
    }
    else{
        printf("Rejected Input\n");
    }
	DFA converted =  converter(n1);
	
	printf("The converted dfa has %d states. \n", DFA_get_size(converted));
	printf("The transition from %d on letter %c is %d", 2,'d',DFA_get_transition(converted, 2, 'd'));
	

	 int didAccept3 = DFA_execute(converted, input2);
    if ((didAccept3 == 1)){
        printf("Accepted Input\n");
    }
    else{
        printf("Rejected Input\n");
	}*/




DFA_REPL(DFA_csc173());

    printf("\n");

    DFA_REPL(DFA_cat());

    printf("\n");

    DFA_REPL(DFA_even0s());

    printf("\n");

    DFA_REPL(DFA_even0s_and1s());

    printf("\n");

    DFA_REPL(DFA_miller_or_shoham());

    printf("\n");

    
//for first two NFA's I will convert to DFA
	NFA n1 = NFA_ends_in_code();
	DFA d1 = converter(n1);
 	printf("Converting an NFA that accepts strings ending in 'code' to an equivalent DFA..\n");
   	 DFA_REPL(d1);

    	printf("\n");
	
	NFA n2 = NFA_contains_code();
	DFA d2 = converter(n2);
 	printf("Converting an NFA that accepts strings containing 'code' to an equivalent DFA..\n");
    DFA_REPL(d2);

    printf("\n");

    NFA_REPL(NFA_washington());

    printf("\n");

    NFA_REPL(NFA_vowels());

    printf("\n");




}







