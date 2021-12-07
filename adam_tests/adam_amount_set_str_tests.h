#ifndef ADAM_AMOUNT_SET_STR_TESTS_H_
#define ADAM_AMOUNT_SET_STR_TESTS_H_

#include <stdio.h>
#include "../amount_set_str.c"


void TEST_asRegister(AmountSet set, FILE* file);
void TEST_asChangeAmount(AmountSet set, FILE* file);
void TEST_asDelete(AmountSet set, FILE* file);
void TEST_asClear(AmountSet set, FILE* file);
void TEST_asGetFirst(AmountSet set, FILE* file);
void TEST_asGetNext(AmountSet set, FILE* file);




#endif // ADAM_AMOUNT_SET_STR_TESTS_H_O