/*
 * Example how new process by using fork(),exec(),wait(),kill() calls.
 * All std system calls are in <unistd.h> file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
    //kill(getpid(),SIGINT); // uncomment to generate KILL Interrupt signal.

    printf("hello world (pid:%d) \n",(int) getpid());
    int rc = fork();
    if (rc < 0){ // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){ // child new process
        close(STDOUT_FILENO);

        open("../cmd.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);  //  this will redirected to file not a terminal.

        printf("hello, I am child (pid:%d) \n",(int) getpid());
        char *myarg[3];  // execute "wc main.c" command from a child process
        myarg[0] = strdup("wc");
        myarg[1] = strdup("../main.c");
        myarg[2] = NULL; // this required to mark end of array.
        execvp(myarg[0], myarg);
        printf("This should not print out");


    } else {
        int rc_wait = wait(NULL); // for explicit wait for child process to finish.

        printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n",rc,rc_wait,(int) getpid());
    }
    return 0;
}