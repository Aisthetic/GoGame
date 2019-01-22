#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

typedef struct Token Token;
typedef struct Team Team;

struct Team{
    Token* Members;
    int MembersCount;
    void (*addMember)(Team* Self, Token Member);
};

struct Token{
    char side;
	int X;
	int Y;
	Team (*surroundingAllies)(Token* self);//Pointeurs sur une fonction
	Team (*surroundingEnnemies)(Token* self);
	Team team; //Pointer to keep track of the changings that happens to the team
};

void addMember(Team* self,Token member);
Team surroundingAllies(Token* self);
Team surroundingEnnemies(Token* self);
Team ConstructTeam();


#endif // LOGIC_H_INCLUDED



