#include<stdio.h>
#include<signal.h>
#include<unistd.h>

#define INPUTLEN 100

int main(){
    struct sigaction newhandler;
    sigset_t blocked;
    void inthandler();
    char x[INPUTLEN];

    newhandler.sa_handler = inthandler;  //SIG_DFL,SIG_IGN or function
    newhandler.sa_flags   = SA_RESETHAND | SA_RESTART; //当处理函数被调用时重置
    
    sigemptyset(&blocked); //clear all signals
    sigaddset(&blocked, SIGQUIT);
    newhandler.sa_mask = blocked; // block SIGQUIT

    if(sigaction(SIGINT,&newhandler,NULL)==-1)
        perror("sigaction");
    else
    while(1){
        fgets(x,INPUTLEN,stdin);
        printf("input: %s",x);
    }
    return 0;
}   


void inthandler(int s){
    printf("called with signal %d\n",s);
    sleep(s);
    printf("done handling signal %d\n",s);
}