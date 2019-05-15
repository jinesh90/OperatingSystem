/*
 * This program will demo how OS is doing memory virtulization,
 * when you run this program on two different terminals,it will point to the same memory location.
 * OS is creating virtual address space or just address space for two different programs.
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char *argv[]){
    // allocate memory
    int *p = malloc(sizeof(int));

    assert(p != NULL);

    printf("(%d) address pointed by p: %p\n",getpid(),p);
    *p = 0;
    while(1){
        Spin(1);
        *p = *p + 1;
        printf("(%d) p: %d\n", getpid(), *p);
    }
    return 0;

}