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
    LinkedList waerhouse = (LinkedList)malloc(sizeof(waerhouse));
    if(!waerhouse){
        free(new_matamikya);
        return NULL;
    }
    LinkedList orders = (LinkedList)malloc(sizeof(orders));
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

bool isNameValid(const char* name){
    bool num = (name[0]>='0' && name[0]<='9'), A_Z = (name[0]>='A' && name[0]<='Z'),
        a_z = (name[0]>='a' && name[0]<='z'); 
    return (num || A_Z || a_z);
}

bool isAmountConsistene(const double amount, const MatamikyaAmountType amountType);

bool isContains(unsigned int id, LinkedList list){
    if(!list){
        return false;
    }
    LL_FOREACH(unsigned int, it, list){
        if(it == id){
            return true;
        }
    }
    return false;
}

MatamikyaResult mtmNewProduct(Matamikya matamikya, const unsigned int id, const char *name,
                              const double amount, const MatamikyaAmountType amountType,
                              const MtmProductData customData, MtmCopyData copyData,
                              MtmFreeData freeData, MtmGetProductPrice prodPrice){
                                
                                if(!matamikya  || !name  || !amountType  || !customData  || !copyData  
                                        || !freeData  || !prodPrice){
                                       return MATAMIKYA_NULL_ARGUMENT;     
                                }
                                if(isContains(id, matamikya->orders_t)){
                                    return MATAMIKYA_PRODUCT_ALREADY_EXIST;
                                }
                                if(!isNameValid(name)){
                                    return MATAMIKYA_INVALID_NAME;
                                }
                                //TODO: amunt type func by matamikya h file 
                                if(!isAmountConsistene(amount,amountType)){
                                    return MATAMIKYA_INVALID_AMOUNT;
                                }

                                if(!llAddNode(matamikya->warehouse_t, id, customData, freeData)){
                                    return MATAMIKYA_OUT_OF_MEMORY;
                                }
                                return MATAMIKYA_SUCCESS;
                              }


MatamikyaAmountType amountSelector(const double amount);

bool isAmountValid(MatamikyaAmountType amount_in_warehouse, MatamikyaAmountType amount);

MatamikyaResult mtmChangeProductAmount(Matamikya matamikya, const unsigned int id, const double amount){
    if(!matamikya){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    LinkedList orders = matamikya->orders_t;
    Node change_amount_node = getHead(orders);
    if(!isContains(id, orders)){
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    LL_FOREACH(unsigned int, it, orders){
        if(it == id){
            change_amount_node = getCurrent(orders);
            //TODO: amountSelector func
            //TODO: isAmountValid func
            MatamikyaAmountType amount_in_warehouse = getUnits(getData(change_amount_node));
            MatamikyaAmountType units = amountSelector(amount);
            if(units == amount_in_warehouse){
                double new_amount = getInStoreg(getData(change_amount_node));
                if(new_amount += amount > 0){
                    setInStoreg(getData(change_amount_node) ,new_amount);
                    return MATAMIKYA_SUCCESS;
                }
                return MATAMIKYA_INSUFFICIENT_AMOUNT;
            }
            return MATAMIKYA_INVALID_AMOUNT;
        }
    }
}

MatamikyaResult mtmClearProduct(Matamikya matamikya, const unsigned int id){
    if(!matamikya){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    LinkedList orders = matamikya->orders_t;
    if(!isContains(id, orders)){
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    LL_FOREACH(unsigned int , it, orders){
        if(id == it){
            deleteNode(getCurrent(orders), getDeleteDataMethod(orders));
            return MATAMIKYA_SUCCESS;
        }
    }
}

unsigned int mtmCreateNewOrder(Matamikya matamikya){

}

MatamikyaResult mtmChangeProductAmountInOrder(Matamikya matamikya, const unsigned int orderId,
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