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
  ech[idEchangeur-1].dispo = 1;

  while(true){

    // Attends l'autorisation du serveur pour ouvrir la barrière
    sem_wait(semEchangeurLever[idEchangeur-1]);

    // Ouvre la barrière
    printf("\n\n\t[Echangeur n°%d] : Ouverture de la barriere [/] pour la voiture n°%d" ,idEchangeur,echan->idVehicule);
    // Envoi l'autorisation de circulation au véhicule
    // Simultation temps de lever
    usleep(3000);
    sem_post(semDepartVehicule[echan->idVehicule-1]);

    // Attends le signal du véhicule pour fermer la barrière
    sem_wait(semEchangeurDescendre[idEchangeur-1]);

    // Ferme la barrière
    printf("\n\n\t[Echangeur n°%d] : Fermeture de la barriere [--]",idEchangeur);
    // Simulation temps de descente
    usleep(3000);
    ech[idEchangeur-1].dispo = true;
  }
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
