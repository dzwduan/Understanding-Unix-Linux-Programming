#include<stdio.h>
#include<sys/ioctl.h>

void print_screen(){
    struct winsize wbuf;
    if(ioctl(0,TIOCGWINSZ,&wbuf)!=-1){
        printf("%d rows x %d cols\n",wbuf.ws_col,wbuf.ws_col);
        printf("%d wide x %d tall\n",wbuf.ws_xpixel,wbuf.ws_ypixel);
    }
} 

int main(){
    print_screen();
    return 0;
}