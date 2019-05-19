/*
 * Homework solution for process magt API.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER 1024

int main(int argc, char *argv[]){

    /*
     * Write a program that calls fork(). Before calling fork(), have the main
     * process access a variable (e.g., x) and set its value to something (e.g., 100).
     * What value is the variable in the child process? What happens to the vari-
     * able when both the child and parent change the value of x?
     *
     * ANSWER: value of x is the same value in child process, if child changes value it wil not effect parent's value.
     */
    int x = 100;
    printf("Starting Parent process (pid = %d) and value of Parent variable x is %d\n",(int)getpid(),x);

    int rc = fork();
    if (rc < 0){ // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){ // child new process
        printf("This is child process (pid=%d) and value of Parent variable x is %d\n",(int) getpid(),x);
        // modify value of x
        x = 200;
        printf("This is child process (pid=%d) and value of Parent variable x AFTER modification  is %d\n",(int) getpid(),x);
    } else {
        int rc_wait = wait(NULL); // for explicit wait for child process to finish.
        printf("After child process done value of x is :%d\n",x);
        printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n",rc,rc_wait,(int) getpid());
    }

    /*
     * Write a program that opens a file (with the open() system call) and then
     * calls fork() to create a new process. Can both the child and parent ac-
     * cess the file descriptor returned by open()? What happens when they are
     * writing to the file concurrently, i.e., at the same time?
     */
    int fd;
    fd = open("../newfile.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    printf("Starting Parent process (pid = %d) and FILE descriptor is %d\n",(int)getpid(),fd);
    char *buff;
    buff =  "Hello Jinesh by Parent\n";
    write(fd,buff,strlen(buff));
    int rc2 = fork();
    if (rc < 0){ // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc2 == 0){ // child new process
        printf("This is child process (pid=%d) and FILE descriptor is %d\n",(int) getpid(),fd);
        char *child;
        child =  "Hello Jinesh by Child\n";
        write(fd,child,strlen(child));

        //printf("This is child process (pid=%d) and value of Parent variable x AFTER modification  is %d\n",(int) getpid(),x);
    } else {
        int rc_wait = wait(NULL); // for explicit wait for child process to finish.
        //printf("After child process done value of x is :%d\n",x);
        printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n",rc,rc_wait,(int) getpid());
    }


    return 0;
}