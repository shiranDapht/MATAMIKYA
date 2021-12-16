#include "cart_item.h"

#include <stdlib.h>
#include <stdbool.h>

struct CartItem_t{
    unsigned int id_t;
    double amount_t;
};


CartItem createCartItem(unsigned int id, double amount){
    CartItem new_cart_item = (CartItem)malloc(sizeof(struct CartItem_t));
    if(!new_cart_item){
        return NULL;
    }
    if(!setCartItemId(new_cart_item,id)){
        deleteCartItem(new_cart_item);
        return NULL;
    }
    if(!setCartItemAmount(new_cart_item,amount)){
        deleteCartItem(new_cart_item);
        return NULL;
    }
    return new_cart_item;
}

void deleteCartItem(void* cart_item){
    if(cart_item){
        free(cart_item);
    }
}


unsigned int getCartItemId(CartItem cart_item){
    return cart_item->id_t;
}

bool setCartItemId(CartItem cart_item, unsigned int id){
    if(!cart_item){
        return false;
    }
    cart_item->id_t = id;
    return true;
}

double getCartItemAmount(CartItem cart_item){
    return cart_item->amount_t;
}

bool setCartItemAmount(CartItem cart_item, double amount){
    if(!cart_item){
        return false;
    }
    cart_item->amount_t = amount;
    return true;
}