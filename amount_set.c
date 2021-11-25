#include "amount_set.h"
#include <stdlib.h>

#define ERROR_SIZE_FUNCTION -1




typedef struct asNode_t* asNode;
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
    AS_FOREACH(asNode, it, set){
        if(!set->compareElements(it->data, element)){
            return it;
        }
    }
    return NULL;
};


struct AmountSet_t{
    CopyASElement copyElement;
    FreeASElement freeElement;
    CompareASElements compareElements;
    asNode head;
    asNode current;
};



ASElement asGetFirst(AmountSet set){
    if(!set){
        return NULL;
    }
    set->current = set->head->next;
    return set->current;   
};


ASElement asGetNext(AmountSet set){
    if(!set){
        return NULL;
    }
    set->current = set->current->next; // Advance one step
    return set->current;
};


AmountSet asCreate(CopyASElement copyElement, FreeASElement freeElement,
                        CompareASElements compareElements){
                            if (!copyElement || !freeElement || !compareElements){
                                return NULL;
                            }

                            AmountSet set = malloc(sizeof(set));

                            if(!set){
                                return NULL;
                            }

                            set->copyElement = copyElement;
                            set->freeElement = freeElement;
                            set->compareElements = compareElements;

                            set->head = malloc(sizeof(set->head));
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
    
    return AS_SUCCESS;

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
            asNode toDelete = currentNode;
            previousNode->next = currentNode->next;
            asNodeDelete(set, toDelete);
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
   AS_FOREACH(asNode,it,set){
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

    AS_FOREACH(asNode,it,set){
        //it->next == NULL means that it is end of the list
        if(it->next == NULL || set->compareElements(it->next->data,element) < 0){
            asNode biggerNode = it->next;
            asNode node = malloc(sizeof(asNode));
            if(!node){
                return AS_OUT_OF_MEMORY;
            }
            asNodeCreate(node,element);
            node->next = biggerNode;
            it->next = node;
            return AS_SUCCESS;
        }
    }
/*
    asNode currentNode = set->head->next;
    asNode previousNode = set->head;

    while (currentNode){
        if(set->compareElements(currentNode,element) < 0){
            asNode node = malloc(sizeof(node));
            if(!node){
                return AS_OUT_OF_MEMORY;
            }
            asNodeCreate(node ,element);
            previousNode->next = node;
            node->next = currentNode;

            return AS_SUCCESS;
        }

        previousNode = previousNode->next;
        currentNode = currentNode->next;
    }

    asNode node = malloc(sizeof(node));
    if(!node){
        return AS_OUT_OF_MEMORY;
    }
    asNodeCreate(node ,element);
    currentNode->next = node;

    return AS_SUCCESS;
*/
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

    AS_FOREACH(asNode,it,set){
        copy->current->next = malloc(sizeof(copy->current->next));
        asNodeCreate(copy->current->next,it->data);
        asGetNext(copy);
    }

    return copy;
}