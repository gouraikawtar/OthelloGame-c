/**
* Player vs Player functions implementation
*/

#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "1vs1-functions.h"
#include "menu.h"
#define N 8
#define N_PATH 50

int** initBoard(int** board)
{
    int i;
    ///Allocate memory for lines
    board = (int**)malloc(N*sizeof(int*));
    for(i=0;i<N;i++){
        /** Allocate memory for columns with initialization by 0
        * to indicate that the board is empty
        */
        *(board+i) = calloc(N,sizeof(int));
    }
    ///Initialization: Start position
    *(*(board+3)+4) = *(*(board+4)+3) = 1; ///d5 & e4 must be black, so we initialize positions (3,4) and (4,3) by 1
    *(*(board+3)+3) = *(*(board+4)+4) = 2;  ///d4 & e5 must be white, so we initialize positions (3,3) and (4,4) by 2

    return board;
}

void displayBoard(int** board)
{
    int i, j, k, c = 97;

    ///print columns indexes (letters)
    for(i=0;i<N+1;i++)
    {
        if(i==0)
            printw("  |");
        else
            printw(" %c |",c++);
    }
    printw("\n");
    ///print line
    for(i=0;i<N+1;i++)
    {
        if(i==0)
            printw("   ");
        else
            printw("----");
    }
    printw("\n");
    ///print board
    for(i=0;i<N;i++)
    {
        ///print lines indexes
        printw("%d |",i+1);
        ///print lines values
        for(j=0;j<N;j++){
            if(*(*(board+i)+j)==0)      ///if value == 0 print space
                printw("   |");
            else if(*(*(board+i)+j)==1) ///if value == 1 print B for Black
                printw(" B |");
            else                        ///if value == 2 print W for White
                printw(" W |");
        }
        printw("\n");
        ///print line
        for(k=0;k<N+1;k++)
        {
            if(k==0)
                printw("   ");
            else
                printw("----");
        }
        printw("\n");
    }

    refresh();
}

void destroyBoard(int **board)
{
    int i;
    ///free allocated columns
    for(i=0;i<N;i++)
        free(*(board+i));

    ///free allocated lines
    free(board);
}

int countColor(int color, int **board)
{
    int ctr = 0, i, j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(*(*(board+i)+j) == color)
                ctr++;
        }
    }
    return ctr;
}

int validPosition(int x, int y)
{
    /** 0   &&  0   =   0
    *   0   &&  1   =   0
    *   1   &&  0   =   0
    *   1   &&  1   =   1
    */
    return ((x>=0) && (x<N) && (y>=0) && (y<N));
}

int directionsTestPassed(int **board, int current_player, int x, int y)
{
    int i, j, switch_color, adv_player;

    if(current_player==1)
        adv_player = 2;
    else
        adv_player = 1;

    ///Test if the position is not valid or not empty
    if(validPosition(x,y)==0 || *(*(board+x)+y) != 0)
        return 0;

    ///North Test
    i = x-1;
    switch_color = 0;
    while(validPosition(i,y) && *(*(board+i)+y) == adv_player)
    {
        i--;
        switch_color = 1;
    }
    if(validPosition(i,y) && *(*(board+i)+y) == current_player && switch_color==1)
        return 1;

    ///South Test
    i = x+1;
    switch_color = 0;
    while(validPosition(i,y) && *(*(board+i)+y) == adv_player)
    {
        i++;
        switch_color = 1;
    }
    if(validPosition(i,y) && *(*(board+i)+y) == current_player && switch_color==1)
        return 1;

    ///West Test
    j = y-1;
    switch_color = 0;
    while(validPosition(x,j) && *(*(board+x)+j) == adv_player)
    {
        j--;
        switch_color = 1;
    }
    if(validPosition(x,j) && *(*(board+x)+j) == current_player && switch_color==1)
        return 1;

    ///East test
    j = y+1;
    switch_color = 0;
    while(validPosition(x,j) && *(*(board+x)+j) == adv_player)
    {
        j++;
        switch_color = 1;
    }
    if(validPosition(x,j) && *(*(board+x)+j) == current_player && switch_color==1)
        return 1;

    ///North-West test
    i = x-1, j = y-1;
    switch_color = 0;
    while(validPosition(i,j) && *(*(board+i)+j) == adv_player)
    {
        i--; j--;
        switch_color = 1;
    }
    if(validPosition(i,j) && *(*(board+i)+j) == current_player && switch_color==1)
        return 1;

    ///North-East test
    i = x-1, j = y+1;
    switch_color = 0;
    while(validPosition(i,j) && *(*(board+i)+j) == adv_player)
    {
        i--; j++;
        switch_color = 1;
    }
    if(validPosition(i,j) && *(*(board+i)+j) == current_player && switch_color==1)
        return 1;

    ///South-West test
    i = x+1, j = y-1;
    switch_color = 0;
    while(validPosition(i,j) && *(*(board+i)+j) == adv_player)
    {
        i++; j--;
        switch_color = 1;
    }
    if(validPosition(i,j) && *(*(board+i)+j) == current_player && switch_color==1)
        return 1;

    ///South-East test
    i = x+1, j = y+1;
    switch_color = 0;
    while(validPosition(i,j) && *(*(board+i)+j) == adv_player)
    {
        i++; j++;
        switch_color = 1;
    }
    if(validPosition(i,j) && *(*(board+i)+j) == current_player && switch_color==1)
        return 1;

    return 0;
}

