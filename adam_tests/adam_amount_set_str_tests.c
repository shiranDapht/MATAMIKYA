#include <stdio.h>
#include <stdlib.h>
#include "adam_amount_set_str_tests.h"
#include <time.h>


void PrintAllElements(AmountSet set, FILE* file){
    fprintf(file,"  All elements: \n");
    AS_FOREACH(asNode,i,set){
        fprintf(file,"      %s\n",i->data);
    }
}


void TEST_asRegister(AmountSet set, FILE* file){
    set = asCopy(set);
    fprintf(file,"asRegister:\n");

    fprintf(file,"  NULL check:\n");
    fprintf(file,"      Returned value: %d\n",asRegister(NULL,set->current->data));
    fprintf(file,"      Returned value: %d\n",asRegister(set,NULL));

    char** elements[5];
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

    fprintf(file,"    Elements meant to be in set:\n");
    AmountSetResult values[5];
    for(int i = 0; sizeof(elements)/sizeof(ASElement); i++){
        values[i] = asRegister(set,elements[i]);
        fprintf(file,"      %s\n",elements[i]);
    }

    fprintf(file,"  Calling asRegister for every element:\n");
    for(int i = 0; i < 5; i++){
        fprintf(file,"      Returned value: %d\n",values[i]);
    }

    PrintAllElements(set,file);

    asDestroy(set);
}

void TEST_asChangeAmount(AmountSet set, FILE* file){
    set = asCopy(set);
    fprintf(file,"asChangeAmount:\n");
    fprintf(file,"  NULL check:\n");
    fprintf(file,"      Returned value: %d\n",asChangeAmount(NULL,set->current->data,1));
    fprintf(file,"      Returned value: %d\n",asChangeAmount(set,NULL,1));


    srand(time(NULL));
    AS_FOREACH(asNode,i,set){
        AmountSetResult result = asChangeAmount(set,i->data,( (double)rand()/RAND_MAX*2000-1000) ); // changes amount by a random number in [-1000,1000]
        fprintf(file, "Returned value: %d\n",result);
    }

    AS_FOREACH(asNode,i,set){
        fprintf(file,"  Element: %s   Amount: %f",i->data,i->amount);
    }

    asDestroy(set);
}

void TEST_asDelete(AmountSet set, FILE* file){
    set = asCopy(set);

    fprintf(file,"asDelete:\n");
    PrintAllElements(set,file);

    fprintf(file,"  NULL check:\n");
    fprintf(file,"      returned value: %d\n",asDelete(set,NULL));
    fprintf(file,"      returned value: %d\n",asDelete(NULL,set->current->data));
    
    fprintf(file,"  Removing first element, returned value: %d\n",asDelete(set,asGetFirst(set)));
    PrintAllElements(set,file);
    
    
    AS_FOREACH(asNode,i,set){
        if(i->next == NULL){
            fprintf(file,"  Removing last element, returned value: %d\n",asDelete(set,i->data));
        }
    }
    PrintAllElements(set,file);
    
    fprintf(file,"  Removing all elements\n");
    AS_FOREACH(asNode,i,set){
        fprintf(file, "returned value: %d",asDelete(set,i->data));
    }
    fprintf(file, "\n");
    PrintAllElements(set,file);

    asDestroy(set);
}

void TEST_asClear(AmountSet set, FILE* file){
    set = asCopy(set);

    fprintf(file,"  NULL check: %d\n", asClear(NULL));
    fprintf(file,"asClear:\n");
    fprintf(file,"  Before asClear:\n");
    PrintAllElements(set,file);
    fprintf(file,"  Returned value: \n",asClear(set));
    fprintf(file,"  After asClear:\n");
    PrintAllElements(set,file);

    asDestroy(set);
}

void TEST_asGetFirst(AmountSet set, FILE* file){
    set = asCopy(set);

    fprintf(file,"asGetFirst:\n");

    fprintf(file, "     NULL check\n       %s", asGetFirst(NULL));
    PrintAllElements(set,file);
    fprintf(file, "     From asGetFirst\n       %s", asGetFirst(set));
    asDelete(set,asGetFirst(set));
    fprintf(file, "     From asGetFirst after asDelete(set,asGetFirst(set))\n       %s", asGetFirst(set));
    asClear(set);
    fprintf(file, "     From asGetFirst after asClear(set,asGetFirst(set))\n       %s", asGetFirst(set));

    asDestroy(set);
}

void TEST_asGetNext(AmountSet set, FILE* file){
    set = asCopy(set);

    fprintf(file,"asGetNext:\n");
    fprintf(file, "     NULL check\n       %s", asGetNext(NULL));

    AS_FOREACH(asNode,i,set){

    }

    fprintf(file, " Returned value after AS_FOREACH: %s", asGetNext(set));

    fprintf(file,"  Initializing with asGetFirst()");
    asGetFirst(set); //init asGetNext

    PrintAllElements(set,file);
    fprintf(file, "     From asGetNext\n       %s", asGetFirst(set));
    asDelete(set,asGetNext(set));
    fprintf(file, "     From asGetNext after asDelete(set,asGetNext(set))\n       %s", asGetNext(set));
    asClear(set);
    fprintf(file, "     From asGetNext after asClear(set,asGetNext(set))\n       %s", asGetNext(set));


    asDestroy(set);
}