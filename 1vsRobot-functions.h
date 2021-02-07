/**
* Player vs Robot functions headers
*/
/*************************** Structures ********************************/

typedef struct position
{
    int x ;
    int y ;

} position ;

/*************************** Functions ********************************/
/// Return all the legal moves
position* legal_moves ( int player , int** board , int * legalPosNmb);
/// Choose a random move using legal_move() function
position random_move (int player , int** board, int * legalPosNmb);
/// Easy Mode (random)
void playVsRobot_Easy();
/// Evaluate a position
int diffeval (int player, int ** board);
/// We use this function to create a provisional board to test the position , this function is called by alpha_beta ()
int ** copy_board (int ** board);
/// Choose the best position
int alpha_beta (int player ,int ** board , int depth , int alpha , int beta , int *legPosNbr , position *bestMove);
/// Hard Mode ( Using Alpha Beta Algorithm )
void playVsRobot_Hard ();
/// Return the opponent , if player = 1 return 2 if player = 2 return 1 , this function is called by diffeval
int opponent (int player);
