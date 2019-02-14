#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "dfa.h"
#include "nfa.h"
#include "IntHashSet.h"
#include "LinkedList.h"


IntHashSet get_nextStates(NFA nfa, int state, char c){
	return NFA_get_transitions(nfa, state, c);
}

DFA converter(NFA nfa){
	int nfaStates = NFA_get_size(nfa);
	int dfaStates = pow(2, nfaStates);
	DFA dfa = new_DFA(dfaStates);
	
	for(int i = 0; i < nfaStates; i++){
		for(int j = 0; j < 128; j++){
			char c = (char)j;
			IntHashSet nextStates = get_nextStates(nfa,i, c);
			if(IntHashSet_count(nextStates) == 1){ // would be same transition
				IntHashSetIterator iterator = IntHashSet_iterator(nextStates);
				int dst = IntHashSetIterator_next(iterator);
				DFA_set_transition(dfa, i, c, dst);
				//printf("Setting transition from state %d on character %c to state %d\n", i,c,dst);
			}
			if(IntHashSet_count(nextStates) > 1){
				IntHashSetIterator iterator = IntHashSet_iterator(nextStates);
				while(IntHashSetIterator_hasNext(iterator)){
					int dst = IntHashSetIterator_next(iterator);
					DFA_set_transition(dfa,i,c,dst);
					//printf("Setting transition from state %d on character %c to state %d\n", i,c,dst);
				}
			}		
		}
	}
	//set accepting for DFA
	return dfa;
}
