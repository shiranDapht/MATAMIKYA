//#include "amount_set.h"
#include "amount_set_str.h"
#include <stdlib.h>
#include <string.h>
#include "set.h"

#define ERROR_SIZE_FUNCTION -1


typedef char* (*CopyASElement)(const char*);

typedef void (*FreeASElement)(char*);

typedef int (*CompareASElements)(const char*, const char*);

typedef struct asNode_t* asNode;

char* CopyStr(const char* str);
struct AmountSet_t{
    CopyASElement copyElement;
    FreeASElement freeElement;
    CompareASElements compareElements;
    asNode head;
    asNode current;
};

/**
 * @brief 
 *  struct for node in AmountSet linked node list
 */
struct asNode_t{
    char* data;
    double amount;
    asNode next;
};


/**
 * @brief 
 * Constructor for asNode
 * @param node 
 * @param element 
 */
void asNodeCreate(asNode node ,const char* element){
    if(!node || !element){
        return;
    }
    node->next = NULL;
    node->amount = 0;
    node->data = CopyStr(element);
    return;
};


/**
 * @brief 
 * asNode destructor
 * @param set 
 * @param node 
 */
void asNodeDelete(AmountSet set, asNode node){
    if(!set || !node){
        return;
    }
    set->freeElement(node->data);
    free(node);
};


/**
 * @brief 
 * find and return node with identical element
 * @param set 
 * @param element 
 * @return asNode 
 */
asNode findElement(AmountSet set, const char* element){
    if(!set || !element){
        return NULL;
    }
    asNode node = set->head;
    AS_FOREACH(char*, it, set){
        node = node->next;
        if(!set->compareElements(it, element)){
            return node;  
        }
    }
    return NULL;
};

char* CopyStr(const char* str){
    if(!str){
        return NULL;
    }
    char* strCopy = (char*)malloc(strlen((char*)str)+1);
    if(!strCopy){
        return NULL;
    }
    strcpy(strCopy,str);
    return strCopy;
} 

int CompareStr(const char* str1, const char* str2){
    return strcmp(str1, str2);
}

void FreeStr(char* str){
    free(str);
}

char* asGetFirst(AmountSet set){
    if(!set){
        return NULL;
    }
    set->current = set->head->next;
    if(!set->current){
        return NULL;
    }
    return set->current->data;   
};


char* asGetNext(AmountSet set){
    if(!set || !set->current){
        return NULL;
    }
    set->current = set->current->next; // Advance one step
    if(!set->current){
        return NULL;
    }
    return set->current->data;
};


AmountSet asCreate(){
    AmountSet set = (AmountSet)malloc(sizeof(struct AmountSet_t));

    if(!set){
        return NULL;
    }

    set->copyElement = CopyStr;
    set->freeElement = FreeStr;
    set->compareElements = CompareStr;

    set->head = (asNode)malloc(sizeof(struct asNode_t));
    if (!set->head){
        free(set);
        return NULL;
    }
    
    set->head->amount = 0;
    set->head->data = NULL;

    set->head->next = NULL;
    set->current = set->head->next;
    
    return set;
};



AmountSetResult asClear(AmountSet set){
    if(!set){
        return AS_NULL_ARGUMENT;
    }
    
    asNode curr = set->head->next;

    while(curr){   
        asNode toDelete = curr;
        curr = curr->next;
        asNodeDelete(set, toDelete);
    }

    return AS_SUCCESS;
};


void asDestroy(AmountSet set){
    if(!set || asClear(set) != AS_SUCCESS){
        return;
    }
    set->freeElement(set->head->data);
    free(set->head);
};


bool asContains(AmountSet set, const char* element){
    if(!set || !element){
        return false;
    }

    if(!findElement(set, element)){
        return true;
    }

    return false;
};


AmountSetResult asDelete(AmountSet set, const char* element){
    if(!set || !element){
        return AS_NULL_ARGUMENT;
    }

    if(asContains(set,element) == false){
        return AS_ITEM_DOES_NOT_EXIST;
    }

    asNode currentNode = set->head->next;
    asNode previousNode = set->head;

    while (currentNode){
        if(set->compareElements(currentNode->data,element)){
            previousNode->next = currentNode->next;
            asNodeDelete(set, currentNode);
            break;
        }
        previousNode = previousNode->next;
        currentNode = currentNode->next;
       
    }
    return AS_SUCCESS;
};

int asGetSize(AmountSet set){
    if(!set){
        return ERROR_SIZE_FUNCTION;
    }

    int size = 0;
    /*
    asNode currentNode = set->head->next;

    while (currentNode)
    {
        size++;
        currentNode = currentNode->next;
    }
    */
   AS_FOREACH(char*,it,set){
       size++;
   }
    return size;
};

AmountSetResult asGetAmount(AmountSet set, const char* element, double *outAmount){
    if(!set || !element || !outAmount){
        return AS_NULL_ARGUMENT;
    }

    if(asContains(set,element) == false){
        return AS_ITEM_DOES_NOT_EXIST;
    }

    asNode node = findElement(set, element);
    *outAmount = node->amount;

    return AS_SUCCESS;
};

AmountSetResult asRegister(AmountSet set, const char* element){
    if(!set || !element){
        return AS_NULL_ARGUMENT;
    }

    if(asContains(set,element)){
        return AS_ITEM_ALREADY_EXISTS;
    }

    AS_FOREACH(char*,it,set){
        //it->next == NULL means that it is end of the list
        asNode tempNode = findElement(set,it);
        if(!tempNode->next || set->compareElements(tempNode->next->data,element) < 0){
            asNode biggerNode = tempNode->next;
            asNode newNode = (asNode)malloc(sizeof(struct asNode_t));
            if(!newNode){
                return AS_OUT_OF_MEMORY;
            }
            asNodeCreate(newNode,element);
            newNode->next = biggerNode;
            tempNode->next = newNode;
            return AS_SUCCESS;
        }
    }
    return AS_OUT_OF_MEMORY;
};

AmountSetResult asChangeAmount(AmountSet set, const char* element, const double amount){

    if(!set || !element || !amount){
        return AS_NULL_ARGUMENT;
    }

    if(asContains(set,element) == false){
        return AS_ITEM_DOES_NOT_EXIST;
    }

    asNode node = findElement(set, element);
    
    double val = node->amount + amount;
    if(val < 0 ){
        return AS_INSUFFICIENT_AMOUNT;
    }

    node->amount += amount;

    return AS_SUCCESS;
};

AmountSet asCopy(AmountSet set){
    AmountSet copy = asCreate();
    if(!copy){
        return NULL;
    }
    copy->current = (asNode)malloc(sizeof(struct asNode_t));
    AS_FOREACH(char*,it,set){
        if(!copy->current){
            asDestroy(copy);
            free(copy);
            return NULL;
        }
        asNodeCreate(copy->current,it);
        copy->current->next = (asNode)malloc(sizeof(struct asNode_t));
        asGetNext(copy);
    }

    return copy;
}