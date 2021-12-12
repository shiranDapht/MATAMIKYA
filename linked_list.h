#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "generic_node.h"

typedef struct LinkedList_t* LinkedList;

/**
 * @brief Get the Head object
 * 
 * @param list 
 * @return Node 
 */
Node getHead(LinkedList list);

/**
 * @brief Set the Head object
 * 
 * @param list 
 * @param head 
 * @return true 
 * @return false 
 */
bool setHead(LinkedList list, Node head);

/**
 * @brief Get the Current object
 * 
 * @param list 
 * @return Node 
 */
Node getCurrent(LinkedList list);

/**
 * @brief Set the Current object
 * 
 * @param list 
 * @param current 
 * @return true 
 * @return false 
 */
bool setCurrent(LinkedList list, Node current);


#endif