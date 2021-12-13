#ifndef ITEM_DATA_H_
#define ITEM_DATA_H_

#include "matamikya.h"

typedef struct ItemData_t* ItemData;

/**
 * @brief Create a Item Data object
 * 
 * @param product_data 
 * @param copy_data 
 * @param free_data 
 * @param product_price 
 * @param units 
 * @param item_sold 
 * @return ItemData 
 */
ItemData createItemData(MtmProductData product_data, MtmCopyData copy_data,
        MtmFreeData free_data, MtmGetProductPrice product_price,
        MatamikyaAmountType units, double item_sold);

/**
 * @brief 
 * 
 * @param item_data 
 */
void deleteItemData(ItemData item_data);

/**
 * @brief Get the Product Data object
 * 
 * @param item_data 
 * @return MtmProductData 
 */
MtmProductData getProductData(ItemData item_data);

/**
 * @brief Set the Product Data object
 * 
 * @param item_data 
 * @param product_data 
 * @return true 
 * @return false 
 */
bool setProductData(ItemData item_data, MtmGetProductPrice product_data);

/**
 * @brief Get the Copy Data object
 * 
 * @param item_data 
 * @return MtmCopyData 
 */
MtmCopyData getCopyData(ItemData item_data);

/**
 * @brief Set the Copy Data object
 * 
 * @param item_data 
 * @param copy_data 
 * @return true 
 * @return false 
 */
bool setCopyData(ItemData item_data, MtmCopyData copy_data);

/**
 * @brief Get the Free Data object
 * 
 * @param item_data 
 * @return MtmFreeData 
 */
MtmFreeData getFreeData(ItemData item_data);

/**
 * @brief Set the Free Data object
 * 
 * @param item_data 
 * @param free_data 
 * @return true 
 * @return false 
 */
bool setFreeData(ItemData item_data, MtmFreeData free_data);

/**
 * @brief Get the Product Price object
 * 
 * @param item_data 
 * @return MtmGetProductPrice 
 */
MtmGetProductPrice getProductPrice(ItemData item_data);

/**
 * @brief Set the Product Price object
 * 
 * @param item_data 
 * @param product_price 
 * @return true 
 * @return false 
 */
bool setProductPrice(ItemData item_data, MtmGetProductPrice product_price);

/**
 * @brief Get the Units object
 * 
 * @param item_data 
 * @return MatamikyaAmountType 
 */
MatamikyaAmountType getUnits(ItemData item_data);

/**
 * @brief Set the Units object
 * 
 * @param item_data 
 * @param units 
 * @return true 
 * @return false 
 */
bool setUnits(ItemData item_data, MatamikyaAmountType units);

/**
 * @brief Get the Item Sold object
 * 
 * @param item_data 
 * @return double 
 */
double getItemSold(ItemData item_data);

/**
 * @brief Set the Item Sold object
 * 
 * @param item_data 
 * @param item_sold 
 * @return true 
 * @return false 
 */
bool setItemSold(ItemData item_data, double item_sold);

/**
 * @brief Get the Product Amount object
 * 
 * @param item_data 
 * @return double 
 */
double getProductIncome(ItemData item_data);

/**
 * @brief Get the In Storeg object
 * 
 * @param item_data 
 * @return double 
 */
double getInStoreg(ItemData item_data);

/**
 * @brief Set the In Storeg object
 * 
 * @param item_data 
 * @param amount 
 * @return true 
 * @return false 
 */
bool setInStoreg(ItemData item_data, double amount);

#endif