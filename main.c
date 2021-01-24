#include <ncurses.h>
#include <stdlib.h>
#include "1vs1-functions.h"

int main()
{
    /// initializes the screen
    /// sets up memory and clears the screen
    initscr();

    /****************************** Menu test ********************************/

    //beforeAuthMenu();

    /****************************** 1 vs 1 mode test ********************************/

    int **othello_b = NULL;
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
    destroyBoard(othello_b);

    getch();
    endwin();

    return 0;
}
