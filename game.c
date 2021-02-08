#include "main.h"

/*void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds) ;
}
*/
void game()
{
    User *my_player = NULL;
    User *scores = NULL;
    int **game_board = NULL;
    int x_max, y_max;
    int start;
    int *t_size;

    /// initializes the screen
    /// sets up memory and clears the screen
    initscr();

    my_player = authentication(my_player);

    if(my_player != NULL)
    {
        x_max = getmaxx(stdscr);
        y_max = getmaxy(stdscr);
        clear();
        mvprintw(y_max/2,x_max/4,"Welcome to the game %s\n",my_player->userName);
        refresh();
        getch();
        clear();
        start = 1;
        while(start)
        {
            clear();
            switch(afterAuthMenu())
            {
            case 0:
                clear();
                switch(modesMenu())
                {
                case 0:
                    clear();
                    playFirstMode(game_board,my_player);
                    break;
                case 1:
                    clear();
                    switch(_1vsRobotMenu())
                    {
                        case 0:
                            clear();
                            playVsRobot_Easy(game_board,my_player);
                            break;
                        case 1:
                            clear();
                            playVsRobot_Hard (game_board,my_player);
                            break;
                    }
                    break;
                }
                break;
            case 1:
                clear();
                switch(modesMenu())
                {
                case 0:
                    clear();
                    if(fileExist(my_player->userName,1) == 1)
                        playSavedGameHuman(game_board,my_player);
                    else
                    {
                        printw("No saved game!\nPress any key to go back to main menu..");
                        getch();
                    }
                    refresh();
                    break;
                case 1:
                    clear();
                    switch(_1vsRobotMenu())
                    {
                    case 0:
                        clear();
                        if(fileExist(my_player->userName,2) == 1)
                            playSavedGameVsRobot_Easy(game_board,my_player);
                        else
                        {
                            printw("No saved game!\nPress any key to go back to main menu..");
                            getch();
                        }
                        refresh();
                        break;
                    case 1:
                        clear();
                        if(fileExist(my_player->userName,3) == 1)
                            playSavedGameVsRobot_Hard(game_board,my_player);
                        else
                        {
                            printw("No saved game!\nPress any key to go back to main menu..");
                            getch();
                        }
                        refresh();
                        break;
                    }
                    break;
                }
                break;
            case 2:
                clear();
                scores = getBestScores();
                displayBestScores(scores);
                //printw("Best scores\n");
                getch();
                refresh();
                break;
            case 3:
                clear();
                start = 0;
                printw("Goodbye\n");
                refresh();
                break;
            }
        }
    }
    getch();
    endwin();
}

