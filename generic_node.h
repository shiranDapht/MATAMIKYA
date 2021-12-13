#ifndef GENERIC_NODE_H_
#define GENERIC_NODE_H_

#include <stdbool.h>

typedef struct Node_t* Node;

typedef void* NodeData;

typedef void (*deleteMethod)(NodeData);

/**
 * @brief Create a Node object
 * 
 * @param id 
 * @param data 
 * @param next could be NULL
 * @return Node 
 */
Node createNode(unsigned int id, NodeData data, deleteMethod deleteData, Node next);

/**
 * @brief free node
 * 
 * @param node 
 */
void deleteNode(Node node);

/**
 * @brief Get Delete Data Method function pointer
 * 
 * @param node 
 * @return deleteMethod 
 */
deleteMethod getDeleteDataMethod(Node node);

/**
 * @brief Get the Id object
 * 
 * @param node 
 * @return unsigned int 
 */
unsigned int getId(Node node);

/**
 * @brief Set the Id object
 * 
 * @param node 
 * @param id 
 * @return true 
 * @return false 
 */
bool setId(Node node, unsigned int id);

/**
 * @brief Get the Data object
 * 
 * @param node 
 * @return void* 
 */
void* getData(Node node);

/**
 * @brief Set the Data object
 * 
 * @param node 
 * @param data 
 * @return true 
 * @return false 
 */
bool setData(Node node, void* data);

/**
 * @brief Get the Next object
 * 
 * @param node 
 * @return Node 
 */
Node getNext(Node node);

/**
 * @brief Set the Next object
 * 
 * @param node 
 * @param next 
 * @return true 
 * @return false 
 */
bool setNext(Node node, Node next);


#endif
