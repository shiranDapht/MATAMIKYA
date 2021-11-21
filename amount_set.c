#include "amount_set.h"
#include <stdlib.h>


typedef struct asNode_t *asNode;

// Node struct
struct asNode_t{
    ASElement data;
    int amount;
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

    AS_FOREACH(asNode, it, set){
        if(set->compareElements(it->data, element)){
            return true;
        }
    }

    return false;
};