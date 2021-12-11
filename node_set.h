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

bool setItemName(Node node, char* itemName);

double getAmount(Node node);

bool setAmount(Node node, double amount);

Node getNext(Node node);

bool setNext(Node node ,Node next);

Node getHead(AmountSet as);

bool setHead(AmountSet as, Node head);

Node getCurrent(AmountSet as);

bool setCurrent(AmountSet as, Node current);

#endif



