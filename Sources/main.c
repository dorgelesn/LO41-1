/**
* \file main.c
* \brief Simulation de carrefours routiers intelligents
* \author Florian Lacour & Michaël Ayeng
* \version 0.1
* \date 13 Mai 2015
*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "echangeur.h"
#include "menu.h"
#include "linkedList.h"
#include "structures.h"
#include "serveur.h"
#include "voiture.h"
#include <stdint.h>
#include <string.h>
/**
* \fn void traitantSignt()
* \brief Fonction de traitement des interruptions
* Permet la suppresion des mutex
*/

void traitantSignt(){
  int i;
  char mot[30];
      for(i=0;i<maxiEchangeur;i++){
        sprintf(mot,"/semEchangeur%d",i);
        sem_unlink(mot);
      }
  serv.liste = effacerListe(serv.liste);
  printf("\n");
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
  char mot[30];
  // Initialisation des variables
  int nbEchangeurs = 4, nbVehicules , i,rc;
  nbVehicules=atoi(argv[1]);
  // Initialisation du serveur
  serv.NbVoiture = nbVehicules;
  serv.NbEchangeur = nbEchangeurs;
//  serv.liste = initialisation();
  // Initialisation des mutex


  for(i=0;i<maxiEchangeur;i++){
    sprintf(mot,"/semEchangeur%d",i);
    semEchangeurLever[i]=sem_open(mot, O_RDWR);
    if (semEchangeurLever[i] == SEM_FAILED) {
      if (errno != ENOENT) {
        perror("probléme de creation semaphore echangeur");
        exit(EXIT_FAILURE);
      }
      semEchangeurLever[i] = sem_open(mot, O_RDWR | O_CREAT, 0666, 0);
      if (semEchangeurLever[i] == SEM_FAILED) {
        perror("probléme de creation semaphore echangeur");
        exit(EXIT_FAILURE);
      }
    }
  }





    for(i=0;i<maxiEchangeur;i++){
      sprintf(mot,"/semEchangeurDescendre%d",i);
      semEchangeurDescendre[i]=sem_open(mot, O_RDWR);
      if (semEchangeurDescendre[i] == SEM_FAILED) {
        if (errno != ENOENT) {
          perror("probléme de creation semaphore echangeur Descente");
          exit(EXIT_FAILURE);
        }
        semEchangeurDescendre[i] = sem_open(mot, O_RDWR | O_CREAT, 0666, 0);
        if (semEchangeurDescendre[i] == SEM_FAILED) {
          perror("probléme de creation semaphore echangeur Descente");
          exit(EXIT_FAILURE);
        }
      }
    }




        for(i=0;i<maxiVoiture;i++){
          sprintf(mot,"/semEchangeurVoiture%d",i);
          semDepartVehicule[i]=sem_open(mot, O_RDWR);
          if (semDepartVehicule[i] == SEM_FAILED) {
            if (errno != ENOENT) {
              perror("probléme de creation semaphore voiture");
              exit(EXIT_FAILURE);
            }
            semDepartVehicule[i] = sem_open(mot, O_RDWR | O_CREAT, 0666, 0);
            if (semDepartVehicule[i] == SEM_FAILED) {
              perror("probléme de creation semaphore voiture");
              exit(EXIT_FAILURE);
            }
          }
        }





  sem = sem_open("/pthread", O_RDWR);
  	if (sem == SEM_FAILED) {
  		if (errno != ENOENT) {
        perror("probléme de creation semaphore serveur");
  			exit(EXIT_FAILURE);
  		}
  		sem = sem_open("/pthread", O_RDWR | O_CREAT, 0666, 0);
  		if (sem == SEM_FAILED) {
        perror("probléme de creation semaphore erreur");
  			exit(EXIT_FAILURE);
  		}
  	}

  // Linkage des signaux
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
  creationEchangeur(&ech[0],1,4,0,0,2);
  creationEchangeur(&ech[1],2,3,0,1,0);
  creationEchangeur(&ech[2],3,0,2,4,0);
  creationEchangeur(&ech[3],4,0,1,0,3);


  // Creation du thread du serveur
  rc = pthread_create(&threadServeur,NULL,traitantThreadServeur,(void*) &serv);
  if(rc)
  printf("\n(!)erreur creation thread serveur ");

  // Creation du thread generateur de vehicule
  rc = pthread_create(&threadGenerateur,NULL,traitantThreadGenerationVoiture,(void*)(intptr_t) nbVehicules);
  if(rc)
  printf("\n(!)erreur creation thread Generation echangeur");


  // Creation des threads des echangeurs
  for(i = 0; i < nbEchangeurs; i++){
    rc = pthread_create(&threadsEchangeur[i],NULL,traitantThreadEchangeur,(void*) &ech[i]);
    if(rc)
    printf("\n(!)erreur creation thread echangeur");
  }

  sleep(1);




  // Attente de fin du thread générateur de véhicule
  pthread_join(threadGenerateur,NULL);

  // Attente de fin des threads véhicule
  for (i = 0; i < nbVehicules; i++){
    pthread_join(threadsVehicule[i],NULL);
    printf("\n*Fin du thread du vehicule n°%d",i+1);
  }

  serv.liste = effacerListe(serv.liste);
  sem_unlink("/pthread");

    for(i=0;i<maxiEchangeur;i++){
      sprintf(mot,"/semEchangeur%d",i);
      sem_unlink(mot);
    }
    for(i=0;i<maxiVoiture;i++){
      sprintf(mot,"/semEchangeurVoiture%d",i);
      sem_unlink(mot);

    }
    printf("\n\n");
    exit(0);
}
