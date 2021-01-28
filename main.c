#include <ncurses.h>
#include <stdlib.h>
#include "1vs1-functions.h"
#include "menu.h"

int main()
{
    /// initializes the screen
    /// sets up memory and clears the screen
    initscr();

    /****************************** Menu test ********************************/

    /*int click;
    //click = gameOptionsMenu();
    //click = afterAuthMenu();
    click = modesMenu();
    clear();
    printw("click = %d\n",click);

    refresh();*/
    //beforeAuthMenu();

    /****************************** 1 vs 1 mode test ********************************/

    /*int **othello_b = NULL;
    int pos_x, pos_y;
    int player = 1;
    ///Initialize board
    othello_b = initBoard(othello_b);
    //displayBoard(othello_b);
    //validTry(othello_b,player,&pos_x,&pos_y);
    ///Play game
    while(!gameOver(othello_b))
    {
        displayBoard(othello_b);
        validTry(othello_b,player,&pos_x,&pos_y);
        othello_b = changeColor(othello_b,player,pos_x,pos_y);
        if(play(othello_b,player%2+1))
            player = player%2+1;
        clear();
    }
    ///Display winner when the game is over
    displayWinner(othello_b);
    ///Destroy board and free memory
    destroyBoard(othello_b);*/
    playFirstMode();

    getch();
    endwin();

    return 0;
}

/*int x = 5;
    int y = 2;
    int p = 1;
    savePlayer_sPosition(x,y,p,"username2.bin");*/

    /*int **othello_b = NULL;
    int player = 1;
    ///Initialize board
    othello_b = initBoard(othello_b);
    othello_b = getPlayer_sPosition(othello_b,&player,"username2.bin");
    displayBoard(othello_b);
    printw("next player = %d \n",player);
    destroyBoard(othello_b);*/
