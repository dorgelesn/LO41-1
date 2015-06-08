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

  pthread_mutex_lock(&mutex);
  while(true){
    liste = NULL;
    // Attente du signal d'un véhicule prêt
    pthread_cond_wait (&voitureReady,&mutex);

    // Recherche du premier véhicule prêt dans la liste
    liste = element_i(serv->liste,rechercherPlaceByReady(serv->liste,true));

    // Verification de la disponibilité de l'échangeur
    if(ech[liste->val->idEchangeur-1].dispo == true){
      // Envoi l'autorisation à l'échangeur
      ech[liste->val->idEchangeur-1].idVehicule = liste->val->idVehicule; // Assigne le véhicule à l'échangeur
      printf("\n\n[Serveur] : Autorisation accordée à l'échangeur n°%d pour la traversée du véhicule n°%d [@]",liste->val->idEchangeur,liste->val->idVehicule);
      //printf("\n#DEBUG : Signal | Serveur -> Echangeur n°%d",liste->val->idEchangeur);
      pthread_cond_signal(&BarriereEchangeur[liste->val->idEchangeur-1]);
    }
<<<<<<< 5adea4018b5855dbbf8ee2447328c435f45c9f68
    pthread_mutex_unlock(&mutex);
    usleep(50);

   // Ordonne au nouveau véhicule de démarrer
   //simulation temps de lever
   usleep(500);
   /*
   pthread_mutex_lock(&mutex);
   pthread_cond_signal(&departVehicule[serv->liste->val->idVehicule]);
   pthread_mutex_unlock(&mutex);*/
    // Fin de section critique
=======
    /* PROBLEME
        Si l'échangeur n'est pas disponible, un décalage entre les réveils du wait
        et le traitement des véhicules ready se forme
        ex: Vehicule 1 est ready mais son echangeur n'est pas disponible
        la boucle du thread reprend, vehicule 2 est ready et active le wait.
        le thread traite le premier vehicule ready de la liste, donc le vehicule 1
        puis reboucle et attend dans son wait. Cependant, aucun autre véhicule n'arrive
        le vehicule 2 n'est donc pas traité */
>>>>>>> 6410db18aa778eeab874ea4add10c902d203184b
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
