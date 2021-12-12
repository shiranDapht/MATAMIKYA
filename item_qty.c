#include "item_qty.h"
#include <stdbool.h>

struct ItemQty_t{
    unsigned int id_t;
    double amount_t;
};

unsigned int getId(ItemQty item){
    return item->id_t;
}

bool setId(ItemQty item, unsigned int id){
    if(!item){
        return false;
    }
    item->id_t = id;
    return true;
}

double getAmount(ItemQty item){
    return item->amount_t;
}

bool setAmount(ItemQty item, double amount){
    if(!item){
        return false;
    }
    item->amount_t = amount;
    return true;
}