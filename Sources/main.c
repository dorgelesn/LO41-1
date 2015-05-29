/**
* \file main.c
* \brief Simulation de carrefours routiers intelligents
* \author Florian Lacour & Michaël Ayeng
* \version 0.1
* \date 13 Mai 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "echangeur.h"
#include "menu.h"
#include "linkedList.h"
#include "structures.h"
#include "serveur.h"

/**
* \fn void traitantSignt()
* \brief Fonction de traitement des interruptions
* Permet la suppresion des mutex
*/
void traitantSignt(){
  printf("\n interruption avec suppresion des mutex");
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&attendre);
  exit(1);
}


/**
* \fn int main(int argc, char *argv[])
* \brief Programme principal de la simulation
*
* \param argc Valeur représentant le nombre d'argument passés lors de l'appel du binaire exécutable
* \param argv Tableau de char* contenant le nombre d'échangeur gérer
* \return Renvoi 0 si le programme s'est déroulé normalement
*/
int main(int argc,char *argv[]) {

  // Initialisation des variables
  int nbEchangeurs = 4, nbVehicules = 0, i,rc;
  // Initialisation des echangeurs
  echangeur ech[nbEchangeurs];
  pthread_t threads[nbEchangeurs];
  // Initialisation du serveur
  serveur a;
  a.NbVoiture = 0;
  a.NbEchangeur = nbEchangeurs;
  a.liste = initialisation();
  // Initialisation des mutex
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&attendre,NULL);
  // Linkage des signals
  signal(SIGINT,traitantSignt);

  /*
          Schema des connexions
            0        0
           ||       ||
    0== |  1  |== | 4 | == 0
           ||       ||
    0 == | 2  | == | 3 | == 0
           ||        ||
           0         0
  */
    // Creation des echangeurs
    printf("\n-----------------------");
    printf("\nCreation des echangeurs");
    creationEchangeur(&ech[0],1,4,0,0,2);
    creationEchangeur(&ech[1],2,3,0,1,0);
    creationEchangeur(&ech[2],3,0,2,4,0);
    creationEchangeur(&ech[3],4,0,1,0,3);

    // Creation du thread du serveur
    printf("\n-----------------------");
    rc = pthread_create(&threads[0],NULL,traitantThreadServeur,(void*) &a);
    if(rc){
      printf("\n(!)erreur creation thread serveur ");
    } else {
      printf("\nCreation du thread du serveur");
    }

    // Creation des threads des echangeurs
    for(i = 1; i < nbEchangeurs+1; i++){
      rc = pthread_create(&threads[i],NULL,traitantThreadEchangeur,(void*) &ech[i-1]);
      if(rc){
        printf("\n(!)erreur creation thread echangeur");
      } else {
        printf("\n-----------------------");
        printf("\nCreation du thread de l'echangeur %d",i);
      }
      sleep(1);
  }


  // Attente de fin des threads
  printf("\n\n");
  for(i = 0; i <= nbEchangeurs+1; i++){
    pthread_join(threads[i],NULL);
    printf("\n*Fin du thread %d",i);
  }

  // Destruction des mutex
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&attendre);
}
