#include "amuont_set_str_tests.h"
#include "../amount_set_str.h"
#include "../node_set.h"

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
        if(compareItemNames(it , getItemName(getCurrent(copy)) )){
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
    if(asContains(set,element)){

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

    if(result != AS_SUCCESS || result != AS_INSUFFICIENT_AMOUNT){
        printf("TestAsChangeAmount_Failed\n");
        return TEST_FAILED;
    }
    double outAmount;
    asGetAmount(set,element,&outAmount);
    printf("%s\n",  outAmount == amount + previusValue ? "true\n" : "TestAsChangeAmount_Failed\n");
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
    if(!asContains(set,element)){

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
    if(result == AS_SUCCESS && !getNext(getHead(set))){
        printf("TestAsClear_Failed\n");
        return TEST_FAILED;
    }
    printf("TestAsClear_Success\n");
    return TEST_SUCCESS;
}

TestRes TestAsDestroy(AmountSet set){
    asDestroy(set);
    if(set){
      printf("TestAsDestroy_Failed\n");
      return TEST_FAILED;
    }
    printf("TestAsDestroy_Success\n");
    return TEST_SUCCESS;
}

int main(){
    //Geting array of sets
    AmountSet arr[5];
    for(int i=0;i<5;i++){
        arr[i] = asCreate();
        int sizeOfSet;
        scanf("%d", &sizeOfSet);
        for (int j = 0; j < sizeOfSet; j++)
        {
            char str[100];
            double amount = 0;
            scanf("%s %lf",str, &amount);
            asRegister(arr[i],str);
            asChangeAmount(arr[i],str,amount);
        }        
    }

    //Testing asCreate
    TestAmountSet();
    //Testing asCopy
    for (int i = 0; i < 5; i++){
        TestAsCopy(arr[i]);
    }
    
    //Testing asGetSize
    for (int i = 0; i < 5; i++){
        TestAsGetSize(arr[i]);
    }

    //Testing asContains
    for (int i = 0; i < 5; i++){
        char str[100];
        scanf("%s",str);
        TestAsContains(arr[i],str);
    }

    //Testing asGetAmount
    for (int i = 0; i < 5; i++){
        double outAmount;
        char str[100];
        scanf("%s",str);
        TestAsGetAmount(arr[i],str, &outAmount);
    }

    //Testing asRegister
    for (int i = 0; i < 5; i++){
        char str[100];
        scanf("%s",str);
        TestAsRegister(arr[i],str);
        AS_FOREACH(char*,it,arr[i]){
            printf("%s\n",it);
        }
        
    }

    //Testing asChangeAmount
    for (int i = 0; i < 5; i++){
        double amount;
        char str[100];
        scanf("%s %lf",str,&amount);
        TestAsChangeAmount(arr[i],str,amount);
    }

    //Testing asDelete
    for (int i = 0; i < 5; i++){
        char str[100];
        scanf("%s",str);
        TestAsDelete(arr[i],str);
        AS_FOREACH(char*,it,arr[i]){
            printf("%s\n",it);
        }
    }

    //Tesintg asGetFirst
    for (int i = 0; i < 5; i++){
        TestAsGetFirst(arr[i]);
    }
    
    //Testing asGetNext
    for (int i = 0; i < 5; i++){
        TestAsGetNext(arr[i]);
    }

    //Testing asClear
    for (int i = 0; i < 5; i++){
        TestAsClear(arr[i]);
    }

    //Testing asDestroy
    for (int i = 0; i < 5; i++){
        TestAsDestroy(arr[i]);
    }

}