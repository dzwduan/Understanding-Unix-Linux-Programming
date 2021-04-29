#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define YES 1
#define NO 0
#define DFL_PROMT "$"
#define IS_DELIM(x) ((x) == ' ' || (x) == '\t')

//忽略退出信号
void setup()
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
    fprintf(stderr, "Error: %s, %s\n", s1, s2);
    exit(n);
}

/**
 * @brief 运行命令
 * 
 * @param argv 二维数组
 * @return int 命令的结束状态
 */
int execute(char *argv[])
{
    int pid;
    int child_info = -1;

    if (argv[0] == NULL)
    {
        return 0;
    }
    if ((pid = fork()) == -1)
    {
        perror("fork");
    }
    else if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        execvp(argv[0], argv);
        perror("can not execute command");
        exit(1);
    }
    else
    {
        if (wait(&child_info) == -1)
        {
            perror("wait");
        }
    }
    //返回的是退出状态
    return child_info;
}

/**
 * @brief 分配n字节并检错
 * 
 * @param n 
 * @return void* 
 */
void *emalloc(size_t n)
{
    void *rv;
    if ((rv = malloc(n)) == NULL)
        fatal("out of memory", "", 1);
    return rv;
}

/**
 * @brief realloc n字节
 * 
 * @param p 
 * @param n 
 * @return void* 
 */
void *erealloc(void *p, size_t n)
{
    void *rv;
    if ((rv = realloc(p, n)) == NULL)
        fatal("realloc() failed", "", 1);
}

/**
 * @brief 从输入流中读入下一个命令
 * 
 * @param prompt 命令行起始符号
 * @param fp 
 * @return char* 动态分配的string
 */
char *next_cmd(char *prompt, FILE *fp)
{
    char *buf;        /*the buffer */
    int bufspace = 0; /*total size*/
    int pos = 0;      /*current position */
    int c;            /*input char*/

    printf("%s", prompt);

    while ((c = getc(fp)) != EOF)
    {
        /*need space?*/
        if (pos + 1 >= bufspace)
        {
            if (bufspace == 0)
            {
                //BUFSIZ 8192
                buf = emalloc(BUFSIZ);
            }
            else
            { /*expand*/
                buf = erealloc(buf, bufspace + BUFSIZ);
            }
            bufspace += BUFSIZ;
        }

        if (c == '\n')
        {
            break;
        }

        buf[pos++] = c;
    }

    //EOF and no input
    if (c == EOF && pos == 0)
    {
        return NULL;
    }
    buf[pos] = '\0';
    return buf;
}

/**
 * @brief 为字符串s分配长度为l+1的空间
 * 
 * @param s 
 * @param l 
 * @return char* 分配后的新地址
 */
char *newstr(char *s, int l)
{
    char *rv = emalloc(l + 1);
    rv[l] = '\0';
    strncpy(rv, s, l);
    return rv;
}

/**
 * @brief 将字符串分解为字符数组
 * 
 * @param line  字符串
 * @return char** 分解后的字符数组
 */
char **splitline(char *line)
{

    char **args;
    int spots = 0;    //spots in table
    int bufspace = 0; //bytes in table
    int argnum = 0;   //slots used
    char *cp = line;  //pos in string
    char *start;
    int len;

    if (line == NULL)
    {
        return NULL;
    }

    args = emalloc(BUFSIZ);
    bufspace = BUFSIZ;
    spots = BUFSIZ / sizeof(char *);

    while (*cp != '\0')
    {
        while(IS_DELIM(*cp)) cp++;
        if(*cp == '\0') break;

        if(argnum + 1 >= spots){
            args = erealloc(args,bufspace+BUFSIZ);
            bufspace += BUFSIZ;
            spots +=(BUFSIZ/sizeof(char *));
        }
        start = cp;
        len = 1;
        while(*++cp !='\0' && !(IS_DELIM(*cp))) len++;
        //新建字符串
        args[argnum++] = newstr(start,len);

        //printf("%s ",args[argnum-1]);
    }

    args[argnum] = NULL;
    return args;
}

/**
 * @brief 释放二维数组
 * 
 * @param list 
 */
void freelist(char **list){
    char **cp = list;
    while(*cp) {
        free(*cp++);
    }
    free(list);
}


int main()
{

    char *cmdline, **arglist;
    int result;

    setup();

    while ((cmdline = next_cmd(DFL_PROMT, stdin)) != NULL)
    {   //printf("%s \n",cmdline);
        if ((arglist = splitline(cmdline)) != NULL)
        {
            result = execute(arglist);
            freelist(arglist);
        }
        free(cmdline);
    }
    return 0;
}
