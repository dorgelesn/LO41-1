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
* \fn void supression()
* \brief Fonction de suppresion des semaphore et de la liste cjaine
*
*/
void supression(){
  char mot[30];
  int i;
  serv.liste = effacerListe(serv.liste);
  sem_unlink("/pthread");

    for(i=0;i<maxiEchangeur;i++){
      sprintf(mot,"/semEchangeur%d",i);
      sem_unlink(mot);
    }

    for(i=0;i<maxiEchangeur;i++){
      sprintf(mot,"/semEchangeurDescendre%d",i);
      sem_unlink(mot);
    }
    for(i=0;i<maxiVoiture;i++){
      sprintf(mot,"/semEchangeurVoiture%d",i);
      sem_unlink(mot);

    }
}

/**
* \fn void traitantSignt()
* \brief Fonction de traitement du ctrl+c
* Permet la suppresion des semaphore
*/
void traitantSignt(){
  supression();
  printf("\n");
  exit(1);
}

/**
* \fn void initialisationMain()
* \brief Fonction permettant d'initialiser les semaphore
* Permet l'initialisation des semaphore ainsi que la prise en compte du signal ctrl+C
*/
void initialisationMain(){
  // Initialisation du serveur
  char mot[30];
  int i;
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
int nbEchangeurs = 4, nbVehicules , i,rc;
if (argc != 2) {
	fprintf(stderr, "usage: %s nombre de voiture (<%d)\n", argv[0],maxiVoiture);
	exit(EXIT_FAILURE);
}
nbVehicules=atoi(argv[1]);

if(nbVehicules > maxiVoiture){
  fprintf(stderr, "nombre de voiture suppereieur a la limite ( %d )\n",maxiVoiture );
  exit(EXIT_FAILURE);
}
  serv.NbVoiture = nbVehicules;
  serv.NbEchangeur = nbEchangeurs;
  initialisationMain();

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
// atribut des thread deatacher
pthread_attr_t thread_attr;

  if (pthread_attr_init (&thread_attr) != 0) {
    fprintf (stderr, "pthread_attr_init error");
    exit (1);
  }
  if (pthread_attr_setdetachstate (&thread_attr, PTHREAD_CREATE_DETACHED) != 0) {
    fprintf (stderr, "pthread_attr_setdetachstate error");

    exit (1);
  }
  // Creation du thread du serveur
  rc = pthread_create(&threadServeur, &thread_attr,traitantThreadServeur,(void*) &serv);
  if(rc)
  printf("\n(!)erreur creation thread serveur ");

  // Creation du thread generateur de vehicule
  rc = pthread_create(&threadGenerateur,NULL,traitantThreadGenerationVoiture,(void*)(intptr_t) nbVehicules);
  if(rc)
  printf("\n(!)erreur creation thread Generation Generateur");


  // Creation des threads des echangeurs
  for(i = 0; i < nbEchangeurs; i++){
    rc = pthread_create(&threadsEchangeur[i], &thread_attr,traitantThreadEchangeur,(void*) &ech[i]);
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
  supression();
  printf("\n\n");
  exit(0);
}
