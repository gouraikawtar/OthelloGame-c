#include "main.h"

int main()

{
    /// initializes the screen
    /// sets up memory and clears the screen
    initscr();

    /****************************** Menu test ********************************/

    /****************************** 1 vs Robot mode  test - Random  ********************************/


    /****************************** 1 vs 1 mode test ********************************/
    /*int **othello_b = NULL;
    int player;
    othello_b = initBoard(othello_b);
    othello_b = setSavedGame(othello_b,&player,"kawtar");
    displayBoard(othello_b);*/
    /*Queue *q = createQueue();
    enQueue(q,'c',4,1);
    enQueue(q,'d',1,2);
    displayQueue(q);*/

    //getBest10Scores();
    game();
    /*User u;
    u = authentication();
    printw("Username = %s\n",u.userName);
    refresh();*/
    /*int accessTest = 0 , mode , robotMode ;
    User currentUser ;
    currentUser = access(&accessTest);
    printw("%s",currentUser.userName);
    if (accessTest==1)
    {
      clear();
      switch(modesMenu())
      {
      case 0 :
        playFirstMode();
        break;
      case 1 :
          switch(_1vsRobotMenu())
          {
          case 0 :
              playVsRobot_Easy();

          }

      }

    }

    else
    {
        clear();
        move(3,40);
        printw("We couldn't access this account , please exit and try again !");
    }*/


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


