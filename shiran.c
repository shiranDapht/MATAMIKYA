#include "warehouse_item.h"
#include "cart_item.h"
#include "linked_list.h"
#include "matamikya.h"

struct Matamikya_t{
    LinkedList stock_t;
    LinkedList orders_t;
};

MatamikyaResult mtmPrintBestSelling(Matamikya matamikya, FILE *output){
    if(!matamikya || !output){
        return MATAMIKYA_NULL_ARGUMENT;
    }

    double best_selling = 0;

    
}