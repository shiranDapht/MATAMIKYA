#include "amuont_set_str_tests.h"
#include "../amount_set_str.h"
#include "../amount_set_str_node_set.h"

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
    printf("Testing asCreate\n");
    TestAmountSet();

    //Testing asCopy
    printf("Testing asCopy\n");
    for (int i = 0; i < 5; i++){
        TestAsCopy(arr[i]);
    }
    
    //Testing asGetSize
    printf("Testing asGetSize\n");
    for (int i = 0; i < 5; i++){
        TestAsGetSize(arr[i]);
    }

    //Testing asContains
    printf("Testing asContains\n");
    for (int i = 0; i < 5; i++){
        char str[100];
        scanf("%s",str);
        TestAsContains(arr[i],str);
    }

    //Testing asGetAmount
    printf("Testing asGetAmount\n");
    for (int i = 0; i < 5; i++){
        double outAmount;
        char str[100];
        scanf("%s",str);
        TestAsGetAmount(arr[i],str, &outAmount);
    }

    //Testing asRegister
    printf("Testing asRegister\n");
    for (int i = 0; i < 5; i++){
        char str[100];
        scanf("%s",str);
        TestAsRegister(arr[i],str);
        AS_FOREACH(char*,it,arr[i]){
            printf("%s\n",it);
        }
    }

    //Testing asChangeAmount
    printf("Testing asChangeAmount\n");
    for (int i = 0; i < 5; i++){
        double amount;
        char str[100];
        scanf("%s %lf",str,&amount);
        TestAsChangeAmount(arr[i],str,amount);
    }

    //Testing asDelete
    printf("Testing asDelete\n");
    for (int i = 0; i < 5; i++){
        char str[100];
        scanf("%s",str);
        TestAsDelete(arr[i],str);
        AS_FOREACH(char*,it,arr[i]){
            printf("%s\n",it);
        }
    }

    //Tesintg asGetFirst
    printf("Testing asGetFirst\n");
    for (int i = 0; i < 5; i++){
        TestAsGetFirst(arr[i]);
    }
    
    //Testing asGetNext
    printf("Testing asGetNext\n");
    for (int i = 0; i < 5; i++){
        TestAsGetNext(arr[i]);
    }

    //Testing asClear
    printf("Testing asClear\n");
    for (int i = 0; i < 5; i++){
        TestAsClear(arr[i]);
    }

    for(int i = 0; i<5;i++){
        asDestroy(arr[i]);
    }

    return 0;
}