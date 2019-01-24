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
            for (int i=0;i<territoryLen;i++){
                int xx = territoryX[i];
                int yy = territoryY[i];
                if(grid[yy][xx]!=' '){
                    if(territorySide == ' ') territorySide = tGrid[xx][yy].side;
                    else if(territorySide != tGrid[xx][yy].side) break;
                }
            }
            //Ajout du score
            if(territorySide == 'A')
                AScore += territoryLen;
            if(territorySide == 'B')
                BScore += territoryLen;
        }
    }
    printf("scores : A = %d,B = %d",AScore,BScore);
}

/*
    Description : fonction qui retourne le territoire associé à un token
    Params : coordinates (x,y)
    Returns : array of tokens
*/
void compute(int x,int y){
    if(!SlotInGrid(x,y) || isFlagged(x,y)) return;
    flaggedX[flaggedLen] = x;
    flaggedY[flaggedLen] = y;
    flaggedLen++;
    if(grid[y][x]!=' '){
        territoryX[territoryLen]=x;
        territoryY[territoryLen]=y;
        territoryLen++;
        return;
    }
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
