#include "amuont_set_str_tests.h"
#include "./amount_set_str.h"
#include "./amount_set_str_node_set.h"

TestRes TestAmountSet(){
    AmountSet arr[100];
    for(int i = 0; i<100; i++){
        arr[i] = asCreate();
        if(!arr[i]){
           for(int j=0;j<i;j++){
             asDestroy(arr[j]);
         }
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
        char* name_from_copy = getItemName(getCurrent(copy));
        if(compareItemNames(name_from_copy,it)){
            asDestroy(copy);
            printf("TestAsCopy_Failed\n");
            return TEST_FAILED;
        }
        asGetNext(copy);
    }
    asDestroy(copy);
    printf("TestAsCopy_Success\n");
    return TEST_SUCCESS;
}

TestRes TestAsGetSize(AmountSet set){
    int size = asGetSize(set);
    if(size == -1){
        printf("TestAsCopy_Failed\n");
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
    printf("%s\n", result ? "true" : "false");
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
    if(!asContains(set,element)){
        if(result != AS_ITEM_DOES_NOT_EXIST){
            printf("TestAsGetAmount_Failed\n");
            return TEST_FAILED;
        }
        else{
            printf("-1\n");
            return TEST_SUCCESS;
        }
    }

    if(result != AS_SUCCESS){
        printf("TestAsGetAmount_Failed\n");
        return TEST_FAILED;
    }
    printf("%f\n",*outAmount);
    return TEST_SUCCESS;
    
}

TestRes TestAsRegister(AmountSet set, const char* element){
    bool is_contained = asContains(set,element);
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
    if(is_contained){

        if(result != AS_ITEM_ALREADY_EXISTS){
            printf("TestAsRegister_Failed\n");
            return TEST_FAILED;
        }
        else{
            printf("TestAsRegister_Success\n");
            return TEST_SUCCESS;
        }
    }

    printf("TestAsRegister_Success\n");
    return TEST_SUCCESS;
}

TestRes TestAsChangeAmount(AmountSet set, const char* element, double amount){
    double previusValue;
    asGetAmount(set,element,&previusValue);
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
    if(!asContains(set,element)){

        if(result != AS_ITEM_DOES_NOT_EXIST){
            printf("TestAsChangeAmount_Failed\n");
            return TEST_FAILED;
        }
        else{
            printf("TestAsChangeAmount_Success\n");
            return TEST_SUCCESS;
        }
    }


    double outAmount;
    asGetAmount(set,element,&outAmount);
    if(outAmount != amount + previusValue && result != AS_INSUFFICIENT_AMOUNT){
        printf("TestAsChangeAmount_Failed\n");
        return TEST_FAILED;
    }
    printf("true\n");
    return TEST_SUCCESS;
}

TestRes TestAsDelete(AmountSet set, const char* element){
    bool is_contained = asContains(set,element);
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
    if(!is_contained){

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

TestRes TestAsGetFirst(AmountSet set){
    char* first = asGetFirst(set);
    if(!set && first){
        printf("TestAsGetFIrst_Failed\n");
        return TEST_FAILED;
    }
    printf("%s\n", !first ? "NULL" : first);
    return TEST_SUCCESS;
}

TestRes TestAsGetNext(AmountSet set){
    char* result = asGetNext(set);
    if(!set && result){
        printf("TestAsGetNext_Failed\n");
        return TEST_FAILED;
    }
    if(!getCurrent(set) && result){
        printf("TestAsGetNext_Failed\n");
        return TEST_FAILED;
    }
    printf("%s\n",!result ? "NULL" : result);
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
    if(result == AS_SUCCESS && getNext(getHead(set))){
        printf("TestAsClear_Failed\n");
        return TEST_FAILED;
    }
    printf("TestAsClear_Success\n");
    return TEST_SUCCESS;
}
