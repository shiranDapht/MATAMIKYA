#include "warehouse_item.h"
#include "cart_item.h"
#include "linked_list.h"
#include "matamikya.h"

struct Matamikya_t{
    LinkedList stock_t;
    LinkedList orders_t;
};

Matamikya matamikyaCreate(){
    Matamikya new_matamikya = (Matamikya)malloc(sizeof(struct Matamikya_t));
    if(!new_matamikya){
        return NULL;
    }
    LinkedList new_stock = (LinkedList)malloc()
}