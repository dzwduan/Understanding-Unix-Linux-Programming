#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"smsh.h"

#define is_delim(x) ((x)==' '||(x)=='\t')

/**
 * @brief 从fp读取下一个命令行
 * 
 * @param prompt 
 * @param fp 
 * @return char* 读取到的命令行
 */
char *next_cmd(char* prompt, FILE *fp){
    char * buf;         //buffer
    int bufsize = 0;    //totalsize
    int pos = 0;        //current position
    int c;              //input char

    //每次打印前置引导符号
    printf("%s",prompt);

    //每次读一个字符
    while((c=getc(fp))!=EOF) {
        //是否需要扩容
        if(pos+1 >= bufsize){
            if(bufsize==0) 
                buf = emalloc(BUFSIZ);
            else
                buf = erealloc(buf,bufsize + BUFSIZ);
            bufsize += BUFSIZ;
        }
        
        //是否结束
        if(c=='\n')
            break;
        buf[pos++] = c;
    }
    // EOF and no input
    if(c==EOF && pos==0)
        return NULL;
    buf[pos] = '\0';
    return buf;
}

/**
 * @brief 根据空白切割字符串
 * 
 * @param line 
 * @return char** 二维字符数组
 */
char ** splitline(char * line) {
    char **args;
    int spots = 0;
    int bufspace = 0;
    int argnum = 0;    //记录字符串个数
    char * cp = line;  //current position
    char * start;
    int len;

    //输入为空直接ret
    if(line==NULL)
        return NULL;

    //args用于返回
    args = emalloc(BUFSIZ);
    //表中字节数
    bufspace = BUFSIZ;
    //存储了多少指针类型
    spots = BUFSIZ/sizeof(char *);
    //cp遍历line的每个字符
    while(*cp!='\0') {
        //跳过空白字符
        while(is_delim(*cp)) cp++;
        //读到末尾
        if(*cp=='\0')   break;
        //是否需要扩容
        if(argnum+1 > spots) {
            args = erealloc(args,bufspace+BUFSIZ);
            bufspace += BUFSIZ;
            spots += (BUFSIZ/sizeof(char *));
        }

        //截取字符串
        start = cp;
        len = 1;
        while(*++cp!='\0' && !is_delim(*cp)) len++;
        args[argnum++] = newstr(start,len);
    }
    args[argnum] = NULL;
    return args;
}

/**
 * @brief 为字符串分配空间
 * 
 * @param s char *
 * @param l int 
 * @return char* 已分配空间的字符串
 */
char * newstr(char *s, int l){
    char * rv = emalloc(l+1);
    rv[l] = '\0';
    strncpy(rv,s,l);
    return rv;
}

/**
 * @brief 释放二维字符数组
 * 
 * @param list 
 */
void freelist(char **list) {
    char ** cp = list;
    while(*cp){
        free(*cp++);
    }
    free(list);
}

void * emalloc(size_t n) {
    assert(n>=0);

    void * rv;
    if((rv=malloc(n))==NULL) 
        fatal("out of memory","",1);
    return rv;
}

void * erealloc(void * p, size_t n) {
    assert(n>=0);

    void * rv;
    if((rv=realloc(p,n))==NULL)
        fatal("realloc() failed","",1);
    return rv;
}

