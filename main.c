#include "main.h"

int main()

{
    /// initializes the screen
    /// sets up memory and clears the screen
    initscr();

    /****************************** Menu test ********************************/

    /****************************** 1 vs Robot mode  test - Random  ********************************/


    /****************************** 1 vs 1 mode test ********************************/
    game();

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


    /****************************** 1 vs Robot test - Random  ********************************/


