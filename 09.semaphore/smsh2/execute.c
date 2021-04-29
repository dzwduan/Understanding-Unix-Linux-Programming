#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include"smsh.h"

/**
 * @brief 执行argv命令
 * 
 * @param argv 命令
 * @return int wait返回状态 或者 -1代表错误
 */
int execute(char * argv[]) {
    int pid;
    int child_info = -1; //初始-1代表错误

    //命令不为空
    if(argv[0]==NULL) return 0;
    //fork不出错
    if((pid = fork())==-1) perror("Fork");
    //子进程 执行
    else if(pid == 0) {
        //默认信号处理方式
        signal(SIGQUIT,SIG_DFL);
        signal(SIGINT,SIG_DFL);
        execvp(argv[0],argv);
        perror("can not execute command");
        //1是正确退出
        exit(1);
    }
    //父进程 等待
    else{
        if(wait(&child_info)==-1) perror("wait");
        return child_info;
    }
}