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
  llist listeTemp;

  while(true){

    listeTemp = serv->liste; // On mémorise le premier élément

    // Tant que la liste du serveur n'est pas vide
      while(listeTemp->val != NULL) {
        // Si l'échangeur de la voiture est libre
         if (ech[listeTemp->val->idEchangeur-1].dispo == true){
          // Autorise le départ du véhicule
          pthread_mutex_lock(&mutex);
          affichageServeur();
          printf("[Serveur] : (Vehicule n°%d) [~]Autorisation depart accorde",listeTemp->val->idVehicule);
          pthread_cond_signal(&BarriereEchangeur[listeTemp->val->idEchangeur-1]);  // Ordonne l'ouverture de la barrière de l'échangeur
          pthread_mutex_unlock(&mutex);

          sleep(1);  // Simulation temps ouverture barrière

          pthread_mutex_lock(&mutex);
          pthread_cond_signal(&departVehicule[listeTemp->val->idVehicule]); // Ordonne le départ du véhicule
          pthread_mutex_unlock(&mutex);

          sleep(2); // Simulation temps déplacement véhicule

          pthread_mutex_lock(&mutex);
          pthread_cond_signal(&BarriereEchangeur[listeTemp->val->idEchangeur-1]); // Ordonne la fermeture de la barrière de l'échangeur
          pthread_mutex_unlock(&mutex);

          sleep(1);  // Simulation temps fermeture barrière
        }
        // On passe à la voiture suivante
        listeTemp = listeTemp->nxt;
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

void affichageServeur(){
  printf("\n\n");
  }
