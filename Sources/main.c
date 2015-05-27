/**
* \file main.c
* \brief Simulation de carrefours routiers intelligents
* \author Florian Lacour & Michaël Ayeng
* \version 0.1
* \date 13 Mai 2015
*/

#include <stdio.h>
#include <stdlib.h>

#include "echangeur.h"
#include "menu.h"


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
* \fn int main(int argc, char *argv[])
* \brief Programme principal de la simulation
*
*
* \param argc Valeur représentant le nombre d'argument passés lors de l'appel du binaire exécutable
* \param argv Tableau de char* contenant le nombre d'échangeur gérer
* \return Renvoi 0 si le programme s'est déroulé normalement
*/
int main(int argc,char *argv[]) {

  int nbEchangeurs=4, nbVehicules=0, i,rc;
  echangeur ech[nbEchangeurs];
  pthread_t threads[nbEchangeurs];
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

for(i=0;i<nbEchangeurs;i++){

  rc=  pthread_create(&threads[i],NULL,traitantThread,(void*) &ech[i]);
  if(rc){
  printf("erreur creation thread");
  }
  sleep(1);
}
printf("\n \n");
}
