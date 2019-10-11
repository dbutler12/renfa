#include "renfa.h"

// For debugging purposes
// Prints everything on the stack, including the nfas and the lists
// Useful for seeing if there are multiple nfas on the stack
void debugger(STACK **stack){
    
    NFA *top = popStack(stack);
    NFA *topNext;
    
    if(top == NULL){
        printf("S F (q1, E)->q2\n");
        return;
    }
    
    do{
        
        printf("NFA: %i to %i\n", top->s, top->f);
        
        LIST *list = top->list;
        
        while(list != NULL){
            printf("(q%d, %c) -> q%d\n", list->node, list->sym, list->next);
            list = list->list;
        }
        
        topNext = popStack(stack);
        
        if(topNext != NULL){ top = topNext; }
    }while(topNext != NULL);
    
    pushStack(top, stack);
}

// Concatenates a new q node onto the string of other q nodes
// Sets aside memory for the new string based on size of passed string
// If the passed string is empty, returns just the q node
char *concat(int q, char *str){
    
    int count = 0, i, j;
    char *node = itoa(q); // Turn the passed number into a string
    
    while(str[count] != '\0'){ count++; }
    char *conc = malloc((count+7)*sizeof(char));

    if(count == 0){ // Create new q node and return that
        conc[0] = 'q';
        
        i = 0;
        while(node[i] != '\0'){
            char c = node[i];
            conc[i+1] = c;
            i++;
        }
        
        conc[i+1] = '\0';
    }else{ // Concatenate previous q node with new one
        
        for(i = 0; i < count; ++i){
            conc[i] = str[i];
        }
        
        conc[count++] = ',';
        conc[count++] = 'q';
        
        i = 0;
        while(node[i] != '\0'){
            char c = node[i];
            conc[i + count] = c;
            i++;
        }
        
        conc[i+count] = '\0';
    }
    
    free(node); // Free the node, as it's not needed anymore.
    return conc;    
}

// Turns the symbols into their respective numbers
int symToNum(char c){
    switch(c){
        case 'E':
            return 0;
        case 'a':
            return 1;
        case 'b':
            return 2;
        case 'c':
            return 3;
        case 'd':
            return 4;
        case 'e':
            return 5;
    }
}

// Personal itoa (int to string) function, since this doesn't exist in my library
// Sets aside some memory for a string
// Uses modulo operator mod 10 to strip apart the digits of the number to build a temporary string
// Uses a flag to ignore the useless zeros until it reaches the first valid digit of the number
// Then appends the rest of the number to the string to be returned
char *itoa(int num){
    char *str = malloc(10*sizeof(char));
    char temp[10];
    int i;
    int flag = 0;
    
    for(i = 0; i < 10; ++i){
        str[i] = '\0';
        temp[i] = '0';
    }
    
    if(num < 10){
        str[0] = num + '0';
        str[1] = '\0';
        return str;
    }
    
    i = 0;
    while(num != 0 && i < 10){
        temp[i++] = num%10 + '0';
        num /= 10;
    }
    
    int j = 0;
    for(i; i >= 0; i--){        
        if(flag == 1){
            str[j++] = temp[i];
        }
        
        if(flag == 0 && temp[i] != 0){
            flag = 1;
        }
    }
    
    return str;
}


// Main print function. Assumes the top of stack is the final nfa 
// Pops from stack, creates a table of pointers set up for the printout using the maximum node of the list
int printNfa(STACK **stack){
    
    NFA *top = popStack(stack);
    NFA *garbage = popStack(stack);
    
    if(garbage != NULL){
        printf("The user input has too many values.\n\n");
        freeNfa(top);
        freeNfa(garbage);
        freeStack(stack);
        return 1;
    }
    
    if(top == NULL){
        printf("S F (q1, E)->q2\n");
        return 0;
    }
    
    LIST *list = top->list;    
    int max = maxQ(list);
    char *table[max][6];
    int tableMem[max][6]; // Table to determine which memory slot has been allocated

    int i, j;
    for(i = 0; i < max; i++){ // Initialize table and memory allocations
        for(j = 0; j < 6; j++){
            table[i][j] = "\0";
            tableMem[i][j] = 0;
        }
    }

    while(list != NULL){ // Fills table with proper strings by traversing the NFA transition list.
        int sym = symToNum(list->sym);
        int node = list->node - 1;
        char *buffer = table[node][sym];
        char *str = concat(list->next, buffer);
        
        if(tableMem[node][sym] == 1){ // Free previous string stored in table.
            free(buffer);
        }
        
        table[node][sym] = str;
        tableMem[node][sym] = 1;
        list = list->list;
    }
    
    printf("       | %8s | %8s | %8s | %8s | %8s | %8s \n", "   a    ", "   b    ", "   c    ", "   d    ", "   e    ", "   E    ");

    for(i = 0; i < max; ++i){ // Print the table
        
        if(i == top->s - 1 && i == top->f - 1){ // Edgecase: the node is both the start and end
            printf("q%2i S F| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s \n", i+1, table[i][1], table[i][2], table[i][3], table[i][4], table[i][5], table[i][0]);
        }else if(i == top->s-1){ // Edgecase: the node is the start
            printf("q%2i S  | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s \n", i+1, table[i][1], table[i][2], table[i][3], table[i][4], table[i][5], table[i][0]);
        }else if(i == top->f - 1){ // Edgecase: the node is the end
            printf("q%2i F  | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s \n", i+1, table[i][1], table[i][2], table[i][3], table[i][4], table[i][5], table[i][0]);
        }else{ // Regular nodes
            printf("q%2i    | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s \n", i+1, table[i][1], table[i][2], table[i][3], table[i][4], table[i][5], table[i][0]);
        }
        
        for(j = 0; j < 6; ++j){ // Free table memory using the table memory allocator
            if(table[i][j] != NULL && tableMem[i][j] != 0){
                free(table[i][j]);
            }
        }
    }
    
    freeNfa(top); // Free the nfa
    
    printf("\n");
    
    return 0;
}
