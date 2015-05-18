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
#include "messagerie.h"

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

  int msgid, idEchangeur, nbVehicules;
  int tailleMessage = sizeof(message)-sizeof(long);
  message M;

  // Réception des paramètres de l'échangeur
  msgid = atoi(argv[1]);
  idEchangeur = atoi(argv[2]);
  nbVehicules = atoi(argv[3]);

  printf("\nEchangeur n°%d crée",idEchangeur);
  printf("\nReception de la file de message %d",msgid);
  printf("\nNombre de véhicule à gérer: %d",nbVehicules);

  sleep(1); // Temps de repos pour fluidifier l'affichage

  printf("\nEchangeur n°%d en attente de véhicule\n",idEchangeur);
  msgrcv(msgid,&M,tailleMessage,idEchangeur,0);
  printf("Requête reçu, de %d a %d a",M.vehicule.départ, M.vehicule.arrivée);
}
