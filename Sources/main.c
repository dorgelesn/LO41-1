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
#include "voiture.h"

/**
* \fn void traitantSignt()
* \brief Fonction de traitement des interruptions
* Permet la suppresion des mutex
*/
void traitantSignt(){
//  printf("\n interruption avec suppresion des mutex");
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&attendre);
  int i;
  for(i=0;i<maxiEchangeur;i++){
    pthread_cond_destroy(&BarierreEchangeur[i]);
  }

  pthread_cond_destroy(&partir);
  serv.liste=effacerListe(serv.liste);
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
  int nbEchangeurs = 4, nbVehicules = 10, i,rc;
  // Initialisation des echangeurs


  // Initialisation du serveur

  serv.NbVoiture = nbVehicules;
  serv.NbEchangeur = nbEchangeurs;
  serv.liste = initialisation();
  // Initialisation des mutex
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&attendre,NULL);
  for(i=0;i<maxiEchangeur;i++){
    pthread_cond_init(&BarierreEchangeur[i],NULL);
  }

  pthread_cond_init(&partir, NULL);


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
    creationEchangeur(&ech[0],1,4,0,0,2);
    creationEchangeur(&ech[1],2,3,0,1,0);
    creationEchangeur(&ech[2],3,0,2,4,0);
    creationEchangeur(&ech[3],4,0,1,0,3);
    // Creation du thread du serveur
    rc = pthread_create(&threads[0],NULL,traitantThreadServeurAjout,(void*) &serv);
    if(rc){
      printf("\n(!)erreur creation thread serveur ");
    }
rc = pthread_create(&threads[1],NULL,traitantThreadGenerationVoiture,NULL );
if(rc)
  printf("\n(!)erreur creation threadt Generation echangeur");

    // Creation des threads des echangeurs
    for(i = 0; i < nbEchangeurs; i++){
      rc = pthread_create(&threads[i+2],NULL,traitantThreadEchangeur,(void*) i);
            if(rc){
                printf("\n(!)erreur creation thread echangeur");
                  }
          }

// Lancement de Thread
sleep(1);
  pthread_cond_signal (&partir);

  // Attente de fin des threads
  //printf("\n\n attente fin de thread");
  for(i = 1; i <2; i++){
    pthread_join(threads[i],NULL);
   printf("\n*Fin du thread %d",i);

  }
  printf("\n\n");
usleep(1000);
  // Destruction des mutex

  printf("\n\n");
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&attendre);
  for(i=0;i<maxiEchangeur;i++){
    pthread_cond_destroy(&BarierreEchangeur[i]);
  }
  pthread_cond_destroy(&partir);


  serv.liste=effacerListe(serv.liste);
}
