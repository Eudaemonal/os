#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
    int sockfd, newsockfd, portno, clilen;

    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    // socket 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){ 
        perror("socket");
        exit(1);        
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // bind
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        perror("bind");
        exit(1);
    }

    // listen
    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    // accept
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0){ 
        perror("accept");
        exit(1);
    }

    bzero(buffer,256);

    // read
    n = read(newsockfd,buffer,255);
    if (n < 0){
       perror("read");
       exit(1);
    }
    printf("Here is the message: %s\n",buffer);
    
    // write
    n = write(newsockfd,"I got your message",18);
    if (n < 0){
       perror("write");
        exit(1);
    }
                                                                             
    return EXIT_SUCCESS;    
}
