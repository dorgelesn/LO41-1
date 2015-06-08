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

  while(true){
    // Section critique
    pthread_mutex_lock(&mutex);
    pthread_cond_wait (&attendre,&mutex);  // Attente de la generation d'un nouveau vehicule
    pthread_cond_wait (&voitureReady,&mutex);
    printf("\n\n[Serveur] :vehicule (n°%d), depart %d ",serv->liste->val->idVehicule,serv->liste->val->depart);
    if(ech[serv->liste->val->idEchangeur].dispo==false){

      pthread_cond_signal(&BarriereEchangeur[serv->liste->val->depart-1]);
    }

    pthread_cond_signal(&departVehicule[serv->liste->val->idVehicule]);
    pthread_mutex_unlock(&mutex);
   // Ordonne au nouveau véhicule de démarrer
   //simulation temps de lever
   usleep(500);
   /*
   pthread_mutex_lock(&mutex);
   pthread_cond_signal(&departVehicule[serv->liste->val->idVehicule]);
   pthread_mutex_unlock(&mutex);*/
    // Fin de section critique
  }

  sleep(2);

/*
  // SECTION A PROBLEME
  while(true){
    // Section critique
    pthread_mutex_lock(&mutex);
    element* debutListe = serv->liste;  // Sauvegarde du début de la liste
    // Parcours de la liste
    while (!estVide(serv->liste)){
  //    afficherVehicule(serv->liste->val);
      // Si l'echangeur où se trouve le véhicule est disponible, ordonne d'ouvrir la barrière
      /*if(ech[serv->liste->val->idEchangeur].dispo == true){
        pthread_cond_signal(&BarriereEchangeur[serv->liste->val->idEchangeur-1]);
      }
      serv->liste = serv->liste->nxt; // On passe à l'élément suivant
    }
    pthread_mutex_unlock(&mutex);
    // Fin de section critique
  }*/
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
