#include<stdio.h>
#include<termios.h>
#include<fcntl.h>
#include<string.h>
#include <unistd.h>
#include <ctype.h>

#define ASK "Do you want another transaction"
#define TRIES 3
#define SLEEPRIME 2
#define BEEP putchar('\a')

int get_ok_char(){
    int  c;
    while((c=getchar())!=EOF && strchr("yYnN",c)==NULL);
    return c;
}


int get_response(char *question, int maxtries){
    int input;
    printf("%s (y|n)?",question);
    fflush(stdout); //force output

    while(1){
        sleep(SLEEPRIME);
        input = tolower(get_ok_char());
        if(input == 'y') return 0;
        if(input == 'n') return 1;
        if(maxtries -- == 0) return 2;
        BEEP;
    }
}


void set_cr_noecho_mode(){
    struct termios ttystate;
    tcgetattr(0,&ttystate);
    ttystate.c_lflag &=~ICANON;
    ttystate.c_lflag &=~ECHO;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &ttystate);   
}

void set_nodelay_mode(){
    int termflags;
    termflags = fcntl(0,F_GETFL); //read curr settings
    termflags |= O_NDELAY;
    fcntl(0,F_SETFL,termflags);
}

void tty_mode(int how){
    static struct termios original_mode;
    static int original_flags;
    if(how==0){
        tcgetattr(0,&original_mode);
        original_flags = fcntl(0,F_GETFL);
    }   
    else{
        tcsetattr(0, TCSANOW, &original_mode);
        fcntl(0,F_SETFL,original_flags);
    }
}

int main(){
    int response;
    tty_mode(0); //saved
    set_cr_noecho_mode();
    set_nodelay_mode();
    response = get_response(ASK,TRIES);
    tty_mode(1);
    return response;
}

//fflush为什么要用：因为终端驱动缓冲了输出，直到接收一个换行符或者试图从终端读取输入才写出缓冲
//使用fflush立即写出

//问题 ctrl-c会终止