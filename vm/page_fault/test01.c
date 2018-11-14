#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define ADDR  ((char *) 0xdeadbeef)

void handler (int signum, siginfo_t *si, void *ctx){
    void *addr;
    if (SIGSEGV != signum) {
        printf ("Panic!");
        exit (1);
    }

    printf ("Caught a SEGV...\n");
    addr = si->si_addr;       /* here we get the fault address */

    printf ("...and the offending address is %p.\n", addr);
    exit (0);
}



int main(int argc, char *argv[]){
    struct sigaction sa;

    sa.sa_sigaction = handler;
    sa.sa_flags     = SA_SIGINFO;
    sigemptyset (&sa.sa_mask);
    sigaction (SIGSEGV, &sa, NULL);         /* set the signal handler... */
    *ADDR = 'A';                      /* ...and die! */

    return EXIT_SUCCESS; /* we'll never get here */
}
