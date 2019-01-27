#include "grid.h"
#include "game.h"
#include "logic.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>

void play(){
    int chosenX=-1;
    int chosenY=-1;
    getAllTeams();
    int teamsLen=0;
    //On récup la longueur du tableau
    for(int i=0;i<81;i++){
        if(allTeams[i].MembersCount=-1){
            teamsLen = i;
            break;
        }
    }

    //On parcourt toutes les teams
    for(int i=0;i<teamsLen;i++){
        if(allTeams[i].Members[0].side == 'A'&&true)//Ennemy or ally on applique cette methode car dans le cas d'un allié ça va le sortir d'une
        //situation de mort et dans le cas d'un ennemie ça va le capturer
        {
            int teamLiberty=0;
            int freeGuyX;
            int freeGuyY;
            for(int j = 0; j < allTeams[i].MembersCount; j++){//Pour définir la libérté de la team
                printf("checking capture for token (%d,%d) \n",allTeams[i].Members[j].X,allTeams[i].Members[j].Y);
                Team allies;
                Team ennemies;
                allies = allTeams[i].Members[j].surroundingAllies(&allTeams[i].Members[j]);
                ennemies = allTeams[i].Members[j].surroundingEnnemies(&allTeams[i].Members[j]);
                int liberty=4;
                liberty = liberty - allies.MembersCount;
                liberty = liberty - ennemies.MembersCount;
                //Pour les tokens aux limites
                if(allTeams[i].Members[j].X==0 || allTeams[i].Members[j].X==8) liberty = liberty-1;
                if(allTeams[i].Members[j].Y==0 || allTeams[i].Members[j].Y==8) liberty = liberty-1;
                printf("token's liberty degree is %d \n",liberty);
                if(liberty>teamLiberty){
                    teamLiberty=liberty;
                    freeGuyX = allTeams[i].Members[j].X;
                    freeGuyY = allTeams[i].Members[j].Y;
                }
            }
            if(teamLiberty==1){//si la team peut être capturée , on cherche la pos pour la capturer;
                if(SlotInGrid(freeGuyX-1,freeGuyY)&&grid[freeGuyY][freeGuyX-1]==' '){
                    chosenX = freeGuyX-1;
                    chosenY = freeGuyY;
                }
                if(SlotInGrid(freeGuyX+1,freeGuyY)&&grid[freeGuyY][freeGuyX+1]==' '){
                    chosenX = freeGuyX+1;
                    chosenY = freeGuyY;
                }
                if(SlotInGrid(freeGuyX,freeGuyY-1)&&grid[freeGuyY-1][freeGuyX]==' '){
                    chosenX = freeGuyX;
                    chosenY = freeGuyY-1;
                }
                if(SlotInGrid(freeGuyX,freeGuyY+1)&&grid[freeGuyY+1][freeGuyX]==' '){
                    chosenX = freeGuyX;
                    chosenY = freeGuyY+1;
                }
            }
        }
    }
}

/*
    Description: fonction pour trouver toutes les teams de la grille
    Params: none
    Return: tableau
*/
void getAllTeams(){
    int teamsCount = 0;
        printf("The solver is thinking.. \n");

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++){
            int teamRegistred=0;
            for(int k=0;k<teamsCount;k++){
                printf("check for (%d,%d),teamsCount %d.. \n",i,j,teamsCount);
                if(sameTeam(tGrid[i][j],allTeams[i].Members[0]))
                    teamRegistred=1;
            }
            if(!teamRegistred && grid[j][i] != ' '){
                allTeams[teamsCount] = tGrid[i][j].team;
                teamsCount++;
            }
        }
    }
    //On met -1 sur le memberCount de la derniere team pour marquer la fin du tableau
    allTeams[teamsCount].MembersCount = -1;
}

