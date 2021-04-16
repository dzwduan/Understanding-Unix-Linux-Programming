#include<stdio.h>
#include<signal.h>

void main(){
    void wake_up(int);
    printf("about to sleep for 4 seconds\n");
    signal(SIGALRM,wake_up);
    alarm(4);
    pause();
    printf("Morning so soon?\n");
}


void wakeup(int signnum){
    #ifndef SHHHH
        printf("Alarm received from kernel\n");
    #endif
}