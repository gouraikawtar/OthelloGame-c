/**
* Register and login functions headers
*/

/*************************** Structures ********************************/
/// User's structure
typedef struct User
{
    char password[20];
    char firstName[20];
    char lastName[20];
    char userName[10];
    int score;
}User;

/*************************** Functions ********************************/
/// Checks if the username exists or no, return 1 if yes, 0 if no
int usernameExist(char username[20]);
/// Checks if the user exists or no, return 1 if yes, 0 if no
int userExist(char username[20], char password[20]);
/// Gets the user from file
User* getUser(User *my_player, char username[20], char password[20]);
/// Create new user, adds it to file, and return the created user
User* signup(User *new_player);
/// Returns logged in user
User* login(User *my_player);
/// All the authentication process
User* authentication(User *my_player);
