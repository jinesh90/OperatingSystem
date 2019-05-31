/*
 * Thread creation example with mutex.
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NUM_THREADS 4

void *hello(void *args){
    pthread_mutex_t mu;
    pthread_mutex_lock(&mu);
    char num = *((char*) args);
    printf("Thread number %c\n",num);
    pthread_mutex_unlock(&mu);
    return 0;
}


int main(int argc, char *argv[]){

    int i;
    char nu[NUM_THREADS] = {'a','b','c','d'};
    pthread_t tid[NUM_THREADS];
    for (i=0;i< NUM_THREADS;i++){
        /* create fork threads */

        pthread_create(&tid[i], NULL, hello, &nu[i]);
        //printf("%p\n",&nu[i]);
    }
    for (i=0;i< NUM_THREADS;i++){
        /* join/wait on threads */
        pthread_join(tid[i],NULL);
    }
    return 0;
}

