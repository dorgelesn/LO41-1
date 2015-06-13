/**
* \file serveur.c
* \brief Serveur de gestion du trafic
* \author Florian Lacour & Michaël Ayeng
* \version 0.2
* \date 13 Mai 2015
*/

#include "linkedList.h"
#include "structures.h"
#include "serveur.h"

/**
* \fn void* traitantThreadServeur(void* param)
* \brief Fonction traitante du thread serveur
*
* \param param Paramètre du thread contenant la structure du serveur
*/
void* traitantThreadServeur(void* param){
  serveur* serv = (serveur*) param;
  int i ;
  llist liste;

  while(true){


    // Attente du signal d'un véhicule prêt
    sem_wait(sem);
    usleep(50);
    liste = NULL;
    // Recherche du premier véhicule prêt dans la liste et en fonction de sa prioriter
    // PEUT ETRE AMELIORER AVEC rechercherPlaceByReadyPriority =>beug il prend une seul voiture et fait tous sont trajet
  //  liste = element_i(serv->liste,rechercherPlaceByReady(serv->liste,true));
  liste = element_i(serv->liste,rechercherPlaceByReadyPriority(serv->liste,true));
    usleep(1000);
    if(liste!=NULL){


    // Verification de la disponibilité de l'échangeu
 if(ech[liste->val->idEchangeur-1].dispo ==0){
    liste->val->prioriter+=1;

  //  printf("\n voiture %d",  liste->val->idVehicule);
    sem_post(sem);
    usleep(100000);

  }else{

    // Envoi l'autorisation à l'échangeur
    liste->val->ready=0;//0=> false ( la voiture n'est plus en demand)
    ech[liste->val->idEchangeur-1].dispo=0; // l'echangeur n'est plus disppo
    ech[liste->val->idEchangeur-1].idVehicule = liste->val->idVehicule; // Assigne le véhicule à l'échangeur
    liste->val->prioriter=1;// le vehicule redevient avec une prioriter "normal"
    reinitialiserPrioEchan(serv->liste,liste->val->idEchangeur-1);

    sem_post(semEchangeurLever[liste->val->idEchangeur-1]);
    usleep(400);
        }
  }

}
}


/**
* \fn void ajouterVehicule(serveur* serv,int ech,int dep,int arr)
* \brief Permet de générer un véhicule dans la simulation
*
* \param serv Pointeur sur le serveur gérant le véhicule
* \param ech Numéro d'identification de l'échangeur du véhicule
* \param dep Départ du véhicule
* \param arr Arrivée du véhicule
*/
vehicule* ajouterVehicule(serveur* serv,int id, int ech,int dep,int arr){
  // Initialisation du véhicule
  vehicule* v = malloc(sizeof(vehicule));
  // Configuration du véhicule
  // le resultat est stocker dans V
  creationVehicule(v,id,ech,dep,arr);
  // Ajout du véhicule en tête de la liste de traitement du serveur
  (*serv).liste = ajouterEnTeteListe((*serv).liste,v);
  return v;
}

/**
* \fn void afficherServeur(serveur* s)
* \brief Fonction permettant l'affichage d'informations concernant le serveur
*
* \param c Structure du serveur
*
*/
void afficherServeur(serveur* s){
  printf("\n-----------------------");
  printf("\nInformations serveur");
  printf("\n-----------------------");
  printf("\n\tNombre de vehicule: %d\n\tNombre d'echangeurs: %d",s->NbVoiture,s->NbEchangeur);
}
