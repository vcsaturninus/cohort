#include <stdio.h>

#include "cohort.h"


enum status example1(void){
    //printf("I'm going to segfault lol.");
    int *num = NULL;
    *num = 44;
    return FAILURE;
}

enum status example2(void){
    //printf("This test is gonna fail and that's all right.");

    return FAILURE;
}

enum status example3(void){
    //printf("Run, Forest, run!! (running last test)");

    return SUCCESS;
}
