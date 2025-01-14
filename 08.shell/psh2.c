#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>

#define MAXARGS 20   //cmd line args
#define ARGLEN 100   //token length

//add terminal signal and malloc space.
char * makestring(char * buf){
    char * cp;

    buf[strlen(buf)-1] = '\0';
    cp = malloc(strlen(buf)+1);
    if(cp==NULL){
        fprintf(stderr, "no memory\n");
        exit(1);
    }
    strcpy(cp,buf);
    return cp;
}

void execute(char * arglist[]){
    int pid, exitstatus;
    
    pid = fork();
    switch(pid){
        case -1:
            perror("fork failed");
            exit(1);
        case 0: 
            execvp(arglist[0], arglist);
            perror("execvp failed");
            exit(1);
        default:
            while(wait(&exitstatus)!=pid);
            printf("child exited with status %d, %d\n", exitstatus>>8,exitstatus&0377);
    }
}

int main(){

    char * arglist[MAXARGS+1]; //array of ptrs 二维数组
    int numargs;               //index into array 
    char argbuf[ARGLEN];       //read stuff
    char * makestring();       //malloc etc.

    numargs = 0;

    while(numargs<MAXARGS){
        printf("arg[%d]: ",numargs);
        //stdin -> argbuf , size == ARGLEN
        if(fgets(argbuf,ARGLEN,stdin) && *argbuf != '\n'){
            arglist[numargs++] = makestring(argbuf);
        }else {
            if(numargs > 0){
                arglist[numargs] = NULL; //close list
                execute(arglist);
                numargs = 0; //reset
            }
        }
    }
    return 0;
}