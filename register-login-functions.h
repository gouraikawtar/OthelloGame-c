/**
* Register and login functions headers
*/

typedef struct User
{
    char password[20];
    char firstName[20];
    char lastName[20];
    char userName[10];
    int score;
}User;

User userSearch(char *username, char *password);
int userNameSearch(char *username);
User sign_up();
User log_in();
