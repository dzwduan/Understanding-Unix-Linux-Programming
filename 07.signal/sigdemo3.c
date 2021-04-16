#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>

#define INPUTLEN 100

int main(int argc, char * argv[]){
    void inthandler(int);
    void quithandler(int);
    char input[INPUTLEN];
    int nchars;

    signal(SIGINT,inthandler);
    signal(SIGQUIT,quithandler);

    do{
        printf("\nType a message\n");
        //read每次都是读到起始位置
        nchars = read(0,input,(INPUTLEN-1));
        if(nchars==-1) perror("read return error");
        else{
            input[nchars] = '\0';
            printf("You typed: %s",input);
            
        }
        //printf("input now : %p\n",input);
    }while(strncmp(input,"quit",4)!=0);
}

void inthandler(int s){
    printf("Received signal %d..waiting\n",s);
    sleep(2);
    printf("Leaving inthandler\n");
}


void quithandler(int s){
    printf("Received signal %d..waiting\n",s);
    sleep(2); //sleep直到时间够了或者遇到不能忽略的信号为止
    printf("Leaving quithandler\n");
}