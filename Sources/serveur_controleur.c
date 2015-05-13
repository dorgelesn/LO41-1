/**
 * \file serveur_controleur.c
 * \brief Programme de calcul des flux de trafic
 * \author Florian Lacour & Michaël Ayeng
 * \version 0.1
 * \date 13 Mai 2015
 */

#include <stdio.h>
#include <stdlib.h>

#include "serveur_controleur.h"
#include "echangeur.h"


/**
 * \fn int main(int argc, char *argv[])
 * \brief Fonction de base du serveur_controleur
 *
 * \details Le serveur controleur est le processus père de la simulation.
 * Il fork les processus fils représentant les échangeurs.
 *
 * \param argc Valeur représentant le nombre d'argument passés lors de l'appel du binaire exécutable
 * \param argv Tableau de caractère contenant les arguments de la ligne de commande
 * \return Renvoi 0 si le programme s'est déroulé normalement
 */
int main(int argc, char argv[]) {

  int nbEchangeurs, nbVehicules, i;

  nbEchangeurs = argv[1];
  nbVehicules = argv[2];

  printf("\nServeur-controleur crée");

  for (i = 1; i <= nbEchangeurs; i++) {
    // Chaque processus fils lance sa fonction echangeur
    if (fork() == 0){
      echangeur(i, nbVehicules);
    }
  }

}
