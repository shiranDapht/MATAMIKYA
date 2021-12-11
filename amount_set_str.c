#include "amount_set_str.h"
#include "node_set.h"

AmountSet asCreate(){
    return createAmountSet();
}

void asDestroy(AmountSet set){
    if(!set){
        asClear(set);
        deleteNode(getHead(set));
        free(set);
    }
}

AmountSet asCopy(AmountSet set){
    if(!set){
        return NULL;
    }
    AmountSet copy = asCreate();
    if(!copy){
        return NULL;
    }
    Node original_iterator_state = getCurrent(set);
    AS_FOREACH(char*,it,set){
        asRegister(copy,it);
    }
    setCurrent(set,original_iterator_state);
    return copy;
}

int asGetSize(AmountSet set){
    if(!set){
        return -1;
    }
    Node original_iterator_state = getCurrent(set);
    int count = 0;
    AS_FOREACH(char*,it,set){
        count++;
    }
    setCurrent(set,original_iterator_state);
    return count;
}

bool asContains(AmountSet set, const char* element){
    if(!set){
        return false;
    }
    Node original_iterator_state = getCurrent(set);

    AS_FOREACH(char*,it,set){
        if(!compareItemNames(it,element)){
            setCurrent(set,original_iterator_state);
            return true;
        }
    }

    setCurrent(set,original_iterator_state);
    return false;
}

AmountSetResult asGetAmount(AmountSet set, const char* element, double* outAmount){
    if(!set || !element || !outAmount){
        return AS_NULL_ARGUMENT;
    }
    if(!asContains(set,element)){
        return AS_ITEM_DOES_NOT_EXIST;
    }
    Node original_iterator_state = getCurrent(set);

    AS_FOREACH(char*,it,set){
        if(!compareItemNames(it,element)){
            *outAmount = getAmount(getCurrent(set));
            break;
        }
    }

    setCurrent(set,original_iterator_state);
    return AS_SUCCESS;
}

AmountSetResult asRegister(AmountSet set, const char* element){
    if(!set || !element){
        return NULL;
    }
    if(asContains(set,element)){
        return AS_ITEM_ALREADY_EXISTS;
    }
    AS_FOREACH(char*,it,set){
        Node next_node = getNext(getCurrent(set));
        //it < element < next
        if(compareItemNames(it,element) < 0 && compareItemNames(element,getItemName(next_node)) < 0){
            Node new_node = createNode(copyItemName(element),0);
            setNext(new_node,next_node);
            setNext(getCurrent(set),new_node);
            break;
        }
    }

    return AS_SUCCESS;
}

AmountSetResult asDelete(AmountSet set, const char* element){
    if(!set || !element){
        return AS_NULL_ARGUMENT;
    }
    if (!asContains(set,element)){
        return AS_ITEM_DOES_NOT_EXIST;
    }

    Node previus_node = getHead(set);
    AS_FOREACH(char*,it,set){
        if(!compareItemNames(it,element)){
            setNext(previus_node,getNext(getCurrent(set)));
            deleteNode(getCurrent(set));
            break;
        }
        previus_node = getCurrent(set);
    }
    return AS_SUCCESS;
}


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