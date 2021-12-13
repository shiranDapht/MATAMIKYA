#include "generic_node.h"

#include <stdlib.h>
#include <stdbool.h>




struct Node_t{
    unsigned int id_t;
    NodeData data_t;
    deleteMethod deleteData_t;
    Node next_t;
};

//private method
void setDeleteMethod(Node node, deleteMethod dm){
    if(!node){
        node->deleteData_t = dm;
    }
}

Node createNode(unsigned int id, NodeData data, deleteMethod deleteData, Node next){
    Node new_node = (Node)malloc(sizeof(struct Node_t));
    if(!new_node){
        return NULL;
    }
    setId(new_node,id);
    setData(new_node,data);
    setDeleteMethod(new_node,deleteData);
    setNext(new_node,next);
    return new_node;
}

void deleteNode(Node node){
    if(!node){
        return;
    }
    getDeleteDataMethod(node)(getData(node));
}

deleteMethod getDeleteDataMethod(Node node){
    return node->deleteData_t;
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