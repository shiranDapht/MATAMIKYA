/**
 * @file dry.c
 * @author Adam Katav 318758489, 
 *         Shiran Dapht 208397414.
 * @brief dry part of HW1 
 */

/**
 *2.1.1 - stringDuplicator
 * The line corrected is commented above the correct line.  
 * You can see the error type (convention/logic) and error number
 * at the end of the corrected line in "()".
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

// char *stringduplicator(char *s, int times) { (code conventions #1)
char *stringDuplicator(char *s, int times)
{
    // assert(!s); (programming error #1)
    if (!s)
    {
        return NULL;
    }
    assert(times > 0); // assuming that times is positive
    // int LEN = strlen(*s); (programming error #2 ,code conventions #2)
    int len = strlen(s);
    // char *out = malloc(len * times); 
    //(programming error #3, code conventions #3)
    char *duplicated_str = malloc(sizeof(char) * len * times + 1);
    char* start_of_str = duplicated_str;
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
    return start_of_str;
}



/*
2.2
*/
#include <stdbool.h>
#include <stdio.h>

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
bool isListSorted(Node list){
    int prev = list->x;
    while(list->next){
        if(list->x < prev){
            return false;
        }
        list = list->next;
        prev = list->x;
    }
    return true;
}
/**
 * function needed to be added to compleate the mergeSortedLists function
 */

/**
 * @brief delete the new list if could'nt create new node
 * 
 * @param list 
 */
void deleteList(Node list);

/**
 * @brief assign the data value from the list into the sorted list data
 * 
 * @param list_ptr 
 * @param sorted_list 
 */
void assignNode(Node *list_ptr, Node sorted_list);

/**
 * @brief assign the minimum data value from one of two lists into the sorted list data
 * 
 * @param list1_ptr 
 * @param list2_ptr 
 * @param sorted_list 
 */
void assignMax(Node *list1_ptr, Node *list2_ptr, Node sorted_list);


/**
 * implementation of our functions 
 */

void deleteList(Node list){
    Node previous = list;

    while (list){
        Node to_delete = previous;
        previous = list->next;
        list = list->next;
        free(to_delete);
    }
}

void assignNode(Node *list_ptr, Node sorted_list){
    sorted_list->x = (*list_ptr)->x;
    *list_ptr = (*list_ptr)->next;
}

void assignMax(Node *list1_ptr, Node *list2_ptr, Node sorted_list){
    if((*list1_ptr)->x <= (*list2_ptr)->x){
        assignNode(list1_ptr, sorted_list);
    }
    else{
        assignNode(list2_ptr, sorted_list);
    }
}

//implementation of mergeSortedLists 

ErrorCode mergeSortedLists(Node list1, Node list2, Node *mergedOut); 
//convention error #6 :P

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

    Node list1_ptr = list1, list2_ptr = list2, sorted_list = malloc(sizeof(struct node_t));
    if(!sorted_list){
        return MEMORY_ERROR;
    }
    *merged_out = sorted_list;

    assignMax(&list1_ptr, &list2_ptr, sorted_list);

    while (list1_ptr && list2_ptr){
        sorted_list->next = malloc(sizeof(struct node_t));
        if(!sorted_list->next){
            deleteList(*merged_out);
            *merged_out = NULL;
            return MEMORY_ERROR;
        }
        sorted_list = sorted_list->next;
        assignMax(&list1_ptr, &list2_ptr, sorted_list);
    }

    while (list1_ptr){
        sorted_list->next = malloc(sizeof(struct node_t));
        if(!sorted_list){
            deleteList(*merged_out);
            *merged_out = NULL;
            return MEMORY_ERROR;
        }
        sorted_list = sorted_list->next;
        assignNode(&list1_ptr, sorted_list);
    }
    
    while (list2_ptr){
        sorted_list->next = malloc(sizeof(struct node_t));
        if(!sorted_list){
            deleteList(*merged_out);
            *merged_out = NULL;
            return MEMORY_ERROR;
        }
        sorted_list = sorted_list->next;
        assignNode(&list2_ptr, sorted_list);
    }    

    return SUCCESS;
}
