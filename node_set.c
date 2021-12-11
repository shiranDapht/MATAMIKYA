#include "node_set.h"

struct node_t{
    char* itemName;
    double amount;
    Node next; 
};

struct AmountSet_t{
    Node head;
    Node current;
};

char* copyItemName(const char* itemName){
    if(!itemName){
        
    }
}

int compareItemNames(const char* itemName1, const char* itemName2);

void freeItemName(char* itemName);

char* getItemName(Node node);

void setItemName(Node node, char* itemName);

double getAmount(Node node);

void setAmount(Node node, double amount);

Node getNext(Node node);

void setNext(Node node ,Node next);

Node getHead(AmountSet as);

void setHead(AmountSet as, Node node);

Node getCurrent(AmountSet as);

void setCurrent(AmountSet as, Node current);