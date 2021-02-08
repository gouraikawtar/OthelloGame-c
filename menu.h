/**
* Game menus functions headers
*/

/*********************************** Structures *************************************/
// Menu choice structure
typedef struct _choice{
    char option[20];
}choice;

/*********************************** Functions **************************************/
void firstScreen();
// Displays game options menu and returns chosen option
int gameOptionsMenu();
//
int afterAuthMenu();
//
int modesMenu();
//
int _1vsRobotMenu();
//
int exitGameMenu();
//
int LoginMenu();
