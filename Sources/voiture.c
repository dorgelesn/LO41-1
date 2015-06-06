#include "voiture.h"

void* traitantThreadGenerationVoiture(void* param){


    pthread_mutex_lock(&mutex);
    pthread_cond_wait (&partir,&mutex);
    pthread_mutex_unlock(&mutex);
  vehicule* voiture;
  int depart, arrivee, idEchangeur, i;
  srand(time(NULL));


  for (i = 0; i < 2; i++){

    // Détermination des propriétés du véhicule
    idEchangeur = rand()%4 + 1; // Assigne la voiture à un échangeur de manière aléatoire
    depart = idEchangeur;   // Assigne l'échangeur de départ du véhicule
    do{
      arrivee = rand()%4 + 1;   // Tente d'assigner un échangeur d'arrivée
    } while(arrivee == depart);
    printf("\n~ voiture depart a %d ",depart);
    // Section critique
    pthread_mutex_lock(&mutex);
    voiture = ajouterVehicule(&serv,idEchangeur,depart,arrivee); // Ajoute le véhicule dans la liste du serveur
    pthread_cond_signal (&attendre); // Envoi un signal de réveil au serveur
    pthread_mutex_unlock(&mutex);
    // Fin de section critique

    sleep(1);
    }

    printf("\nfin du thread generation de voiture");

}

/**
* \fn void afficherVehicule(vehicule* v)
* \brief Fonction permettant l'affichage d'informations concernant un véhicule
*
* \param c Structure du véhicule
*
*/
void afficherVehicule(vehicule* v){
  printf("\n-----------------------");
  printf("\nInformations véhicule");
  printf("\n-----------------------");
  printf("\n\tEchangeur propriétaire: %d\n\tPoint de départ: %d\n\tPoint d'arrivée: %d",v->IdEchangeur,v->depart,v->arrivee);
}
