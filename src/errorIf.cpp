#include "errorIf.h"
#include <stdio.h>
#include <stdlib.h>

void errorIf(bool flag, const char * str){
    if(flag){
        perror(str);
        exit(EXIT_FAILURE);
    }
}