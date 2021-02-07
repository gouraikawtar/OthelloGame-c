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

