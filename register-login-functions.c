/**
* Register and login functions implementation
*/
#include "main.h"

int usernameExist(char username[20])
{
    int exist = 0;
    User u_exist;
    FILE *f_users = NULL;
    f_users = fopen(".\\game_files\\users.bin","rb");
    if(f_users != NULL)
    {
        while(!feof(f_users) && exist == 0)
        {
            fread(&u_exist,sizeof(User),1,f_users);
            if(strcmp(username,u_exist.userName)==0)
                exist = 1;
        }
        fclose(f_users);
    }
    return exist;
}

int userExist(char username[20], char password[20])
{
    int exist = 0;
    User u_exist;
    FILE *f_users = NULL;
    f_users = fopen(".\\game_files\\users.bin","rb");
    if(f_users != NULL)
    {
        while(!feof(f_users) && exist == 0)
        {
            fread(&u_exist,sizeof(User),1,f_users);
            if(strcmp(username,u_exist.userName)==0 && strcmp(password,u_exist.password)==0)
                exist = 1;
        }
        fclose(f_users);
    }
    return exist;
}

User* getUser(User *my_player, char username[20], char password[20])
{
    FILE *f_users = NULL;
    int find = 0;

    my_player = malloc(sizeof(User));
    f_users = fopen(".\\game_files\\users.bin","rb");
    if(f_users != NULL)
    {
        while(!feof(f_users) && find == 0)
        {
            fread(my_player,sizeof(User),1,f_users);
            if(strcmp(username,my_player->userName)==0 && strcmp(password,my_player->password)==0)
                find = 1;
        }
        fclose(f_users);
    }
    return my_player;
}

User* signup(User *new_player)
{
    FILE *f_users = NULL;

    new_player = malloc(sizeof(User));

    printw("Sign up\n");
    printw("First name: ");
    getstr(new_player->firstName);
    printw("Last name: ");
    getstr(new_player->lastName);
    printw("Username: ");
    getstr(new_player->userName);
    while(usernameExist(new_player->userName)==1)
    {
        printw("Username exist, please try another one!\n");
        printw("Username: ");
        getstr(new_player->userName);
    }
    printw("Password: ");
    getstr(new_player->password);
    new_player->score = 0;
    refresh();

    f_users = fopen(".\\game_files\\users.bin","ab+");
    if(f_users != NULL)
    {
        fwrite(new_player,sizeof(User),1,f_users);
        fclose(f_users);
    }
    return new_player;
}
/*User signUp(User *new_player, int *has_accessed)
{
    User new_user;
    FILE *f_users = NULL;

    printw("Sign up\n");
    printw("First name: ");
    getstr(new_user.firstName);
    printw("Last name: ");
    getstr(new_user.lastName);
    printw("Username: ");
    getstr(new_user.userName);
    while(usernameExist(new_user.userName)==1)
    {
        printw("Username exist, please try another one!\n");
        printw("Username: ");
        getstr(new_user.userName);
    }
    printw("Password: ");
    getstr(new_user.password);
    new_user.score = 0;
    refresh();

    f_users = fopen(".\\game_files\\users.bin","ab+");
    if(f_users != NULL)
    {
        fwrite(&new_user,sizeof(User),1,f_users);
        *has_accessed = 1;
        fclose(f_users);
    }
    return new_user;
}
*/

User* login(User *my_player)
{
    char username[20], password[20];

    printw("Login\n");
    printw("Username: ");
    getstr(username);
    printw("Password: ");
    getstr(password);
    refresh();
    if(userExist(username,password) == 1)
    {
        my_player = getUser(my_player,username,password);
    }

    return my_player;
}

