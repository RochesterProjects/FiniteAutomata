
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "dfa.h"
#include "nfa.h"
#include "nfa2dfa.h"
//create DFA that accepts exactly "csc173"
int main()
{

    
    NFA n1 = new_NFA(5);
    NFA_add_transition_all(n1, 0, 0);
    NFA_add_transition(n1, 0, 'c', 1);
    //printf("done with second\n");
    NFA_add_transition(n1, 1, 'o', 2);
    NFA_add_transition(n1, 2, 'd', 3);
    NFA_add_transition(n1, 3, 'e', 4);
    //printf("added all the transitions\n");
    NFA_set_accepting(n1, 4, true);
    char *input2 = {"code"};
    int didAccept2 = NFA_execute(n1, input2);
    if ((didAccept2 == 1)){
        printf("Accepted Input\n");
    }
    else{
        printf("Rejected Input\n");
    }
	DFA converted =  converter(n1);
	printf("The converted dfa has %d states. \n", DFA_get_size(converted));
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

    

    NFA_REPL(NFA_ends_in_code());

    printf("\n");

    NFA_REPL(NFA_contains_code());

    printf("\n");

    NFA_REPL(NFA_washington());

    printf("\n");

    NFA_REPL(NFA_vowels());

    printf("\n");




}







