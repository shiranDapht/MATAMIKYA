#include "linked_list.h"
#include "generic_node.h"

#include <stdbool.h>
#include <stdlib.h>


struct LinkedList_t{
    deleteMethod deleteData_t;
    Node head_t;
    Node current_t;

};

//private method
void setDeleteMethod(LinkedList list, deleteMethod dm){
    if(list){
        list->deleteData_t = dm;
    }
}

LinkedList createLinkedList(){

    LinkedList linked_list = (LinkedList)malloc(sizeof(struct LinkedList_t));
    Node head = createNode(0, NULL, NULL, NULL);
    if(!linked_list || !head){
        if (!linked_list){
            deleteNode(head);
        }
        return NULL;
    }
    linked_list->head_t = head;
    bool sn = setNext(head, NULL);
    bool sc = setCurrent(linked_list, getNext(head));
    if(!sn || !sc){
        deleteNode(head);
        deleteLinkedList(linked_list);
    }
    return linked_list;
}

void deleteLinkedList(LinkedList list){
    if(!list){
        return;
    }
    if(!getHead(list)){
        free(list);
    }
    if(list){
        Node current = getNext(getHead(list));
        while (current){
            Node to_delete = current;
            current = getNext(current);
            deleteNode(to_delete);
        }
    }
}

Node getHead(LinkedList list){
    return list->head_t;
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

NodeData llGetFirst(LinkedList list){
    if(!list){
        return NULL;
    }
    Node first = getNext(getHead(list));
    if(!first){
        return NULL;
    }
    if(!setCurrent(list, first)){
        return NULL;
    }
    return getData(first);
}

NodeData llGetNext(LinkedList list){
    if(!list){
        return NULL;
    }
    Node next = getCurrent(list);
    if(!getNext(next)){
        return NULL;
    }
    if(!setCurrent(list, next)){
        return NULL;
    }
    return getData(next);
}

bool llAddNode(LinkedList list, unsigned int id, NodeData data, deleteMethod deleteData){
    if(!list || !data || !deleteData){
        return false;
    }

    Node new_node = createNode(id,data, deleteData, NULL);
    if(!new_node){
        return false;
    }
    if(!setNext(getCurrent(list), new_node)){
        deleteNode(new_node);
        return false;
    }
    return true;
}