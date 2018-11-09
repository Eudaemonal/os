#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


// Example ./test02 ls tee

int main(int argc, char* argv[]){
    int fd[2];

    if(argc < 3){
        fprintf(stderr, "Usage: %s command1 command2\n", argv[0]);
        exit(1);
    }

    if(pipe(fd)==-1){
        perror("pipe call");
        exit(2);
    }

    switch(fork()){
        case -1:
            perror("fork");
            exit(1);
        case 0:
            dup2(fd[1], fileno(stdout));
            close(fd[0]);
            close(fd[1]);
            execlp(argv[1], argv[1], NULL);
            perror("execlp");
            exit(1);
        default:
            dup2(fd[0], fileno(stdin));
            close(fd[0]);
            close(fd[1]);
            execlp(argv[2], argv[2], NULL);
            exit(2);
    }
    return 0;

}
