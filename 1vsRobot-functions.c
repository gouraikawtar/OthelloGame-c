/**
* Player vs Robot functions implementation
*/
#include "main.h"

void setRobotMoves(char *c, int *l,position pos)
{
    char nbr_to_char = pos.y + '0';
    *c = nbr_to_char + 49;
    *l = pos.x+1;
}
/*************************** Easy Mode ********************************/
position* legal_moves ( int player , int** board ,int* legalPosNmb)
{
    int taille =0 ;
    int x , y ;
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

void playVsRobot_Easy(int **game_board, User *my_player)
{
    int pos_x, pos_y;
    int player;
    int choice;
    int mode;
    position randomPosition ;
    int legPosNb ;
    char r_col;
    int r_line;
    Queue *q = NULL;

    // initialize game
    game_board = initBoard(game_board);
    player = 1;
    mode = 2;
    q = createQueue();

    while(!gameOver(game_board))
    {
        displayBoard(game_board);
        displayQueue(q);
        switch(player)
        {
        case 1: // Player 1 = HUMAN
            printw("Player %d | Press Enter to play or Esc for game options: ",player);
            choice = getch();
            switch(choice)
            {
            case 10:    // Enter key pressed
                validTry(game_board,player,&pos_x,&pos_y,&q);
                savePlayer_sPosition(pos_x,pos_y,player,my_player->userName,mode);
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
                        q = createQueue();
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
                                destroyFile(my_player->userName,mode);
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
            break;
        case 2: // Player 2 = ROBOT
            printw("Robot is thinking.. | Press Enter to continue :");
            randomPosition = random_move (player , game_board, &legPosNb);
            savePlayer_sPosition(randomPosition.x,randomPosition.y,player,my_player->userName,mode);
            game_board = changeColor(game_board,player,randomPosition.x,randomPosition.y);
            setRobotMoves(&r_col,&r_line,randomPosition);   // transform robot chosen position from int to char
            enQueue(q,r_col,r_line,player); // Add robot chosen position to movements queue
            if(play(game_board,player%2+1))
                player = player%2+1;
            getch();
            clear();
            break;
        }
    }
    if(game_board != NULL)
    {
        displayWinner(game_board,my_player);
        destroyBoard(game_board);
        destroyFile(my_player->userName,mode);
        printw("Press any key to go back to main menu..");
        getch();
    }
}

void playSavedGameVsRobot_Easy(int **game_board, User *my_player)
{
    int pos_x, pos_y;
    int player;
    int choice;
    int mode = 2;
    position randomPosition ;
    int legPosNb ;
    char r_col;
    int r_line;
    Queue *q = NULL;

    // initialize game
    game_board = initBoard(game_board);
    game_board = setSavedGame(game_board,&player,my_player->userName,mode);
    q = createQueue();

    while(!gameOver(game_board))
    {
        displayBoard(game_board);
        displayQueue(q);
        switch(player)
        {
        case 1: // Player 1 = HUMAN
            printw("Player %d | Press Enter to play or Esc for game options: ",player);
            choice = getch();
            switch(choice)
            {
            case 10:    // Enter key pressed
                validTry(game_board,player,&pos_x,&pos_y,&q);
                savePlayer_sPosition(pos_x,pos_y,player,my_player->userName,mode);
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
                        q = createQueue();
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
                                destroyFile(my_player->userName,mode);
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
            break;
        case 2: // Player 2 = ROBOT
            printw("Robot is thinking.. | Press Enter to continue :");
            randomPosition = random_move (player , game_board, &legPosNb);
            savePlayer_sPosition(randomPosition.x,randomPosition.y,player,my_player->userName,mode);
            game_board = changeColor(game_board,player,randomPosition.x,randomPosition.y);
            setRobotMoves(&r_col,&r_line,randomPosition);   // transform robot chosen position from int to char
            enQueue(q,r_col,r_line,player); // Add robot chosen position to movements queue
            if(play(game_board,player%2+1))
                player = player%2+1;
            //getch();
            clear();
            break;
        }
    }
    if(game_board != NULL)
    {
        displayWinner(game_board,my_player);
        destroyBoard(game_board);
        destroyFile(my_player->userName,mode);
        printw("Press any key to go back to main menu..");
        getch();
    }
}

/*************************** Hard Mode ********************************/

int opponent (int player)
 {
  switch (player)
  {
  case 1: return 2;
  case 2: return 1;
  }
  return 0 ;
 }

int diffeval (int player, int ** board)
{
  int ocnt, pcnt, opp;
  opp = opponent(player);
  ocnt = countColor(opp, board);
  pcnt =  countColor(player,board);
  return (pcnt-ocnt);
}

int ** copy_board (int ** board)
{
    int i , j , **newboard ;
    newboard =(int **)malloc(N*sizeof(int**));
    newboard=initBoard(newboard);
      for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            *(*(newboard+i)+j) = *(*(board+i)+j);

        }
    }
    return newboard ;
}

int alpha_beta (int player ,int ** board , int profondeur , int alpha , int beta , int *legPosNbr , position *bestMove)
{
    int i , score;
    position *legalMoves ;
    int ** new_board ;
    if (gameOver==1 || profondeur<=0)
    {
        return diffeval(player,board);
    }
    legalMoves = legal_moves(player,board,legPosNbr);
    for (i=0;i<= *legPosNbr; i++)
    {
        new_board = copy_board(board);
        new_board=changeColor(new_board,player,legalMoves[i].x,legalMoves[i].y);
        score= -alpha_beta(player,board,profondeur-1,-beta,-alpha, legPosNbr,bestMove);
        if (score >= alpha)
        {
            alpha = score;
            bestMove->x = legalMoves[i].x;
            bestMove->y = legalMoves[i].y ;
            if(alpha>=beta)
                break ;
        }
    }
    return alpha ;
}

void playVsRobot_Hard (int **game_board, User *my_player)
{
    int pos_x, pos_y;
    game_board = initBoard(game_board);
    int player=1;
    int choice;
    int mode = 3;
    char r_col;
    int r_line;
    Queue *q = createQueue();
    position bestMove ;
    int legPosNb ;
    int alpha = -64 , beta = +64 ; // alpha = -Infinity , beta = +Infinity

    while(!gameOver(game_board))
    {
        displayBoard(game_board);
        displayQueue(q);
        switch(player)
        {
        case 1: // Player 1 = HUMAN
            printw("Player %d | Press Enter to play or Esc for game options: ",player);
            choice = getch();
            switch(choice)
            {
            case 10:    // Enter key pressed
                validTry(game_board,player,&pos_x,&pos_y,&q);
                savePlayer_sPosition(pos_x,pos_y,player,my_player->userName,mode);
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
                        q = createQueue();
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
                                destroyFile(my_player->userName,mode);
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
            break;
        case 2: // Player 2 = ROBOT
            printw("Robot turn | Press Enter to continue :");
            alpha_beta (player,game_board,3,alpha,beta,&legPosNb,&bestMove);
            game_board = changeColor(game_board,player,bestMove.x,bestMove.y);
            setRobotMoves(&r_col,&r_line,bestMove);   // transform robot chosen position from int to char
            enQueue(q,r_col,r_line,player); // Add robot chosen position to movements queue
            if(play(game_board,player%2+1))
                player = player%2+1;
            getch();
            clear();
            break;
        }
    }
    if(game_board != NULL)
    {
        displayWinner(game_board,my_player);
        destroyBoard(game_board);
        destroyFile(my_player->userName,mode);
        printw("Press any key to go back to main menu..");
        getch();
    }
}

void playSavedGameVsRobot_Hard (int **game_board, User *my_player)
{
    int pos_x, pos_y;
    game_board = initBoard(game_board);
    int player;
    int choice;
    int mode = 3;
    char r_col;
    int r_line;
    Queue *q = createQueue();
    position bestMove ;
    int legPosNb ;
    int alpha = -64 , beta = +64 ; // alpha = -Infinity , beta = +Infinity

    game_board = setSavedGame(game_board,&player,my_player->userName,mode);

    while(!gameOver(game_board))
    {
        displayBoard(game_board);
        displayQueue(q);
        switch(player)
        {
        case 1: // Player 1 = HUMAN
            printw("Player %d | Press Enter to play or Esc for game options: ",player);
            choice = getch();
            switch(choice)
            {
            case 10:    // Enter key pressed
                validTry(game_board,player,&pos_x,&pos_y,&q);
                savePlayer_sPosition(pos_x,pos_y,player,my_player->userName,mode);
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
                        q = createQueue();
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
                                destroyFile(my_player->userName,mode);
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
            break;
        case 2: // Player 2 = ROBOT
            printw("Robot turn | Press Enter to continue :");
            alpha_beta (player,game_board,3,alpha,beta,&legPosNb,&bestMove);
            game_board = changeColor(game_board,player,bestMove.x,bestMove.y);
            setRobotMoves(&r_col,&r_line,bestMove);   // transform robot chosen position from int to char
            enQueue(q,r_col,r_line,player); // Add robot chosen position to movements queue
            if(play(game_board,player%2+1))
                player = player%2+1;
            getch();
            clear();
            break;
        }
    }
    if(game_board != NULL)
    {
        displayWinner(game_board,my_player);
        destroyBoard(game_board);
        destroyFile(my_player->userName,mode);
        printw("Press any key to go back to main menu..");
        getch();
    }
}
