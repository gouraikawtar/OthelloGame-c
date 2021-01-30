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
