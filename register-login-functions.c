/**
* Register and login functions implementation
*/
#include "main.h"

int usernameExist(char username[20])
{
    int exist = 0;
    User u_exist;
    FILE *f_users = NULL;
    f_users = fopen(".\\game_files\\users\\users.bin","rb");
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
    f_users = fopen(".\\game_files\\users\\users.bin","rb");
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
    f_users = fopen(".\\game_files\\users\\users.bin","rb");
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

    move(5,20);
    printw("****************** SIGN UP ********************\n\n\n");
    printw("\t\tFirst name: ");
    getstr(new_player->firstName);
    printw("\t\tLast name: ");
    getstr(new_player->lastName);
    printw("\t\tUsername: ");
    getstr(new_player->userName);
    while(usernameExist(new_player->userName)==1)
    {
        printw("\t\tUsername exist, please try another one!\n");
        printw("\t\tUsername: ");
        getstr(new_player->userName);
    }
    printw("\t\tPassword: ");
    getstr(new_player->password);
    new_player->score = 0;
    refresh();

    f_users = fopen(".\\game_files\\users\\users.bin","ab+");
    if(f_users != NULL)
    {
        fwrite(new_player,sizeof(User),1,f_users);
        fclose(f_users);
    }
    return new_player;
}

User* login(User *my_player)
{
    char username[20], password[20];

    move(5,20);
    printw("****************** LOGIN ********************\n\n\n");
    printw("\t\tUsername: ");
    getstr(username);
    printw("\t\tPassword: ");
    getstr(password);
    refresh();
    if(userExist(username,password) == 1)
    {
        my_player = getUser(my_player,username,password);
    }

    return my_player;
}

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
        move(getmaxy(stdscr)/2,getmaxx(stdscr)/4);
        printw("GOODBYE CHAMP!\n");
        mvprintw(getmaxy(stdscr)-2,getmaxx(stdscr)-40,"Press any key to exit..");
        break;
    }
    return my_player;
}

