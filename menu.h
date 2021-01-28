/**
* Game menus functions headers
*/

/*********************************** Structures *************************************/
// Menu choice structure
typedef struct _choice{
    char option[20];
}choice;

/*********************************** Functions **************************************/
// Displays game options menu and returns chosen option
int gameOptionsMenu();
//
int afterAuthMenu();
//
int modesMenu();
//
int exitGameMenu();
