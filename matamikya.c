#include "warehouse_item.h"
#include "cart_item.h"
#include "linked_list.h"
#include "matamikya.h"

#include <stdlib.h>

struct Matamikya_t{
    LinkedList warehouse_t;
    LinkedList orders_t;
};

Matamikya matamikyaCreate(){
    Matamikya new_matamikya = (Matamikya)malloc(sizeof(struct Matamikya_t));
    if(!new_matamikya){
        return NULL;
    }
    LinkedList waerhouse = (LinkedList)malloc(sizeof(LinkedList_t));
    if(!waerhouse){
        free(new_matamikya);
        return NULL;
    }
    LinkedList orders = (LinkedList)malloc(sizeof(LinkedList_t));
    if(!orders){
        free(new_matamikya);
        return NULL;
    }
    return new_matamikya;
}

void matamikyaDestroy(Matamikya matamikya){
    if(matamikya){
        if(matamikya->warehouse_t){
            deleteLinkedList(matamikya->warehouse_t);
        }
        if(matamikya->orders_t){
            deleteLinkedList(matamikya->orders_t);
        }
    }
}

MatamikyaResult mtmNewProduct(Matamikya matamikya, const unsigned int id, const char *name,
                              const double amount, const MatamikyaAmountType amountType,
                              const MtmProductData customData, MtmCopyData copyData,
                              MtmFreeData freeData, MtmGetProductPrice prodPrice){
                                
                                if(!matamikya  || !name  || !amountType  || !customData  || !copyData  
                                        || !freeData  || !prodPrice){
                                            
                                }
                              }

MatamikyaResult mtmChangeProductAmount(Matamikya matamikya, const unsigned int id, const double amount){

}

MatamikyaResult mtmClearProduct(Matamikya matamikya, const unsigned int id){

}

unsigned int mtmCreateNewOrder(Matamikya matamikya){

}

MatamikyaResult mtmChangeProductAmountInOrder(Matamikya, const unsigned int orderId,
                                     const unsigned int productId, const double amount){

                                     }

MatamikyaResult mtmShipOrder(Matamikya matamikya, const unsigned int orderId){

}   

MatamikyaResult mtmCancelOrder(Matamikya matamikya, const unsigned int orderId){

}

MatamikyaResult mtmPrintInventory(Matamikya matamikya, FILE *output){

}

MatamikyaResult mtmPrintOrder(Matamikya matamikya, const unsigned int orderId, FILE *output){

}

MatamikyaResult mtmPrintBestSelling(Matamikya matamikya, FILE *output){
    if(!matamikya || !output){
        return MATAMIKYA_NULL_ARGUMENT;
    }

    double best_selling = 0;

    
}