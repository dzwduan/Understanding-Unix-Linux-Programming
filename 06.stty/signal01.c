#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int main(){
    void f(int);
    int i;
    signal(SIGINT,f);
    for(i=0;i<5;i++){
        printf("Hello\n");
        sleep(1);
    }
}

void f(int signum){
    printf("Ctrl-C\n");
}