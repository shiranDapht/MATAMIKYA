#ifndef GENERIC_NODE_H_
#define GENERIC_NODE_H_

#include <stdbool.h>
typedef struct Node_t* Node;

unsigned int getId(Node node);
bool setId(Node node, unsigned int id);

void* getData(Node node);
bool setData(Node node, void* data);

Node getNext(Node node);
bool setNext(Node node, Node next);


#endif
