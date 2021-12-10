#include "amount_set.h"
#include <stdlib.h>
#include <string.h>
#include "set.h"

#define ERROR_SIZE_FUNCTION -1



//typedef char* ASElement;
typedef struct asNode_t* asNode;
/*typedef ASElement (*CopyASElements)(ASElement);
typedef int (*CompareASElements)(ASElement, ASElement);
typedef void (*FreeASElement)(ASElement);
*/

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
    ASElement data;
    double amount;
    asNode next;
};


/**
 * @brief 
 * Constructor for asNode
 * @param node 
 * @param element 
 */
void asNodeCreate(asNode node ,ASElement element){
    if(!node || !element){
        return;
    }
    node->next = NULL;
    node->amount = 0;
    node->data = element;
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
asNode findElement(AmountSet set, ASElement element){
    if(!set || !element){
        return NULL;
    }
    asNode node = set->head;
    AS_FOREACH(ASElement, it, set){
        node = node->next;
        if(!set->compareElements(it, element)){
            return node;  
        }
    }
    return NULL;
};

ASElement CopyStr(ASElement str){
    if(!str){
        return NULL;
    }
    char* strCopy = (char*)malloc(strlen((char*)str)+1);
    if(!strCopy){
        return NULL;
    }
    strcpy(strCopy,(char*)str);
    return strCopy;
} 

int CompareStr(ASElement str1, ASElement str2){
    return strcmp((char*)str1, (char*)str2);
}

void FreeStr(ASElement str){
    free(str);
}

ASElement asGetFirst(AmountSet set){
    if(!set){
        return NULL;
    }
    set->current = set->head->next;
    return set->current->data;   
};


ASElement asGetNext(AmountSet set){
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
    AmountSet set = (AmountSet)malloc(sizeof(set));

    if(!set){
        return NULL;
    }

    set->copyElement = CopyStr;
    set->freeElement = FreeStr;
    set->compareElements = CompareStr;

    set->head = (asNode)malloc(sizeof(set->head));
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
    set->freeElement(set->head);
    free(set->head);
};


bool asContains(AmountSet set, ASElement element){
    if(!set || !element){
        return false;
    }

    if(!findElement(set, element)){
        return true;
    }

    return false;
};


AmountSetResult asDelete(AmountSet set, ASElement element){
    if(!set || !element){
        return AS_NULL_ARGUMENT;
    }

    if(asContains(set,element) == false){
        return AS_ITEM_DOES_NOT_EXIST;
    }

    asNode currentNode = set->head->next;
    asNode previousNode = set->head;

    while (currentNode){
        if(set->compareElements(currentNode,element)){
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
   AS_FOREACH(ASElement,it,set){
       size++;
   }
    return size;
};

AmountSetResult asGetAmount(AmountSet set, ASElement element, double *outAmount){
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

AmountSetResult asRegister(AmountSet set, ASElement element){
    if(!set || !element){
        return AS_NULL_ARGUMENT;
    }

    if(asContains(set,element) == true){
        return AS_ITEM_ALREADY_EXISTS;
    }

    AS_FOREACH(ASElement,it,set){
        //it->next == NULL means that it is end of the list
        asNode tempNode = findElement(set,it);
        if(tempNode->next == NULL || set->compareElements(tempNode->next->data,element) < 0){
            asNode biggerNode = tempNode->next;
            asNode node = (asNode)malloc(sizeof(node));
            if(!node){
                return AS_OUT_OF_MEMORY;
            }
            asNodeCreate(node,element);
            node->next = biggerNode;
            tempNode->next = node;
            return AS_SUCCESS;
        }
    }
    return AS_OUT_OF_MEMORY;
};

AmountSetResult asChangeAmount(AmountSet set, ASElement element, const double amount){

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
    AmountSet copy = asCreate(set->copyElement,set->freeElement,set->compareElements);
    if(!copy){
        return NULL;
    }
    copy->current = (asNode)malloc(sizeof(copy->current));
    AS_FOREACH(ASElement,it,set){
        if(!copy->current){
            asDestroy(copy);
            free(copy);
            return NULL;
        }
        asNodeCreate(copy->current,it);
        copy->current->next = (asNode)malloc(sizeof(copy->current->next));
        asGetNext(copy);
    }

    return copy;
}