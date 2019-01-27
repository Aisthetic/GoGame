#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void printLogo(){
    printf("                  ************************************************************************************\n");
    printf("                  *                                                                                  *\n");
    printf("                  *     ::::::::   ::::::::        ::::::::      :::     ::::    ::::  ::::::::::    *  \n");
    printf("                  *    :+:    :+: :+:    :+:      :+:    :+:   :+: :+:   +:+:+: :+:+:+ :+:           *   \n")    ;
    printf("                  *    +:+        +:+    +:+      +:+         +:+   +:+  +:+ +:+:+ +:+ +:+           *      \n");
    printf("                  *    :#:        +#+    +:+      :#:        +#++:++#++: +#+  +:+  +#+ +#++:++#      *   \n");
    printf("                  *    +#+   +#+# +#+    +#+      +#+   +#+# +#+     +#+ +#+       +#+ +#+           *       \n");
    printf("                  *    #+#    #+# #+#    #+#      #+#    #+# #+#     #+# #+#       #+# #+#           *      \n") ;
    printf("                  *     ########   ########        ########  ###     ### ###       ### ##########    *  \n");
    printf("                  *                                                                                  *\n");
    printf("                  ************************************************************************************\n\n");

}

int MainMenu(){
    int choice = 0;
    FILE* rules = NULL ;
    printLogo();
    printf("                            ****************************************************************\n");
    printf("                            *     *                                                        *\n");
    printf("                            *  1  *                  Nouvelle partie                       *\n");
    printf("                            *     *                                                        *\n");
    printf("                            ****************************************************************\n");
    printf("                            *     *                                                        *\n");
    printf("                            *  2  *                       Aide                             *\n");
    printf("                            *     *                                                        *\n");
    printf("                            ****************************************************************\n");
    printf("                            *     *                                                        *\n");
    printf("                            *  3  *                      Quitter                           *\n");
    printf("                            *     *                                                        *\n");
    printf("                            ****************************************************************\n");
    scanf("%d",&choice);
    switch(choice){
        case 2:
            rules = fopen("rules.txt","r"); //On ouvre le fichier aide
            int caractereActuel = 0;
            if (rules != NULL){
            // On peut lire le fichier
            // Boucle de lecture des caractères un à un
            do{
                caractereActuel = fgetc(rules); // On lit le caractère
                printf("%c", caractereActuel); // On l'affiche
            } while (caractereActuel != EOF);


            }
            else
            {
            // On affiche un message d'erreur si on veut
            printf("Erreur lors de l'ouverture");
            }
            system("pause");
            fclose(rules); //on ferme le fichier
            system("cls");
            break;
        case 3 :
            exit(0);
            break;
        case 1 :
            //Choix du mode de  jeu
            printf("                            ****************************************************************\n");
            printf("                            *     *                                                        *\n");
            printf("                            *  1  *                   Homme VS Homme                       *\n");
            printf("                            *     *                                                        *\n");
            printf("                            ****************************************************************\n");
            printf("                            *     *                                                        *\n");
            printf("                            *  2  *                  Homme VS Machine                      *\n");
            printf("                            *     *                                                        *\n");
            printf("                            ****************************************************************\n");
            scanf("%d",&choice);
            return choice;
            break;
        default :
            system("cls");
            break;
    }
}

int PVEMenu(){
        printf("                            ****************************************************************\n");
        printf("                            *     *                                                        *\n");
        printf("                            *  !  *             Choisissez une difficulte                  *\n");
        printf("                            *     *                                                        *\n");
        printf("                            ****************************************************************\n");
        int difficulty;
        printf("                            ****************************************************************\n");
        printf("                            *     *                                                        *\n");
        printf("                            *  1  *                      Facile                            *\n");
        printf("                            *     *                                                        *\n");
        printf("                            ****************************************************************\n");
        printf("                            *     *                                                        *\n");
        printf("                            *  2  *                      Avancee                           *\n");
        printf("                            *     *                                                        *\n");
        printf("                            ****************************************************************\n");
        scanf("%d",&difficulty);
        return difficulty;
}

