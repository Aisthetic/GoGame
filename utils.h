#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

int compare(Token token1,Token token2);//Comparer deux tokens
int checkIfTokenisInTeam(Team team , Token token);
Team teamUnion(Team team1, Team team2);//L'union de deux teams
void copyMatrix(void** a,void** c);
#endif // UTILS_H_INCLUDED
