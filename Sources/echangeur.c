/**
* \file echangeur.c
* \brief Programme de simulation des échangeurs
* \author Florian Lacour & Michaël Ayeng
* \version 0.2
* \date 13 Mai 2015
*/

#include "echangeur.h"

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
    c->dispo = false;
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
  printf("\n\tConnexion haute: %d\n\tConnexion basse: %d\n\tConnexion gauche: %d\n\tConnexion droite: %d\n\tBlocage: %d",c->haut,c->bas,c->gauche,c->droite,c->dispo);
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

/**
* \fn void* traitantThread(void* param)
* \brief Fonction gerant un thread "Echangeur"
*
* \param param Pointeur contenant un echangeur
*
*/
void* traitantThreadEchangeur(void* param){
  int ech= (int) param;
    // Utilisation Mutex ????
    while(true){
    pthread_mutex_lock(&mutex);
    printf("\n Numero d'echangeur %d en attente",ech);
    pthread_cond_wait (&dispoEchangeur[ech],&mutex);
    printf("\n \t l'changeur %d ouvre la barriére",ech);
    pthread_mutex_unlock(&mutex);
    }
    fflush(stdout);
    pthread_exit(NULL);
}
