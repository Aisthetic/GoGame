#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pvp.h"
#include "logic.h"

void addMember(Team *self, Token member){
    self->Members[self->MembersCount] = member;
    self->MembersCount++;
    printf("Ajout du token(%d,%d,%c) à la team members count %d \n",member.X,member.Y,member.side,self->MembersCount);
}
Team ConstructTeam(){
    Team team;
    team.MembersCount=0;
    team.Members = (Token*)(malloc(100*sizeof(Token)));
    team.addMember = addMember;
    return team;
}

int SlotInGrid(int x,int y){
    //printf("checking if slot (%d,%d) is in grid",x,y);
    if( ((x>=0)&&(x<=8)) && ((y>=0)&&(y<=8)) ){
        //printf(" YES \n");
        return 1; //yes
    }
    //printf(" no \n");
    return 0; //no
}

int SlotFree(int x,int y){
    return grid[y][x] == ' ' ? 1 : 0;
}

int sameTeam(Token token1,Token token2){
    printf("same team check (%d,%d) vs (%d,%d) = %d \n",token1.X,token1.Y,token2.X,token2.Y,token1.side == token2.side?1:0);

    return token1.side == token2.side?1:0;
}
Team surroundingAllies(Token* pToken){//petite team de surrounding allies
    printf("Checking surrounding allies for (%d,%d) \n",pToken->X,pToken->Y);
    Token token = *pToken;
    Team allies = ConstructTeam();
    if(SlotInGrid(token.X+1,token.Y)==1 && SlotFree(token.X+1,token.Y) != 1 && sameTeam(token,tGrid[token.X+1][token.Y])) allies.addMember(&allies,tGrid[token.X+1][token.Y]);
    if(SlotInGrid(token.X,token.Y+1)==1 && SlotFree(token.X,token.Y+1) != 1 && sameTeam(token,tGrid[token.X][token.Y+1])) allies.addMember(&allies,tGrid[token.X][token.Y+1]);
    if(SlotInGrid(token.X-1,token.Y)==1 && SlotFree(token.X-1,token.Y) != 1 && sameTeam(token,tGrid[token.X-1][token.Y])) allies.addMember(&allies,tGrid[token.X-1][token.Y]);
    if(SlotInGrid(token.X,token.Y-1)==1 && SlotFree(token.X,token.Y-1) != 1 && sameTeam(token,tGrid[token.X][token.Y-1])) allies.addMember(&allies,tGrid[token.X][token.Y-1]);
    return allies;
}

Team surroundingEnnemies(Token* pToken){//petite team de surrounding ennemies
    Token token = *pToken;
    Team allies = ConstructTeam();//allies==ennemies flemme de tout réecrire
    if(SlotInGrid(token.X+1,token.Y)==1 && SlotFree(token.X+1,token.Y) != 1 && !sameTeam(token,tGrid[token.X+1][token.Y])) allies.addMember(&allies,tGrid[token.X+1][token.Y]);
    if(SlotInGrid(token.X,token.Y+1)==1 && SlotFree(token.X,token.Y+1) != 1 && !sameTeam(token,tGrid[token.X][token.Y+1])) allies.addMember(&allies,tGrid[token.X][token.Y+1]);
    if(SlotInGrid(token.X-1,token.Y)==1 && SlotFree(token.X-1,token.Y) != 1 && !sameTeam(token,tGrid[token.X-1][token.Y])) allies.addMember(&allies,tGrid[token.X-1][token.Y]);
    if(SlotInGrid(token.X,token.Y-1)==1 && SlotFree(token.X,token.Y-1) != 1 && !sameTeam(token,tGrid[token.X][token.Y-1])) allies.addMember(&allies,tGrid[token.X][token.Y-1]);
    return allies;
}

