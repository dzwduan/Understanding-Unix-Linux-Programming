/*
+----> show 24 lines from input
| +--> print [more?] message
| |    input Enter, SPACE, or q
| +--> if Enter, advance next page
+ ---- if Space, advance one line
       if q --> exit

*/


#include<stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE*);
int see_more(FILE*);


int main(int ac, int * av[]){
    FILE * fp;
    if(ac == 1)
    //没有参数，可能是 ls | more， 从stdin读入
        do_more(stdin);
    //否则从文件获取输入
    else
        while(--ac)
        //如果有多个文件，分别对每个do_more
        if((fp=fopen((char *)*++av,"r"))!=NULL){
            do_more(fp);
            fclose(fp);
        }
        else exit(1);
    return 0;
}

void do_more(FILE* fp){
    char line[LINELEN];
    int num_of_lines = 0;

    int see_more(FILE *), reply;//??
    FILE *fp_tty = fopen("/dev/tty","r");
    if(fp_tty==NULL) exit(1);
    //fp -> line
    while(fgets(line,LINELEN,fp)){
        //当读到24行需要换页时
        if(num_of_lines == PAGELEN){
            //是否获取分页显示的内容
            reply = see_more(fp_tty);
            if(reply == 0) break;
            num_of_lines -= reply;
        }
        // line -> stdout
        if(fputs(line,stdout) == EOF)
            exit(1);
        num_of_lines++;
    }
}


int see_more(FILE* cmd){
    int c;
    printf("\033[7m more?\033[m");
    //添加stty设置使得按下q直接退出
    system("stty -icanon");
    while((c=getc(cmd))!=EOF){
        //退出
        if(c=='q') return 0;
        //读取下一个24行
        if(c==' ') return PAGELEN;
        //换行
        if(c=='\n') return 1;
    }
    return 0;
}

//bug,滚动时more?也会随之向上,输入q不按回车没有反应
//因为getchar从标准输入读取的数据，ls也是标准输入
//解决办法是从stdin读入要分页的数据，从键盘读入用户输入
//  /dev/tty是键盘和显示器的设备描述文件