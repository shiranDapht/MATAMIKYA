#ifndef _NODE_SET_H_
#define _NODE_SET_H_

#include "amount_set_str.h"

#include <stdlib.h>
#include <string.h>

#define ERROR_AMOUNT -1

typedef struct node_t* Node;

/**
 * @brief make a copy of item name
 * 
 * @param itemName 
 * @return char* 
 */
char* copyItemName(const char* itemName);

/**
 * @brief compare two item with strcmp function
 * Worrning! make sure argument are not null
 * 
 * @param itemName1 
 * @param itemName2 
 * @return int 
 */
int compareItemNames(const char* itemName1, const char* itemName2);

/**
 * @brief free item name
 * 
 * @param itemName 
 */
void freeItemName(char* itemName);

/**
 * @brief Create a Node object
 * 
 * @param itemName 
 * @param amount 
 * @return Node 
 */
Node createNode(char* itemName, double amount);

/**
 * @brief delete node struct include all members
 * 
 * @param node 
 */
void deleteNode(Node node);

/**
 * @brief Get the Item Name object
 * 
 * @param node 
 * @return char* 
 */
char* getItemName(Node node);

/**
 * @brief Set the Item Name object
 * 
 * @param node 
 * @param itemName 
 * @return true 
 * @return false 
 */
bool setItemName(Node node, char* itemName);

/**
 * @brief Get the Amount object
 * 
 * @param node 
 * @return double 
 */
double getAmount(Node node);

/**
 * @brief Set the Amount object
 * 
 * @param node 
 * @param amount 
 * @return true 
 * @return false 
 */
bool setAmount(Node node, double amount);

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
bool setNext(Node node ,Node next);

/**
 * @brief Get the Head object
 * 
 * @param as 
 * @return Node 
 */
Node getHead(AmountSet as);

/**
 * @brief Get the Current object
 * 
 * @param as 
 * @return Node 
 */
Node getCurrent(AmountSet as);

/**
 * @brief Set the Current object
 * 
 * @param as 
 * @param current 
 * @return true 
 * @return false 
 */
bool setCurrent(AmountSet as, Node current);

AmountSet createAmountSet();

#endif