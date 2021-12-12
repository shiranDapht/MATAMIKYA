#ifndef ITEM_DATA_H_
#define ITEM_DATA_H_

#include "matamikya.h"

typedef struct ItemData_t* ItemData;

MtmProductData getProductData(ItemData item_data);
bool setProductData(ItemData item_data, MtmGetProductPrice product_data);

MtmCopyData getCopyData(ItemData item_data);
bool setCopyData(ItemData item_data, MtmCopyData copy_data);

MtmFreeData getFreeData(ItemData item_data);
bool setFreeData(ItemData item_data, MtmFreeData free_data);

MtmGetProductPrice getProductPrice(ItemData item_data);
bool setProductPrice(ItemData item_data, MtmGetProductPrice product_price);

MatamikyaAmountType getUnits(ItemData item_data);
bool setUnits(ItemData item_data, MatamikyaAmountType units);

double getItemSold(ItemData item_data);
bool setItemSold(ItemData item_data, double item_sold);

double getProductAmount(ItemData item_data);
bool setProductAmount(ItemData item_data, double product_amount);


#endif