#include <stdio.h>
#include <stdlib.h>
#include "pvp.h"
#include "grid.h"
#include "menu.h"
#include "logic.h"



int main(){
	int choice = showMenu();//Affichage du menu et choix du mode
	char ** grid;
	grid = getBlankGrid();

	printGrid(grid);
	if(choice == 1){//Mode pvp
		initPvp(grid);
	}
	system("pause");
	return 0;
}
