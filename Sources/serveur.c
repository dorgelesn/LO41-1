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
void* traitantThreadServeurAjout(void* param){

  serveur* serv = (serveur*) param;
  int i = 0;

  for (i = 0; i < 10; i++){
    // Section critique
    pthread_mutex_lock(&mutex);
    pthread_cond_wait (&attendre,&mutex);  // Attente du signal du thread generateur de voiture
    printf("\n\n~Serveur : Reception d'un nouveau vehicule à gerer");
    afficherVehicule(serv->liste->val); // Affiche les informations relatives au véhicule
    if(ech[serv->liste->val->depart].dispo==false){
      pthread_cond_signal (&dispoEchangeur[serv->liste->val->depart]);
    }
    pthread_mutex_unlock(&mutex);
    // Fin de section critique
  }

  printf("\nfin du thread serveur");
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
vehicule *ajouterVehicule(serveur* serv,int ech,int dep,int arr){
  // Initialisation du véhicule
  vehicule* v=malloc(sizeof(vehicule));
  // Configuration du véhicule
  // le resultat est stocker dans V
  creationVehicule(v,ech,dep,arr);
  // Ajout du véhicule en tête de la liste de traitement du serveur
  (*serv).liste = ajouterEnTeteListe((*serv).liste,v);
  return v;
}

/**
* \fn void creationVehicule(vehicule* v,int IdEchangeur,int depart,int arrivee)
* \brief Fonction permettant le paramètrage d'un véhicule
*
* \param v Structure du véhicule
* \param IdEchangeur Numéro d'identification de l'échangeur
* \param depart Point de départ du véhicule
* \param arrivee Point d'arrivée du véhicule
*
*/
void creationVehicule(vehicule* v,int IdEchangeur,int depart,int arrivee){
  v->IdEchangeur = IdEchangeur;
  v->depart = depart;
  v->arrivee = arrivee;
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
