#ifndef SHIRAN_AMOUNT_SET_STR_TESTS_H_
#define SHIRAN_AMOUNT_SET_STR_TESTS_H_

#include <stdio.h>
#include "../amount_set_str.c" 

typedef enum TestRes_t{
    TEST_SUCCESS,
    TEST_FAILED,
} TestRes;

TestRes TestAmountSet();
TestRes TestAsDestroy(AmountSet set);
TestRes TestAsCopy(AmountSet set);
TestRes TestAsGetSize(AmountSet set);
TestRes TestAsContains(AmountSet set, const char* element);
TestRes TestAsGetAmount(AmountSet set, const char* element, double* outAmount);

TestRes TestAsRegister(AmountSet set, const char* element);
TestRes TestAChangeAmount(AmountSet set, const char* element, double amount);
TestRes TestAsDelete(AmountSet set, const char* element);
TestRes TestAsClear(AmountSet set);
TestRes TestAsGetFirst(AmountSet set);
TestRes TestAsGetNext(AmountSet set);



#endif
