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
