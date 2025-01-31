/**
* Game menus functions implementation
*/
#include "main.h"

void firstScreen()
{
    int w_width, w_height;
    int x, y;
    struct tm* local;
    time_t t = time(NULL);
    local = localtime(&t);

    w_width = 50;
    w_height = 20;
    y = (getmaxy(stdscr) - w_height)/2;
    x = (getmaxx(stdscr) - w_width)/2;

    WINDOW *win = newwin(w_height,w_width,y,x);
    refresh();
    // sets window's borders
    box(win,0,0);
    wrefresh(win);
    mvwprintw(win,5,15,"WELCOME TO OTHELLO");
    mvwprintw(win,10,13,"Made by : ZINEB & KAWTAR");
    mvwprintw(win,15,13,"%s",asctime(local));
    wrefresh(win);
    move(getmaxy(stdscr)-2,getmaxx(stdscr)-40);
    printw("Press any key to continue..");
    refresh();
}

int LoginMenu()
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
}

int gameOptionsMenu()
{
    // sets menu's options
    choice menu[3] = {"Resume game","Restart game","Exit"};
    int menu_length = 3;
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
    wprintw(menu_win,"Game Options");
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
    delwin(menu_win);
    // returns index of the chosen option
    return highlight;
        //mvwprintw(stdscr,0,0,"Your choice was %s",menu[highlight].option);
    //wrefresh(menu_win);
}

int afterAuthMenu()
{
    // sets menu's options
    choice menu[4] = {"New game","Continue game","Best scores","Exit"};
    int choice;
    int highlight = 0;
    int y, x_max, y_max;

    // gets window's max x & window's max y
    // Window = stdscr in this case
    x_max = getmaxx(stdscr); y_max = getmaxy(stdscr);
    // creates a window
    WINDOW *menu_win = newwin(15,20,y_max/6,x_max/3);
    refresh();
    // sets window's borders
    box(menu_win,0,0);
    wrefresh(menu_win);

    // makes cursor invisible
    curs_set(0);

    // prints menu's options
    wprintw(menu_win,"Main Menu");
    keypad(menu_win,true);
    // while no option is chosen, keeps displaying the menu
    while(1)
    {
        // sets y position on 3
        y = 3;
        for(int i=0;i<4;i++)
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
                if(highlight == 4) // highlight value == 4, there's no option[4]
                    highlight = 3;  //sets value on 3
                break;
            default:
                break;
        }
        if(choice == 10) // enter key is clicked
            break;
    }
    delwin(menu_win);
    // returns index of the chosen option
    return highlight;
}

int modesMenu()
{
    // sets menu's options
    choice menu[2] = {"1 vs 1","1 vs Robot "};
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
    wprintw(menu_win,"Game Mode");
    keypad(menu_win,true);
    // while no option is chosen, keeps displaying the menu
    while(1)
    {
        // sets y position on 3
        y = 3;
        for(int i=0;i<2;i++)
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
                if(highlight == 2) // highlight value == 2, there's no option[2]
                    highlight = 1;  //sets value on 1
                break;
            default:
                break;
        }
        if(choice == 10) // enter key is clicked
            break;
    }
    delwin(menu_win);
    // returns index of the chosen option
    return highlight;
}

int _1vsRobotMenu()
{
    // sets menu's options
    choice menu[2] = {"Easy","Hard "};
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
    wprintw(menu_win,"1 vs Robot");
    keypad(menu_win,true);
    // while no option is chosen, keeps displaying the menu
    while(1)
    {
        // sets y position on 3
        y = 3;
        for(int i=0;i<2;i++)
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
                if(highlight == 2) // highlight value == 2, there's no option[2]
                    highlight = 1;  //sets value on 1
                break;
            default:
                break;
        }
        if(choice == 10) // enter key is clicked
            break;
    }
    // returns index of the chosen option
    return highlight;
}


int exitGameMenu()
{
    // sets menu's options
    choice menu[2] = {"Yes","No"};
    int choice;
    int highlight = 0;
    int y, x_max, y_max;

    // gets window's max x & window's max y
    // Window = stdscr in this case
    x_max = getmaxx(stdscr); y_max = getmaxy(stdscr);
    // creates a window
    WINDOW *menu_win = newwin(10,50,y_max/6,x_max/3);
    refresh();
    // sets window's borders
    box(menu_win,0,0);
    wrefresh(menu_win);

    // makes cursor invisible
    curs_set(0);

    // prints menu's options
    wprintw(menu_win,"Exit Game");
    keypad(menu_win,true);
    // while no option is chosen, keeps displaying the menu
    while(1)
    {
        mvwprintw(menu_win,1,1,"Do you want to save for later ?");
        // sets y position on 3
        y = 3;
        for(int i=0;i<2;i++)
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
                if(highlight == 2) // highlight value == 2, there's no option[2]
                    highlight = 1;  //sets value on 1
                break;
            default:
                break;
        }
        if(choice == 10) // enter key is clicked
            break;
    }
    delwin(menu_win);
    // returns index of the chosen option
    return highlight;
}
