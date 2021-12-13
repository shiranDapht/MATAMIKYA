#include "item_qty.h"
#include <stdbool.h>

struct ItemQty_t{
    unsigned int id_t;
    double amount_t;
};


ItemQty createItemQty(unsigned int id, double amount){
    ItemQty new_item_qty = (ItemQty)malloc(sizeof(struct ItemQty_t));
    setQtyId(new_item_qty,id);
    setQtyAmount(new_item_qty,amount);
    return new_item_qty;
}

void deleteItemQty(ItemQty item_qty){
    if(item_qty){
        free(item_qty);
    }
}


unsigned int getQtyId(ItemQty item){
    return item->id_t;
}

bool setQtyId(ItemQty item, unsigned int id){
    if(!item){
        return false;
    }
    item->id_t = id;
    return true;
}

double getQtyAmount(ItemQty item){
    return item->amount_t;
}

bool setQtyAmount(ItemQty item, double amount){
    if(!item){
        return false;
    }
    item->amount_t = amount;
    return true;
}