/*User login(int *has_accessed)
{
    char username[20], password[20];
    User my_player;

    printw("Login\n");
    printw("Username: ");
    getstr(username);
    printw("Password: ");
    getstr(password);
    refresh();
    if(userExist(username,password) == 1)
    {
        my_player = getUser(username,password);
        *has_accessed = 1;
    }
    return my_player;
}
*/
User* authentication(User *my_player)
{
    start: switch(LoginMenu())
    {
    case 0:
        clear();
        my_player = login(my_player);
        if(my_player == NULL)
        {
            printw("Username or password incorrect! Try again or maybe register!\nPress any key to continue..");
            getch();
            clear();
            goto start;
        }
        break;
    case 1:
        clear();
        my_player = signup(my_player);
        break;
    case 2:
        clear();
        printw("Goodbye!\n");
        break;
    }
    return my_player;
}
/*User* userSearch(char *username, char *password)
{
    int exist = 0;
    User eu;
    FILE *users = NULL;
    users = fopen(".\\game_files\\users.bin","rb");
    /// Read from the users information 's file to check the validity of password and  user name
     if(users != NULL)
     {
         while(!feof(users) && exist == 0){
            fread(&eu,sizeof(User),1,users);
            if(strcmp(username,eu.userName)==0 && strcmp(password,eu.userName)==0)
                exist = 1;

         }
         fclose(users);
     }
     if(exist == 1)
        return &eu;
     else
        return NULL;
}
*/
/*int userNameSearch(char *username)
{
    int exist =0;
    struct User eu;
    FILE    *users ;
    users = fopen(".\\game_files\\users.bin","rb");
    /// Read from the users information 's file to check if the username chosen isn't used before
     if(users != NULL)
     {
         while(!feof(users) && exist == 0){
            fread(&eu,sizeof(User),1,users);
            if(strcmp(username,eu.userName)==0)
                exist = 1;

         }
         fclose(users);
     }
     return exist ;

}

User sign_up(int * accessTest)
{
    User newUser ;
    *accessTest=0;
    FILE *users;
    clear();
    move(3,40);
    printw("<--<<Create Account>>--> \n\n");
    /// New_user's informations
     printw("     Enter First Name: ");
     fflush(stdin);
     scanw("%s" ,newUser.firstName);
     printw("\n     Enter Last Name: ");
     scanw("%s",newUser.lastName);
     printw("\n     Enter Username: ");
     scanw("%s",newUser.userName);
     /// The user can not choose an existing username , he keeps entering until he choose an unique user name
           while(userNameSearch(&newUser.userName)==1)
    {
        printw("\n     User name already exist please enter another one !\n");
        printw("\n     Enter Username: ");
        scanw("%s",newUser.userName);
    }
     printw("\n     Enter Password: ");
     scanw("%s",newUser.password);
     newUser.score = 0;
     users=fopen(".\\game_files\\users.bin","ab+");
     if(users != NULL)
     {
        fwrite(&newUser,sizeof(newUser),1,users);
        fclose(users);
        *accessTest=1; /// Set the access test if  the account created successfully
        printw(" Account Created Successfully.");
        move(25,75);
        printw("Press any key to continue...");
        getch();
        clear();
        refresh();
     }

     return newUser;

}

User log_in(int *accessTest)
{
    char userName[20],password[20];
    User u ;
    clear();
    move(3,53);
    printw("<--<<LOGIN TO YOUR ACCOUNT>>->\n\n");
    printw(" Enter Username: ");
    scanw("%s",userName);
    printw("\n Enter Password: ");
    scanw("%s",password);
    u = userSearch(&userName, &password);
    if(strcmp(userName,u.userName)==0 && strcmp(password,u.userName)==0)
        {
            *accessTest = 1 ; /// Set the access test if the user logged in successfully
            printw(" \n Username And Password is Correct.\n");
            printw(" Press any key to continue...");
            getch();
            move(12,57);
            printw(" Welcome %s %s ", u.firstName,u.lastName);
            getch();
        }
    else
        {
            *accessTest= 0 ; /// Reset the access test if the user could not access
            printw("\n Username And Password is Incorrect.\n\n");
            printw(" Press any key to continue...");
            getch();
        }
    return u ;
}



User access(int * accessTest)
{
    User currentUser ;
    switch (LoginMenu())
        {

        case 0:
            {
            currentUser = log_in(accessTest);
            break;
            }


        case 1:
            {
            currentUser = sign_up( accessTest);
            break;
            }

        case 2:
            exit(0);

        default:
            printw("Invalid Choice! ");
            refresh();
            break;
        }

      return currentUser;



}
*/


