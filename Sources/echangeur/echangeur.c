/**
 * \file echangeur.c
 * \brief Programme de simulation des échangeurs
 * \author Florian Lacour & Michaël Ayeng
 * \version 0.1
 * \date 13 Mai 2015
 */

 #include <stdio.h>
 #include <stdlib.h>

 typedef struct voiture voiture;
 struct voiture {
   int depart;
   int arriver;
 };
 typedef struct {
   long type;
   voiture V;
   pid_t numPid;
 } message;

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
   int tailleMessage= sizeof(message)-sizeof(long);
   int idEchangeur,nbVehicules;
   int msgid = atoi(argv[1]);
   printf("\n reception  de la fille de message %d",msgid);
   idEchangeur = atoi(argv[2]);
   nbVehicules = atoi(argv[3]);

   printf("\nEchangeur n°%d crée",idEchangeur);
   printf("\nNombre de véhicule à gérer: %d",nbVehicules);

   printf("\n Echangeur n°%d en attente de vehicule\n",idEchangeur);
   message M;
   msgrcv(msgid,&M,tailleMessage,idEchangeur,0);
   printf("requete recut, de %d a %d a",M.V.depart, M.V.arriver);
 }
