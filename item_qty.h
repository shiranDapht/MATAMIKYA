#ifndef ITEM_QTY_H_
#define ITEM_QTY_H_
#include <stdbool.h>
typedef struct ItemQty_t* ItemQty;

/**
 * @brief Create a Item Qty object
 * 
 * @param id 
 * @param amount 
 * @return ItemQty 
 */
ItemQty createItemQty(unsigned int id, double amount);

/**
 * @brief 
 * 
 * @param item_qty 
 */
void deleteItemQty(ItemQty item_qty);

/**
 * @brief Get the Id object
 * 
 * @param item 
 * @return unsigned int 
 */
unsigned int getQtyId(ItemQty item);

/**
 * @brief Set the Id object
 * 
 * @param item 
 * @param id 
 * @return true 
 * @return false 
 */
bool setQtyId(ItemQty item, unsigned int id);

/**
 * @brief Get the Amount object
 * 
 * @param item 
 * @return double 
 */
double getQtyAmount(ItemQty item);

/**
 * @brief Set the Amount object
 * 
 * @param item 
 * @param amount 
 * @return true 
 * @return false 
 */
bool setQtyAmount(ItemQty item, double amount);


#endif