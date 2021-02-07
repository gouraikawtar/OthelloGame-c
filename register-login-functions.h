/**
* Register and login functions headers
*/

/*************************** Structures ********************************/
/// User's structure
typedef struct User User;
struct User
{
    char password[20];
    char firstName[20];
    char lastName[20];
    char userName[10];
    int score;
};

/*************************** Functions ********************************/

int usernameExist(char username[20]);
int userExist(char username[20], char password[20]);
User* getUser(User *my_player, char username[20], char password[20]);
User* signup(User *new_player);
User* login(User *my_player);
User* authentication(User *my_player);

/*
/// Return the current user and test the access
User access(int * acessTest);
/// Check the informations entered by the user to log in
User* userSearch(char *username, char *password);
/// Check if the user name entered is already used ( 0 if not and 1 if it exists )
int userNameSearch(char *username);
/// Return the new user and check the access
User sign_up(int * accessTest);
/// Return the current user and check the access
User log_in(int * accessTest);
*/
