#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "grid.h"
#include "menu.h"
#include "logic.h"



int main(){
	int choice = -1;//Affichage du menu et choix du modes
	while(choice < 1 || choice > 2){
        choice = MainMenu();
        switch(choice){
            case 1:
                pvp=1;
                break;
            case 2:
                pve=1;
                difficulty = PVEMenu();
                break;
        }
	}
	grid = getBlankGrid();
    printGrid(grid);
    initGame(grid);
	system("pause");
	return 0;
}
