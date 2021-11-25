#ifndef ADAM_AMOUNT_SET_STR_TESTS_H_
#define ADAM_AMOUNT_SET_STR_TESTS_H_

#include <stdio.h>
#include "../amount_set.c"


AmountSetResult TEST_asRegister(AmountSet set, ASElement element);
AmountSetResult TEST_asChangeAmount(AmountSet set, ASElement element, const double amount);
AmountSetResult TEST_asDelete(AmountSet set, ASElement element);
AmountSetResult TEST_asClear(AmountSet set);
ASElement TEST_asGetFirst(AmountSet set);
ASElement TEST_asGetNext(AmountSet set);




#endif // ADAM_AMOUNT_SET_STR_TESTS_H_O