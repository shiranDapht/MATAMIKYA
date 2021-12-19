#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

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
ErrorCode mergeSortedLists(Node list1, Node list2, Node *mergedOut); 
//convention error #6 :P

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

    Node list1_ptr = list1, list2_ptr = list2, sorted_list = malloc(sizeof(struct node_t));
    *merged_out = sorted_list;

    if(list1_ptr->x <= list2_ptr->x){
        sorted_list->x = list1_ptr->x;
        list1_ptr = list1_ptr->next;
    }
    else{
        sorted_list->x = list2_ptr->x;
        list1_ptr = list1_ptr->next;
    }

    while (list1_ptr && list2_ptr)
    {
        sorted_list->next = malloc(sizeof(struct node_t));
        if(!sorted_list){
            deleteList(*merged_out);
            *merged_out = NULL;
            return MEMORY_ERROR;
        }
        sorted_list = sorted_list->next;
        if(list1_ptr->x <= list2_ptr->x){
            sorted_list->x = list1_ptr->x;
            list1_ptr = list1_ptr->next;
        }
        else{
            sorted_list->x = list2_ptr->x;
            list2_ptr = list2_ptr->next;
        }
    }

    while (list1_ptr)
    {
        sorted_list->next = malloc(sizeof(struct node_t));
        if(!sorted_list){
            deleteList(*merged_out);
            *merged_out = NULL;
            return MEMORY_ERROR;
        }
        sorted_list = sorted_list->next;
        sorted_list->x = list1_ptr->x;
        list1_ptr = list1_ptr->next;
    }
    
    while (list2_ptr)
    {
        sorted_list->next = malloc(sizeof(struct node_t));
        if(!sorted_list){
            deleteList(*merged_out);
            *merged_out = NULL;
            return MEMORY_ERROR;
        }
        sorted_list = sorted_list->next;
        sorted_list->x = list2_ptr->x;
        list2_ptr = list2_ptr->next;
    }    

    return SUCCESS;

}

int main(){
    Node list1 = malloc(sizeof(struct node_t));
    Node first1 = list1;
    Node list2 = malloc(sizeof(struct node_t));
    Node first2 = list2;

    for (int i = 0; i < 5; i++){
        list1->x = i;
        list2->x = i+1;
        if(i!=4){
            list1->next = malloc(sizeof(struct node_t));
            list2->next = malloc(sizeof(struct node_t));
            list1 = list1->next;
            list2 = list2->next;
        }
    }

    Node sorted;
    mergeSortedLists(first1,first2,&sorted);
    if(!isListSorted(sorted)){
        return 1;
    }

    char* s = "hello";
    char* g = stringDuplicator(s,3);
    printf("%s\n",g);

    return 0;
}