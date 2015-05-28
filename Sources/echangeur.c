/**
* \file main.c
* \brief Programme de simulation des échangeurs
* \author Florian Lacour & Michaël Ayeng
* \version 0.2
* \date 13 Mai 2015
*/

#include "echangeur.h"

void creationEchangeur(echangeur* c,int Id,int D,int G,int H,int B){
    c->numId=Id;
    c->haut=H;
    c->bas=B;
    c->droite=D;
    c->gauche=G;
    c->occuper=false;
}
void afficherEchangeur(echangeur* c){
  printf("\nNumero Echangeur: %d\n\tConnexion haute: %d\n\tConnexion basse: %d\n\tConnexion gauche: %d\n\tConnexion droite: %d\n\t il est dans l'états :%d",c->numId,c->haut,c->bas,c->gauche,c->droite,c->occuper);
}



void creationVehicule(vehicule* v,int IdEchangeur,int depart,int arrivee){
  v->IdEchangeur=IdEchangeur;
  v->depart=depart;
  v->arrivee=arrivee;
}
void afficherVehicule(vehicule* v){
  printf("\n voiture appartenant a l'echangeur %d, partant de %d, et allant a %d",v->IdEchangeur,v->depart,v->arrivee);
}




/**
* \fn traitantThread(void* param)
* \brief Fonction gerant un thread "Echangeur"
*
* \param void* seras convertie en echangeur
*
*/
void* traitantThreadEchangeur(void* param){
    echangeur* ech= (echangeur*) param;
    // Utilisation Mutex ????
    afficherEchangeur(ech);
    fflush(stdout);
    pthread_exit(NULL);
}
