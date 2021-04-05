/*
step1: man who     # Know who uses struct utmp
step2: man -k utmp # search utmp manual
step3: man utmp    # learn its structure, in see also, find related functions
step4: man getutent
step5: Write your own who command!
*/

/* who -- show users currently logged in

1. read the data structrue from utmp file
2. display information in a suitable way
*/

// man who -> utmp
// man -k file | grep utmp
// man 5 utmp

    //   struct utmp {
    //            short   ut_type;              /* Type of record */
//                pid_t   ut_pid;               /* PID of login process */
//                char    ut_line[UT_LINESIZE]; /* Device name of tty - "/dev/" */
//                char    ut_id[4];             /* Terminal name suffix,
//                                                 or inittab(5) ID */
//                char    ut_user[UT_NAMESIZE]; /* Username */
//                char    ut_host[UT_HOSTSIZE]; /* Hostname for remote login, or
//                                                 kernel version for run-level
//                                                 messages */
//                struct  exit_status ut_exit;  /* Exit status of a process
//                                                 marked as DEAD_PROCESS; not
//                                                 used by Linux init (1 */
//                /* The ut_session and ut_tv fields must be the same size when
//                   compiled 32- and 64-bit.  This allows data files and shared
//                   memory to be shared between 32- and 64-bit applications. */
//            #if __WORDSIZE == 64 && defined __WORDSIZE_COMPAT32
//                int32_t ut_session;           /* Session ID (getsid(2)),
//                                                 used for windowing */
//                struct {
//                    int32_t tv_sec;           /* Seconds */
//                    int32_t tv_usec;          /* Microseconds */
//                } ut_tv;                      /* Time entry was made */
//            #else
//                 long   ut_session;           /* Session ID */
//                 struct timeval ut_tv;        /* Time entry was made */
//            #endif

//                int32_t ut_addr_v6[4];        /* Internet address of remote
//                                                 host; IPv4 address uses
//                                                 just ut_addr_v6[0] */
//                ch
// };

//how to read ? man 2 read
//how to get file descriptor? man 2 open
//how to release file descriptor? man 2 close

#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include<utmp.h>
#include<fcntl.h>
#include<time.h>

#define SHOWHOST 

void show_time(time_t *);
void show_info(struct utmp * ut);

int main(){
    //ut用于读取缓冲值
    struct utmp ut;
    size_t ut_size = sizeof(struct utmp);
    //char buf[ut_size];
    int fp = open(UTMP_FILE,O_RDONLY);
    if(fp == -1){
        perror(UTMP_FILE);
        exit(1);
    }

    while((read(fp,&ut,ut_size))==ut_size){
        show_info(&ut);
    }
    //用完释放文件描述符
    close(fp);
    return 0;
}

void show_time(time_t* t){
    char *cp = ctime((const time_t *)&t);
    printf("%12.12s",cp+4);
}


void show_info(struct utmp * ut){

    if(ut->ut_type!=USER_PROCESS) return;

    printf("%-8.8s",   ut->ut_user);
    printf("tty%-8.8s",ut->ut_line);

    show_time((time_t *)ut->ut_tv.tv_sec);

    #ifdef SHOWHOST
    printf("   (%s", ut->ut_host);
    #endif
    puts("");
}