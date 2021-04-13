#include <stdio.h>
#include <curses.h>

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
    }

    refresh();
    getch();
    endwin();
}