/**
* Game menus functions implementation
*/
#include <ncurses.h>
#include <stdlib.h>
#include "menu.h"
/*int LoginMenu()
{
    // sets menu's options
    choice menu[3] = {"Login","Create Account","Exit"};
    int choice;
    int highlight = 0;
    int y, x_max, y_max;

    // gets window's max x & window's max y
    // Window = stdscr in this case
    x_max = getmaxx(stdscr); y_max = getmaxy(stdscr);
    // creates a window
    WINDOW *menu_win = newwin(10,20,y_max/6,x_max/3);
    refresh();
    // sets window's borders
    box(menu_win,0,0);
    wrefresh(menu_win);

    // makes cursor invisible
    curs_set(0);

    // prints menu's options
    wprintw(menu_win," Welcome to OTHELLO ");
    keypad(menu_win,true);
    // while no option is chosen, keeps displaying the menu
    while(1)
    {
        // sets y position on 3
        y = 3;
        for(int i=0;i<3;i++)
        {
            if(i==highlight)    // the cursor is on the option of position i
                wattron(menu_win,A_REVERSE);    // sets attribute on A_REVERSE
            mvwprintw(menu_win,y,4,menu[i].option); // prints the option
            wattroff(menu_win,A_REVERSE);       // disables the A_REVERSE attribute
            y = y +2;
        }
        // gets user's click
        choice = wgetch(menu_win);
        switch(choice)
        {
            case KEY_UP:   // up key is clicked
                highlight--;    // moves to previous option, there's no option[-1]
                if(highlight == -1) // highlight value is negative
                    highlight = 0;  // sets value on 0
                break;
            case KEY_DOWN:  // down key is clicked
                highlight++;    // moves to next option
                if(highlight == 3) // highlight value == 3, there's no option[3]
                    highlight = 2;  //sets value on 2
                break;
            default:
                break;
        }
        if(choice == 10) // enter key is clicked
            break;
    }
    // returns index of the chosen option
    return highlight;
        //mvwprintw(stdscr,0,0,"Your choice was %s",menu[highlight].option);
    //wrefresh(menu_win);
}*/
