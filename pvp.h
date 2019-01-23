#ifndef PVP_H_INCLUDED
#define PVP_H_INCLUDED
#include "logic.h"

int skipTurn;
int gameOver;
int turn;
int passCount;
char** grid;
Token tGrid[9][9];
int ACapturedTokens;
int BCapturedTokens;
int AScore;
int BScore;
void endGame();
void endTurn();
void startTurnLoop();
void putToken(int hpos,int vpos);
int checkSlot(int hpos,int vpos);
void initPvp(char ** _grid);
int checkCapture(Token token);
void capture(Token token);
void computeScore();
Team* getAllTeams();
int teamIsClosed();

#endif

