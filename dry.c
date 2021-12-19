#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

// char *stringduplicator(char *s, int times) { (code conventions #1)
char *stringDuplicator(char *s, int times)
{
    // assert(!s); (programming error #1)
    if (!s)
    {
        return NULL;
    }
    assert(times > 0); // asuming that times is possitive
    // int LEN = strlen(*s); (programming error #2 , code conventions #2)
    int len = strlen(s);
    // char *out = malloc(len * times); (programming error #3, code conventions #3)
    char *duplicated_str = malloc(sizeof(char) * len * times + 1);
    // assert(out); (programming error #4)
    if (!duplicated_str)
    {
        return NULL;
    }
    for (int i = 0; i < times; i++)
    {
    // out = out + len;
    // strcpy(out, s); (programming error #5, code conventions #4)
        strcpy(duplicated_str, s);
        duplicated_str += len;
    }
    return duplicated_str;
}

/*
2.2
*/

typedef struct node_t
{
    int x;
    struct node_t *next;
} *Node;

typedef enum
{
    SUCCESS = 0,
    MEMORY_ERROR,
    EMPTY_LIST,
    UNSORTED_LIST,
    NULL_ARGUMENT,
} ErrorCode;

int getListLength(Node list);
bool isListSorted(Node list);
ErrorCode mergeSortedLists(Node list1, Node list2, Node *mergedOut); //convention error #6 :P

void deleteList(Node list);

void deleteList(Node list){
    Node previous = list;

    while (list){
        Node to_delete = previous;
        previous = list->next;
        list = list->next;
        free(to_delete);
    }
}

ErrorCode mergeSortedLists(Node list1, Node list2, Node *merged_out){
    if(!merged_out){
        return NULL_ARGUMENT;
    }
    if(!list1 || !list2){
        *merged_out = NULL;
        return EMPTY_LIST;
    }

    if(!isListSorted(list1) || !isListSorted(list2)){
        *merged_out = NULL;
        return UNSORTED_LIST;
    }

    Node list1_ptr = list1, list2_ptr = list2, sorted_list;
    bool is_first = true;

    while (list1_ptr && list2_ptr)
    {
        sorted_list = malloc(sizeof(struct node_t));
        if(!sorted_list){
            deleteList(merged_out);
            *merged_out = NULL;
            return MEMORY_ERROR;
        }
        if(list1_ptr->x <= list2_ptr->x){
            sorted_list->x = list1_ptr->x;
            list1_ptr = list1_ptr->next;
        }
        else{
            sorted_list->x = list2_ptr->x;
            list2_ptr = list2_ptr->next;
        }
        sorted_list = sorted_list->next;
        if(is_first){
            is_first = false;
            *merged_out = sorted_list;
        }

    }

    while (list1_ptr)
    {
        sorted_list = malloc(sizeof(struct node_t));
        if(!sorted_list){
            deleteList(merged_out);
            *merged_out = NULL;
            return MEMORY_ERROR;
        }
        sorted_list->x = list1_ptr->x;
        list1_ptr = list1_ptr->next;
        sorted_list = sorted_list->next;
    }
    
    while (list2_ptr)
    {
        sorted_list = malloc(sizeof(struct node_t));
        if(!sorted_list){
            deleteList(merged_out);
            *merged_out = NULL;
            return MEMORY_ERROR;
        }
        sorted_list->x = list2_ptr->x;
        list2_ptr = list2_ptr->next;
        sorted_list = sorted_list->next;
    }    

    return SUCCESS;
    

}