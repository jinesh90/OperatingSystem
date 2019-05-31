/*
 * Producer consumer problem
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUF_SIZE 3  /* size of shared buffer*/

int buffer[BUF_SIZE]; /*shared buffer */
int add = 0;
int rem = 0;
int num = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;     /* mutex lock for buffer */
pthread_cond_t  c_con = PTHREAD_COND_INITIALIZER;  /* consumer waits on this condition */
pthread_cond_t  c_prod = PTHREAD_COND_INITIALIZER; /* producer wait on this condition */

void *producer(void *params);                      /* prototyping for producer*/
void *consumer(void *params);                      /* prototyping for consumer*/


int main (int argc, char *argv[]){

    pthread_t tid1,tid2;                         /* create two threads for consumer producer */
    if(pthread_create(&tid1,NULL,producer,NULL) != 0){
        fprintf(stderr,"Unable to create producer\n");
        exit(1);
    }
    if(pthread_create(&tid2,NULL,consumer,NULL) != 0){
        fprintf(stderr,"Unable to create consumer\n");
        exit(1);
    }

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    printf("Main process Ends\n");

}

void *producer(void *params){
    int i;
    for(i=1;i<=20;i++){

        pthread_mutex_lock(&m); /* lock critical section */
        if (num > BUF_SIZE){ /* incase of overflow */
            exit(1);
        }
        while(num == BUF_SIZE){ /*blocks if buffer is full */
            pthread_cond_wait(&c_prod, &m);
        }
        buffer[add] = i; /*in case of buffer is not full add element,*/
        add = (add + 1) % BUF_SIZE;
        num ++;
        pthread_mutex_unlock(&m);     /* unlock critical section */
        pthread_cond_signal(&c_con); /*in case of consumer thread is waiting, signal that produce is ready to pick up */
        printf("producer: inserted %d\n",i);
        fflush(stdout);
        printf("producer terminated\n");

    }
}

void *consumer(void *params){
    int i;
    while(1){
        pthread_mutex_lock(&m);
        if (num < 0){/*underflow */
            exit(1);
        }
        while (num == 0){ /*block if buffer is empty */
            pthread_cond_wait(&c_con,&m);
        }
        i = buffer[rem];
        rem = (rem+1) % BUF_SIZE;
        num--;
        pthread_mutex_unlock(&m);
        pthread_cond_signal(&c_prod);
        printf("Consume value %d\n",i);
        fflush(stdout);
    }
}

