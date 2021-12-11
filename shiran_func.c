#include "node_set.h"
#include "amount_set_str.h"

AmountSetResult asClear(AmountSet set){
    if(!set){
        return AS_NULL_ARGUMENT;
    }

    Node current = getHead(set);
    if(!current){
        return AS_NULL_ARGUMENT;
    }

    current = getNext(current);

    while (current)
    {
        Node toDelete = current;
        current = getNext(current);
        deleteNode(toDelete);
    }
    return AS_SUCCESS;
}

char* asGetFirst(AmountSet set){
    if(!set){
        return NULL;
    }
    Node first = getNext(getHead(set));
    if(!first){
        return NULL;
    }
    bool b = setCurrent(set, first);
    if(!b){
        return NULL;
    }
    return getItemName(first);
}

char* asGetNext(AmountSet set){
    if(!set){
        return NULL;
    }
    Node next = getCurrent(set);
    next = getNext(next);
    if(!next){
        return NULL;
    }
    bool b =  setCurrent(set, next);
    if(!b){
        return NULL;
    }
    return getItemName(next);
}

AmountSetResult asChangeAmount(AmountSet set, const char* element, double amount){
    if(!set || !element || !amount){
        return AS_NULL_ARGUMENT;
    }
    Node original_iterator_state = getCurrent(set);
    if(!asContains(set,element)){
        setCurrent(set,original_iterator_state);
        return AS_ITEM_DOES_NOT_EXIST;
    }
    AS_FOREACH(char*, it, set){
        if(compareItemNames(it,element) == 0){
            double currentAmount = getAmount(getCurrent(set));
            currentAmount += amount;
            if(currentAmount < 0){
                setCurrent(set,original_iterator_state);
                return AS_INSUFFICIENT_AMOUNT;
            }
            bool b = setAmount(getCurrent(set), currentAmount);
            if(!b){
                return AS_NULL_ARGUMENT;
            }
            setCurrent(set,original_iterator_state);
            return AS_SUCCESS;
        }
    }
    setCurrent(set,original_iterator_state);
    return AS_NULL_ARGUMENT;
}