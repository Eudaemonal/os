#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>



void SIGUSR1_handler(int signum, siginfo_t *si, void *ctx) {
    if (signum == SIGUSR1){
        pid_t pid;
        pid = getpid();

        printf("Process %d Receive SIGUSER1\n", pid);

        exit(0);
    }
}

int main(int argc, char *argv[]){

    struct sigaction sa;
    sa.sa_sigaction = SIGUSR1_handler;
    sa.sa_flags     = SA_SIGINFO|SA_RESTART;
    sigemptyset (&sa.sa_mask);
    sigaction (SIGUSR1, &sa, NULL);

    pid_t pid;
    pid = fork(); /* call fork() from parent process*/
    if (0 == pid){
        printf("Child process %d\n", getpid());
        while(1);    
    }
    else{
        printf("Parent process %d\n", getpid());
        /* Send signal to child process*/
        sleep(1);
        kill(pid, SIGUSR1);
    } 

    return EXIT_SUCCESS;
}
