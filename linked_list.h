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
LinkedList createLinkedList(deleteNodeDataMethod deleteData);

/**
 * @brief destroy list completely
 * 
 * @param list 
 */
void deleteLinkedList(LinkedList list);


/**
 * @brief Get the Head object
 * 
 * @param list 
 * @return Node 
 */
Node getHead(LinkedList list);

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
 * @brief 
 * 
 * @param list 
 * @return unsigned int 
 */
unsigned int llGetFirst(LinkedList list);

/**
 * @brief 
 * 
 * @param list 
 * @return unsigned int 
 */
unsigned int llGetNext(LinkedList list);

/**
 * @brief 
 * 
 * @param list 
 * @param id 
 * @param data 
 * @param deleteData 
 * @return true 
 * @return false 
 */
bool llAddNode(LinkedList list, unsigned int id , NodeData data, deleteNodeDataMethod deleteData);

deleteNodeDataMethod getDeleteDataMethod(LinkedList list);

/*!
* Macro for iterating over a set.
* Declares a new iterator for the loop.
*/
#define LL_FOREACH(type,iterator,list) \
  for(type iterator = setGetFirst(list) ; \
    iterator ;\
    iterator = setGetNext(list))

#endif