#include "amount_set.h"
#include "asNode.h"
#include <stdlib.h>


// asNode constructor, returns pointer to new asNode, NULL if node or element is NULL.
void asNodeCreate(asNode node ,ASElement element){
    if(!node || !element){
        return;
    }
    node->next = NULL;
    node->amount = 0;
    node->data = element;
    return;
};
