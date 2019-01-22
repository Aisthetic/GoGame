#include <stdio.h>
#include <stdlib.h>
#include "logic.h"
#include "pvp.h"

int compare(Token token1,Token token2){//Comparer deux tokens
    return (token1.X == token2.X && token1.Y == token2.Y)?1:0;
}

int checkIfTokenisInTeam(Team team , Token token){
    for(int i = 0 ; i++ ; i<team.MembersCount){
        if(compare(token,team.Members[i])) {
            return 1;
        }
    }
    return 0;
}

Team teamUnion(Team team1, Team team2)//L'union de deux teams
{
    printf("Union de deux teams \n");
    for (int i = 0; i<team1.MembersCount; i++){
        printf("team1 member (%d,%d) \n",team1.Members[i].X,team1.Members[i].Y);
    }
    for (int i = 0; i<team2.MembersCount; i++){
        printf("team2 member (%d,%d) \n",team2.Members[i].X,team2.Members[i].Y);
    }
    for(int i = 0;  i < team2.MembersCount;i ++ ){
        if(checkIfTokenisInTeam(team1,team2.Members[i])==0)
            team1.addMember(&team1,team2.Members[i]);
        else
            printf("already in team");
    }
    printf("result\n");
    for (int i = 0; i<team1.MembersCount; i++){
        printf("Membre (%d,%d) \n",team1.Members[i].X,team1.Members[i].Y);
    }
    return team1;
}
