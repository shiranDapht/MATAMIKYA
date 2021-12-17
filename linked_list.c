#include "linked_list.h"
#include "generic_node.h"

#include <stdbool.h>
#include <stdlib.h>


struct LinkedList_t{
    deleteNodeDataMethod deleteData_t;
    Node head_t;
    Node current_t;

};

//private method
void setDeleteMethod(LinkedList list, deleteNodeDataMethod dm){
    list->deleteData_t = dm;
}

LinkedList createLinkedList(deleteNodeDataMethod deleteData){

    if(!deleteData){
        return NULL;
    }
    LinkedList linked_list = (LinkedList)malloc(sizeof(struct LinkedList_t));
    if(!linked_list){
        return NULL;
    }
    setDeleteMethod(linked_list,deleteData);
    Node head = createNode(0, NULL, deleteData);
    if(!head){
        free(linked_list);
        return NULL;
    }
    linked_list->head_t = head;
    return linked_list;
}

void deleteLinkedList(void* list){
    Node node = getNext(getHead(list));
    while(node){
        Node to_delete = node;
        node = getNext(node);
        deleteNode(to_delete,getDeleteDataMethod(list));
    }
    free(getHead(list));
    free(list);
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

unsigned int llGetFirst(LinkedList list){
    if(!list){
        return 0;
    }
    Node first = getNext(getHead(list));
    if(!first){
        return 0;
    }
    if(!setCurrent(list, first)){
        return 0;
    }
    return getId(first);
}

unsigned int llGetNext(LinkedList list){
    if(!list){
        return 0;
    }
    Node next = getNext(getCurrent(list));
    if(!next){
        return 0;
    }
    if(!setCurrent(list, next)){
        return 0;
    }
    return getId(next);
}

bool llAddNode(LinkedList list, unsigned int id, NodeData data, deleteNodeDataMethod deleteData){
    if(!list || !data || !deleteData){
        return false;
    }

    Node new_node = createNode(id,data, deleteData);
    if(!new_node){
        return false;
    }
    if(!getNext(getHead(list))){
        setNext(getHead(list),new_node);
        return true;
    }
    LL_FOREACH(unsigned int, it, list){
        if(!getNext(getCurrent(list))){
            setNext(getCurrent(list), new_node);
            return true;
        }
    }
    deleteNode(new_node,deleteData);
    return false;
}

unsigned int makeNewListNodeId(LinkedList list){
    int max = 0;
    LL_FOREACH(unsigned int, it, list){
        if(it > max){
            max = it;
        }
    }
    return max + 1;
}

NodeData getDataById(LinkedList list, unsigned int id){
    LL_FOREACH(unsigned int, it, list){
        if(it == id){
            return getData(getCurrent(list));
        }
    }
    return NULL;
}

deleteNodeDataMethod getDeleteDataMethod(LinkedList list){
    if(!list){
        return NULL;
    }
    return list->deleteData_t;
}

void deleteNodeById(LinkedList list, unsigned int id){
    if(list){
        Node previus = getHead(list);
        LL_FOREACH(unsigned int, it, list){
            if(it == id){
                Node to_delete = getCurrent(list);
                setNext(previus,getNext(to_delete));
                deleteNode(to_delete, getDeleteDataMethod(list));
                return;
            }
            previus = getNext(previus);
        }
    }
}