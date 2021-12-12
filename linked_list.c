#include "linked_list.h"
#include "generic_node.h"
#include <stdbool.h>


struct LinkedList_t{
    Node head_t;
    Node current_t;
};

Node getHead(LinkedList list){
    return list->head_t;
}


bool setHead(LinkedList list, Node head){
    if(!list || !head){
        return false;
    }
    list->head_t = head;
    return true;
}

Node getCurrent(LinkedList list){
    return list->current_t;
}

bool setCurrent(LinkedList list, Node current){
    if(!list){
        return false;
    }
    list->current_t = current;
    return true;
}
