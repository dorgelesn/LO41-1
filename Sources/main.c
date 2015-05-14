/**
 * \file main.c
 * \brief Simulation de carrefours routiers intelligents
 * \author Florian Lacour & Michaël Ayeng
 * \version 0.1
 * \date 13 Mai 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"


/**
 * \fn int main(int argc, char *argv[])
 * \brief Programme principal de la simulation
 *
 *
 * \param argc Valeur représentant le nombre d'argument passés lors de l'appel du binaire exécutable
 * \param argv Tableau de char* contenant le nombre d'échangeur gérer
 * \return Renvoi 0 si le programme s'est déroulé normalement
 */
int main(int argc, char *argv[]) {

  int nbEchangeurs, nbVehicules, i;
  char arguments[3][2];

  menuPrincipal(&nbEchangeurs,&nbVehicules);

  // Pour une execution, passage d'argument via char* uniquement
  sprintf(arguments[1],"%d",nbVehicules);   // Converti le nombre de vehicules en char*
  sprintf(arguments[2],"%d",nbEchangeurs);  // Converti le nombre d'échangeur en char*

  // Execution des échangeurs
  for (i = 1; i <= nbEchangeurs; i++) {
    if (fork() == 0){
      sprintf(arguments[0],"%d",i);   // Converti le numéro d'échangeur en char*
      printf("\nExecution de l'échangeur n°%d",i);
      execl("./echangeur/echangeur","echangeur",arguments[0],arguments[1],NULL);
      perror("execl()");  // Affiche une eventuelle erreur
    }
    sleep(1); // Temps de repos pour fluidifier l'affichage
  }

  // Execution du serveur
  if (fork() == 0) {
      printf("\nExecution du serveur");
      execl("./serveur/serveur","serveur",arguments[2],NULL);
      perror("execl()");
  }

  sleep(1); // Temps de repos pour fluidifier l'affichage

  
}
