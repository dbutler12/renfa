#include "renfa.h"

// Free the stack (leaves the empty stack allocated)
// Frees the nfas on the stack as well
void freeStack(STACK **stack){
    NFA *remove = popStack(stack);
    
    while(remove != NULL){
        freeNfa(remove);
        remove = popStack(stack);
    }
}

// Free the memory of the passed nfa 
// Free the list of the passed nfa
void freeNfa(NFA *nfa){
    if(nfa != NULL){
        freeList(nfa->list);
        free(nfa);
    }
}

// Free the list by traversing it to the end and freeing as it goes
void freeList(LIST *list){
    while(list != NULL){
        LIST *temp = list->list;
        free(list);
        list = temp;
    }
}
