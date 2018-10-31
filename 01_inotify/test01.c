#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/inotify.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )


void read_callback(struct inotify_event* event){
    switch(event->mask){
        case IN_CREATE:
            if(event->mask & IN_ISDIR){
                printf( "Directory %s created.\n", event->name );
            }else{
                printf( "File %s created.\n", event->name );
            }
            break;
        case IN_DELETE:
            if ( event->mask & IN_ISDIR ) {
                printf( "Directory %s deleted.\n", event->name );
            }
            else {
                printf( "File %s deleted.\n", event->name );
            }
            break;
        case IN_OPEN:
            printf("File %s opened.\n", event->name);
            break;
        case IN_MODIFY:
            printf("File %s modified.\n", event->name);
            break;
        default:
            printf("Unhandled event %x.\n", event->mask);
            return;
    }
}

int main(int argc, char* argv[]){
    int length, i = 0;
    int fd;
    int wd;
    char buffer[EVENT_BUF_LEN];

    /*creating the INOTIFY instance*/
    fd = inotify_init();

    /*checking for error*/
    if ( fd < 0 ) {
        perror( "inotify_init error" );
    }

    /*adding the “tmp” directory into watch list. Here, the suggestion is to validate the existence of the directory before adding into monitoring list.*/
    wd = inotify_add_watch( fd, "tmp", IN_CREATE | IN_DELETE );

    /*read to determine the event change happens on “tmp” directory. Actually this read blocks until the change event occurs*/ 

    length = read( fd, buffer, EVENT_BUF_LEN ); 

    /*checking for error*/
    if ( length < 0 ) {
        perror( "read" );
    }  

    /*actually read return the list of change events happens. Here, read the change event one by one and process it accordingly.*/
    while ( i < length ) {     
        struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];     
        if ( event->len ) {
            read_callback(event);
        }
        i += EVENT_SIZE + event->len;
    }
    /*removing the “tmp” directory from the watch list.*/
    inotify_rm_watch( fd, wd );

    /*closing the INOTIFY instance*/
    close( fd );
}

