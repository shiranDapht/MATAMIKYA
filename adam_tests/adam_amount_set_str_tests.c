#include <stdio.h>
#include <stdlib.h>
#include "adam_amount_set_str_tests.h"
#include <time.h>

AmountSetResult TEST_asRegister(AmountSet set, FILE* file){
    ASElement elements[5];
    char* regular_str = "First Element";
    elements[0] = regular_str;
    char* empty_str = "";
    elements[1] = empty_str;
    char* null_str = NULL;
    elements[2] = null_str;
    char* all_chars = "123456789 10 11 12 99 $@#$@!%(*akjsdakjnbsd%%asdlkasd\n\w\"\j\a      \  ' \' \\\\ ";
    elements[3] = all_chars;
    char* whitespaces = "\n   \n\n \n     \n \n      \n     \n";
    elements[4] = null_str;

    fprintf(file,"asRegister:\n");
    fprintf(file,"    Elements meant to be in set:\n");

    for(int i = 0; sizeof(elements)/sizeof(ASElement); i++){
        asRegister(set,elements[i]);
        fprintf(file,"      %s\n",elements[i]);
    }

    
    fprintf(file,"    Elements in set:\n");
    AS_FOREACH(asNode,i,set){
        fprintf(file,"      %s\n",i->data);
    }
}

AmountSetResult TEST_asChangeAmount(AmountSet set, const double amount, FILE* file){
    srand(time(NULL));
    AS_FOREACH(asNode,i,set){
        asChangeAmount(set,i->data,( (double)rand()/RAND_MAX*2-1) ); // changes amount by a random number in [-1,1]
    }
    fprintf(file,"asChangeAmount:\n");
    AS_FOREACH(asNode,i,set){
        fprintf(file,"  Element: %s   Amount: %f",i->data,i->amount);
    }
}

AmountSetResult TEST_asDelete(AmountSet set, ASElement element);

AmountSetResult TEST_asClear(AmountSet set);

ASElement TEST_asGetFirst(AmountSet set);

ASElement TEST_asGetNext(AmountSet set);