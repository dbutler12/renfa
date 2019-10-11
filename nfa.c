#include "renfa.h"

// Sets aside memory for an nfa 
// Sets the start to 1 and end to 2 (for a basic nfa)
// Sets the transition symbol to the passed character using newList
void createNfa(char c, STACK **stack){
    
    NFA *nfa = malloc(sizeof(NFA));
    LIST *list = newList(1, 2, c);
    
    nfa->s = 1;
    nfa->f = 2;
    
    nfa->list = list;
    
    // push to stack
    pushStack(nfa, stack);
    
}

// Checks if the two passed nfas are valid, if not exits the program.
// Does not free memory, since it's exiting
int isInvalid(NFA *nfa1, NFA *nfa2){
    if(nfa1 == NULL || nfa2 == NULL){
        printf("The user has not input sufficient values in the expression.\n\n");
        return 1;
    }

    return 0;
}

// Uses the nfa currently on the stack to apply the kleene star to
// Checks if the nfa from the stack is valid then increases the values of the nfa by 1 (to make up for adding a new node)
// Creates the necessary new lists for the transitions
int kleeneNfa(STACK **stack){
    NFA *nfa = popStack(stack);
    
    if(isInvalid(nfa, nfa)){
        freeNfa(nfa);
        return 1;
    }
    
    nfa->list = addNumsToList(nfa->list, 1);
    
    LIST *newStart = newList(1, nfa->s + 1, 'E');
    LIST *finalTrans = newList(nfa->f + 1, 1, 'E');
    
    nfa->s = 1;
    nfa->f = 1;
    
    nfa->list = addToListEnd(newStart, nfa->list);
    nfa->list = addToListEnd(nfa->list, finalTrans);
    
    // push to stack
    pushStack(nfa, stack);
    
    return 0;
}

// nfa concatenator with the two nfas on the stack
// If either is invalid, quits program
// Uses nfa1 as the base nfa
// Shifts the second nfa by the max of the first + 1
// Creates the one transition it needs between the two nfas
int concatNfa(STACK **stack){
    NFA *nfa2 = popStack(stack);    
    NFA *nfa1 = popStack(stack);
    
    if(isInvalid(nfa1, nfa2)){
        freeNfa(nfa1);
        freeNfa(nfa2);
        return 1;
    }
    
    // Before shifting anything, get base numbers of both nfas
    int maxQ1 = maxQ(nfa1->list);
    int maxQ2 = maxQ(nfa2->list);
    int max = maxQ1 + maxQ2 + 2;
    
    nfa2->list = addNumsToList(nfa2->list, maxQ1);
    
    LIST *transition = newList(nfa1->f, nfa2->s + maxQ1, 'E');
    nfa1->f = maxQ1 + maxQ2;
    
    nfa1->list = addToListEnd(nfa1->list, transition);
    nfa1->list = addToListEnd(nfa1->list, nfa2->list);
    
    free(nfa2); // Free the unnecessary nfa
    pushStack(nfa1, stack); // push to stack
    
    return 0;
}

// Union of two nfas with the two on the top of the stack
// If either is invalid, quits program
// Uses nfa1 as the base nfa
// Shifts the first nfa by 1 and the second by the max of the first + 1
// Adds the four transitions s1, s2, f1, f2 necessary for the addition of a node on beginning and end 
// Creates list in the order s1 -> s2 -> nfa1 list -> nfa2 list -> f1 -> f2
int unionNfa(STACK **stack){
    NFA *nfa2 = popStack(stack);
    NFA *nfa1 = popStack(stack);
    
    if(isInvalid(nfa1, nfa2)){
        freeNfa(nfa1);
        freeNfa(nfa2);
        return 1;
    }
    
    // Before shifting anything, get base numbers of both nfas
    int maxQ1 = maxQ(nfa1->list);
    int maxQ2 = maxQ(nfa2->list);
    int max = maxQ1 + maxQ2 + 2;
    
    nfa1->list = addNumsToList(nfa1->list, 1); // Increase q values by 1 to make room for node 1 being start
    nfa2->list = addNumsToList(nfa2->list, maxQ1 + 1); // Increase q values by final value + 1 to add to end of first nfa list
    
    LIST *s1 = newList(1, 2, 'E'); // Add E transition from start node to nfa1 start node
    LIST *s2 = newList(1, 2 + maxQ1, 'E'); // Add E transition from start node to new nfa2 start node
    s1->list = s2;
    
    nfa1->list = addToListEnd(s1, nfa1->list); // Push to end of new nfa list
    
    LIST *f1 = newList(nfa1->f + 1, max, 'E'); 
    LIST *f2 = newList(nfa2->f + maxQ1 + 1, max, 'E');
    f1->list = f2;
    
    nfa1->list = addToListEnd(nfa1->list, nfa2->list);
    nfa1->list = addToListEnd(nfa1->list, f1);
    
    nfa1->s = 1;
    nfa1->f = max;
    
    free(nfa2); // Free the unnecessary nfa
    pushStack(nfa1, stack); // Push to stack
    
    return 0;
}

// Creates an nfa given a stack of nfas and a character
int nfa(char c, STACK **stack){
    switch(c){
        case '|':
            if(unionNfa(stack)){
                return 1;
            }
            break;
        case '&':
            if(concatNfa(stack)){
                return 1;
            }
            break;
        case '*':
            if(kleeneNfa(stack)){
                return 1;
            }
            break;
        default: // Default case is to create a basic nfa
            createNfa(c, stack);
            break;
    }
    
    return 0;
}
