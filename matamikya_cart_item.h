#ifndef _MATAMIKYA_CART_ITEM_H_
#define _MATAMIKYA_CART_ITEM_H_
#include <stdbool.h>
typedef struct CartItem_t* CartItem;

/**
 * @brief Create a Item Qty object
 * 
 * @param id 
 * @param amount 
 * @return ItemQty 
 */
CartItem createCartItem(unsigned int id, double amount);

/**
 * @brief 
 * 
 * @param item_qty 
 */
void deleteCartItem(void* item_qty);

/**
 * @brief Get the Id object
 * 
 * @param item 
 * @return unsigned int 
 */
unsigned int getCartItemId(CartItem item);

/**
 * @brief Set the Id object
 * 
 * @param item 
 * @param id 
 * @return true 
 * @return false 
 */
bool setCartItemId(CartItem item, unsigned int id);

/**
 * @brief Get the Amount object
 * 
 * @param item 
 * @return double 
 */
double getCartItemAmount(CartItem item);

/**
 * @brief Set the Amount object
 * 
 * @param item 
 * @param amount 
 * @return true 
 * @return false 
 */
bool setCartItemAmount(CartItem item, double amount);


#endif