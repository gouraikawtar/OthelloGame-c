#include "main.h"

void game()
{
    User *my_player = NULL;
    int **game_board = NULL;
    int start;

    my_player = authentication(my_player);

    if(my_player != NULL)
    {
        clear();
        printw("Welcome to the game %s\n",my_player->userName);
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
                    playVsRobot_Easy();
                    break;
                }
                break;
            case 1:
                clear();
                if(fileExist(my_player->userName) == 1)
                    playSavedGame(game_board,my_player);
                else
                {
                    printw("No saved game!\nPress any key to go back to main menu..");
                    getch();
                }
                refresh();
                break;
            case 2:
                clear();
                printw("Best scores\n");
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
}