/*void validTry(int **board, int current_player, int *x, int *y)
{
    printf("Player %d - Choose your position:\n",current_player);
    printf("\tLine: ");scanf("%d",x);
    printf("\tColumn: ");scanf("%d",y);
    *x = (*x)-1;
    *y = (*y)-1;
    while(!directionsTestPassed(board,current_player,*x,*y))
    {
        printf("Player %d - Invalid position! Please choose again:\n",current_player);
        printf("\tLine: ");scanf("%d",x);
        printf("\tColumn: ");scanf("%d",y);
        *x = (*x)-1;
        *y = (*y)-1;
    }
}*/
void validTry(int **board, int current_player, int *x, int *y)
{
    char c;
    int l, ic;

    ///the player choose a position: c for column and l for line
    printw("Player %d\n\tChoose your position (example e4): ",current_player);
    scanw("%c%d",&c,&l);
    ///conversion from uppercase to lowercase
    if(c >= 'A' && c <= 'H')
        c = (char)tolower(c);
    ///conversion from letter to it's equivalent number (using ASCII) (a <=> 0, b <=> 1, ... , h <=> 7)
    c = c-49;
    ic = c - '0';   ///conversion from number in char to number in int
    *y = ic;    ///assignment to y
    l--;    ///decrementing the line index value
    *x = l; ///assignment to x
    //while ((getchar()) != '\n');

    while(!directionsTestPassed(board,current_player,*x,*y))
    {
        ///while the chosen position is invalid, the player keeps trying
        printw("Player %d\n\tInvalid position! Please choose another one (example e4): ", current_player);
        scanw("%c%d",&c,&l);
        if(c >= 'A' && c <= 'H')
            c = (char)tolower(c);
        c = c-49;
        ic = c - '0'; *y = ic;
        l--; *x = l;

        //while ((getchar()) != '\n');
    }

    refresh();
}

int** changeColor(int **board, int current_player, int x, int y)
{
    int i,j,adv_player;

    if(current_player==1)
        adv_player = 2;
    else
        adv_player = 1;

    ///North
    i = x-1;
    while(validPosition(i,y) && *(*(board+i)+y) == adv_player)
    {
        i--;
    }
    if(validPosition(i,y) && *(*(board+i)+y) == current_player)
    {
        while(i < x)
        {
            i++;
            *(*(board+i)+y) = current_player;
        }
    }

    ///South
    i = x+1;
    while(validPosition(i,y) && *(*(board+i)+y) == adv_player)
    {
        i++;
    }
    if(validPosition(i,y) && *(*(board+i)+y) == current_player)
    {
        while(i > x)
        {
            i--;
            *(*(board+i)+y) = current_player;
        }
    }

    ///West
    j = y-1;
    while(validPosition(x,j) && *(*(board+x)+j) == adv_player)
    {
        j--;
    }
    if(validPosition(x,j) && *(*(board+x)+j) == current_player)
    {
        while(j < y)
        {
            j++;
            *(*(board+x)+j) = current_player;
        }
    }

    ///East
    j = y+1;
    while(validPosition(x,j) && *(*(board+x)+j) == adv_player)
    {
        j++;
    }
    if(validPosition(x,j) && *(*(board+x)+j) == current_player)
    {
        while(j > y)
        {
            j--;
            *(*(board+x)+j) = current_player;
        }
    }

    ///North-West
    i = x-1, j = y-1;
    while(validPosition(i,j) && *(*(board+i)+j) == adv_player)
    {
        i--; j--;
    }
    if(validPosition(i,j) && *(*(board+i)+j) == current_player)
    {
        while(i < x && j < y)
        {
            i++; j++;
            *(*(board+i)+j) = current_player;
        }
    }

    ///North-East
    i = x-1, j = y+1;
    while(validPosition(i,j) && *(*(board+i)+j) == adv_player)
    {
        i--; j++;
    }
    if(validPosition(i,j) && *(*(board+i)+j) == current_player)
    {
        while(i < x && j > y)
        {
            i++; j--;
            *(*(board+i)+j) = current_player;
        }
    }

    ///South-West
    i = x+1, j = y-1;
    while(validPosition(i,j) && *(*(board+i)+j) == adv_player)
    {
        i++; j--;
    }
    if(validPosition(i,j) && *(*(board+i)+j) == current_player)
    {
        while(i > x && j < y)
        {
            i--; j++;
            *(*(board+i)+j) = current_player;
        }
    }

    ///South-East
    i = x+1, j = y+1;
    while(validPosition(i,j) && *(*(board+i)+j) == adv_player)
    {
        i++; j++;
    }
    if(validPosition(i,j) && *(*(board+i)+j) == current_player)
    {
        while(i > x && j > y)
        {
            i--; j--;
            *(*(board+i)+j) = current_player;
        }
    }

    return board;
}

