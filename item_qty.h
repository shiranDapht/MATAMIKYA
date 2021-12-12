#ifndef ITEM_QTY_H_
#define ITEM_QTY_H_

typedef struct ItemQty_t* ItemQty;

unsigned int getId(ItemQty item);
bool setId(ItemQty item, unsigned int id);


#endif