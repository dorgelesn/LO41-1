/**
* \file echangeur.c
* \brief Programme de simulation des échangeurs
* \author Florian Lacour & Michaël Ayeng
* \version 0.2
* \date 13 Mai 2015
*/

#include "echangeur.h"

/**
* \fn void* traitantThread(void* param)
* \brief Fonction gerant un thread "Echangeur"
*
* \param param Pointeur contenant un echangeur
*
*/
void* traitantThreadEchangeur(void* param){

  echangeur* echan = (echangeur*) param;
  int idEchangeur, i;
  idEchangeur = echan->numId;

  pthread_mutex_lock(&mutex);
  while(true){

    // Attends l'autorisation du serveur
    ech[idEchangeur-1].dispo = true;
    pthread_cond_wait(&BarriereEchangeur[idEchangeur-1],&mutex);

    // Ouvre la barière et envoie l'autorisation au véhicule
    //afficherEchangeur(echan);
    printf("\n\n[Echangeur n°%d] : Ouverture de la barriere [/]",idEchangeur);
    //printf("\n#DEBUG : Signal | Echangeur n°%d -> Vehicule n°%d",idEchangeur,echan->idVehicule);
    pthread_cond_signal(&departVehicule[echan->idVehicule-1]);

    // Attends le signal du véhicule pour fermer la barrière
    pthread_cond_wait (&BarriereEchangeur[idEchangeur-1],&mutex);
    ech[idEchangeur-1].dispo = false;
    printf("\n\n[Echangeur n°%d] : Fermeture de la barriere [--]",idEchangeur);

  }
  pthread_mutex_unlock(&mutex);
  fflush(stdout);
  pthread_exit(NULL);
}


/**
* \fn void creationEchangeur(echangeur* c,int Id,int D,int G,int H,int B)
* \brief Fonction permettant le paramètrage d'un echangeur
*
* \param c Structure de l'échangeur
* \param Id Numéro d'identification de l'échangeur
* \param D Numéro de l'échangeur se trouvant à droite
* \param G Numéro de l'échangeur se trouvant à gauche
* \param H Numéro de l'échangeur se trouvant en haut
* \param B Numéro de l'échangeur se trouvant en bas
*
*/
void creationEchangeur(echangeur* c,int Id,int D,int G,int H,int B){
  c->numId = Id;
  c->haut = H;
  c->bas = B;
  c->droite = D;
  c->gauche = G;
  c->dispo = true;
  c->idVehicule = 0;
}

/**
* \fn void afficherEchangeur(echangeur* c)
* \brief Fonction permettant l'affichage d'informations concernant un échangeur
*
* \param c Structure de l'échangeur
*
*/
void afficherEchangeur(echangeur* c){
  printf("\n-----------------------");
  printf("\nInformations echangeur n°%d",c->numId);
  printf("\n-----------------------");
  printf("\n\tConnexion haute: %d\n\tConnexion basse: %d\n\tConnexion gauche: %d\n\tConnexion droite: %d\n\tDisponible: %d\n\tVéhicule attribué: %d",c->haut,c->bas,c->gauche,c->droite,c->dispo,c->idVehicule);
}
