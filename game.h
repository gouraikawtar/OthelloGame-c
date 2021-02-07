/**
* Game functions headers
*/

typedef struct _qnode{
    char c; // column
    int l;  //line
    int player; //player's color
    struct _qnode *next;
}qnode;

typedef struct Queue{
    qnode *q_front;
    qnode *q_rear;
}Queue;

/// Creates new node
qnode* newNode(char c, int l,int current_player);
/// Creates empty queue
Queue* createQueue();
/// Gets queue size
int queueSize(Queue* q);
/// Deletes element from queue
void deQueue(Queue* q);
/// Adds elements to queue
void enQueue(Queue* q, char c, int l, int current_player);
/// Displays queue elements
void displayQueue(Queue *q);
///
//User* getBestScores();
///
//void setBestScores(User my_player);
///
//void displayBestScores(User *tab);
///
void playFirstMode(int **game_board, User *my_player);
///
void game();
