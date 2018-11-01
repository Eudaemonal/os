#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


void SIGUSR1_handler(int signum, siginfo_t *si, void *ctx) {
    if (signum == SIGUSR1){
        printf("Receive SIGUSER1\n");
    }
}

int main(int argc, char *argv[]){

    struct sigaction sa;
    sa.sa_sigaction = SIGUSR1_handler;
    sa.sa_flags     = SA_SIGINFO|SA_RESTART;
    sigemptyset (&sa.sa_mask);
    sigaction (SIGUSR1, &sa, NULL);

    raise(SIGUSR1);


    return EXIT_SUCCESS;
}
