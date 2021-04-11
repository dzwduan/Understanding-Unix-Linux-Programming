#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int ac, char * av){
    int fd;
    char buf[BUFSIZ];
    if(ac!=2){
        fprintf(stderr,"usage:wriet0 ttyname\n");
        exit(1);
    }

    fd = open(av[1],O_WRONLY);
    if(fd==-1){
        perror(av[1]);
        exit(1);
    }
    //stream->buf
    while(fgets(buf,BUFSIZ,stdin)){
        //buf->fd fd即ttyname
        if(write(fd,buf,strlen(buf))==-1) break;
    }

    close(fd);
    return 0;
}