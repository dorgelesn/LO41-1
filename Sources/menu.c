/**
 * \file menu.c
 * \brief Affichage des menus
 * \author Florian Lacour & Michaël Ayeng
 * \version 0.1
 * \date 12 Mai 2015
 */
 
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"


/**
 * \fn void menuPrincipal(void)
 * \brief Fonction d'affichage du menu principal
 */
void menuPrincipal(void) {

	int choix;
	
	do {
		
		printf("\n\n\n\n******************************\n");
		printf("\tMenu Principal");
		printf("\n******************************\n");
		   
		printf("1) Version standard\n");
		printf("2) Version paramétrée\n");
		printf("3) A propos\n");

		printf("\nVotre choix: ");
		scanf("%d",&choix);
	
		switch (choix) {
	
			case 1: 
		
			break;
		
			case 2:
		
			break;
		
			case 3:
			aPropos();
			break;
		
			default:
			printf("\n\nChoix incorrect");
		}
	} while (1);
}

/**
 * \fn void aPropos(void)
 * \brief Fonction d'affichage des informations relatives au programme
 */
void aPropos(void) {
		
	printf("\n\n\n\n******************************\n");
	printf("\tA propos");
	printf("\n******************************\n");
	
	printf("\nProgramme réalisé dans le cadre de l'UV LO41 à l'Université de technologie de Belfort-Montbéliard");
	printf("\nAuteurs: Florian Lacour, Michaël Ayeng");
	printf("\nSujet du programme: Simulation de carrefours routiers intelligents");
	
	
}
