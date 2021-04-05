#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

#define BUFFER_SIZE 4096
#define COPYMODE    0644

void oops(char *, char *);

int main(int argc,char *argv[]){
    
    int in_fd,out_fd,n_chars;

    char buf[BUFFER_SIZE];


    if(argc!=3){
        fprintf(stderr, "usage: %s source destination\n",*argv);
        exit(1); //why 1?
    }

    if((in_fd = open(argv[1],O_RDONLY))==-1)
        oops("can not open", argv[1]);
    if((out_fd= creat(argv[2],COPYMODE))==-1)
        oops("can not create",argv[2]);
    
    //一直读到结束
    while((n_chars = read(in_fd,buf,BUFFER_SIZE))>0)
        if(write(out_fd,buf,n_chars)!=n_chars)
            oops("Write error to",argv[2]);

    if(n_chars == -1)
        oops("read error from",argv[1]);

    if(close(in_fd) == -1 || close(out_fd) == -1)
        oops("Error closing files","");
    puts("");
    return 0;
}

void oops(char *s1, char* s2){
    fprintf(stderr, "error:%s",s1);
    perror(s2);
    exit(1);
}