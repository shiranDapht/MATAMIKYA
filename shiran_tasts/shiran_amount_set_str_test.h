#ifndef SHIRAN_AMOUNT_SET_STR_TESTS_H_
#define SHIRAN_AMOUNT_SET_STR_TESTS_H_

#include <stdio.h>
#include "../amount_set_str.c" 

typedef enum TestRes_t{
    TEST_SUCCESS,
    TEST_FAILED,
} TestRes;

TestRes TestAmountSet (FILE* file);
TestRes TestAsDestroy(AmountSet set, FILE* file);
TestRes TestAsCopy(AmountSet set, FILE* file);
TestRes TestAsGetSize(AmountSet set, FILE* file);
TestRes TestAsContains(AmountSet set,FILE* fileA , FILE* fileB);
TestRes TestAsGetAmount(AmountSet set, FILE* fileA , FILE* fileB);

TestRes TEST_asRegister(AmountSet set, FILE* file);
TestRes TEST_asChangeAmount(AmountSet set, FILE* file);
TestRes TEST_asDelete(AmountSet set, FILE* file);
TestRes TEST_asClear(AmountSet set, FILE* file);
TestRes TEST_asGetFirst(AmountSet set, FILE* file);
TestRes TEST_asGetNext(AmountSet set, FILE* file);



#endif
