/**
 * \file menu.c
 * \brief Affichage des menus
 * \author Florian Lacour & Michaël Ayeng
 * \version 0.1
 * \date 12 Mai 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"

#define NB_ECHANGEUR_DEFAUT 4
#define NB_VEHICULES_DEFAUT 5


/**
 * \fn void menuPrincipal(void)
 * \brief Fonction d'affichage du menu principal
 *
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
      executionStandard();
			break;

			case 2:
      executionParametree();
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
 * \fn void executionStandard(void)
 * \brief Fonction d'execution de la simulation en mode standard
 *
 * \details Cette fonction permet d'executer la simulation en mode standard,
 * avec les paramètres par défaut
 */
void executionStandard(void) {

  printf("\n\n\n\n******************************\n");
	printf("\tVersion standard");
	printf("\n******************************\n");

  printf("\nExecution de la simulation");
  execlp("./serveur_controleur","serveur_controleur",NB_ECHANGEUR_DEFAUT,NB_VEHICULES_DEFAUT,NULL);
}


/**
 * \fn void executionParametree(void)
 * \brief Fonction d'execution de la simulation en mode parametrée
 *
 * \details Cette fonction permet d'afficher un menu où l'utilisateur peut
 * spécifier le nombre d'échangeur présent dans la simulation
 * ainsi que le nombre de véhicule que chaque échangeur possèdera
 * au début de la simulation.
 * La fonction execute ensuite la simulation
 *
 */
void executionParametree(void) {
  int nbEchangeurs, nbVehicules;

  printf("\n\n\n\n******************************\n");
	printf("\tVersion parametrée");
	printf("\n******************************\n");

  printf("\nVeuillez entrer le nombre d'échangeurs: ");
  scanf("%d",&nbEchangeurs);

  printf("\nVeuillez entrer le nombre de véhicules par échangeur: ");
  scanf("%d",&nbVehicules);

  printf("\nExecution de la simulation");
  execlp("./serveur_controleur","serveur_controleur",nbEchangeurs,nbVehicules,NULL);
}

/**
 * \fn void aPropos(void)
 * \brief Fonction d'affichage des informations relatives au programme
 *
 */
void aPropos(void) {

	printf("\n\n\n\n******************************\n");
	printf("\tA propos");
	printf("\n******************************\n");

	printf("\nProgramme réalisé dans le cadre de l'UV LO41 à l'Université de technologie de Belfort-Montbéliard");
	printf("\nAuteurs: Florian Lacour, Michaël Ayeng");
	printf("\nSujet du programme: Simulation de carrefours routiers intelligents");

}
