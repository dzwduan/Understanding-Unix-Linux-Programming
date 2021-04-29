#include<stdio.h>
#include<string.h>
#include"smsh.h"

enum status {NEUTRAL,WANT_THEN,THEN_BLOCK,WANT_ELSE,ELSE_BLOCK};
enum results {SUCCESS,FAIL};

static int if_state = NEUTRAL;
static int if_result = SUCCESS;
static int last_state = 0;

/**
 * @brief 根据所处区域和堆区域的判断决定是否能够执行
 * 
 * @return int 
 */
int ok_to_execute() {
    int rv = 1;
    if(if_state==WANT_THEN) {
        syn_err("then expected");
        rv = 0;
    }
    else if(if_state==WANT_ELSE) {
        syn_err("ELSE expected");
        rv = 0;
    }
    else if((if_state==THEN_BLOCK||if_state==ELSE_BLOCK) && if_result==SUCCESS)
        rv = 1;
    else if((if_state==THEN_BLOCK||if_state==ELSE_BLOCK) && if_result==FAIL)
        rv = 0;

    return rv;
}

int check_if(char *s){
    return strcmp(s,"if");
}

int check_then(char *s){
    return strcmp(s,"then");
}

int check_else(char *s){
    return strcmp(s,"else");
}

int check_fi(char *s){
    return strcmp(s,"fi");
}

/**
 * @brief 判断是否是 if then else fi 这几个命令
 * 
 * @param s 
 * @return int 
 */
int is_control_command(char *s) {
    return (check_if(s)==0 || check_then(s)==0 || check_else(s)==0 || check_fi(s)==0);
}

/**
 * @brief 根据if then else fi 改变状态  if then then_block else else_block fi
 * 
 * @param args 
 * @return int 
 */
int do_control_command(char** args){
    char * cmd = args[0];
    int rv = -1;

    if(check_if(cmd)==0){

        if(if_state!=NEUTRAL)
            rv = syn_err("if unexpected");
        else{
            last_state = process(args+1);
            if_result = (last_state==0?SUCCESS:FAIL);
            if_state = WANT_THEN; //下一个区域
            rv = 0;
        }
    }
    else if(check_then(cmd)==0){
        if(if_state!=WANT_THEN)
            rv = syn_err("then unexpected");
        else {
            if_state = THEN_BLOCK;
            rv = 0;
        }
    }
    else if(check_else(cmd)==0){
        if(if_state!=WANT_ELSE)
            rv = syn_err("else unexpected");
        else {
            if_state = ELSE_BLOCK;
            rv = 0;
        }
    }
    else if(check_fi(cmd)==0){
        if(if_state!=THEN_BLOCK || if_state!=ELSE_BLOCK)
            rv = syn_err("fi unexpected");
        else {
            if_state = NEUTRAL;
            rv = 0;
        }
    }
    else
        fatal("internal error processing:",cmd,2);
    return rv;
}

/**
 * @brief 处理语法错误
 * 
 * @param msg 
 * @return int 
 */
int syn_err(char *msg) {
   if_state = NEUTRAL;
   fprintf(stderr,"syntax error: %s\n",msg);
   return -1; 
}