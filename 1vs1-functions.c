/**
* Player vs Player functions implementation
*/
#include "main.h"

/************************************* Movements queue logic *************************/

qnode* newNode(char c, int l,int current_player)
{
    qnode *n = NULL;
    n = malloc(sizeof(qnode));
    n->c = c;
    n->l = l;
    n->player = current_player;
    n->next = NULL;
    return n;
}

Queue* createQueue()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->q_front = q->q_rear = NULL;
    return q;
}
int queueSize(Queue* q)
{
    int ctr = 0;
    qnode *ptr;
    if(q->q_front == NULL && q->q_rear == NULL)
        return 0;
    else
    {
        ptr = q->q_front;
        while(ptr != NULL)
        {
            ctr++;
            ptr = ptr->next;
        }
    }
    return ctr;
}

void deQueue(Queue* q)
{
    // If queue is empty, return NULL.
    if (q->q_front == NULL)
        return;

    // Store previous front and move front one node ahead
    qnode* temp = q->q_front;

    q->q_front = q->q_front->next;

    // If front becomes NULL, then change rear also as NULL
    if (q->q_front == NULL)
        q->q_rear = NULL;

    free(temp);
}

void enQueue(Queue* q, char c, int l,int current_player)
{
    // Create a new node
    qnode* temp = newNode(c,l,current_player);

    // If queue is empty, then new node is front and rear both
    if (q->q_rear == NULL) {
        q->q_front = q->q_rear = temp;
        return;
    }
    else
    {
        if(queueSize(q) == 10)
            deQueue(q);
        // If queue not empty add the new node at the end of queue and change rear
        q->q_rear->next = temp;
        q->q_rear = temp;
    }
}

void displayQueue(Queue *q)
{
    qnode *ptr;
    int y;
    WINDOW *q_wind = newwin(15,25,2,70);
    refresh();
    box(q_wind,0,0);
    wrefresh(q_wind);
    wprintw(q_wind," Last movements ");
    y = 2;
    if(queueSize(q) != 0)
    {
        ptr = q->q_front;
        while(ptr != NULL)
        {
            mvwprintw(q_wind,y++,2,"Player %d : %c%d",ptr->player,ptr->c,ptr->l);
            ptr = ptr->next;
        }
    }
    else
        mvwprintw(q_wind,y++,2,"No movements yet");
    wrefresh(q_wind);
}

/************************************* Game's logic **********************************/

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

void validTry(int **board, int current_player, int *x, int *y, Queue **q)
{
    char col, c;
    int line, l, ic;

    ///the player choose a position: c for column and l for line
    printw("Player %d\n\tChoose your position (example e4): ",current_player);
    scanw("%c%d",&c,&l);
    col = c; line = l;
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
        col = c; line = l;
        if(c >= 'A' && c <= 'H')
            c = (char)tolower(c);
        c = c-49;
        ic = c - '0'; *y = ic;
        l--; *x = l;

        //while ((getchar()) != '\n');
    }
    // Add chosen move to queue
    enQueue(*q,col,line,current_player);

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

/********************************* Scoring logic ***********************/

User* setScore(User *my_player, int new_score)
{
    FILE *f_users = NULL;
    User u;
    int find = 0;
    if(new_score > my_player->score)
    {
        my_player->score = new_score;
        f_users = fopen(".\\game_files\\users.bin","ab+");
        if(f_users != NULL)
        {
            while(find == 0 && !feof(f_users))
            {
                fread(&u,sizeof(User),1,f_users);
                if(strcmp(u.userName,my_player->userName)==0)
                    find = 1;
            }
            u.score = my_player->score;
            fclose(f_users);
        }
    }
    return my_player;
}
User* getBestScores()
{
    User *tab = NULL;
    FILE *f_best_scores = NULL;
    int i;

    tab = malloc(T_MAX*sizeof(User));
    f_best_scores = fopen(".\\game_files\\best_scores.bin","rb");
    if(f_best_scores != NULL)
    {
        i = 0;
        while(i<T_MAX && !feof(f_best_scores))
        {
            fread(tab+i,sizeof(User),1,f_best_scores);
            i++;
        }
        fclose(f_best_scores);
    }
    return tab;
}

