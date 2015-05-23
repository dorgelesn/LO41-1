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


void* traitantThread(void* param){
    int i= (int) param;
    printf("creation du thread %d, de TID %ld",i,(long)pthread_self());
    fflush(stdout);
    pthread_exit(NULL);
}


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

  int msgid, nbVehicules,nbEchangeur,i,rc;
  int tailleMessage = sizeof(message)-sizeof(long);
  message M;

  // Réception des paramètres de l'échangeur
  msgid = atoi(argv[1]);

  nbVehicules = atoi(argv[3]);
  nbEchangeur =atoi(argv[4]);
  pthread_t threads[nbEchangeur];
  printf("\n Nb ecgangeur a creer %d ",nbEchangeur);
  printf("\nReception de la file de message %d",msgid);
for(i=0;i<nbEchangeur;i++){
printf("\ncreation du %d thread",i);
rc=  pthread_create(&threads[i],NULL,traitantThread,(void*) i);
if(rc){
  printf("erreur creation thread");
}
}

  sleep(1); // Temps de repos pour fluidifier l'affichage

  msgrcv(msgid,&M,tailleMessage,10,0);
  printf("Requête reçu, de %d a %d a",M.vehicule.depart, M.vehicule.arrivee);
}
