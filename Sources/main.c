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
#include "linkedList.h"
#include "structures.h"
#include "serveur.h"

void* traitantThreadServeur(void* param);
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
  serveur a;
  a.NbVoiture=0;
  a.NbEchangeur=nbEchangeurs;
  a.liste=initialisation();
  rc=  pthread_create(&threads[0],NULL,traitantThreadServeur,(void*) &a);
  if(rc){
  printf("erreur creation thread serveur ");
  }
for(i=1;i<nbEchangeurs+1;i++){

  rc=  pthread_create(&threads[i],NULL,traitantThreadEchangeur,(void*) &ech[i-1]);
  if(rc){
  printf("erreur creation thread");
  }
  sleep(1);
}


// Attente de fin des thread

pthread_join(threads[0],NULL);
for(i=1;i<nbEchangeurs+1;i++){
    pthread_join(threads[i],NULL);
}





printf("\n \n");
}
