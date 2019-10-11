#include "renfa.h"

// Sets aside memory for the beginning of stack
// Stack with NULL node is the beginning stack
STACK *startStack(){
    STACK *stack = malloc(sizeof(STACK));
    stack->node = NULL;
    stack->next = NULL;
    return stack;
}

// Sets aside memory for a new stack node
// Adds the passed nfa to the node and sets previous stack node to next
void pushStack(NFA *nfa, STACK **stack){
    STACK *newNode = malloc(sizeof(STACK));
    newNode->node = nfa;
    newNode->next = *stack;
    *stack = newNode;
}

// Takes the node pointed to by the stack (top of stack) and returns the nfa on it
// Frees the stack node and sets stack to the next stack node
NFA *popStack(STACK **stack){
    if(stack == NULL){
        printf("Stack uninitialized!\n");
        return NULL;
    }
    
    // Empty stack
    if((*stack)->node == NULL){
        return NULL;
    }
    
    NFA *top = (*stack)->node;
    STACK *temp = (*stack)->next;
    
    free(*stack);
    
    *stack = temp;
    
    return top;
}
