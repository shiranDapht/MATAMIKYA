#include "amount_set.h"
#include <stdlib.h>

#define NULL_POINTER -1

typedef struct asNode_t *asNode;

// Node struct
struct asNode_t{
    ASElement data;
    double amount;
    asNode next;
};

// Node destroyer
void asNodeDelete(AmountSet set, asNode node){
    if(!set || !node){
        return;
    }
    set->freeElement(node->data);
    free(node);
};

void addNode(asNode node ,ASElement element){
    node->amount = 0;
    node->data = element;
};

// AmountSet implementation
struct AmountSet_t{
    CopyASElement copyElement;
    FreeASElement freeElement;
    CompareASElements compareElements;
    asNode head;
    asNode current;
};

// Return first real element (after dummy)
ASElement asGetFirst(AmountSet set){
    return set->head->next;   
};

// Return next element of current for iteration
ASElement asGetNext(AmountSet set){
    return set->current->next;
};

// Constructor for AmountSet
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

// Free all nodes of set except the dummy
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

// Destructor of AmountSet
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

    if(compareElementLoop(set, element) != NULL){
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

//use only if argument are not null
asNode compareElementLoop(AmountSet set, ASElement element){
    AS_FOREACH(asNode, it, set){
        if(set->compareElements(it->data, element)){
            return it;
        }
    }
};

int asGetSize(AmountSet set){
    if(!set){
        return NULL_POINTER;
    }

    int size = 0;

    asNode currentNode = set->head->next;

    while (currentNode)
    {
        size++;
        currentNode = currentNode->next;
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

    asNode node = compareElementLoop(set, element);
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

    asNode currentNode = set->head->next;
    asNode previousNode = set->head;

    while (currentNode){
        if(set->compareElements(currentNode,element) < 0){
            asNode node = malloc(sizeof(node));
            if(!node){
                //Ask Adam
            }
            addNode(node ,element))
            previousNode->next = node;
            node->next = currentNode;

            return AS_SUCCESS;
        }

        previousNode = previousNode->next;
        currentNode = currentNode->next;
    }

    asNode node = malloc(sizeof(node));
    if(!node){
        //Ask Adam
    }
    addNode(node ,element);
    currentNode->next = node;

    return AS_SUCCESS;

};

AmountSetResult asChangeAmount(AmountSet set, ASElement element, const double amount){
    if(!set || !element || !amount){
            return AS_NULL_ARGUMENT;
        }

        if(asContains(set,element) == false){
            return AS_ITEM_DOES_NOT_EXIST;
        }

        asNode node = compareElementLoop(set, element);
        
        double val = node->amount + amount;
        if(val < 0 ){
            return AS_INSUFFICIENT_AMOUNT;
        }

        node->amount += amount;

        return AS_SUCCESS;
};