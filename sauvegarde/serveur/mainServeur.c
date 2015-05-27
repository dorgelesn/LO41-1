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

int msgid;
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

  // Réception du paramètre de l'échangeur
  nbEchangeurs = atoi(argv[1]);
  msgid=atoi(argv[2]);
  printf("le serveur a recus le msgid : %d",msgid);
  printf("\nServeur crée");
  message M;
  printf("\nattente de message");
  msgrcv(msgid,&M,sizeof(message) - sizeof(long),1,0);
  printf("\nServeur: Requête reçu, de %d a %d",M.vehicule.depart, M.vehicule.arrivee);

}
