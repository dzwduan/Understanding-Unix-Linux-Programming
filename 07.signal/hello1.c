#include<stdio.h>
#include<curses.h>

int main(){
    initscr();

    clear();
    move(10,20);
    addstr("Hello World");
    move(LINES-1,0); //move(y,x)
    refresh();
    getch();
    endwin();
    return 0;
}