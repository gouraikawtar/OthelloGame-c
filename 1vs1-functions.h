/**
* Player vs Player functions headers
*/
/*************************** Structures ********************************/

typedef struct _movement{
    int pos_x;
    int pos_y;
    int player;
}movement;

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

/*************************** Functions ********************************/

/*************************** Movements queue logic ********************/
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

/************************** Game's logic ****************************/
/// Initializes the board array by 0 if empty, 1 if black & 2 if white
int** initBoard(int** board);
/// Displays the board
void displayBoard(int** board);
/// Destroys the board and free memory
void destroyBoard(int **board);
/// Counts pawns from specific color
int countColor(int color, int **board);
/// Checks if the coordinates of the chosen position are within the boundaries of the board or not (value >= 0 && value < N)
int validPosition(int x, int y);
/** Executes tests (north, south, east, west, ne, nw, se, sw) on the chosen position,
returns 1 if at least one test is valid & 0 if the position is invalid or not empty or none of the tests is valid*/
int directionsTestPassed(int **board, int current_player, int x, int y);
/// Asks the current player to choose a position and tests if it's correct or not using the function directionsTestPassed()
void validTry(int **board, int current_player, int *x, int *y, Queue **q);
/// Changes the pawns color to the current player's color
int** changeColor(int **board, int current_player, int x, int y);
/// Checks if the player can play his turn or not
int play(int** board, int current_player);
/// Checks if the game is over or not
int gameOver(int** board);

/********************************* Scoring logic **************************************/

/// Sets player's score
User* setScore(User *my_player, int new_score);
///
User* getBestScores();
///
void setBestScores(User my_player);
///
void displayBestScores(User *tab);
/// Displays the final score and winner
void displayWinner(int** board, User *my_player);

/*********************************** Reset saved game's logic ****************************/

/// Saves player's position
int savePlayer_sPosition(int x, int y, int current_player, char username[20],int mode);
/// Sets saved undone game
int** setSavedGame(int **board, int *next_player, char username[20],int mode);
/// Destroys created file
int destroyFile(char username[20],int mode);
/// Checks if a file exists or no
int fileExist(char username[20],int mode);
/************************** Play Human vs. Human mode logic *******************************/
void playFirstMode(int **game_board, User *my_player);

/******************************** Play saved game logic ******************************/
void playSavedGameHuman(int **game_board, User *my_player);
