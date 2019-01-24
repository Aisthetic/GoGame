#include <stdio.h>
#include "pvp.h"
#include "logic.h"
#include "score.h"

int computeScore(){
    flaggedLen=0;
    territoryLen=0;
    for(int x=0;x<9;x++){
        for(int y=0;y<9;y++){
            //Formation du territoire associé
            if(!isFlagged(x,y)) compute(x,y);
            char territorySide = ' ';
            //Détermination du side
            printf("territory : ");
            for (int i=0;i<territoryLen;i++){
                int xx = territoryX[i];
                int yy = territoryY[i];
                printf("(%d,%d) ",xx,yy);
                if(grid[yy][xx]!=' '){
                    if(territorySide == ' ') territorySide = tGrid[xx][yy].side;
                    else if(territorySide != tGrid[xx][yy].side) break;
                }
            }
            printf("\nBoucle (%d,%d) , territoire de longueur %d , side %c \n",x,y,territoryLen,territorySide);
            //Ajout du score
            if(territorySide == 'A')
                AScore += territoryLen;
            if(territorySide == 'B')
                BScore += territoryLen;

            //Reset
            territoryLen = 0;
        }
    }
    printf("scores : A = %d,B = %d",AScore+ACapturedTokens,BScore+BCapturedTokens);
}

/*
    Description : fonction qui retourne le territoire associé à un token
    Params : coordinates (x,y)
    Returns : array of tokens
*/
void compute(int x,int y){
    printf("computing score for (%d,%d) \n",x,y);
    if(!SlotInGrid(x,y) || isFlagged(x,y)) return;
    //put a flag on the slot
    flaggedX[flaggedLen] = x;
    flaggedY[flaggedLen] = y;
    flaggedLen++;
    //add it to the territory
    territoryX[territoryLen]=x;
    territoryY[territoryLen]=y;
    territoryLen++;
    //if it's a border stop
    if(grid[y][x]!=' ')
        return;
    compute(x-1,y);
    compute(x+1,y);
    compute(x,y-1);
    compute(x,y+1);
}

/*
    Description : check if a slot is already flagged
    Params : coordinates (x,y)
    Returns : bool yes or no

*/
int isFlagged(int x,int y){
    for(int i = 0; i < flaggedLen ; i++){
        if((flaggedX[i]==x)&&(flaggedY[i]==y)) return 1;
    }
    return 0;
}
