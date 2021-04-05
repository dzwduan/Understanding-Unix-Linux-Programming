#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>

void do_ls(char []);

int main(int argc, char *argv[]){

    if(argc == 1) do_ls(".");
    else
    while(--argc){
        printf("%s:\n",*++argv);
        do_ls(*argv);
    }
    return 0;
}



void do_ls(char dirname[]){
    DIR * dir_ptr;
    struct dirent * direntp;

    if((dir_ptr = opendir(dirname))==NULL){
        fprintf(stderr, "ls1: can not open %s\n",dirname);
    }
    else{
        while((direntp = readdir(dir_ptr))){
            printf("%s ",direntp->d_name);
        }
        puts("");
        closedir(dir_ptr);
    }
}

//没有排序
//没有分栏
//多列出了 .  ..
//没有添加-l选项 ，没有高亮