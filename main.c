#include <ncurses.h>
#include <stdlib.h>

int main()
{
    initscr();

    printw("Hello world!\n");

    refresh();
    getch();
    endwin();
    return 0;
}
