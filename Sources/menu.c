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

#define NB_ECHANGEURS_DEFAUT 4
#define NB_VEHICULES_DEFAUT 5

void erreur(const char *msg)
{
    perror(msg);
    exit(1);
}

void envoitMessage(int msgid,int numeroEchangeur,voiture V){
	message a;
	a.type=numeroEchangeur;
	a.V=V;
	a.numPid=getpid();
	if(msgsnd(msgid,&a,sizeof(message) - sizeof(long),0)){
		perror("Erreur d'envoit requete");
		exit(1);
	}


}







int creationFile(void*a){
	int msgid;			/* valeur de retour de la creation de la file */
	    key_t key;			/* valeur de retour de la creation de la clé */
			/****************************************************************/
			/*  Creation de la clé IPC 					*/
			/****************************************************************/
    if ((key = ftok((char*)a, 'A')) == -1) {
	perror("Erreur de creation de la clé \n");
	exit(1);
		}
		/****************************************************************/
/* Creation de la file de message 				*/
/* int msgget(key_t key, int msgflg);				*/
/****************************************************************/

    if ((msgid = msgget(key, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
	perror("Erreur de creation de la file\n");
	exit(1);
    }
		return msgid;
}
/**
 * \fn void menuPrincipal(int* nbEchangeurs, int* nbVehicules)
 * \brief Fonction d'affichage du menu principal
 *
 * \param nbEchangeurs Un pointeur sur le nombre d'échangeur de la simulation
 * \param nbVehicules Un pointeur sur le nombre de véhicules de la simulation
 *
 */
void menuPrincipal(int* nbEchangeurs, int* nbVehicules) {

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
      executionStandard(nbEchangeurs,nbVehicules);
			break;

			case 2:
      executionParametree(nbEchangeurs,nbVehicules);
			break;

			case 3:
			aPropos();
			break;

			default:
			printf("\n\nChoix incorrect");
		}
	} while (choix != 1 && choix != 2);
}


/**
 * \fn void executionStandard(int* nbEchangeurs, int* nbVehicules)
 * \brief Fonction d'execution de la simulation en mode standard
 *
 * \details Cette fonction permet d'executer la simulation en mode standard,
 * avec les paramètres par défaut
 *
 * \param nbEchangeurs Un pointeur sur le nombre d'échangeur de la simulation
 * \param nbVehicules Un pointeur sur le nombre de véhicules de la simulation
 */
void executionStandard(int* nbEchangeurs, int* nbVehicules) {

  printf("\n\n\n\n******************************\n");
	printf("\tVersion standard");
	printf("\n******************************\n");

	*nbEchangeurs = NB_ECHANGEURS_DEFAUT;
	*nbVehicules = NB_VEHICULES_DEFAUT;

}


/**
 * \fn void executionParametree(intù nbEchangeurs, int* nbVehicules)
 * \brief Fonction d'execution de la simulation en mode parametrée
 *
 * \details Cette fonction permet d'afficher un menu où l'utilisateur peut
 * spécifier le nombre d'échangeur présent dans la simulation
 * ainsi que le nombre de véhicule que chaque échangeur possèdera
 * au début de la simulation.
 *
 * \param nbEchangeurs Un pointeur sur le nombre d'échangeur de la simulation
 * \param nbVehicules Un pointeur sur le nombre de véhicules de la simulation
 *
 */
void executionParametree(int* nbEchangeurs, int* nbVehicules) {

  printf("\n\n\n\n******************************\n");
	printf("\tVersion parametrée");
	printf("\n******************************\n");

  printf("\nVeuillez entrer le nombre d'échangeurs: ");
  scanf("%d",nbEchangeurs);

  printf("\nVeuillez entrer le nombre de véhicules par échangeur: ");
  scanf("%d",nbVehicules);

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
