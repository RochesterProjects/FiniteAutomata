# FiniteAutomata
Using C to create formal systems of Deterministic Finite Automata and NonDeterministic Finite Automata \n
#Collaborators: Shoham Shitrit and Miller Hickman
#Net ID: sshitrit and mhickman


## 1.) Creating a DFA representation
	This was made using a dfa.c file. We defined a DFA as a struct with a specified number of states, a linked list for all the accepting states, and a 2d array of ints for our transition table. To execute, we looped through a given input string, and got appropriate states using the transition table. If the final state is wihting the linked list of accepting states, we returned true. 

##2.) Creating a NFA representation
	This was made using a nfa.c file. We defined a NFA as a struct with a specified number of states, a linked list for all the accepting states, and a 2d array of IntHashSets for our transition table. Each IntHashSet contained the reuslting possible states the transtion function could lead it. To execute, we looped through a given input string, and got appropriate states using the transition table. If the final state is wihting the linked list of accepting states, we returned true.

##3.) Creating an NFA-DFA converter
	Using the Subset Construction algorthim, we extracted the sets that the NFA's transition function results. Then, we separated each individual element from each subset and inserted it into a resulting DFA.



###Regarding Warnings
	We couldn't figure out how to clear the warnings regarding the LinkedList.c/h that was supplied to us. Because of this, we ignored the -Wall -Werror flags in order to run our code. We attempted to use these flags, but in order to complete the project, we disregarded them.
