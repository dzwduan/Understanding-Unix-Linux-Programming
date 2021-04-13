#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int main(){
    signal(SIGINT,SIG_IGN);
    printf("YOU can not stop me\n");
    for(int i=0;i<5;i++){
        sleep(1);
        printf("haha\n"); //如果不加换行就会缓冲一起输出
    }
}