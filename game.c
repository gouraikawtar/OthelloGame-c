#include "main.h"


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

/*void setBestScores(User my_player)
{
    User *tab = NULL;
    FILE *f_best_scores = NULL;
    int i;

    tab = getBestScores();

    if(my_player.score >= *(tab+0).score)
    {
        for(i=T_MAX-1;i>0;i--)
        {
            *(tab+i) = *(tab+i-1);
        }
        *(tab+0) = my_player;
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
    mvprintw(0,5,"10 Best Scores");
    mvprintw(1,1,"Username");
    mvprintw(2,15,"Score");
    y = 4;
    for(i=0;i<T_MAX;i++)
    {
        mvprintw(y,1,"%s",tab[i]->userName);
        mvprintw(y,15,"%d",tab[i]->score);
        y++;
    }
}
*/
void playFirstMode(int **game_board, User *my_player)
{
    int pos_x, pos_y;   // Pawn's position
    int player; // player's pawn color
    int choice; // player's choice (ENTER KEY or ESC KEY)
    Queue *q;   // Movements queue (to show 10 last movements made by the players)


    // Initialize game
    game_board = initBoard(game_board); // Allocates memory for board, and set initial positions
    player = 1; //  Set turn to 1 (==color to BLACK)
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
                    savePlayer_sPosition(pos_x,pos_y,player,my_player->userName);
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
                                    destroyFile(my_player->userName);
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
            savePlayer_sPosition(pos_x,pos_y,player,my_player->userName);
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
        destroyFile(my_player->userName);
        printw("Press any key to go back to main menu..");
        getch();
    }
}



void game()
{
    User *my_player = NULL;
    int **game_board = NULL;
    int x_max, y_max;
    int start;

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

