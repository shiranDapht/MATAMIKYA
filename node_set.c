#include "node_set.h"
#include "amount_set_str.h"
struct node_t{
    char* itemName_t;
    double amount_t;
    Node next_t; 
};

struct AmountSet_t{
    Node head_t;
    Node current_t;
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

int compareItemNames(const char* itemName1, const char* itemName2){
    return strcmp(itemName1, itemName2);
}

void freeItemName(char* itemName){
    if(!itemName){
        return;
    }
    free(itemName);
}

Node createNode(const char* itemName, double amount){
    if(!itemName){
        return NULL;
    }
    Node newNode = (Node)malloc(sizeof(struct node_t));
    if(!newNode){
        return NULL;
    }
    //Init members of Node
    bool b = setAmount(newNode, amount);
    newNode->itemName_t = copyItemName(itemName);
    setNext(newNode, NULL);
    if(!b || !newNode->itemName_t){
        deleteNode(newNode);
        return NULL;
    }
    return newNode;
}

void deleteNode(Node node){
    if(!node){
        return;
    }
    freeItemName(getItemName(node));
    free(node);
}

char* getItemName(Node node){
    if(!node){
        return NULL;
    }
    return node->itemName_t;
}

bool setItemName(Node node, char* itemName){
    if(!node || !itemName){
        return false;
    }
    freeItemName(node->itemName_t);
    node->itemName_t = copyItemName(itemName);
    return true;
}

double getAmount(Node node){
    if(!node){
        return ERROR_AMOUNT;
    }
    return node->amount_t;
}

bool setAmount(Node node, double amount){
    if(!node || amount < 0){
        return false;
    }
    node->amount_t = amount;
    return true;
}

Node getNext(Node node){
    if(!node){
        return NULL;
    }
    return node->next_t;
}

bool setNext(Node node ,Node next){
    if(!node){
        return false;
    }
    node->next_t = next;
    return true;
}

Node getHead(AmountSet as){
    if(!as){
        return NULL;
    }
    return as->head_t;
}

Node getCurrent(AmountSet as){
    if(!as){
        return NULL;
    }
    return as->current_t;
}

bool setCurrent(AmountSet as, Node current){
    if(!as || !current){
        return false;
    }
    as->current_t = current;
    return true;
}

AmountSet createAmountSet(){
    AmountSet set = (AmountSet)malloc(sizeof(struct AmountSet_t));
    if(!set){
        return NULL;
    }
    set->head_t = (Node)malloc(sizeof(struct node_t));
    if(!set->head_t){
        asDestroy(set);
        return NULL;
    }
    set->head_t->next_t = NULL;
    set->current_t = NULL;
    return set;
}