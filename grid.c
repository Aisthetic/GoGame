//Formatte et affiche une ligne donnée de la grille
	void printLine(char line[]){
		//Chaque boucle doit afficher un char du tableau puis '|'
		for (int i = 0; i < 8; ++i)
	{
		printf("%c-----", line[i] );
	}
	printf("%c\n", line[8]);
}


void printGrid(char ** grid){
    int i,j;

	//affiche les coord horizontales
    printf("                                  ");
	for (j = 0; j < 8; ++j)
	{
		printf("%d     ", j+1);
	}
	printf("9\n");


	for (i = 0; i < 8; ++i)
	{
		printf("                                %d ", i+1);
		printLine(grid[i]);
		printf("                                  ");

		//Boucle pour afficher les '| | | | | |'
		for (int j = 0; j < 8; ++j)
		{
			printf("|     ");
		}
		printf("|\n");

		printf("                                  ");
		for (int k = 0; k < 8; ++k)
		{
			printf("|     ");
		}
		printf("|\n");

	}
	printf("                                9 ");
	printLine(grid[8]);
}

//Retourne une grille vide
char ** getBlankGrid(){
	char ** mat = (char *) malloc((sizeof(char *))*9);
	int i=0,j=0;
    for(i=0; i<9; i++)
        mat[i] = (char *) malloc(sizeof(char)*9);
    for(i=0; i<9; i++){
           for(j=0; j<9; j++){
           	mat[i][j] = ' ';
           }
       }
	return mat;
}
