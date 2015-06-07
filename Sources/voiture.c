#include "voiture.h"

void* traitantThreadGenerationVoiture(void* param){

  vehicule* voiture;
  int depart, arrivee, idVehicule, idEchangeur, i, nbVehicules, rc;
  nbVehicules = (int) param;
  srand(time(NULL));

  // Section critique
  pthread_mutex_lock(&mutex);
  pthread_cond_wait (&partir,&mutex); // Attente du signal de départ du main
  pthread_mutex_unlock(&mutex);
  // Fin de section critique

  for (i = 0; i < nbVehicules; i++){

    // Détermination des propriétés du véhicule
    idVehicule = i+1;
    idEchangeur = rand()%4 + 1; // Assigne la voiture à un échangeur de manière aléatoire
    depart = idEchangeur;   // Assigne l'échangeur de départ du véhicule
    do{
      arrivee = rand()%4 + 1;   // Tente d'assigner un échangeur d'arrivée
    } while(arrivee == depart);

    // Section critique
    pthread_mutex_lock(&mutex);
    voiture = ajouterVehicule(&serv,idVehicule,idEchangeur,depart,arrivee); // Ajoute le véhicule dans la liste du serveur
    pthread_cond_signal (&attendre); // Envoi un signal de réveil au serveur
    pthread_mutex_unlock(&mutex);
    // Fin de section critique

    // Creation du thread du vehicule
    rc = pthread_create(&threadsVehicule[i],NULL,traitantThreadVehicule,(void *) voiture);
    if(rc)
    printf("\n(!)erreur creation thread vehicule");

    sleep(1);
  }

  printf("\nfin du thread generation de voiture");

}

void* traitantThreadVehicule(void* param){

  vehicule* voiture = (vehicule*) param;
  // Section critique
  pthread_mutex_lock(&mutex);
  pthread_cond_wait(&departVehicule,&mutex);
  affichageVehicule();
  printf("[Voiture n°%d] : Depart depuis l'echangeur n°%d ",voiture->idVehicule,voiture->idEchangeur);
  pthread_mutex_unlock(&mutex);
  // Fin de section critique
}

/**
* \fn void creationVehicule(vehicule* v,int idEchangeur,int depart,int arrivee)
* \brief Fonction permettant le paramètrage d'un véhicule
*
* \param v Structure du véhicule
* \param idEchangeur Numéro d'identification de l'échangeur
* \param depart Point de départ du véhicule
* \param arrivee Point d'arrivée du véhicule
*
*/
void creationVehicule(vehicule* v,int idVehicule, int idEchangeur,int depart,int arrivee){
  v->idVehicule = idVehicule;
  v->idEchangeur = idEchangeur;
  v->depart = depart;
  v->arrivee = arrivee;
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
  printf("\n\tIdentifiant: %d\n\tEchangeur propriétaire: %d\n\tPoint de départ: %d\n\tPoint d'arrivée: %d",v->idVehicule,v->idEchangeur,v->depart,v->arrivee);
}

void affichageVehicule(){
  int i;
  printf("\n");
  for (i = 0; i < 4; i++){
    printf("\t");
  }
}
