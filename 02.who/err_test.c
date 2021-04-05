#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


extern int errno;

int main(){
    int fd;

    fd = open("file",O_RDONLY);
    if(fd == -1){
        perror("cant open file");

    }
}