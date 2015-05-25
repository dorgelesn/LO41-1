
#include "echangeur.h"
void creationEchangeur(echangeur* c,int Id,int D,int G,int H,int B){
    c->numId=Id;
    c->haut=H;
    c->bas=B;
    c->droite=D;
    c->gauche=G;
}


void afficherEchangeur(echangeur* c){
  printf("\n Numero Echangeur : %d, connecter en haut %d,connecter en bas %d, a gauche %d, a droite %d",c->numId,c->haut,c->bas,c->gauche,c->droite);


}
