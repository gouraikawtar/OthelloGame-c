#include "main.h"


int main()
{
    game();
   /* User u;
    strcpy(u.firstName,"NENE");
    strcpy(u.lastName,"Nene");
    strcpy(u.userName,"nene");
    strcpy(u.password, "1457");
    u.score = 63;
    setBestScores(u);

    User *tab = getBestScores();
    for(int i=0;i<T_MAX;i++)
        printf("Username: %s | Score %d\n",tab[i].userName,tab[i].score);*/
    /*User u;
    FILE *f_users = fopen(".\\game_files\\users.bin","wb+");
    FILE *f_scores = fopen(".\\game_files\\best_scores.bin","wb+");
    if( f_users != NULL && f_scores != NULL)
    {
        for(int i=0;i<10;i++)
        {
            scanf("%s",u.firstName);
        scanf("%s",u.lastName);
        scanf("%s",u.userName);
        scanf("%s",u.password);
        scanf("%d",&u.score);
        fwrite(&u,sizeof(User),1,f_users);
        fwrite(&u,sizeof(User),1,f_scores);
        }
        fclose(f_users);
        fclose(f_scores);
    }*/

    /*int *t_size = NULL;
    t_size = fileLines();
    printf("%d",*t_size);*/
    /*User *tab = getBestScores(tab, t_size);
    if(tab != NULL)
        printf("Username : %s | Score : %d",tab[0].userName,tab[0].score);
    else
        printf("NULL");*/
   /* FILE *file = fopen(".\\game_files\\best_scores.bin","rb");
    User u;
    int lines = 0;
    if(file != NULL)
    {
        while(!feof(file))
        {
            fread(&u,sizeof(User),1,file);
            lines++;
        }
        fclose(file);
    }
    printf("lines = %d",lines);*/
    return 0;
}
