/**
 * \file echangeur.c
 * \brief Programme de simulation des échangeurs
 * \author Florian Lacour & Michaël Ayeng
 * \version 0.1
 * \date 13 Mai 2015
 */

 #include <stdio.h>
 #include <stdlib.h>

 #include "echangeur.h"

 /**
  * \fn int main(int argc, char *argv[])
  * \brief Programme simulant un échangeur
  *
  *
  * \param argc Valeur représentant le nombre d'argument passés lors de l'appel du binaire exécutable
  * \param argv Tableau de char* contenant le numéro de l'échangeur, ainsi que le nombre de véhicules à gérer
  * \return Renvoi 0 si le programme s'est déroulé normalement
  */
 void main(int argc, char *argv[]) {

   int idEchangeur,nbVehicules;

   idEchangeur = atoi(argv[1]);
   nbVehicules = atoi(argv[2]);

   printf("\nEchangeur n°%d crée",idEchangeur);
   printf("\nNombre de véhicule à gérer: %d",nbVehicules);
 }
