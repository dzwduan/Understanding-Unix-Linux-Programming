#include<stdio.h>
#include<termios.h>

#define QUESTION "Do you want another transaction"



int get_response(char * question){
    printf("%s [y/n]?",question);
    while(1){
        switch(getchar()){
            case 'y':
            case 'Y': return 0;
            case 'n':
            case 'N':
            case EOF: return 1;
        }
    }
}

int main(){
    int response;
    response = get_response(QUESTION);
    return response;
}

//有bug
//1.必须按下回车才能接受数据
//2.按下回车时，接受整行数据进行处理，因此必定为否定
//改进
//关闭规范输入，敲键的同时得到输入的字符
//规范输入是缓冲模式，仅在回车时才将缓冲字符发送到程序