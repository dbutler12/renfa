#ifndef RENFA_H_INCLUDED
#define RENFA_H_INCLUDED
#define MYNULL -1

#include <stdio.h>
#include <stdlib.h>

#define LEN 200
#define DEBUG 0

// Structs
typedef struct stack {
    struct nfa   *node;
    struct stack *next;
} STACK;

typedef struct nfa {
    int s;
    int f;
    struct list *list;
} NFA;

typedef struct list {
    int node;
    int next;
    char sym;
    struct list *list;
} LIST;

// NFA functions
int isInvalid(NFA *nfa1, NFA *nfa2);
void createNfa(char c, STACK **stack);
int nfa(char c, STACK **stack);
int unionNfa(STACK **stack);
int concatNfa(STACK **stack);
int kleeneNfa(STACK **stack);

// List functions
LIST *newList(int node, int next, char c);
LIST *comList(LIST *list1, LIST *list2);
LIST *addNumsToList(LIST *list, int num);
LIST *addToListEnd(LIST *list, LIST *end);

// I/O functions
int readStr(char *str, STACK **stack);
int strCheck(char c);
void debugger(STACK **stack);
char *concat(int q, char *str);
int symToNum(char c);
int printNfa(STACK **stack);
int maxQ(LIST *list);
char *itoa(int num);

// Stack functions
void pushStack(NFA *nfa, STACK **stack);
NFA *popStack(STACK **stack);
STACK *startStack();

// Memory Freeing Functions
void freeStack(STACK **stack);
void freeNfa(NFA *nfa);
void freeList(LIST *list);

#endif // RENFA_H_INCLUDED
