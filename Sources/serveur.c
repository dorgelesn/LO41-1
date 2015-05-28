
#include "linkedList.h"
#include "structures.h"
#include "serveur.h"
void* traitantThreadServeur(void* param){
  serveur* serv= (serveur*) param;
  afficherServeur(serv);
  ajouterVoiture(serv,1,0,24);
  printf("\n\n%d ",serv->liste->val->arrivee);
  sleep(3);
}
void ajouterVoiture(serveur* serv,int ech,int dep,int arr){
  vehicule v;
  creationVehicule(&v,ech,dep,arr);
  (*serv).liste =  ajouterEnTeteListe((*serv).liste,v);
}
void afficherServeur(serveur* s){
  printf("\n le Serveur \n\t Nb de voiture : %d \n\t NbEchangeur %d\n",s->NbVoiture,s->NbEchangeur);
}
