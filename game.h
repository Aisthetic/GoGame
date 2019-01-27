#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "logic.h"
//Variavles pour le mode de jeu
int pvp;
int pve;
int difficulty;
int machineFirst;

int skipTurn;
int gameOver;
int turn;
int passCount;
char** grid;
Token tGrid[9][9];
int ACapturedTokens;
int BCapturedTokens;
void endGame();
void endTurn();
void pvpGameLoop();
void pveGameLoop();
void putToken(int hpos,int vpos);
int checkSlot(int hpos,int vpos);
void initGame(char ** _grid);
void pveEasyGameLoop();
void pveHardGameLoop();
int checkCapture(Token token);
void capture(Token token);
int teamIsClosed();
Token KoIncompatibleSlot;
#endif

