#include "generic_node.h"

#include <stdlib.h>
#include <stdbool.h>




struct Node_t{
    unsigned int id_t;
    NodeData data_t;
    Node next_t;
};

Node createNode(unsigned int id, NodeData data, Node next){
    Node new_node = (Node)malloc(sizeof(struct Node_t));
    if(!new_node){
        return NULL;
    }
    bool i = setId(new_node,id);
    bool d = setData(new_node,data);
    bool n = setNext(new_node,next);
    if(!i || !d || !n){
        deleteNode(new_node);
        return NULL;
    }
    return new_node;
}

void deleteNode(Node node){
    if(!node){
        return;
    }
    getDeleteDataMethod(node)(getData(node));
}


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