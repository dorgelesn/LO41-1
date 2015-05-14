/**
 * \file serveur.c
 * \brief Programme de calcul des flux de trafic
 * \author Florian Lacour & Michaël Ayeng
 * \version 0.1
 * \date 13 Mai 2015
 */

#include <stdio.h>
#include <stdlib.h>

#include "serveur.h"


/**
 * \fn int main(int argc, char *argv[])
 * \brief Programme simulant le serveur
 *
 * \details Le serveur effectue les calculs et gère le trafic
 *
 * \param argc Valeur représentant le nombre d'argument passés lors de l'appel du binaire exécutable
 * \param argv Tableau de char* contenant les arguments de la ligne de commande
 * \return Renvoi 0 si le programme s'est déroulé normalement
 */
int main(int argc, char *argv[]) {

  int nbEchangeurs;

  nbEchangeurs = atoi(argv[1]);

  printf("\nServeur crée");
  printf("\nNombre d'échangeurs gérés par le serveur: %d",nbEchangeurs);
}
