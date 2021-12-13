#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "generic_node.h"

typedef struct LinkedList_t* LinkedList;

/**
 * @brief Create a Linked List object
 * 
 * @param head 
 * @param current 
 * @return LinkedList 
 */
LinkedList createLinkedList(Node head, Node current);

void deleteLinkedList(LinkedList list);


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
/**
 * @brief Resetting iterator
 * 
 * @param list 
 * @return NodeData 
 */
NodeData llGetFirst(LinkedList list);

/**
 * @brief Advances current one step
 * 
 * @param list 
 * @return NodeData 
 */
NodeData llGetNext(LinkedList list);

/**
 * @brief 
 * 
 * @param list 
 * @param node 
 * @return true 
 * @return false 
 */
bool llAddNode(LinkedList list, Node node);

/*!
* Macro for iterating over a set.
* Declares a new iterator for the loop.
*/
#define LL_FOREACH(type,iterator,list) \
  for(type iterator = setGetFirst(list) ; \
    iterator ;\
    iterator = setGetNext(list))

#endif