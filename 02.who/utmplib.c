#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<utmp.h>
#include<unistd.h>

#define SHOWHOST

//开辟缓冲区
#define NRECS 16
#define NULLUT ((struct utmp*)NULL)
#define UTSIZE (sizeof(struct utmp))


//缓冲区大小,为什么是static char?
static char utmpbuf[NRECS * UTSIZE];  //buffer
//读到第几个
static int num_recs;   // num stored
//缓冲区存几个
static int cur_rec;    // next to go
//用于read的文件描述符,注意这里是全局的，所以后面都不用传参
static int fd_utmp = -1; // read from


//初始化 打开
utmp_open(char * filename){
    //打开文件返回文件描述符
    fd_utmp = open(filename, O_RDONLY);
    if(fd_utmp == -1){
        perror(filename);
        exit(1);
    } 
    //当前文件的遍历起点和缓冲总数都是0
    cur_rec = num_recs = 0;
    return fd_utmp;
}

//读下一个结构体
struct utmp* utmp_next(){
    struct utmp * recp;
    //打开失败
    if(fd_utmp == -1) return NULLUT;
    //TODO: reload more or not
    //前面的是什么？？
    if(cur_rec == num_recs && utmp_reload() == 0) return NULLUT;

    //get addr of next record
    recp = (struct tmp *)&utmpbuf[cur_rec*UTSIZE];
    //get finish dont forget add cur_rec
    cur_rec++;
    return recp;
}

int utmp_reload(){
    int amt_read;
    //读到缓冲区结尾是0,为什么没有加判断
    amt_read = read(fd_utmp,utmpbuf,NRECS*UTSIZE);
    //非结尾或者失败不是0
    num_recs = amt_read/UTSIZE;
    //当前位置为0
    cur_rec = 0;
    return num_recs;
}


utmp_close(){
    //文件描述符不出错就释放
    if(fd_utmp !=-1)
        close(fd_utmp);
}

void show_info(struct utmp *);
void show_time(time_t *);

int main(){
    struct utmp * utbufp, *utmp_next();
    
    //获取文件描述符
    if(utmp_open(UTMP_FILE)==-1){
        perror(UTMP_FILE);
        exit(1);
    }
    //从缓冲区里面读取，缓冲区最大16
    while((utbufp = utmp_next())!=NULLUT) show_info(utbufp);

    //读完释放文件描述符
    utmp_close();
    return 0;
}

void show_time(time_t* t){
    char *cp = ctime((const time_t *)&t);
    printf("%12.12s",cp+4);
}


void show_info(struct utmp * ut){

    //不是当前用户
    if(ut->ut_type!=USER_PROCESS) return;

    printf("%-8.8s",   ut->ut_user);
    printf("tty%-8.8s",ut->ut_line);

    show_time((time_t *)ut->ut_tv.tv_sec);

    #ifdef SHOWHOST
    printf("   (%s", ut->ut_host);
    #endif
    puts("");
}