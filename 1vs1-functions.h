/**
* Player vs Player functions headers
*/
/*************************** Structures ********************************/

typedef struct _movement{
    int pos_x;
    int pos_y;
    int player;
}movement;

/*************************** Functions ********************************/

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
/// Sets player's score
void setScore(User *my_player, int new_score);
/// Displays the final score and winner
void displayWinner(int** board, User *my_player);
/// Saves player's position
int savePlayer_sPosition(int x, int y, int current_player, char username[20]);
/// Sets saved undone game
int** setSavedGame(int **board, int *next_player, char username[20]);
/// Destroys created file
int destroyFile(char username[20]);
/// Checks if a file exists or no
int fileExist(char username[20]);
/// Plays 1vs1 mode
//void playFirstMode(int **game_board, User *my_player);
/// Plays saved game
void playSavedGame(int **game_board, User *my_player);
