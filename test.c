
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "dfa.h"
#include "nfa.h"
//create DFA that accepts exactly "csc173"
int main()
{
    printf("Begin test...\n");
    DFA d1 = new_DFA(7);
    DFA_set_transition(d1, 0, 'c', 1);
    DFA_set_transition(d1, 1, 's', 2);
    DFA_set_transition(d1, 2, 'c', 3);
    DFA_set_transition(d1, 3, '1', 4);
    DFA_set_transition(d1, 4, '7', 5);
    DFA_set_transition(d1, 5, '3', 6);
    DFA_set_accepting(d1, 6, true);
    char* input = { "csc173" };
    int didAccept = DFA_execute(d1, input);
    if ((didAccept == 1)) {
        printf("Accepted Input\n");
    }
    else {
        printf("Rejected Input\n");
    }
    
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
return 0;
}
