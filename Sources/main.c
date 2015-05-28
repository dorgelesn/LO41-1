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

  rc=  pthread_create(&threads[i],NULL,traitantThreadEchangeur,(void*) &ech[i]);
  if(rc){
  printf("erreur creation thread");
  }
  sleep(1);
}

// Attente de fin des thread
for(i=0;i<nbEchangeurs;i++){
    pthread_join(threads[i],NULL);
}
llist Liste=initialisation();
llist element;
vehicule v;
creationVehicule(&v,1,0,24);
//afficherVehicule(&v);
Liste=ajouterEnTete(Liste,&v);
element=element_i(Liste,0);
afficherVehicule(element->val
);



printf("\n \n");
}
