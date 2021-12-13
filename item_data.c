#include "matamikya_print.h"
#include "item_data.h"

#include<stdlib.h>
#include <stdbool.h>

#define NULL_ITEM_DATA
struct ItemData_t{
    MtmProductData product_data_t;
    MtmCopyData copy_data_t;
    MtmFreeData free_data_t;
    MtmGetProductPrice product_price_t;
    MatamikyaAmountType units_t;
    double item_sold_t;
    double item_in_storage;
};

ItemData createItemData(MtmProductData product_data, MtmCopyData copy_data,
        MtmFreeData free_data, MtmGetProductPrice product_price,
        MatamikyaAmountType units, double item_sold){
            if(!product_data || !copy_data || !free_data || !product_price 
                || !units){
                    return NULL;
                }
            
            ItemData item_data = (ItemData)malloc(sizeof( struct ItemData_t));
            if(!item_data){
                return NULL;
            }

            bool pd = setProductData(item_data, product_data);
            bool cd = setCopyData(item_data, copy_data);
            bool fd = setFreeData(item_data, free_data);
            bool pp = setProductPrice(item_data, product_price);
            bool u = setUnits(item_data, units);
            bool is = setItemSold(item_data, item_sold);

            if (!pd || !cd || !fd || !pp || !u || !is){
                deleteItemData(item_data);
                return NULL;
            }

            return item_data;
        }

void deleteItemData(ItemData item_data){
    if(item_data){
        getFreeData(item_data)(getProductData(item_data));
        free(item_data);
    }
}

MtmProductData getProductData(ItemData item_data){
    return item_data->product_data_t;
}

bool setProductData(ItemData item_data, MtmGetProductPrice product_data){
    if(!item_data || !product_data){
        return false;
    }
    item_data->product_data_t = product_data;
    return true;
}

MtmCopyData getCopyData(ItemData item_data){
    return item_data->copy_data_t;
}

bool setCopyData(ItemData item_data, MtmCopyData copy_data){
    if(!item_data || !copy_data){
        return false;
    }
    item_data->copy_data_t = copy_data;
    return true;
}

MtmFreeData getFreeData(ItemData item_data){
    return item_data->free_data_t;
}

bool setFreeData(ItemData item_data, MtmFreeData free_data){
    if(!item_data || !free_data){
        return false;
    }
    item_data->free_data_t = free_data;
    return true;
}

MtmGetProductPrice getProductPrice(ItemData item_data){
    return item_data->product_price_t;
}

bool setProductPrice(ItemData item_data, MtmGetProductPrice product_price){
    if(!item_data || !product_price){
        return false;
    }
    item_data->product_price_t = product_price;
    return true;
}

MatamikyaAmountType getUnits(ItemData item_data){
    return item_data->units_t;
}

bool setUnits(ItemData item_data, MatamikyaAmountType units){
    if(!item_data){
        return false;
    }
    item_data->units_t = units;
    return true;
}

double getItemSold(ItemData item_data){
    if(!item_data){
        return NULL_ITEM_DATA;
    }
    return item_data->item_sold_t;
}

bool setItemSold(ItemData item_data, double item_sold){
    if(!item_data){
        return false;
    }
    item_data->item_sold_t = item_sold;
    return true;
}

double getProductIncome(ItemData item_data){
    double items_sold = getItemSold(item_data);
    MtmProductData item_product_data = getProductData(item_data);
    return getProductPrice(item_data)(item_product_data,items_sold);
}

double getInStoreg(ItemData item_data){
    if(!item_data){
        return NULL_ITEM_DATA;
    }
    return item_data->item_in_storage;
}

bool setInStoreg(ItemData item_data, double amount){
    if(!item_data){
        return false;
    }
    item_data->item_in_storage = amount;
    return true;
}
