#define _nfa2dfa_h

extern IntHashSet get_nextStates(NFA nfa, int state, char c);

extern DFA converter(NFA nfa);

