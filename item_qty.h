#ifndef ITEM_QTY_H_
#define ITEM_QTY_H_
#include <stdbool.h>
typedef struct ItemQty_t* ItemQty;

unsigned int getId(ItemQty item);
bool setId(ItemQty item, unsigned int id);

double getAmount(ItemQty item);
bool setAmount(ItemQty item, double amount);


#endif