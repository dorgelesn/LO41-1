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
/**
* \fn void traitantSignt()
* \brief Fonction de traitement des interruptions
* Permet la suppresion des mutex
*/
void traitantSignt(){
  int i;

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&attendre);
  for(i = 0;i < maxiEchangeur; i++){
    pthread_cond_destroy(&BarriereEchangeur[i]);
  }
  for(i = 0; i < maxiVoiture; i++){
    pthread_cond_destroy(&departVehicule[i]);
  }
  pthread_cond_destroy(&partir);
  serv.liste = effacerListe(serv.liste);
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
  int nbEchangeurs = 4, nbVehicules = 4, i,rc;
  // Initialisation du serveur
  serv.NbVoiture = nbVehicules;
  serv.NbEchangeur = nbEchangeurs;
  serv.liste = initialisation();
  // Initialisation des mutex
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&attendre,NULL);
  pthread_cond_init(&partir, NULL);
  pthread_cond_init(&voitureReady, NULL);
  for(i = 0; i < maxiEchangeur; i++){
    pthread_cond_init(&BarriereEchangeur[i],NULL);
  }
  for(i = 0; i < maxiVoiture; i++){
    pthread_cond_init(&departVehicule[i],NULL);
  }



  sem = sem_open("\pthread", O_RDWR);
  	if (sem == SEM_FAILED) {
  		if (errno != ENOENT) {
  			perror(argv[1]);
  			exit(EXIT_FAILURE);
  		}
  		sem = sem_open("\pthread", O_RDWR | O_CREAT, 0666, 0);
  		if (sem == SEM_FAILED) {
  			perror(argv[1]);
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

  // Lancement du thread de génération de véhicule
  pthread_cond_signal (&partir);


  // Attente de fin du thread générateur de véhicule
  pthread_join(threadGenerateur,NULL);

  // Attente de fin des threads véhicule
  for (i = 0; i < nbVehicules; i++){
    pthread_join(threadsVehicule[i],NULL);
    printf("\n*Fin du thread du vehicule n°%d",i+1);
  }


  printf("\n\n");

  /* Nettoyage mémoire */

  // Destruction des mutex
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&attendre);
  for(i = 0; i < maxiEchangeur; i++){
    pthread_cond_destroy(&BarriereEchangeur[i]);
  }
  for(i = 0; i < maxiVoiture; i++){
    pthread_cond_destroy(&departVehicule[i]);
  }
  pthread_cond_destroy(&partir);
  // Vidage de la liste chainée
  serv.liste = effacerListe(serv.liste);
  sem_unlink("\pthread");
}
