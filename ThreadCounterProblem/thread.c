/*
 * Every time run this program will get different output on higher values
 * to compile with thread use this command gcc -o thread thread.c -Wall -pthread
 * ./thread 1000 -> will give you 2000
 * ./thread 100000 -> will give all time different values.
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include <pthread.h>

volatile int counter = 0;

int loops;

void *worker(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        counter++;
    }
    return NULL;
}


int main(int argc, char *argv[]){
    if (argc != 2) {
        fprintf(stderr, "usage: threads <value>\n");
        exit(1);
    }
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    printf("Initial value : %d\n", counter);
    pthread_create(&p1, NULL, worker, NULL);
    pthread_create(&p2, NULL, worker, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("Final value: %d\n", counter);
    return 0;
}