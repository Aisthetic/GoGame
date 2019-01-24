#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include "pvp.h"
#include "utils.h"
#include "score.h"
#include <string.h>
//TODO : Actualisation des teams des allies

void endTurn(){
    //system("@cls||clear");
    printGrid(grid);
    if(!skipTurn)turn++;
}

void endGame(){
    computeScore();
    printf("Game's over \n");
}

/*
    Description: fonction pour trouver toutes les teams de la grille
    Params: none
    Return: tableau
*/
Team* getAllTeams(){
    Team teams[81];
    int teamsCount = 0;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++){
            int teamRegistred=0;
            for(int k=0;k<teamsCount;k++){
                if(sameTeam(tGrid[i][j],teams[i].Members[0]))
                    teamRegistred=1;
            }
            if(!teamRegistred)
                teams[i] = tGrid[i][j].team;
                teamsCount++;
        }
    }
    //On met -1 sur le memberCount de la derniere team pour marquer la fin du tableau
    teams[teamsCount].MembersCount = -1;
    return teams;
}

void startTurnLoop(){
	//Si le nombre de tours est pair alors A joue

	//Choix d'une pos sur la grille
	while(!gameOver){
        printf("----Turn %d %d----\n", turn,passCount);
        skipTurn = 0;//reset de la variable

        //Check si les deux ont passé
        if(passCount == 2){//fin du jeu
            break;
        }

        printf("Player %c's turn \n",turn%2 == 0?'A':'B');
        //Passer ou jouer
        printf("Do you want to pass ?(yes or no)\n");
        char* choice = malloc(sizeof(char)*3);//max 3 pour "yes"
        scanf("%s",choice);
        if (choice[0] == 'y'){//pass case
            passCount++;
            endTurn();
            continue;
        }
        passCount = 0;

        //Si le joueur a choisi de jouer
		int Y=-1,X=-1; //pos verticale/horizontale
		printf("Choose X : \n");//Y
		scanf("%d", &X);
		printf("Choose Y : \n");//X
		scanf("%d", &Y);

       if(checkSlot(X,Y) == 0) {
            continue;
        }
        putToken(X,Y);
		endTurn();
	}
}


void putToken(int X,int Y){
    Token backupTGrid[9][9];

    copyMatrix(backupTGrid,tGrid);
    grid[Y-1][X-1] = turn%2 == 0?'A':'B';//Indexation de 1 à 9 sur l'ihm

    //Définition du token
    Token token;
    token.side = grid[Y-1][X-1] = turn%2 == 0?'A':'B';
    token.X = X-1;
    token.Y = Y-1;
    //token.freedomDeg = &freedomDeg;
    token.surroundingAllies = surroundingAllies;
    token.surroundingEnnemies = surroundingEnnemies;

    //Affectation de la team
    Team _team;
    _team = ConstructTeam();
    token.team = _team;
    token.team.addMember(&token.team,token);
    Team closeAllies;
    closeAllies = token.surroundingAllies(&token);
    printf("%d allies adjacents , on fait l'union.\n",closeAllies.MembersCount);

    //Debug
    if(closeAllies.MembersCount>0){
        for (int i = 0; i<closeAllies.Members[0].team.MembersCount; i++){
            printf("first adjacent team member (%d,%d) \n",closeAllies.Members[0].team.Members[i].X,closeAllies.Members[0].team.Members[i].Y);
        }
    }

    //Union
    for(int i = 0; i<closeAllies.MembersCount ; i++){
        Team tmp;
        tmp = teamUnion(token.team,closeAllies.Members[i].team);
        printf("On fait l'union de la team faite , nouvelle longueur : %d \n",tmp.MembersCount);
        token.team = tmp;
    }

    //Mise a jour de la team pour les autres token
    for(int i = 0; i<token.team.MembersCount;i++){
        token.team.Members[i].team=token.team;
        //Actualisation de tGrid
        tGrid[token.team.Members[i].X][token.team.Members[i].Y] = token.team.Members[i];
    }

    //test afficher une team
    for (int i = 0; i<token.team.MembersCount; i++){
        printf("final team member (%d,%d) \n",token.team.Members[i].X,token.team.Members[i].Y);
    }

    //KoRule
    if(checkCapture(token) || (token.X==KoIncompatibleSlot.X && token.Y==KoIncompatibleSlot.Y)){
        printf("KO rule incompatible slot !");
        grid[Y-1][X-1] = ' ';
        copyMatrix(tGrid,backupTGrid);
        skipTurn = 1;
    }


    //Capture check
    printf("checking if any surrounding ennemy can be captured..\n");
    Team ennemies;
    ennemies = token.surroundingEnnemies(&token);
    for(int i =0; i<ennemies.MembersCount; i++){
        printf("checking capture for team ");
        for (int i = 0; i<token.team.MembersCount; i++){
            printf("(%d,%d) ",ennemies.Members[i].X,ennemies.Members[i].Y);
        }
        printf("\n");
        if(checkCapture(ennemies.Members[i])){
            printf("capture du token (%d,%d) \n",token.X,token.Y);
            capture(ennemies.Members[i]);
        }
    }

    //fin du tour
    system("pause");
}

int checkCapture(Token token){
    for(int i = 0; i < token.team.MembersCount; i++){
        printf("checking capture for token (%d,%d) \n",token.team.Members[i].X,token.team.Members[i].Y);
        Team allies;
        Team ennemies;
        allies = token.team.Members[i].surroundingAllies(&token.team.Members[i]);
        ennemies = token.team.Members[i].surroundingEnnemies(&token.team.Members[i]);
        int liberty=4;
        liberty = liberty - allies.MembersCount;
        liberty = liberty - ennemies.MembersCount;
        //Pour les tokens aux limites
        if(token.team.Members[i].X==0 || token.team.Members[i].X==8) liberty = liberty-1;
        if(token.team.Members[i].Y==0 || token.team.Members[i].Y==8) liberty = liberty-1;
        printf("token's liberty degree is %d \n",liberty);
        if(liberty>0){
            printf("le token est libre. \n");
            return 0;
        }
    }
    return 1;
}


void capture(Token token){
    //Si c'est un seul token, on met en place la règle du KO
    if(token.team.MembersCount==1){
        KoIncompatibleSlot = token;
    }
    //Mise à jour des grid
    for(int i =0;i<token.team.MembersCount;i++){
        grid[token.team.Members[i].Y][token.team.Members[i].X] = ' ';
        tGrid[token.team.Members[i].Y][token.team.Members[i].X].X=-1;
        tGrid[token.team.Members[i].Y][token.team.Members[i].X].Y=-1;
        tGrid[token.team.Members[i].Y][token.team.Members[i].X].side=' ';
    }

    //Scoring
    if(token.side == 'A') BCapturedTokens = BCapturedTokens+token.team.MembersCount;
    else ACapturedTokens = ACapturedTokens+token.team.MembersCount;

    printGrid(grid);
}

//Verifie si le slot est disponible
int checkSlot(int X,int Y){
    if( !((X>=1)&&(X<=9)) || !((Y>=1)&&(X<=9)) ){
        printf("Invalid position (%d,%d)!\n",X,Y);
        return 0;
    }
    if(grid[X-1][Y-1] != ' '){
        printf("Already taken by  ! (%s)\n",grid[X-1][Y-1]);
        return 0;
    }

    //tout est ok
    return 1;
}

//Initiation du mode
void initPvp(char ** _grid){
    gameOver = 0;
    turn= 0;
    passCount= 0;
	grid = _grid;
	KoIncompatibleSlot.X = -1;
	printf("Player A vs Player B\n");
    startTurnLoop();
    endGame();
}


