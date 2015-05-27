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
}


void afficherEchangeur(echangeur* c){
  printf("\nNumero Echangeur: %d\n\tConnexion haute: %d\n\tConnexion basse: %d\n\tConnexion gauche: %d\n\tConnexion droite: %d",c->numId,c->haut,c->bas,c->gauche,c->droite);
}
