#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "generic_node.h"

typedef struct LinkedList_t* LinkedList;


Node getHead(LinkedList list);
bool setHead(LinkedList list, Node head);

Node getCurrent(LinkedList list);
bool setCurrent(LinkedList list, Node current);


#endif