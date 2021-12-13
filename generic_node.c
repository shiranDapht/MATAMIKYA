#include "generic_node.h"
#include <stdbool.h>

struct Node_t{
    unsigned int id_t;
    NodeData data_t;
    Node next_t;
};


unsigned int getId(Node node){
    return node->id_t;
}

bool setId(Node node, unsigned int id){
    if(!node || id <= 0){
        return false;
    }
    node->id_t = id;
    return true;
}

NodeData getData(Node node){
    return node->data_t;
}

bool setData(Node node, NodeData data){
    if(!node || !data){
        return false;
    }
    node->data_t = data;
    return true;
}

Node getNext(Node node){
    return node->next_t;
}

bool setNext(Node node, Node next){
    if(!node){
        return false;
    }
    node->next_t = next;
    return true;
}