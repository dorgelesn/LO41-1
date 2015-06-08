#include "voiture.h"

void* traitantThreadGenerationVoiture(void* param){

  vehicule* voiture;
  int depart, arrivee, idVehicule, idEchangeur, i, nbVehicules, rc;
  nbVehicules = (int)(intptr_t) param;
  srand(time(NULL));

  // Attente du signal de départ du main
  pthread_mutex_lock(&mutex);
  pthread_cond_wait (&partir,&mutex);


  for (i = 0; i < nbVehicules; i++){

    // Détermination des propriétés du véhicule
    idVehicule = i+1;
    idEchangeur = rand()%4 + 1; // Assigne la voiture à un échangeur de manière aléatoire
    depart = idEchangeur;   // Assigne l'échangeur de départ du véhicule
    do{
      arrivee = rand()%4 + 1;   // Tente d'assigner un échangeur d'arrivée
    } while(arrivee == depart);

    // Ajout du véhicule dans la liste du serveur
    voiture = ajouterVehicule(&serv,idVehicule,idEchangeur,depart,arrivee);

    // Creation du thread du vehicule
    rc = pthread_create(&threadsVehicule[i],NULL,traitantThreadVehicule,(void *)(intptr_t) voiture);
    if(rc)
    printf("\n(!)erreur creation thread vehicule");



  }
  pthread_mutex_unlock(&mutex);

  printf("\nFin du thread generation de voiture");

}

void* traitantThreadVehicule(void* param){

  vehicule* voiture = (vehicule*) param;
  int idEchangeur;
  int i = 0;
  bool arrived = false;

  pthread_mutex_lock(&mutex);
  while (arrived == false){
    idEchangeur = voiture->idEchangeur;

    // Averti le serveur de sa disponibilitée et attend l'autorisation de départ
    voiture->ready = true;
    //afficherVehicule(voiture);
    printf("\n\n[Voiture n°%d] Prêt a l'echangeur n°%d [!]",voiture->idVehicule,voiture->idEchangeur);
    //printf("\n#DEBUG : Signal | Vehicule n°%d -> Serveur",voiture->idVehicule);
    pthread_cond_signal (&voitureReady);
    pthread_cond_wait(&departVehicule[voiture->idVehicule-1],&mutex);


    // Traversée de l'echangeur
    voiture->ready = false;
    printf("\n\n[Voiture n°%d] : Traversée de l'echangeur n°%d [>]",voiture->idVehicule,voiture->idEchangeur);
    //printf("\n#DEBUG : Signal | Vehicule n°%d -> Echangeur n°%d",voiture->idVehicule,idEchangeur);
    pthread_cond_signal(&BarriereEchangeur[idEchangeur-1]);

    // Si le véhicule est arrivé à destination, il se supprime de la liste
    if (voiture->idEchangeur == voiture->arrivee) {
      arrived = true;
      printf("\n\n[Voiture n°%d] : Fin de parcours [X]",voiture->idVehicule);
      serv.liste = supprimerElementById(serv.liste,voiture->idVehicule);
      printf("\n\n[Voiture n°%d] : Suppression de la liste [*]",voiture->idVehicule);
    }
    // Sinon, il détermine la prochaine étape du trajet
    else {
      voiture->dejaParcourus[i] = idEchangeur;

      if (ech[idEchangeur-1].haut != 0 && !dejaParcourus(voiture,ech[idEchangeur-1].haut)){
        voiture->idEchangeur = ech[idEchangeur-1].haut;
      } else if (ech[idEchangeur-1].bas != 0 && !dejaParcourus(voiture,ech[idEchangeur-1].bas)) {
        voiture->idEchangeur = ech[idEchangeur-1].bas;
      } else if (ech[idEchangeur-1].gauche != 0 && !dejaParcourus(voiture,ech[idEchangeur-1].gauche)) {
        voiture->idEchangeur = ech[idEchangeur-1].gauche;
      } else if (ech[idEchangeur-1].droite != 0 && !dejaParcourus(voiture,ech[idEchangeur-1].droite)) {
        voiture->idEchangeur = ech[idEchangeur-1].droite;
      }
      i++;
      printf("\n\n[Voiture n°%d] : Prochain échangeur : n°%d [-->]",voiture->idVehicule,voiture->idEchangeur);
    }
  }
  pthread_mutex_unlock(&mutex);

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
  v->ready = false;
}

bool dejaParcourus(vehicule* v,int ech){
  int j=0;
  for(j=0;j<maxiEchangeur;j++){
    if(v->dejaParcourus[j]==ech){
      return true;
    }
  }
  return false;
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
