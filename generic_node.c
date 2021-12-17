#include "generic_node.h"

#include <stdlib.h>
#include <stdbool.h>

struct Node_t{
    unsigned int id_t;
    NodeData data_t;
    Node next_t;
};

Node createNode(unsigned int id, NodeData data, deleteNodeDataMethod deleteData){
    if(!deleteData){
        return NULL;
    }
    Node new_node = (Node)malloc(sizeof(struct Node_t));
    if(!new_node){
        return NULL;
    }
    bool i = setId(new_node,id);
    bool d = setData(new_node,data);
    bool n = setNext(new_node, NULL);
    if(!i || !d || !n){
        deleteNode(new_node, deleteData);
        return NULL;
    }
    return new_node;
}

void deleteNode(Node node, deleteNodeDataMethod dm){
    if(node){
        if(getData(node)){
            dm(getData(node));
        }
        free(node);
    }
}

unsigned int getId(Node node){
    return node->id_t;
}

//privet function
bool setId(Node node, unsigned int id){
    if(id < 0){
        return false;
    }
    node->id_t = id;
    return true;
}

NodeData getData(Node node){
    if(!node){
        return NULL;
    }
    if(!node->data_t){
        return NULL;
    }
    return node->data_t;
}

bool setData(Node node, NodeData data){
    if(!node){
        //node->data_t = NULL;
        return false;
    }
    node->data_t = data;
    return true;
}

Node getNext(Node node){
    if(!node){
        return NULL;
    }
    return node->next_t;
}

bool setNext(Node node, Node next){
    if(!node){
        return false;
    }
    node->next_t = next;
    return true;
}