#include "amuont_set_str_tests.h"
#include "../amount_set_str.c"

TestRes TestAmountSet(){
    AmountSet arr[100];
    for(int i = 0; i<100; i++){
        arr[i] = asCreate();
        if(!arr[i]){
            printf("TestAmountSet_Failed\n");
            return TEST_FAILED;
        }
    }
    for(int i = 0; i< 100; i++){
        asDestroy(arr[i]);
    }
    printf("TestAmountSet_Success\n");
    return TEST_SUCCESS;
}

TestRes TestAsCopy(AmountSet set){
    AmountSet copy = asCopy(set);
    asGetFirst(copy);
    AS_FOREACH(char*,it,set){
        if(CompareStr(it,copy->current->data)){
            printf("TestAsCopy_Failed\n");
            return TEST_FAILED;
        }
        asGetNext(copy);
    }
    printf("TestAsCopy_Success\n");
    return TEST_SUCCESS;
}

TestRes TestAsGetSize(AmountSet set){
    int size = asGetSize(set);
    if(size == -1){
        printf("TestAsCopy_Failed\n");
        printf("Set was NULL\n");
        return TEST_FAILED;
    }
    printf("%d\n",size);
    return TEST_SUCCESS;
}

TestRes TestAsContains(AmountSet set, const char* element){
    bool result = asContains(set,element);
    if((!set || !element) && result){
        printf("TestAsContains_Failed\n");
        return TEST_FAILED;
    }
    printf("%s", result ? "true" : "false");
    return TEST_SUCCESS;
}

TestRes TestAsGetAmount(AmountSet set, const char* element, double* outAmount){
    AmountSetResult result = asGetAmount(set,element,outAmount);
    if(!set || !element || !outAmount){
        if(result != AS_NULL_ARGUMENT){
            printf("TestAsGetAmount_Failed\n");
            return TEST_FAILED;
        }
        else{
            printf("TestAsGetAmount_Success\n");
            return TEST_SUCCESS;
        }
    }
    if(asContains == false){
        if(result != AS_ITEM_DOES_NOT_EXIST){
            printf("TestAsGetAmount_Failed\n");
            return TEST_FAILED;
        }
        else{
            printf("TestAsGetAmount_Success\n");
            return TEST_SUCCESS;
        }
    }

    if(result != AS_SUCCESS){
        printf("TestAsGetAmount_Failed\n");
        return TEST_FAILED;
    }
    printf("TestAsGetAmount_Success\n");
    return TEST_SUCCESS;
    
}

TestRes TestAsRegister(AmountSet set, const char* element){
    AmountSetResult result = asRegister(set,element);
    if(!set || !element){
        if(result != AS_NULL_ARGUMENT){
            printf("TestAsRegister_Failed\n");
            return TEST_FAILED;
        }
        else{
            printf("TestAsRegister_Success\n");
            return TEST_SUCCESS;
        }
    }
    if(asContains == true){

        if(result != AS_ITEM_ALREADY_EXISTS){
            printf("TestAsRegister_Failed\n");
            return TEST_FAILED;
        }
        else{
            printf("TestAsRegister_Success\n");
            return TEST_SUCCESS;
        }
    }

    if(result != AS_SUCCESS || result != AS_OUT_OF_MEMORY){
        printf("TestAsRegister_Failed\n");
        return TEST_FAILED;
    }
    printf("TestAsRegister_Success\n");
    return TEST_SUCCESS;
}

TestRes TestAChangeAmount(AmountSet set, const char* element, double amount){
    AmountSetResult result = asChangeAmount(set,element,amount);
    if(!set || !element){
        if(result != AS_NULL_ARGUMENT){
            printf("TestAsChangeAmount_Failed\n");
            return TEST_FAILED;
        }
        else{
            printf("TestAsChangeAmount_Success\n");
            return TEST_SUCCESS;
        }
    }
    if(asContains == false){

        if(result != AS_ITEM_DOES_NOT_EXIST){
            printf("TestAsChangeAmount_Failed\n");
            return TEST_FAILED;
        }
        else{
            printf("TestAsChangeAmount_Success\n");
            return TEST_SUCCESS;
        }
    }

    if(result != AS_SUCCESS || result != AS_INSUFFICIENT_AMOUNT){
        printf("TestAsChangeAmount_Failed\n");
        return TEST_FAILED;
    }
    printf("%s\n",findElement(set,element)->amount == amount ? "true" : "false");
    return TEST_SUCCESS;
}

TestRes TestAsDelete(AmountSet set, const char* element){
AmountSetResult result = asDelete(set,element);
    if(!set || !element){
        if(result != AS_NULL_ARGUMENT){
            printf("TestAsDelete_Failed\n");
            return TEST_FAILED;
        }
        else{
            printf("TestAsDelete_Success\n");
            return TEST_SUCCESS;
        }
    }
    if(asContains == false){

        if(result != AS_ITEM_DOES_NOT_EXIST){
            printf("TestAsDelete_Failed\n");
            return TEST_FAILED;
        }
        else{
            printf("TestAsDelete_Success\n");
            return TEST_SUCCESS;
        }
    }

    if(result != AS_SUCCESS){
        printf("TestAsDelete_Failed\n");
        return TEST_FAILED;
    }
    printf("TestAsDelete_Success\n");
    return TEST_SUCCESS;
}

TestRes TestAsClear(AmountSet set){
    AmountSetResult result = asClear(set);
    if(!set){
        if(result != AS_NULL_ARGUMENT){
            printf("TestAsClear_Failed\n");
            return TEST_FAILED;
        }
        else{
            printf("TestAsClear_Success\n");
            return TEST_SUCCESS;
        }
    }
    if(result == AS_SUCCESS && !set->head->next){
        printf("TestAsClear_Failed\n");
        return TEST_FAILED;
    }
    printf("TestAsClear_Success\n");
    return TEST_SUCCESS;
}

TestRes TestAsGetFirst(AmountSet set){
    if(!set && asGetFirst(set)){
        printf("TestAsGetFIrst_Failed\n");
        return TEST_FAILED;
    }
    printf("TestAsGetFIrst_Success\n");
    return TEST_SUCCESS;}

TestRes TestAsGetNext(AmountSet set){
    if(!set || !set->current){
        AmountSet copy = asCopy(set);
        if(asGetNext(copy)){
            asDestroy(copy);
            free(copy);
            printf("TestAsGetNext_Failed\n");
            return TEST_FAILED;
        }
    }
    ASElement result = asGetNext(set);
    if(!set->current && result){
        printf("TestAsGetNext_Failed\n");
        return TEST_FAILED;
    }
    printf("TestAsGetNext_Success\n");
    return TEST_SUCCESS;
}