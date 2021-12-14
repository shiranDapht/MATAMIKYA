#include "warehouse_item.h"
#include "cart_item.h"
#include "linked_list.h"
#include "matamikya.h"

#include <stdlib.h>

struct Matamikya_t{
    LinkedList warehouse_t;
    LinkedList orders_t;
};

MatamikyaAmountType amountSelector(const double amount){
    // return (amount != (int)amount) + (amount*2 != (int)(amount*2));
    if(amount != (int)amount){
        if(amount*2 != (int)(amount*2)){
            return MATAMIKYA_ANY_AMOUNT;
        }
        return MATAMIKYA_HALF_INTEGER_AMOUNT;
    }
    return MATAMIKYA_INTEGER_AMOUNT;
}

bool isAmountConsistene(const double amount, const MatamikyaAmountType amountType){
    return amountSelector(amount) <= amountType;
}

Matamikya matamikyaCreate(){
    Matamikya new_matamikya = (Matamikya)malloc(sizeof(struct Matamikya_t));
    if(!new_matamikya){
        return NULL;
    }
    LinkedList warehouse = createLinkedList(deleteItemData);
    if(!warehouse){
        free(new_matamikya);
        return NULL;
    }
    LinkedList orders = createLinkedList(deleteCartItem);
    if(!orders){
        deleteLinkedList(warehouse);
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
    if(!name){
        return false;
    }
    bool num = (name[0]>='0' && name[0]<='9');
    bool A_Z = (name[0]>='A' && name[0]<='Z');
    bool a_z = (name[0]>='a' && name[0]<='z'); 
    return (num || A_Z || a_z);
}



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
    if(isContains(id, matamikya->warehouse_t)){
        return MATAMIKYA_PRODUCT_ALREADY_EXIST;
    }
    if(!isNameValid(name)){
        return MATAMIKYA_INVALID_NAME;
    }
    if(!isAmountConsistene(amount,amountType)){
        return MATAMIKYA_INVALID_AMOUNT;
    }

    bool product_addition_succeed = llAddNode(matamikya->warehouse_t, id, customData, freeData);
    if(!product_addition_succeed){
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    return MATAMIKYA_SUCCESS;
}




MatamikyaResult mtmChangeProductAmount(Matamikya matamikya, const unsigned int id, const double amount){
    if(!matamikya){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    LinkedList warehouse = matamikya->warehouse_t;
    ItemData product_data = getDataById(warehouse, id);
    if(!product_data){
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    double new_amount_in_storage = getItemInStorage(product_data) + amount;
    setItemInStorage(product_data, new_amount_in_storage);
    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmClearProduct(Matamikya matamikya, const unsigned int id){
    if(!matamikya){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    LinkedList orders = matamikya->orders_t;
    LinkedList warehouse = matamikya->warehouse_t;
    if(!isContains(id,warehouse)){
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    
    deleteNodeById(orders, id);
    deleteNodeById(warehouse, id);
    return MATAMIKYA_PRODUCT_NOT_EXIST;
}

unsigned int mtmCreateNewOrder(Matamikya matamikya){
    if(!matamikya){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    LinkedList orders = matamikya->orders_t;
    LinkedList new_cart = createLinkedList(deleteCartItem);
    if(!new_cart){
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    unsigned int new_id = makeNewListNodeId(orders);
    Node new_order = createNode(new_id, new_cart, deleteLinkedList);
    if(!new_order){
        deleteLinkedList(new_cart);
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    bool add_node_succeed = llAddNode(orders, new_id, new_cart, deleteCartItem);
    if(!add_node_succeed){
        deleteLinkedList(new_cart);
        deleteNode(new_order, deleteLinkedList);
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmChangeProductAmountInOrder(Matamikya matamikya, const unsigned int orderId,
                                     const unsigned int productId, const double amount){
    if(!matamikya){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    if(amount == 0){
        return MATAMIKYA_SUCCESS;
    }
    LinkedList orders = matamikya->orders_t;
    LinkedList cart = getDataById(orders, orderId);
    if(!cart){
        if(amount > 0){
            CartItem new_cart_item = createCartItem(productId, amount);
            bool add_item_succeed = llAddNode(cart,makeNewListNodeId(cart),new_cart_item,deleteCartItem);
            if(add_item_succeed){
                return MATAMIKYA_SUCCESS;
            }
            return MATAMIKYA_OUT_OF_MEMORY;
        }
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    CartItem product = getDataById(cart, productId);
    double new_amount = getCartItemAmount(product) + amount;
    if(amount <= 0){
        deleteNodeById(cart,productId);
        return MATAMIKYA_SUCCESS;
    }
    setCartItemAmount(product, new_amount);
    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmShipOrder(Matamikya matamikya, const unsigned int orderId){
    if(!matamikya){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    LinkedList cart = getDataById(matamikya->orders_t, orderId);
    LL_FOREACH(unsigned int, it, cart){
        CartItem current = getData(getCurrent(cart));
        ItemData current_in_warehouse = getDataById(matamikya->warehouse_t, it);
        if(getCartItemAmount(current) > getItemInStorage(current_in_warehouse)){
            return MATAMIKYA_INSUFFICIENT_AMOUNT;
        }
    }

    LL_FOREACH(unsigned int, it, cart){
        ItemData current_in_warehouse = getDataById(matamikya->warehouse_t, it);
        double current_amount = getCartItemAmount(getData(getCurrent(cart)));
        double warehouse_amount = getItemInStorage(current_in_warehouse);
        double new_amount = warehouse_amount - current_amount;
        mtmChangeProductAmount(matamikya, it, new_amount);
        changeProductIncome(current_in_warehouse, current_amount);
    }
    mtmCancelOrder(matamikya, orderId);
    return MATAMIKYA_SUCCESS;
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