/**
* Player vs Robot functions implementation
*/


#include <time.h>
#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "1vs1-functions.h"
#include "1vsRobot-functions.h"
#include "menu.h"
#define N 8
#define N_PATH 50


/*************************** Easy Mode ********************************/
position* legal_moves ( int player , int** board ,int* legalPosNmb)
{
    int taille =0 ;
    int x , y ;
    int nbrDePosLegal;
    position* legalMoves ;
    legalMoves=(position*)malloc(64*sizeof(position));
    for (x=0;x<N;x++)
    {
        for(y=0;y<N;y++)
        {
            if (directionsTestPassed(board,player,  x,  y)==1) //test if the position (x,y) is avalid position
            {
                legalMoves[taille].x=x ;
                legalMoves[taille].y=y;
                taille++;
            }

        }
    }
    *legalPosNmb = taille-1; //Number of legal moves
    return legalMoves ;
}

position random_move (int player , int** board , int* legPosNmb)
{
    position r, *moves;
    moves =legal_moves(player, board,legPosNmb);
    srand(time(NULL));
    int i;
    i=(rand()%(*legPosNmb+1)); //choose one random position of the legal positions
    r.x=moves[i].x;
    r.y=moves[i].y;
    return r;
}

void playVsRobot_Easy ()
{
    int **game_board = NULL;
    int pos_x, pos_y;
    game_board = initBoard(game_board);
    int player=1;
    int choice;
    position randomPosition ;
    int legPosNb ;
    while(!gameOver(game_board))
    {

        if (player==1) // Player 1 = HUMAN
        {
        displayBoard(game_board);
        printw("Player %d | Press Enter to play or Esc for game options: ",player);
        choice = getch();
        switch(choice)
        {
            case 10:    // Enter key pressed
                validTry(game_board,player,&pos_x,&pos_y);
                savePlayer_sPosition(pos_x,pos_y,player,"username3.bin");
                game_board = changeColor(game_board,player,pos_x,pos_y);
                if(play(game_board,player%2+1))
                    player = player%2+1;
                clear();
                break;
            case 27:    // Esc key pressed
                clear();
                switch(gameOptionsMenu())
                {
                    case 0: // Resume
                        clear();
                        break;
                    case 1: // Restart
                        clear();
                        game_board = initBoard(game_board);
                        player = 1;
                        break;
                    case 2: // Exit
                        clear();
                        switch(exitGameMenu())
                        {
                            case 0: // Yes
                                clear();
                                printw("Game saved successfully !\n");
                                destroyBoard(game_board);
                                game_board = NULL;
                                break;
                            case 1: // No
                                clear();
                                destroyFile("username3.bin");
                                destroyBoard(game_board);
                                game_board = NULL;
                                break;
                        }
                        break;
                }
                break;
            default:    // Other key pressed
                clear();
                break;

        }
        }

        if (player==2) //Player 2 = Robot
        {
            displayBoard(game_board);
            printw("Robot turn | Press Enter to continue :");
            randomPosition = random_move (player , game_board, &legPosNb);
            game_board = changeColor(game_board,player,randomPosition.x,randomPosition.y);

            if(play(game_board,player%2+1))
                    player = player%2+1;
                getch();
                clear();


        }
    }
        if(game_board != NULL)
        displayWinner(game_board);

    }











/*************************** Hard Mode ********************************/




