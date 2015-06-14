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
* Attend le signal d'un véhicule prêt
* Recherche la disponibilité de l'échangeur correspondant
* Donne l'autorisation de traitement à l'échangeur
* \param param Paramètre du thread contenant la structure du serveur
*/
void* traitantThreadServeur(void* param){
  serveur* serv = (serveur*) param;
  int i ;
  llist liste;

  while(true){

    // Attente du signal d'un véhicule prêt
    sem_wait(sem);

// usleep(50);
    liste = NULL;

    // Recherche du premier véhicule prêt dans la liste avec prise en compte de sa priorité
    liste = element_i(serv->liste,rechercherPlaceByReadyPriority(serv->liste,true));
    //usleep(1000);

    if(liste != NULL){
      if(liste->val->fin==1){
    //    printf("\n\t\t\t\t\t\t\t\t suppression");
        serv->liste = supprimerElementById(serv->liste,liste->val->idVehicule);

      }
      // Verification de la disponibilité de l'échangeur
      else if(ech[liste->val->idEchangeur-1].dispo == 0){  // Si l'échangeur est indisponible

        // Augmentation de la priorité du véhicule
        liste->val->priorite += 1;
        sem_post(sem);

  //    usleep(100000);

      } else {  // Si l'échangeur est disponible

        printf("\n\n[Serveur] : Requête du véhicule n°%d acceptée [#]" ,liste->val->idVehicule);

        // Autorisation de circulation
        liste->val->ready = 0;  // La voiture ne demande plus à être prise en charge
        ech[liste->val->idEchangeur-1].dispo = 0; // L'échangeur n'est plus disponible
        ech[liste->val->idEchangeur-1].idVehicule = liste->val->idVehicule; // Assigne le véhicule à l'échangeur
        liste->val->priorite = 1; // Le vehicule reprend une priorite "normale"
        reinitialiserPrioEchan(serv->liste,liste->val->idEchangeur-1);  // Réinitialise la priorité de tout les véhicules de l'échangeur

        schemaSimulation();

        // Envoi l'autorisation de traitement à l'échangeur
        sem_post(semEchangeurLever[liste->val->idEchangeur-1]);

      //  usleep(400);
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

  // Paramètrage du véhicule
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

void schemaSimulation(){
  printf("\n\n----------------------------");
  printf("\n   Voitures prises en charge\n");
  printf("\n       ||         ||");
  printf("\n== |  (%d)  | == | (%d) | ==",ech[0].idVehicule,ech[3].idVehicule);
  printf("\n       ||         ||");
  printf("\n== |  (%d)  | == | (%d) | ==",ech[1].idVehicule,ech[2].idVehicule);
  printf("\n       ||         ||");
  printf("\n\n----------------------------");
}
