#ifndef _NODE_SET_H_
#define _NODE_SET_H_

#include "amount_set_str.h"

#include <stdlib.h>
#include <string.h>

#define ERROR_AMOUNT -1

typedef struct node_t* Node;

char* copyItemName(const char* itemName);

int compareItemNames(const char* itemName1, const char* itemName2);

void freeItemName(char* itemName);

Node createNode(char* itemName, double amount);

void deleteNode(Node node);

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

#endif



