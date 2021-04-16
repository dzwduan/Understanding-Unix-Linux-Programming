#include<stdio.h>
#include<sys/time.h>
#include<signal.h>

int main(){
    void countdown(int);

    signal(SIGALRM,countdown);
    
    if(set_ticker(500)==-1) perror("set_ticker");
    else while(1) pause();
    return 0;

}


void countdown(int signum){
    static int num = 10;
    printf("%d..",num--);
    fflush(stdout);  //强制写出缓冲区内容
    if(num<0){
        printf("DONE!\n");
        exit(0);
    }
}


int set_tickr(int n_msecs){
    struct itimerval new_timeset;
}