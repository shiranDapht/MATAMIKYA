#include "warehouse_item.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NULL_ITEM_DATA -1

struct ItemData_t{
    char* item_name_t;
    MtmProductData product_data_t;
    MtmCopyData copy_data_t;
    MtmFreeData free_data_t;
    MtmGetProductPrice product_price_t;
    MatamikyaAmountType units_t;
    double income_t;
    double in_storage_t;
};

ItemData createItemData(const char* item_name, MtmProductData product_data, MtmCopyData copy_data,
        MtmFreeData free_data, MtmGetProductPrice product_price,
        MatamikyaAmountType units, double in_storage){
            if(!item_name || !product_data || !copy_data || !free_data || !product_price){
                    return NULL;
                }
            MtmProductData item_data_PD = copy_data(product_data);
            if(!item_data_PD){
                return NULL;
            }
            ItemData item_data = (ItemData)malloc(sizeof( struct ItemData_t));
            if(!item_data){
                free_data(item_data_PD);
                return NULL;
            }
            char* new_name = (char*)malloc(strlen(item_name)+1);
            strcpy(new_name,item_name);
            item_data->item_name_t = new_name;
            item_data->income_t = 0;
            bool pd = setProductData(item_data, item_data_PD);
            bool cd = setCopyData(item_data, copy_data);
            bool fd = setFreeData(item_data, free_data);
            bool pp = setProductPrice(item_data, product_price);
            bool u = setUnits(item_data, units);
            bool is = setItemInStorage(item_data, in_storage);

            if (!pd || !cd || !fd || !pp || !u || !is){
                deleteItemData(item_data);
                return NULL;
            }

            return item_data;
}
        
char* getItemName(ItemData item_data){
    return item_data->item_name_t;
}

void deleteItemData(void* item_data){
    if(item_data){
        getFreeData(item_data)(getProductData(item_data));
        free(((ItemData)item_data)->item_name_t);
        free(item_data);
    }
}

MtmProductData getProductData(ItemData item_data){
    return item_data->product_data_t;
}

bool setProductData(ItemData item_data, MtmProductData product_data){
    if(!product_data){
        return false;
    }
    item_data->product_data_t = product_data;
    return true;
}

MtmCopyData getCopyData(ItemData item_data){
    return item_data->copy_data_t;
}

bool setCopyData(ItemData item_data, MtmCopyData copy_data){
    if(!copy_data){
        return false;
    }
    item_data->copy_data_t = copy_data;
    return true;
}

MtmFreeData getFreeData(ItemData item_data){
    return item_data->free_data_t;
}

bool setFreeData(ItemData item_data, MtmFreeData free_data){
    if(!free_data){
        return false;
    }
    item_data->free_data_t = free_data;
    return true;
}

MtmGetProductPrice getProductPrice(ItemData item_data){
    return item_data->product_price_t;
}

bool setProductPrice(ItemData item_data, MtmGetProductPrice product_price){
    if(!product_price){
        return false;
    }
    item_data->product_price_t = product_price;
    return true;
}

MatamikyaAmountType getUnits(ItemData item_data){
    return item_data->units_t;
}

bool setUnits(ItemData item_data, MatamikyaAmountType units){
    item_data->units_t = units;
    return true;
}

double getItemInStorage(ItemData item_data){
    if(!item_data){
        return NULL_ITEM_DATA;
    }
    return item_data->in_storage_t;
}

bool setItemInStorage(ItemData item_data, double item_in_storage){
    item_data->in_storage_t = item_in_storage;
    return true;
}


double getProductIncome(ItemData item_data){
    return item_data->income_t;
}

void changeProductIncome(ItemData item_data, double item_amount){
    double income = getProductPrice(item_data)(getProductData(item_data), item_amount);
    item_data->income_t = getProductIncome(item_data) + income;
}

