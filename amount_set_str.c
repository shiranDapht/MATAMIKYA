#include "amount_set.h"
#include "amount_set_str.h"
#include "amount_set.c"
#include <stdlib.h>



typedef const char* ASElement;

int CompareASElements(ASElement str1, ASElement str2){
    return strcmp(str1, str2);
}

void FreeASElement(ASElement str){
    free(str);
}

char* CopyASElement(char* str){
    if(!str){
        return NULL;
    }
    char* strCopy = malloc(sizeof(strlen(str)+1));
    if(!strCopy){
        return NULL;
    }
    strcpy(strCopy,str);
    return strCopy;
}

char* asGetFirst(AmountSet set){
    if(!set){
        return NULL;
    }
    set->current = set->head->next;
    return set->current;
}
char* asGetNext(AmountSet set){
    if(!set){
        return NULL;
    }
    set->current = set->current->next; // Advance one step
    return set->current;
}
