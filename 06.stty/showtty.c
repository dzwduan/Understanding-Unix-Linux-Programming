#include<stdio.h>
#include<termios.h>

int main(){
    struct termios ttyinfo;
    if(tcgetattr(0,&ttyinfo)==-1){
        perror("tcgetattr");
        exit(1);
    }

    //showbaud()

}

struct flaginfo {int flvalue; char *fl_name;};

struct flaginfo input_flags[] = {
    IGNBRK, "Ignore break condition",
    BRKINT, "Signal interrupt on break."
};

struct flaginfo local_flags[] = {
    ISIG, "Enable signals",
    ICANON, "canonical input",
};