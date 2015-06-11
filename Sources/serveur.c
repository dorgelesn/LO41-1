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

  printf("\n envoit le signal");
  while(true){


    // Attente du signal d'un véhicule prêt

    pthread_mutex_unlock(&mutex);
    sem_wait(sem);
    pthread_mutex_lock(&mutex);
    liste = NULL;
    // Recherche du premier véhicule prêt dans la liste
    liste = element_i(serv->liste,rechercherPlaceByReady(serv->liste,true));
    liste->val->ready=false;
    // Verification de la disponibilité de l'échangeur
    while(ech[liste->val->idEchangeur-1].dispo == false){
      usleep(100);
      printf("\n \n\n attente");
    }
    // Envoi l'autorisation à l'échangeur
    ech[liste->val->idEchangeur-1].dispo == false;
    ech[liste->val->idEchangeur-1].idVehicule = liste->val->idVehicule; // Assigne le véhicule à l'échangeur
    printf("\n\n[Serveur] : Autorisation accordée à l'échangeur n°%d pour la traversée du véhicule n°%d [@]",liste->val->idEchangeur,liste->val->idVehicule);
    //printf("\n#DEBUG : Signal | Serveur -> Echangeur n°%d",liste->val->idEchangeur);
    pthread_cond_signal(&BarriereEchangeur[liste->val->idEchangeur-1]);

  }
  pthread_mutex_unlock(&mutex);


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
