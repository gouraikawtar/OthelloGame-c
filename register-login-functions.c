/**
* Register and login functions implementation
*/
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "register-login-functions.h"


User userSearch(char *username, char *password)
{
    int exist =0;
    User eu;
    FILE    *users ;
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
     return eu;

}



int userNameSearch(char *username)
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
           while(userNameSearch(newUser.userName)==1)
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
        *accessTest=1; /// Set the access test if  the account created successfully
        fwrite(&newUser,sizeof(newUser),1,users);
        fclose(users);
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
    u = userSearch(userName, password);
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



