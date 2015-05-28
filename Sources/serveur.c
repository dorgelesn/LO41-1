
#include "linkedList.h"
#include "structures.h"
#include "serveur.h"
void* traitantThreadServeur(void* param){
  serveur* serv= (serveur*) param;
  afficherServeur(serv);
  vehicule v;
  creationVehicule(&v,1,0,24);
  (*serv).liste =  ajouterEnTeteListe((*serv).liste,v);
  printf("\n\n%d ",serv->liste->val->arrivee);
  sleep(3);
}

void afficherServeur(serveur* s){
  printf("\n le Serveur \n\t Nb de voiture : %d \n\t NbEchangeur %d\n",s->NbVoiture,s->NbEchangeur);
}
