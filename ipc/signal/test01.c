#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/*
    SIGHUP        1       Term    Hangup detected on controlling terminal
                                  or death of controlling process
    SIGINT        2       Term    Interrupt from keyboard
    SIGQUIT       3       Core    Quit from keyboard
    SIGILL        4       Core    Illegal Instruction
    SIGABRT       6       Core    Abort signal from abort(3)
    SIGFPE        8       Core    Floating-point exception
    SIGKILL       9       Term    Kill signal
    SIGSEGV      11       Core    Invalid memory reference
    SIGPIPE      13       Term    Broken pipe: write to pipe with no
                                  readers; see pipe(7)
    SIGALRM      14       Term    Timer signal from alarm(2)
    SIGTERM      15       Term    Termination signal
    SIGUSR1   30,10,16    Term    User-defined signal 1
    SIGUSR2   31,12,17    Term    User-defined signal 2
    SIGCHLD   20,17,18    Ign     Child stopped or terminated
    SIGCONT   19,18,25    Cont    Continue if stopped
    SIGSTOP   17,19,23    Stop    Stop process
    SIGTSTP   18,20,24    Stop    Stop typed at terminal
    SIGTTIN   21,21,26    Stop    Terminal input for background process
    SIGTTOU   22,22,27    Stop    Terminal output for background process:wq
*/


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
