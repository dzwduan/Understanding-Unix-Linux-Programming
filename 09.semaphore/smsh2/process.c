#include<stdio.h>
#include"smsh.h"

/**
 * @brief 处理命令,分为不同区域
 * 
 * @param args 
 * @return int 
 */
int process(char **args){
    int rv = 0;
    //判空
    if(args[0]==NULL)
        rv = 0;
    else if(is_control_command(args[0]))
        rv = do_control_command(args);
    else if(ok_to_execute())
        rv = execute(args);

    return rv;
}

