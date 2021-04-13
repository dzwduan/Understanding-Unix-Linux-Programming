#include <stdio.h>
#include <curses.h>
#include <unistd.h>
int main()
{
    int i;
    initscr();
    clear();

    for (int i = 0; i < LINES; i++)
    {
        move(i, i + 1);
        if (i % 2 == 1)
            standout(); //启动反色
        addstr("Hello World");
        if (i % 2 == 1) //关闭反色
            standend();
        //保证每次循环后旧的消失
        refresh();
        sleep(1);
        move(i, i + 1);
        addstr("           ");
    }
    endwin();
}