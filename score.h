#ifndef SCORE_H_INCLUDED
#define SCOR_H_INCLUDED

int AScore;
int BScore;

int flaggedX[81];
int flaggedY[81];
int flaggedLen;

int territoryX[81];
int territoryY[81];
int territoryLen;

char side;

void compute(int x,int y);
int computeScore();
int isFlagged(int x,int y);
#endif // SCORE_H_INCLUDED