void setBestScores(User my_player)
{
    User *tab = NULL;
    FILE *f_best_scores = NULL;
    int i;

    tab = getBestScores();

    if(my_player.score >= tab[0].score)
    {
        for(i=T_MAX-1;i>0;i--)
        {
            tab[i] = tab[i-1];
        }
        tab[i] = my_player;
    }

    f_best_scores = fopen(".\\game_files\\best_scores.bin","wb");
    if(f_best_scores != NULL)
    {
        for(i=0;i<T_MAX;i++)
            fwrite(tab+i,sizeof(User),1,f_best_scores);
        fclose(f_best_scores);
    }
}

void displayBestScores(User *tab)
{
    int i, y;
    mvprintw(5,10,"10 Best Scores");
    mvprintw(6,5,"Username");
    mvprintw(6,20,"Score");
    y = 8;
    for(i=0;i<T_MAX;i++)
    {
        mvprintw(y,5,"%s",tab[i].userName);
        mvprintw(y,20,"%d",tab[i].score);
        y++;
    }
    move(getmaxy(stdscr)-2,getmaxx(stdscr)-40);
    printw("Press any key to continue..");
    refresh();
}

void displayWinner(int** board, User *my_player)
{
    int black = 0, white = 0;

    black = countColor(1,board);
    white = countColor(2,board);
    my_player = setScore(my_player,black);
    setBestScores(*my_player);

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

/************************************* Reset saved game's logic **********************************/

int savePlayer_sPosition(int x, int y, int current_player, char username[20], int mode)
{
    char *path = NULL;
    int saved = 0;
    movement mvt;
    FILE *my_file = NULL;

    // Setting our file's path
    path = malloc(N_PATH*sizeof(char));
    strcpy(path,".\\game_files\\");
    strcat(path,username);
    switch(mode)
    {
    case 1: // Human vs. Human
        strcat(path,".bin");
        break;
    case 2: // Human vs. Robot (easy)
        strcat(path,"_easy.bin");
        break;
    case 3: // Human vs Robot (hard)
        strcat(path,"_hard.bin");
        break;
    }
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

int** setSavedGame(int **board, int *next_player, char username[20], int mode)
{
    char *path = NULL;
    movement mvt;
    FILE *my_file = NULL;

    // Setting our file's path
    path = malloc(N_PATH*sizeof(char));
    strcpy(path,".\\game_files\\");
    strcat(path,username);
    switch(mode)
    {
    case 1: // Human vs. Human
        strcat(path,".bin");
        break;
    case 2: // Human vs. Robot (easy)
        strcat(path,"_easy.bin");
        break;
    case 3: // Human vs Robot (hard)
        strcat(path,"_hard.bin");
        break;
    }
    // Open file and get movements
    my_file = fopen(path,"rb");
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

int destroyFile(char username[20],int mode)
{
    char *path = NULL;
    int removed = 0;
    // Setting our file's path
    path = malloc(N_PATH*sizeof(char));
    strcpy(path,".\\game_files\\");
    strcat(path,username);
    switch(mode)
    {
    case 1: // Human vs. Human
        strcat(path,".bin");
        break;
    case 2: // Human vs. Robot (easy)
        strcat(path,"_easy.bin");
        break;
    case 3: // Human vs Robot (hard)
        strcat(path,"_hard.bin");
        break;
    }

    removed = remove(path);

    free(path);
    return removed;
}

int fileExist(char username[20], int mode)
{
    char *path = NULL;
    FILE *file = NULL;
    int exists = 0; // file does not exist
    // Setting our file's path
    path = malloc(N_PATH*sizeof(char));
    strcpy(path,".\\game_files\\");
    strcat(path,username);
    switch(mode)
    {
    case 1: // Human vs. Human
        strcat(path,".bin");
        break;
    case 2: // Human vs. Robot (easy)
        strcat(path,"_easy.bin");
        break;
    case 3: // Human vs Robot (hard)
        strcat(path,"_hard.bin");
        break;
    }
    file = fopen(path,"rb");
    if(file != NULL)
        exists = 1; // file exists
    fclose(file);
    return exists;

}
/************************** Play Human vs. Human mode logic *******************************/

void playFirstMode(int **game_board, User *my_player)
{
    int pos_x, pos_y;   // Pawn's position
    int player; // player's pawn color
    int choice; // player's choice (ENTER KEY or ESC KEY)
    int mode;
    Queue *q;   // Movements queue (to show 10 last movements made by the players)


    // Initialize game
    game_board = initBoard(game_board); // Allocates memory for board, and set initial positions
    player = 1; //  Set turn to 1 (==color to BLACK)
    mode = 1;
    q = createQueue();  // Create positions queue
    // Start game
    while(!gameOver(game_board))
    {
        displayBoard(game_board);
        displayQueue(q);
        switch(player)
        {
        case 1: // BLACK == Logged in player
            printw("Player %d | Press Enter to play or Esc for game options: ",player);
            choice = getch();
            switch(choice)
            {
                case 10:    // Enter key pressed
                    validTry(game_board,player,&pos_x,&pos_y,&q);
                    savePlayer_sPosition(pos_x,pos_y,player,my_player->userName,mode);
                    game_board = changeColor(game_board,player,pos_x,pos_y);
                    if(play(game_board,player%2+1)) // The next player can play
                        player = player%2+1;    // The turn is now for next player if he can plays
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
                            game_board = initBoard(game_board); // Reset board
                            player = 1; // Reset turn to 1
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
        case 2: // WHITE
            validTry(game_board,player,&pos_x,&pos_y,&q);
            savePlayer_sPosition(pos_x,pos_y,player,my_player->userName,mode);
            game_board = changeColor(game_board,player,pos_x,pos_y);
            if(play(game_board,player%2+1)) // The next player can play
                player = player%2+1;    // The turn is now for next player if he can plays
            clear();
            break;
        }
    }
    // displays winner and final score
    if(game_board != NULL)
    {
        displayWinner(game_board,my_player);
        destroyBoard(game_board);
        destroyFile(my_player->userName,mode);
        printw("Press any key to go back to main menu..");
        getch();
    }
}

/******************************** Play saved game logic ***************************/

void playSavedGameHuman(int **game_board, User *my_player)
{
    int pos_x, pos_y;
    int player;
    int choice;
    int mode = 1;
    Queue *q;

    // initialize game
    game_board = initBoard(game_board); // Set initial positions on board
    game_board = setSavedGame(game_board,&player,my_player->userName,mode);  // Set saved game
    q = createQueue();

       // Start game
    while(!gameOver(game_board))
    {
        displayBoard(game_board);
        displayQueue(q);
        switch(player)
        {
        case 1: // BLACK == Logged in player
            printw("Player %d | Press Enter to play or Esc for game options: ",player);
            choice = getch();
            switch(choice)
            {
                case 10:    // Enter key pressed
                    validTry(game_board,player,&pos_x,&pos_y,&q);
                    savePlayer_sPosition(pos_x,pos_y,player,my_player->userName,mode);
                    game_board = changeColor(game_board,player,pos_x,pos_y);
                    if(play(game_board,player%2+1)) // The next player can play
                        player = player%2+1;    // The turn is now for next player if he can plays
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
                            game_board = initBoard(game_board); // Reset board
                            player = 1; // Reset turn to 1
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
        case 2: // WHITE
            validTry(game_board,player,&pos_x,&pos_y,&q);
            savePlayer_sPosition(pos_x,pos_y,player,my_player->userName,mode);
            game_board = changeColor(game_board,player,pos_x,pos_y);
            if(play(game_board,player%2+1)) // The next player can play
                player = player%2+1;    // The turn is now for next player if he can plays
            clear();
            break;
        }
    }
    // displays winner and final score
    if(game_board != NULL)
    {
        displayWinner(game_board,my_player);
        destroyBoard(game_board);
        destroyFile(my_player->userName,mode);
        printw("Press any key to go back to main menu..");
        getch();
    }
}
