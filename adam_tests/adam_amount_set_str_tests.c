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
    char* duplicate = "123456789 10 11 12 99 $@#$@!%(*akjsdakjnbsd%%asdlkasd\n\w\"\j\a      \  ' \' \\\\ ";
    elements[4] = duplicate;

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
        asChangeAmount(set,i->data,( (double)rand()/RAND_MAX*2000-1000) ); // changes amount by a random number in [-1000,1000]
    }
    fprintf(file,"asChangeAmount:\n");
    AS_FOREACH(asNode,i,set){
        fprintf(file,"  Element: %s   Amount: %f",i->data,i->amount);
    }
}

AmountSetResult TEST_asDelete(AmountSet set, FILE* file){
    fprintf(file,"asDelete:\n");
    fprintf(file,"  All elements: \n");
    AS_FOREACH(asNode,i,set){
        fprintf(file,"      %s\n",i->data);
    }
    fprintf(file,"  Removing first element\n");
    asDelete(set,asGetFirst(set));
    fprintf(file,"  All elements: \n");
    AS_FOREACH(asNode,i,set){
        fprintf(file,"      %s\n",i->data);
    }
    fprintf(file,"  Removing last element\n");
    AS_FOREACH(asNode,i,set){
        if(i->next == NULL){
            asDelete(set,i->data);
        }
    }
    fprintf(file,"  All elements: \n");
    AS_FOREACH(asNode,i,set){
        fprintf(file,"      %s\n",i->data);
    }
    fprintf(file,"  Removing all elements\n");
    AS_FOREACH(asNode,i,set){
        asDelete(set,i->data);
    }
    fprintf(file,"  All elements: \n");
    AS_FOREACH(asNode,i,set){
        fprintf(file,"      %s\n",i->data);
    }

}

AmountSetResult TEST_asClear(AmountSet set);

ASElement TEST_asGetFirst(AmountSet set);

ASElement TEST_asGetNext(AmountSet set);