#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ptrace.h>

int main(int argc, char *argv[]){
    pid_t child_pid;
    if(argc<2){
        fprintf(stderr,"Expected a program name as argument\n");
        return -1;
    }

    child_pid = fork();
    //子进程
    if(child_pid==0){
        run_target(argv[1]);
    }
    else if(child_pid>0){
        run_debugger(child_pid);
    }
    else{
        perror("fork");
        return -1;
    }
    return 0;
}

void run_target(const char * programname){
     procmsg("target started. will run '%s'\n", programname);

    /* Allow tracing of this process */
    if (ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) {
        perror("ptrace");
        return;
    }

    /* Replace this process's image with the given program */
    execl(programname, programname, 0);
}

