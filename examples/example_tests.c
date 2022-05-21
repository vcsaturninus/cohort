#include <stdio.h>

#include "cohort.h"


enum status example1(void){
    int *num = NULL;
    *num = 44;
    return FAILURE;
}

enum status example2(void){
    return FAILURE;
}

enum status example3(void){
    return SUCCESS;
}
