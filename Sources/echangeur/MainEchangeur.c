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
int msgid;

/**
* \fn traitantThread(void* param)
* \brief Fonction gerant un thread "Echangeur"
*
* \param void* seras convertie en echangeur
*
*/
void* traitantThread(void* param){
    echangeur* ech= (echangeur*) param;
    // Utilisation Mutex ????
    afficherEchangeur(ech);
    fflush(stdout);
    pthread_exit(NULL);
}
/**
* \fn traitantFile(void*param)
* \brief Fonction gerant un thread qui verifie la présence de msh dans la file
*
* \param void* seras convertie en message
*
*/
void* traitantFile(void*param){
  message* M=(message*)param;
  msgrcv(msgid,&(*M),sizeof(message) - sizeof(long),3,0);
  printf("\n Requête reçu, de %d a %d ",M->vehicule.depart, M->vehicule.arrivee);

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

  int  nbVehicules,nbEchangeur,i,rc;
  int tailleMessage = sizeof(message)-sizeof(long);
  message M;
  echangeur ech[4];
  // Réception des paramètres de l'échangeur
  msgid = atoi(argv[1]);

  nbVehicules = atoi(argv[3]);
  nbEchangeur =atoi(argv[4]);
  pthread_t threads[nbEchangeur];
  printf("\n l'echangeur a recus la file de message : %d",msgid);
  /*
          Schema des connection
            0        0
           ||       ||
    0== |  1  |== | 4 | == 0
          ||       ||
  0 == | 2  | == | 3 | == 0
        ||        ||
        0         0
  */
  creationEchangeur(&ech[0],1,4,0,0,2);
  creationEchangeur(&ech[1],2,3,0,1,0);
  creationEchangeur(&ech[2],3,0,2,4,0);
  creationEchangeur(&ech[3],4,0,1,0,3);

for(i=0;i<nbEchangeur;i++){

  rc=  pthread_create(&threads[i],NULL,traitantThread,(void*) &ech[i]);
  if(rc){
  printf("erreur creation thread");
}
}
sleep(5);
rc=  pthread_create(&threads[++i],NULL,traitantFile,(void*) &ech[i]);
if(rc){
printf("erreur creation thread");
}


  sleep(1); // Temps de repos pour fluidifier l'affichage

}
