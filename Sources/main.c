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
 * \param argv Tableau de caractère contenant les arguments de la ligne de commande
 * \return Renvoi 0 si le programme s'est déroulé normalement
 */
int main(int argc, char argv[]) {

  int nbEchangeurs, nbVehicules, i;

  menuPrincipal(&nbEchangeurs,&nbVehicules);

  // Execution des échangeurs
  for (i = 1; i <= nbEchangeurs; i++) {
    if (fork() == 0){
      execlp("./echangeur/echangeur","echangeur",i,nbVehicules,NULL);
    }
  }

  // Execution du serveur
  if (fork() == 0) {
      execlp("./serveur/serveur","serveur",nbEchangeurs,NULL);
  }
}
