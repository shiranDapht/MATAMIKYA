#ifndef ITEM_QTY_H_
#define ITEM_QTY_H_
#include <stdbool.h>
typedef struct ItemQty_t* ItemQty;

/**
 * @brief Get the Id object
 * 
 * @param item 
 * @return unsigned int 
 */
unsigned int getId(ItemQty item);

/**
 * @brief Set the Id object
 * 
 * @param item 
 * @param id 
 * @return true 
 * @return false 
 */
bool setId(ItemQty item, unsigned int id);

/**
 * @brief Get the Amount object
 * 
 * @param item 
 * @return double 
 */
double getAmount(ItemQty item);

/**
 * @brief Set the Amount object
 * 
 * @param item 
 * @param amount 
 * @return true 
 * @return false 
 */
bool setAmount(ItemQty item, double amount);


#endif