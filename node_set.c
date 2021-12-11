#include "node_set.h"


struct node_t{
    char* itemName_t;
    double amount_t;
    Node next_t; 
};

struct AmountSet_t{
    Node head;
    Node current;
};

char* copyItemName(const char* itemName){
    if(!itemName){
        return NULL;
    }
    char* itemNameCopy = (char*)malloc(strlen(itemName)+1);
    if(!itemNameCopy){
        return NULL;
    }
    strcpy(itemNameCopy, itemName);
    return itemNameCopy;
}


/**
 * @brief make sure to check null argument before use
 * 
 * @param itemName1 
 * @param itemName2 
 * @return int 
 */
int compareItemNames(const char* itemName1, const char* itemName2){
    return strcmp(itemName1, itemName2);
}

void freeItemName(char* itemName){
    if(!itemName){
        return;
    }
    free(itemName);
}

Node createNode(char* itemName, double amount){

}

void deleteNode(Node node){
    
}

char* getItemName(Node node){
    if(!node){
        return NULL;
    }
    return node->itemName_t;
}

void setItemName(Node node, char* itemName){
    if(!node || !itemName){
        return;
    }
    freeItemName(node->itemName_t);
    node->itemName_t = copyItemName(itemName);
}

double getAmount(Node node){
    if(!node){
        return ERROR_AMOUNT;
    }
    return node->amount_t;
}

void setAmount(Node node, double amount){
    if(!node){
        return;
    }

}

Node getNext(Node node);

void setNext(Node node ,Node next);

Node getHead(AmountSet as);

void setHead(AmountSet as, Node node);

Node getCurrent(AmountSet as);

void setCurrent(AmountSet as, Node current);