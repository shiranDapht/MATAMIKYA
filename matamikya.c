#include "warehouse_item.h"
#include "cart_item.h"
#include "linked_list.h"
#include "matamikya.h"
#include "matamikya_print.h"

#include <stdlib.h>

struct Matamikya_t{
    LinkedList warehouse_t;
    LinkedList orders_t;
};

MatamikyaAmountType amountSelector(const double amount){
    if(amount != (int)amount){
        if(amount*2 != (int)(amount*2)){
            return MATAMIKYA_ANY_AMOUNT;
        }
        return MATAMIKYA_HALF_INTEGER_AMOUNT;
    }
    return MATAMIKYA_INTEGER_AMOUNT;
}

bool isAmountContains(const double amount,  MatamikyaAmountType amountType){
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
    LinkedList orders = createLinkedList(deleteLinkedList);
    if(!orders){
        deleteLinkedList(warehouse);
        free(new_matamikya);
        return NULL;
    }
    new_matamikya->warehouse_t = warehouse;
    new_matamikya->orders_t = orders;
    return new_matamikya;
}

void matamikyaDestroy(Matamikya matamikya){
    if(matamikya){
        deleteLinkedList(matamikya->warehouse_t);
        deleteLinkedList(matamikya->orders_t);
    }
    free(matamikya);
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

    if(!matamikya  || !name  || !customData  || !copyData  
            || !freeData  || !prodPrice){
            return MATAMIKYA_NULL_ARGUMENT;     
    }
    if(isContains(id, matamikya->warehouse_t)){
        return MATAMIKYA_PRODUCT_ALREADY_EXIST;
    }
    if(!isNameValid(name)){
        return MATAMIKYA_INVALID_NAME;
    }
    if(!isAmountContains(amount,amountType)){
        return MATAMIKYA_INVALID_AMOUNT;
    }
    LinkedList warehouse = matamikya->warehouse_t;
    ItemData new_product_data = createItemData(name, customData, copyData, freeData, prodPrice, amountType, amount);
    if(!new_product_data){
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    bool product_addition_succeed = llAddNode(warehouse, id, new_product_data, deleteItemData);
    if(!product_addition_succeed){
        deleteItemData(new_product_data);
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmChangeProductAmount(Matamikya matamikya, const unsigned int id, const double amount){
    if(!matamikya){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    
    LinkedList warehouse = matamikya->warehouse_t;
    if(!isAmountContains(amount,getUnits(getDataById(warehouse,id)))){
        return MATAMIKYA_INVALID_AMOUNT;
    }
    ItemData product_data = getDataById(warehouse, id);
    if(!product_data){
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    double new_amount_in_storage = getItemInStorage(product_data) + amount;
    if(new_amount_in_storage < 0){
        return MATAMIKYA_INSUFFICIENT_AMOUNT;
    }
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
    LL_FOREACH(unsigned int, it, orders){
        deleteNodeById(getData(getCurrent(orders)), id);
    }
    deleteNodeById(warehouse, id);
    return MATAMIKYA_SUCCESS;
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
    bool add_cart = llAddNode(orders, new_id, new_cart, deleteLinkedList);
    if(!add_cart){
        deleteLinkedList(new_cart);
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    return new_id;
}

MatamikyaResult mtmChangeProductAmountInOrder(Matamikya matamikya, const unsigned int orderId,
                                     const unsigned int productId, const double amount){
    if(!matamikya){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    if(!isContains(orderId, matamikya->orders_t)){
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    if(!isContains(productId,matamikya->warehouse_t)){
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    if(amount == 0){
        return MATAMIKYA_SUCCESS;
    }
    if(!isAmountContains(amount,getUnits(getDataById(matamikya->warehouse_t,productId)))){
        return MATAMIKYA_INVALID_AMOUNT;
    }
    LinkedList orders = matamikya->orders_t;
    LinkedList cart = getDataById(orders, orderId);
    if(!getDataById(cart,productId)){
        if(amount > 0){

            CartItem new_cart_item = createCartItem(productId, amount);
            bool add_item_succeed = llAddNode(cart, productId, new_cart_item, deleteCartItem);
            if(add_item_succeed){
                return MATAMIKYA_SUCCESS;
            }
            deleteCartItem(new_cart_item);
            return MATAMIKYA_OUT_OF_MEMORY;
        }
        return MATAMIKYA_INSUFFICIENT_AMOUNT;
    }
    CartItem product = getDataById(cart, productId);
    double new_amount = getCartItemAmount(product) + amount;
    if(new_amount <= 0){
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
    if(!isContains(orderId, matamikya->orders_t)){
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    LinkedList cart = getDataById(matamikya->orders_t, orderId);
    LL_FOREACH(unsigned int, it, cart){
        CartItem current = getData(getCurrent(cart));
        ItemData item_in_warehouse = getDataById(matamikya->warehouse_t, it);
        if(getCartItemAmount(current) > getItemInStorage(item_in_warehouse)){
            return MATAMIKYA_INSUFFICIENT_AMOUNT;
        }
    }

    LL_FOREACH(unsigned int, it, cart){
        ItemData item_in_warehouse = getDataById(matamikya->warehouse_t, it);
        double current_amount_in_cart = getCartItemAmount(getData(getCurrent(cart)));
        double warehouse_amount = getItemInStorage(item_in_warehouse);
        double new_amount_in_warehouse = warehouse_amount - current_amount_in_cart;
        mtmChangeProductAmount(matamikya, it, new_amount_in_warehouse);
        changeProductIncome(item_in_warehouse, current_amount_in_cart);
    }
    mtmCancelOrder(matamikya, orderId);
    return MATAMIKYA_SUCCESS;
}   

MatamikyaResult mtmCancelOrder(Matamikya matamikya, const unsigned int orderId){
    if(!matamikya){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    LinkedList orders = matamikya->orders_t;
    if(!isContains(orderId,orders)){
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    //LinkedList cart_to_delete = getDataById(orders, orderId);
    deleteNodeById(orders,orderId);
    //deleteLinkedList(cart_to_delete);
    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmPrintInventory(Matamikya matamikya, FILE *output){
    if(!matamikya || !output){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    LinkedList warehouse = matamikya->warehouse_t;
    int max_id = 0;
    LL_FOREACH(unsigned int, it, warehouse){
        if(it > max_id){
            max_id = it;
        }
    }
    fprintf(output,"Inventory Status:\n");
    for(int i = 0; i <= max_id; i++){
        ItemData product = getDataById(warehouse,i);
        if(product){
            double price_per_unit = getProductPrice(product)(getProductData(product), 1);
            mtmPrintProductDetails(getItemName(product), i, getItemInStorage(product), price_per_unit, output);
        }
    }

    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmPrintOrder(Matamikya matamikya, const unsigned int orderId, FILE *output){
    if(!matamikya || !output){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    if(!isContains(orderId,matamikya->orders_t)){
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    mtmPrintOrderHeading(orderId, output);
    LinkedList cart = getDataById(matamikya->orders_t, orderId);
    int max_id = 0;
    LL_FOREACH(unsigned int, it, cart){
        if(it > max_id){
            max_id = it;
        }
    }
    double total_price = 0;
    for(int i=0;i<=max_id;i++){
        CartItem product = getDataById(cart, i);
        if(product){
            ItemData product_in_warehouse = getDataById(matamikya->warehouse_t,i);
            double amount = getCartItemAmount(product);
            double price = getProductPrice(product_in_warehouse)(getProductData(product_in_warehouse),amount);
            mtmPrintProductDetails(getItemName(product_in_warehouse),i,amount,price,output);
            total_price += price;
        }
    }

    mtmPrintOrderSummary(total_price, output);
    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmPrintBestSelling(Matamikya matamikya, FILE *output){
    if(!matamikya || !output){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    LinkedList warehouse = matamikya->warehouse_t;
    bool no_sales = true;
    LL_FOREACH(unsigned int, it, warehouse){
        ItemData current_data = getData(getCurrent(warehouse));
        if(getProductIncome(current_data) > 0){
            no_sales = false;
            break;
        }
    }
    fprintf(output, "Best Selling Product:\n");
    if(no_sales){
        fprintf(output, "none\n");
        return MATAMIKYA_SUCCESS;
    }
    double max_sales = 0;
    unsigned int max_sales_id = 0;
    LL_FOREACH(unsigned int, it, warehouse){
        ItemData current_data = getData(getCurrent(warehouse));
        double current_product_income = getProductIncome(current_data);
        if(current_product_income >= max_sales){
            if(current_product_income == max_sales){
                max_sales_id = max_sales_id < it ? max_sales_id : it;
            }
            else{
                max_sales = current_product_income;
                max_sales_id = it;
            }
        }
    }
    ItemData max_data = getDataById(warehouse, max_sales_id);
    mtmPrintIncomeLine(getItemName(max_data), max_sales_id, max_sales, output);
    return MATAMIKYA_SUCCESS;
}