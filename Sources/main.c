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
* \brief Fonction de suppresion des sémaphores et de la liste chainée
*
*/
void supression(){
  char mot[30];
  int i;

  // Suppression de la liste du serveur
  serv.liste = effacerListe(serv.liste);

  // Suppression du sémaphore du serveur
  sem_unlink("/pthread");

  // Suppression des sémaphores d'ouverture des échangeurs
  for(i = 0; i < maxiEchangeur; i++){
    sprintf(mot,"/semEchangeur%d",i);
    sem_unlink(mot);
  }

  // Suppression des sémaphores de fermeture des échangeurs
  for(i = 0; i < maxiEchangeur; i++){
    sprintf(mot,"/semEchangeurDescendre%d",i);
    sem_unlink(mot);
  }

  // Suppression des sémaphores des voitures
  for(i = 0; i < maxiVoiture; i++){
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
* \brief Fonction permettant d'initialiser les sémaphores
* Permet l'initialisation des sémaphores ainsi que la prise en compte du signal ctrl+C
*/
void initialisationMain(){
  // Initialisation du serveur
  char mot[30];
  int i;

  // Création des sémaphores d'ouverture des échangeurs
  for(i = 0; i < maxiEchangeur; i++){
    sprintf(mot,"/semEchangeur%d",i);
    semEchangeurLever[i] = sem_open(mot, O_RDWR);
    if (semEchangeurLever[i] == SEM_FAILED) {
      if (errno != ENOENT) {
        perror("(!) Problème de création sémaphore ouverture echangeur");
        exit(EXIT_FAILURE);
      }
      semEchangeurLever[i] = sem_open(mot, O_RDWR | O_CREAT, 0666, 0);
      if (semEchangeurLever[i] == SEM_FAILED) {
        perror("(!) Problème de création sémaphore ouverture echangeur");
        exit(EXIT_FAILURE);
      }
    }
  }

  // Création des sémaphores de fermeture des échangeurs
  for(i = 0; i < maxiEchangeur; i++){
    sprintf(mot,"/semEchangeurDescendre%d",i);
    semEchangeurDescendre[i] = sem_open(mot, O_RDWR);
    if (semEchangeurDescendre[i] == SEM_FAILED) {
      if (errno != ENOENT) {
        perror("(!) Problème de création sémaphore fermeture echangeur");
        exit(EXIT_FAILURE);
      }
      semEchangeurDescendre[i] = sem_open(mot, O_RDWR | O_CREAT, 0666, 0);
      if (semEchangeurDescendre[i] == SEM_FAILED) {
        perror("(!) Problème de création sémaphore fermeture echangeur");
        exit(EXIT_FAILURE);
      }
    }
  }

  // Création des sémaphores des voitures
  for(i = 0; i < maxiVoiture; i++){
    sprintf(mot,"/semEchangeurVoiture%d",i);
    semDepartVehicule[i]=sem_open(mot, O_RDWR);
    if (semDepartVehicule[i] == SEM_FAILED) {
      if (errno != ENOENT) {
        perror("(!) Problème de création sémaphore voiture");
        exit(EXIT_FAILURE);
      }
      semDepartVehicule[i] = sem_open(mot, O_RDWR | O_CREAT, 0666, 0);
      if (semDepartVehicule[i] == SEM_FAILED) {
        perror("(!) Problème de création sémaphore voiture");
        exit(EXIT_FAILURE);
      }
    }
  }

  // Création du sémaphore du serveur
  sem = sem_open("/pthread", O_RDWR);
  if (sem == SEM_FAILED) {
    if (errno != ENOENT) {
      perror("(!) Problème de création sémaphore serveur");
      exit(EXIT_FAILURE);
    }
    sem = sem_open("/pthread", O_RDWR | O_CREAT, 0666, 0);
    if (sem == SEM_FAILED) {
      perror("(!) Problème de création sémaphore serveur");
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
* \param argv Tableau de char* contenant le nombre de véhicule à simuler
* \return Renvoi 0 si le programme s'est déroulé normalement
*/
int main(int argc,char *argv[]) {

  // Initialisation des variables
  int nbEchangeurs = 4, nbVehicules , i,rc;

  // Message d'erreur si trop d'argument au lancement du programme
  if (argc != 2) {
    fprintf(stderr, "Usage: %s\nUn paramètre représentant le nombre de véhicule à simuler (<%d)\n", argv[0],maxiVoiture);
    exit(EXIT_FAILURE);
  }

  // Obtention du nombre de véhicules à simuler
  nbVehicules = atoi(argv[1]);

  // Message d'erreur si nombre de véhicules à simuler supérieur à la limite
  if(nbVehicules > maxiVoiture){
    fprintf(stderr, "Nombre de voitures supérieur à la limite ( %d )\n",maxiVoiture );
    exit(EXIT_FAILURE);
  }

  // Paramètrage du serveur
  serv.NbVoiture = nbVehicules;
  serv.NbEchangeur = nbEchangeurs;

  // Initialisation des sémaphores et des signaux
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

  // Création du thread du serveur
  rc = pthread_create(&threadServeur, &thread_attr,traitantThreadServeur,(void*) &serv);
  if(rc)
  printf("\n(!)erreur creation thread serveur ");

  // Création du thread générateur de vehicules
  rc = pthread_create(&threadGenerateur,NULL,traitantThreadGenerationVoiture,(void*)(intptr_t) nbVehicules);
  if(rc)
  printf("\n(!)erreur creation thread Generation Generateur");

  // Création des threads des échangeurs
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

  // Suppression des sémaphores et de la liste chainée
  supression();

  printf("\n\n");

  exit(0);
}