int play(int** board, int current_player)
{
    int i, j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(directionsTestPassed(board,current_player,i,j))
                return 1;
        }
    }
    return 0;
}

int gameOver(int** board)
{
    int i, j;
    if(board != NULL)
    {
        for(i=0;i<N;i++)
        {
            for(j=0;j<N;j++)
            {
                if(*(*(board+i)+j) == 0 && (play(board,1) || play(board,2)))
                    return 0;
            }
        }
    }
    return 1;
}

void displayWinner(int** board)
{
    int black = 0, white = 0;

    black = countColor(1,board);
    white = countColor(2,board);
    printw("********************* GAME OVER *********************\n");
    displayBoard(board);
    if(black > white)
        printw("Player 1 = %d / Player 2 = %d\nPlayer 1 won!\n",black, white);
    else if(black < white)
        printw("Player 1 = %d / Player 2 = %d\nPlayer 2 won!\n",black, white);
    else
        printw("Player 1 = %d / Player 2 = %d\nBoth players won!\n",black, white);

    refresh();
}

int savePlayer_sPosition(int x, int y, int current_player, char *file_name)
{
    char *path = NULL;
    int saved = 0;
    movement mvt;
    FILE *my_file = NULL;

    // Setting our file's path
    path = malloc(N_PATH*sizeof(char));
    strcpy(path,"D:\\game_files\\");
    strcat(path,file_name);
    // Setting our mvt variable
    mvt.pos_x = x;
    mvt.pos_y = y;
    mvt.player = current_player;
    // Open file and save movement
    my_file = fopen(path,"ab+");
    if(my_file != NULL)
    {
        fwrite(&mvt,sizeof(movement),1,my_file);
        saved = 1;
        fclose(my_file);
    }
    free(path);
    return saved;
}

int** setSavedGame(int **board, int *next_player, char *file_name)
{
    char *path = NULL;
    movement mvt;
    FILE *my_file = NULL;

    // Setting our file's path
    path = malloc(N_PATH*sizeof(char));
    strcpy(path,"D:\\game_files\\");
    strcat(path,file_name);
    // Open file and get movements
    my_file = fopen(path,"ab+");
    if(my_file != NULL)
    {
        while(!feof(my_file))
        {
            // Reads movement from file
            fread(&mvt,sizeof(movement),1,my_file);
            // Sets movement on the game board
            board = changeColor(board,mvt.player,mvt.pos_x,mvt.pos_y);
        }
        *next_player = (mvt.player%2)+1;
        fclose(my_file);
    }
    free(path);
    return board;
}

int destroyFile(char *file_name)
{
    char *path = NULL;
    int removed = 0;
    // Setting our file's path
    path = malloc(N_PATH*sizeof(char));
    strcpy(path,"D:\\game_files\\");
    strcat(path,file_name);

    removed = remove(path);

    free(path);
    return removed;
}

void playFirstMode()
{
    int **game_board = NULL;
    int pos_x, pos_y;
    int player;
    int choice;


    // Initialize game
    game_board = initBoard(game_board);
    player = 1;
    // Start game
    while(!gameOver(game_board))
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
    // displays winner and final score
    if(game_board != NULL)
        displayWinner(game_board);
}
