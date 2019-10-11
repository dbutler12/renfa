#include "renfa.h"

//List functions

// Sets aside memory for the list stack
LIST *newList(int node, int next, char c){
    LIST *list = malloc(sizeof(LIST));
    list->node = node;
    list->next = next;
    list->sym = c;
    list->list = NULL;

    return list;
}

// Recursive function to increase all list integer attributes by a number
// Updates the number then calls the next list item until the last list item
LIST *addNumsToList(LIST *list, int num){
    
    if(list == NULL){
        return NULL;
    }
    
    list->node = list->node + num;
    list->next = list->next + num;
    
    if(list->list != NULL){
        addNumsToList(list->list, num);
    }
    
    return list;
}

// Recursive function to combine two lists.
// Searches the first list until it finds the end (list1->list == NULL)
// Points the end to the second list
LIST *addToListEnd(LIST *list, LIST *end){
    if(list == NULL){
        return NULL;
    }
    
    if(list->list != NULL){
        addToListEnd(list->list, end);
    }else{
        list->list = end;
    }
    
    return list;
}

// Recursive function to find the maximum node number in the list
// Returns 0 if null, otherwise traverses the list until the end 
// If any node within the list is larger than the running max, returns that back to the beginning
int maxQ(LIST *list){
    if(list == NULL){
        return 0;
    }
    
    int max = maxQ(list->list);
    
    if(list->node > list->next && list->node > max){
        max = list->node;
    }else if(list->next > list->node && list->next > max){
        max = list->next;
    }
    
    return max;
}
