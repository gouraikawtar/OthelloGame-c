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

User sign_up()
{
    User newUser ;
    int exist = 0;
    FILE *users;
     printw("<--<<Create Account>>--> \n\n");
    //New_user's informations
     printw("     Enter First Name: ");
     fflush(stdin);
     scanw("%s" ,newUser.firstName);
     printw("\n     Enter Last Name: ");
     scanw("%s", newUser.lastName);
     printw("\n     Enter Username:");
     scanw("%s",newUser.userName);
      while(userNameSearch(newUser.userName)==1)
    {
        printw("\n     User name already exist please enter another one !\n");
        printw("\n     Enter Username:");
        scanw("%s",newUser.userName);
    }
     printw("\n     Enter Password:");
     scanw("%s",newUser.password);
     newUser.score = 0;
     users=fopen(".\\game_files\\users.bin","ab+");
     if(users != NULL)
     {
        fwrite(&newUser,sizeof(newUser),1,users);
        fclose(users);
     }
     return newUser;

}

User log_in()
{
    char userName[20],password[20];
    printw("<--<<LOGIN TO YOUR ACCOUNT>>->\n\n");
    printw(" Enter Username: ");
    scanw("%s",userName);
    printw("\n Enter Password: ");
    scanw("%s",password);
    return userSearch(userName, password);
}
