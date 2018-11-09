#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
parent will cerate n process, and wait for them to finish execution before exits
*/

void child_process(int id){
    int pid = getpid();
    printf("Child process #%d starts ( pid = %d )\n", id, pid);
}


int main(int argc, char *argv[]){
    int n = 4;
    int pid;
    int i;
    for(i = 0; i < n; ++i){
        pid = fork();
        if(pid==0){
            child_process(i);
            exit(0);
        }else{
            printf("Parent fork new process #%d ( pid = %d )\n", i, pid);
        }
    }
    /*wait untiil all child process exits*/
    while(wait(NULL)>0);    

    return EXIT_SUCCESS;
}
