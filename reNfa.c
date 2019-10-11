#include "renfa.h"

// Checks the character for validity.
int strCheck(char c){
    switch(c){
        case 'E':
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case '|':
        case '&':
        case '*':
            return 0;
        default:
            printf("Input string invalid.\n\n");
            return 1;
    }
}

// Takes a regular expression string and parses it
// It passes the character on to the nfa creation function
int readStr(char *str, STACK **stack){
    if(str == NULL){ return 0; }
    
    int i = 0;
    
    while(str[i] != '\n' && str[i] != '\0'){
        if(strCheck(str[i])) { // If char is invalid, fail and exit.
            return 1;
        }
        
        if(nfa(str[i++], stack)){
            return 1;
        }
    }
    
    return 0;
}

// Takes from stdin if no args are passed, otherwise opens the passed file
// Calls the necessary functions to create and print an nfa from the RE
int main (int argc, char *argv[]){
    
    FILE *in;
    char str[LEN];
    STACK *stack = startStack();
    
	if (argc == 1) {
		in = stdin;
        printf("Enter a postfix regular expression, or q to quit.\n");
	}else if (argc == 2) {
		in = fopen(argv[1], "r");
		if (!in) {
			perror(argv[1]);
			return 1;
		}
	}else {
		fprintf(stderr, "Usage: %s [input-file]\n", argv[0]);
		return 1;
	}
	
	fgets(str, LEN, in);
    
    // read inputs and call necessary functions to create and print the final NFA
    while(!(str[0] == 'q' && str[1] == '\n')){   
        if(readStr(str, &stack)){
            freeStack(&stack);
            fgets(str, LEN, in);
            continue;
        }
        
        if(DEBUG == 1){
            debugger(&stack);
        }else if(DEBUG == 2){
            debugger(&stack);
            printNfa(&stack);
        }else{
            printNfa(&stack); 
        }
        
        if(fgets(str, LEN, in) == NULL){
            break;
        }
        printf("\n");
    }
    
    free(stack);
    fclose(in);

    return 0;
    
}
